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

(* 1a. belongsTo_ext: 'a -> 'a list -> bool *)
let rec belongsTo_ext y xs =
  match xs with
  | [] -> false
  | (x::xs) ->
    if y = x then true else belongsTo_ext y xs

(* 1b. belongsTo_char: ('a -> 'b) -> 'a -> 'b *)
let belongsTo_char a x = (a x)

(* 1c. union_ext: 'a list -> 'a list -> 'a list *)
let rec union_ext xs ys =
  let f x r = if not (belongsTo_ext x ys) then x::r else r
  in List.fold_right f xs ys

(* 1d. union_char: ('a -> bool) -> ('a -> bool) -> 'a -> bool *)
let union_char a b =
  fun n -> (a n) || (b n)

(* 1e. intersection_ext: 'a list -> 'a list -> 'a list *)
let rec intersection_ext xs ys =
  let f x r = if belongsTo_ext x ys then x::r else r
  in List.fold_right f xs []

(* 1f. intersection_char: ('a -> bool) -> ('a -> bool) -> 'a -> bool *)
let intersection_char a b =
  fun n -> (a n) && (b n)

(* 2. remAdjDups: 'a list -> 'a list *)
let rec remAdjDups xs =
  match xs with
  | x::y::xs -> (if x = y then [] else [x]) @ (remAdjDups (y::xs))
  | x -> x

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

(* 01. mapC:  (int -> int) -> calcExp -> calcExp *)
let rec mapC f e =
  match e with
  | Const(x) -> Const(f x)
  | Add(x, y) -> Add(mapC f x, mapC f y)
  | Div(x, y) -> Div(mapC f x, mapC f y)
  | Mult(x, y) -> Mult(mapC f x, mapC f y)
  | Sub(x, y) -> Sub(mapC f x, mapC f y)

(* 02. foldC:  *)
(*
 * Notes from class:

  let rec fold_tree a f = function
    | Empty -> a
    | Node(i, lt, rt) -> f i (fold_tree a f lt) (fold_tree a f rt)

 * Printing the pre-order traversal with this fold
   fold_tree [] (fun i yz zs -> i::(ys@zs))

  * Map with fold
  let map2 f t = fold_tree Empty (fun i xs ys -> )
*)
(**********************************************************************
 * let rec foldC f e =                                                *
 *   match e with                                                     *
 *   | Add(x, y) -> f (Add(foldC f x, foldC f y)) e                   *
 *   | Div(x, y) -> f (Div(foldC f x, foldC f y)) e                   *
 *   | Mult(x, y) -> f (Mult(foldC f x, foldC f y)) e                 *
 *   | Sub(x, y) -> f (Sub(foldC f x, foldC f y)) e                   *
 *   | Const(x) ->  f (Const(x)) e                                    *
 *                                                                    *
 * (\* 03. numAdd: *\)                                                *
 * let numAdd e =                                                     *
 *   let f x r = match x with Add(x, y) -> (+) r 1 | _ -> r           *
 *   in foldC f e 0                                                   *
 *                                                                    *
 * (\* 04. replaceAddWithMult: *\)                                    *
 * let rec replaceAddWithMult e =                                     *
 *   match e with                                                     *
 *   | Const(x) -> Const(x)                                           *
 *   | Add(x, y) -> Mult(replaceAddWithMult x, replaceAddWithMult y)  *
 *   | Div(x, y) -> Div(replaceAddWithMult x, replaceAddWithMult y)   *
 *   | Mult(x, y) -> Mult(replaceAddWithMult x, replaceAddWithMult y) *
 *   | Sub(x, y) -> Sub(replaceAddWithMult x, replaceAddWithMult y)   *
 **********************************************************************)

(* 05. evalC: calcExp -> int *)
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
