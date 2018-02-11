(* 3.1 *)
type dTree = Leaf of int | Node of char*dTree*dTree

(* 3.2 *)
let tLeft = Node('w', Node('x', Leaf 2, Leaf 5), Leaf 8)
let tRight = Node('w', Node('x', Leaf 2, Leaf 5), Node('y', Leaf 7, Leaf 5))

(* 3.3a *)
let rec dTree_height (t: dTree): int = 0

(* 3.3b *)
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

(* 3.3e *)
let rec dTree_map (f: char -> char) (g: int -> int) (t: dTree): dTree =
  match t with
  | Leaf n -> Leaf (g n)
  | Node(c, x, y) -> Node((f c), (dTree_map f g x), (dTree_map f g y))
