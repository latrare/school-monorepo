(* Trevor Miranda *)
(* CS 496 *)
(* I pledge, so on, and so forth. *)

(* 1 *)
type dTree = Leaf of int | Node of char*dTree*dTree


(* 2 *)
let tLeft = Node('w', Node('x', Leaf 2, Leaf 5), Leaf 8)
let tRight = Node('w', Node('x', Leaf 2, Leaf 5), Node('y', Leaf 7, Leaf 5))


(* 3a *)
let rec dTree_height (t: dTree): int =
  match t with
  | Leaf n -> 0
  | Node(c, x, y) ->
    let x_height = dTree_height x + 1 in
    let y_height = dTree_height y + 1 in
    if x_height > y_height then
      x_height
    else
      y_height


(* 3b *)
let rec dTree_size (t: dTree): int =
  match t with
  | Leaf n -> 1
  | Node(c, x, y) -> 1 + (dTree_size x) + (dTree_size y)

open List
(* 3.3c *)
let rec dTree_paths (t: dTree) =
  match t with
  | Leaf n -> []
  | Node(c, x, y) -> (0::(dTree_paths x))::[[]]


(* 3.3d *)
let dTree_is_perfect (t: dTree): bool = false

(* 3e *)
let rec dTree_map (f: char -> char) (g: int -> int) (t: dTree): dTree =
  match t with
  | Leaf n -> Leaf (g n)
  | Node(c, x, y) -> Node((f c), (dTree_map f g x), (dTree_map f g y))


(* 4 *)
let rec list_to_tree (xs: char list): dTree =
  match xs with
  | x::y::xs ->
    Node(x,
      Node(y, list_to_tree xs, list_to_tree xs),
      Node(y, list_to_tree xs, list_to_tree xs))
  | x::xs -> Node(x, list_to_tree xs, list_to_tree xs)
  | x -> Leaf 0
