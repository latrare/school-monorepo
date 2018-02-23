
(* succl :: int list -> int list *)
let rec succl xs =
  let f x = x+1
  in match xs with
  | [] -> []
  | y::ys -> f y :: succl ys

(* upperl :: char list -> char list *)
let rec upperl xs =
  let f x = Char.uppercase_ascii x
  in match xs with
  | [] -> []
  | y::ys -> f y :: upperl ys

(* lengthl :: 'a list list -> int list *)
let rec lengthl xs =
  let f x = List.length x
  in match xs with
  | [] -> []
  | y::ys -> f y :: lengthl ys

(* map :: ('a ->'b ) -> 'a list -> 'b list *)
               
let rec map f = function
  | [] -> []
  | y::ys ->  f y :: map f ys

let succl' xs = map (fun x -> x+1) xs
let upperl' xs = map Char.uppercase_ascii xs
let lengthl' xs = map List.length xs

(* gtzl :: int list -> int list *)
let rec gtzl xs =
  let p y = y>0
  in match xs with
  | [] -> []
  | x::xs ->
    if p x
    then x:: gtzl xs
    else gtzl xs

(* emptyl :: 'a list list -> 'a list list *)
let rec emptyl xs =
  let p y = y!=[]
  in match xs with
  | [] -> []
  | x::xs ->
    if p x
    then x:: emptyl xs
    else emptyl xs

(* filter ::  ( 'a -> bool) -> 'a list -> 'a list  *)
let rec filter p = function
  | [] -> []
  | x::xs ->
    if p x
    then x:: filter p xs
    else filter p xs

let gtzl' xs = filter (fun x -> x>0) xs
let emptyl' xs = filter (fun x-> x!=[]) xs

(* sum :: int list -> int *)
let rec sum xs =
  let a = 0
  in let f x r = x+r
  in match xs with
  | [] -> a
  | x::xs -> f x (sum xs)

(* prod :: int list -> int *)
let rec prod xs =
  let a = 1
  in let f x r = x * r
  in match xs with
  | [] -> a
  | x::xs -> f x (prod xs)

(* andl :: bool list -> bool *)
let rec andl xs =
  let a = true
  in let f x r = x && r
  in match xs with
  | [] -> a
  | x::xs -> f x (andl xs)


(* foldl ::  'c -> ( 'c -> 'a -> 'c ) -> 'a list -> 'c  *)
let rec foldl a f = function
  | [] -> a
  | x::xs -> foldl (f a x) f xs
(* foldr ::  'c ->  ('a -> 'c -> 'c ) -> 'a list ->  'c  *)
let rec foldr a f = function
  | [] -> a
  | x::xs -> f x (foldr a f xs)

let sum' xs = foldr 0 (fun x r -> x+r) xs
let prod' xs = foldr 1 (fun x r -> x*r) xs
let andl' xs = foldr true (fun x r -> x && r) xs

let map' f xs = foldr [] (fun x ys -> f x::ys) xs

let rec myiter f = function
  | [] -> ()
  | x::xs -> f x; myiter f xs

let rec myiter' f xs = foldr () (fun x _ -> f x) (List.rev xs)

(* Algebraic Data Types *)

type color = Red | Green | Blue

let next_color = function
  | Red -> Green
  | Green -> Blue
  | Blue -> Red

type tree_int = Empty | Node of int*tree_int*tree_int

let rec fold_tree a f = function
  | Empty -> a
  | Node(i,lt,rt) -> f i (fold_tree a f lt) (fold_tree a f rt)
    
let t1 = Node(7,Node(3,Empty,Empty),Node(12,Node(8,Empty,Empty),Empty))

let map2 f t = fold_tree Empty (fun i lt rt -> Node(f i,lt,rt)) t
    
let is_leaf = function
  | Empty -> false
  | Node(i,Empty,Empty) -> true
  | _ -> false

let rec map_tree f = function
  | Empty -> Empty
  | Node(i,lt,rt) -> Node(f i,map_tree f lt, map_tree f rt)

let inc_tree t = map_tree (fun x -> x+1) t

let rec spaces = function
  | 0 -> ""
  | n -> "-"^spaces (n-1)
           
let rec string_of_tree_int n = function
  | Empty -> spaces n ^ "Empty\n"
  | Node(i,lt,rt) ->
    spaces n ^ string_of_int i ^"\n"^
    string_of_tree_int (n+1) lt ^
    string_of_tree_int (n+1) rt

let rec mirror = function
  | Empty -> Empty
  | Node(i,lt,rt) -> Node(i,mirror rt,mirror lt)

