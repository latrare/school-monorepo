open Ast
open Ds

let rec eval (en:env) (e:expr):exp_val =
  match e with
  | Int n           -> NumVal n
  | Var x           -> lookup en x

  | Let(x, e1, e2)  ->
    let v1 = eval en e1  in
    eval (extend_env en x v1) e2

  | IsZero(e1)      ->
    let v1 = eval en e1  in
    let n1 = numVal_to_num v1 in
    BoolVal (n1 = 0)

  | ITE(e1, e2, e3) ->
    let v1 = eval en e1  in
    let b1 = boolVal_to_bool v1 in
    if b1 then eval en e2 else eval en e3

  | Sub(e1, e2)     ->
    let v1 = eval en e1 in
    let v2 = eval en e2  in
    NumVal ((numVal_to_num v1) - (numVal_to_num v2))

  | Add(e1, e2)     ->
    let v1 = eval en e1 in
    let v2 = eval en e2 in
    NumVal ((numVal_to_num v1) + (numVal_to_num v2))

  | Div(e1, e2)     ->
    let v1 = eval en e1 in
    let v2 = eval en e2 in
    NumVal ((numVal_to_num v1) / (numVal_to_num v2))

  | Mul(e1, e2)     ->
    let v1 = eval en e1 in
    let v2 = eval en e2 in
    NumVal ((numVal_to_num v1) * (numVal_to_num v2))

  | Abs(e1)         ->
    let v1 = eval en e1 in
    if (numVal_to_num v1) >= 0 then
      NumVal (numVal_to_num v1)
    else
      NumVal ((numVal_to_num v1) * (-1))

  | Cons(e1, e2)    ->
    let v1 = eval en e1 in
    let v2 = eval en e2 in
    (match v2 with
     | ListVal [] -> ListVal [v1]
     | _ -> ListVal [v1; v2])

  | Hd(e1)          ->
    let v1 = eval en e1 in
    let actual_list = listVal_to_list v1 in
    (match actual_list with
     | x::xs -> (
         match x with
         | NumVal x -> NumVal x
         | BoolVal x -> BoolVal x
         | ListVal x -> ListVal x)
     | [] -> ListVal [])

  | Tl(e1)          ->
    let v1 = eval en e1 in
    let actual_list = listVal_to_list v1 in
    let rec tail_actual_list xs =
      (match xs with
       | x::xs -> tail_actual_list xs
       | x -> x
       | _ -> ListVal []) in
    tail_actual_list actual_list

  | Null(e1)        ->
    let v1 = eval en e1 in
    BoolVal (v1 = (ListVal []))

  | EmptyList       ->
    ListVal []


(***********************************************************************)
(* Everything above this is essentially the same as we saw in lecture. *)
(***********************************************************************)

(* Parse a string into an ast *)
let parse s =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast


(* Interpret an expression *)
let interp (e:string):exp_val =
  e |> parse |> eval (empty_env ())
