(* Assignment 01 *)
(* Trevor Miranda *)

(* //////////////// *)
(* || Exercise 1 || *)
(* \\\\\\\\\\\\\\\\ *)

(* 01. seven: 'a -> int *)
let seven x = 7

(* 02. sign: int -> int *)
let sign x =
  if x > 0 then 1
  else if x < 0 then -1
  else 0

(* 03. absolute: int -> int *)
let absolute x =
  if x < 0 then x * (-1) else x

(* 04. andp, orp, notp, xorp *)
(* --- andp: bool -> bool -> bool *)
let andp x y =
  if x then x = y else false

(* --- orp: bool -> bool -> bool *)
let orp x y =
  if x then x
  else if y then y
  else false

(* --- notp: bool -> bool *)
let notp x =
  if x then false else true

(* --- xorp: bool -> bool -> bool *)
let xorp x y =
  if x then x != y
  else if y then y != x
  else false

(* 05. dividesBy: int -> int -> bool *)
let dividesBy x y = (x mod y) = 0

(* 06. is_singleton: 'a list -> bool *)
let is_singleton l =
  match l with
  | [x] -> true
  | _ -> false

(* 07. swap: 'a * 'b -> 'b * 'a *)
let swap (x, y) = (y, x)

(* 08. app: ('a -> 'b) -> 'a -> 'b *)
let app x y = (x y)

(* 09. twice: ('a -> 'a) -> 'a -> 'a *)
let twice x y = (app x (app x y))

(* 10. compose: ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b *)
let compose x y z = (app x (app y z))


(* //////////////// *)
(* || Exercise 2 || *)
(* \\\\\\\\\\\\\\\\ *)

(* 1a. belongsTo_ext:  *)
let rec belongsTo_ext testx xs =
  match xs with
  | [] -> false
  | (x::xs) ->
    if testx = x then true else belongsTo_ext testx xs

(* 1b. belongsTo_char:  *)

(* 1c. union_ext: 'a list -> 'a list -> 'a list *)
let rec union_ext fxs gxs =
  let f x r = if not (belongsTo_ext x gxs) then x::r else r
  in List.fold_right f fxs gxs

(* 1d. union_char:  *)

(* 1e. intersection_ext: 'a list -> 'a list -> 'a list *)
let rec intersection_ext fxs gxs =
  let f x r = if belongsTo_ext x gxs then x::r else r
  in List.fold_right f fxs []

(* 1f. intersection_char:  *)

(* 2. remAdjDups:  *)

(* 3. sublists:  *)



(* //////////////// *)
(* || Exercise 3 || *)
(* \\\\\\\\\\\\\\\\ *)

(* Pre-defined in assignment description *)
type calcExp =
  | Const of int
  | Add of (calcExp * calcExp)
  | Div of (calcExp * calcExp)
  | Mult of (calcExp * calcExp)
  | Sub of (calcExp * calcExp)

let e1 = Const(2)
let e2 = Add(Sub(Const(2), Const(3)), Const(4))

(* 01. mapC:  *)
let rec mapC f e =
  match e with
  | Const(x) -> Const(f x)
  | Add(x, y) -> Add(mapC f x, mapC f y)
  | Div(x, y) -> Div(mapC f x, mapC f y)
  | Mult(x, y) -> Mult(mapC f x, mapC f y)
  | Sub(x, y) -> Sub(mapC f x, mapC f y)

(* 02. foldC:  *)
let rec foldC f a e =
  match e with
  | Const(x) ->  a
  | Add(x, y) -> foldC f (foldC f a x) y
  | Div(x, y) -> foldC f (foldC f a x) y
  | Mult(x, y) -> foldC f (foldC f a x) y
  | Sub(x, y) -> foldC f (foldC f a x) y

(* 03. numAdd: *)
let numAdd e =
  let f r e = match e with Add _ -> (+) r 1 | _ -> r
  in foldC f 0 e
(* 04. replaceAddWithMult: *)

(* 05. evalC: *)
let rec evalC e =
  match e with
  | Const(x) -> x
  | Add(x, y) -> (evalC x) + (evalC y)
  | Div(x, y) -> (evalC x) / (evalC y)
  | Mult(x, y) -> (evalC x) * (evalC y)
  | Sub(x, y) -> (evalC x) - (evalC y)

(* 06. evalCf: *)


(* //////////////// *)
(* || Exercise 4 || *)
(* \\\\\\\\\\\\\\\\ *)

(* 01. f: int list -> int *)
(* This function counts the number of even numbers in a list. *)
let f xs =
  let g = fun x r -> if x mod 2 = 0 then (+) r 1 else r
  in List.fold_right g xs 0
(* Examples to show it working: *)
(* f [1] will return 0 *)
f [1]
(* f [2] will return 1 *)
f [2]
(* f [1;2;3] will return 1 *)
f [1; 2; 3]
(* f [2;4;6;8] will return 4 *)
f [2; 4; 6; 8]
(* f [1;2;3;4;5;6;7;8] will return 4 *)
f [1; 2; 3; 4; 5; 6; 7; 8]

(* 02. concat: 'a list list -> 'a list *)
let concat xss =
  let g = fun xs h -> xs @ h
  in List.fold_right g xss []
