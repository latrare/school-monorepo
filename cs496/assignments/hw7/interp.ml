(* Trevor Miranda *)

open Ast
open Ds

let from_some = function
  | None -> failwith "from_some: None"
  | Some v -> v

let g_store = Store.empty_store 20 (NumVal 0)

let init_env =
  ExtendEnv("i", RefVal (Store.new_ref g_store (NumVal 1)),
   ExtendEnv("v",RefVal (Store.new_ref g_store (NumVal 5)),
    ExtendEnv("x",RefVal (Store.new_ref g_store (NumVal 10)),
      EmptyEnv)))

let rec apply_proc f a =
  match f with
  | ProcVal (x,b,env) ->
     eval_expr (extend_env env x a) b
  | _ -> failwith "apply_proc: Not a procVal"
and
  eval_expr (en:env) (e:expr) :exp_val =
  match e with
  | Int n          -> NumVal n
  | Var id          ->
    (match apply_env en id with
    | None -> failwith @@ "Variable "^id^" undefined"
    | Some ev ->  ev)
  | Unit -> UnitVal
  | ITE(e1, e2, e3)    ->
    let v1 = eval_expr en e1 in
    if boolVal_to_bool v1
    then eval_expr en e2
    else eval_expr en e3
  | Add(e1, e2)    ->
    let v1 = eval_expr en e1 in
    let v2 = eval_expr en e2  in
    NumVal ((numVal_to_num v1) + (numVal_to_num v2))
  | Mul(e1, e2)    ->
    let v1 = eval_expr en e1 in
    let v2 = eval_expr en e2  in
    NumVal ((numVal_to_num v1) * (numVal_to_num v2))
  | Sub(e1, e2)    ->
    let v1 = eval_expr en e1 in
    let v2 = eval_expr en e2  in
    NumVal ((numVal_to_num v1) - (numVal_to_num v2))
  | IsZero(e) ->
    let v1 = eval_expr en e  in
    BoolVal (numVal_to_num v1=0)
  | Let(x, e1, e2) ->
    let v1 = eval_expr en e1
    in eval_expr (extend_env en x v1) e2
  | Proc(x,t,e)      -> ProcVal (x,e,en)
  | App(e1,e2)     ->
    let v1 = eval_expr en e1 in
    let v2 = eval_expr en e2 in
    apply_proc v1 v2
  | Letrec(tparam,id,param,tbody,body,e) ->
    eval_expr (ExtendEnvRec(id,param,body,en)) e
  | Set(id,e) ->
    let v=eval_expr en e
    in Store.set_ref g_store (refVal_to_int (from_some (apply_env en id))) v;
       NumVal 28
  | BeginEnd(es) ->
    List.fold_left (fun v e -> eval_expr en e) (NumVal 28) es
  | NewRef(e) ->
    RefVal(Store.new_ref g_store (eval_expr en e))
  | DeRef(e) ->
    let v1 = eval_expr en e
    in Store.deref g_store (refVal_to_int v1)
  | SetRef(e1,e2) ->
    let v1=eval_expr en e1
    in let v2=eval_expr en e2
    in Store.set_ref g_store (refVal_to_int v1) v2;
    UnitVal
  | TypeDecl(id,cs) ->
    UnitVal
  | Variant(tag,args) ->
    let rec eval_args = begin
      function
      | x::xs -> (eval_expr en x)::(eval_args xs)
      | [] -> []
    end in
    TaggedVariantVal(tag, (eval_args args))
  | Case(cond,branches) ->
    let v1 = eval_expr en cond in
    let variant_tag = ref None in
    let variant_es = ref None in
    begin
      match v1 with
      | TaggedVariantVal(tag, es) -> begin
          variant_tag := Some tag;
          variant_es := Some es
        end;
      | _ -> failwith "Non-Variant provided to Case."
    end;
    let branch_id = ref None in
    let branch_es = ref None in
    let branch_tgt = ref None in
    for i = 0 to (List.length branches) - 1 do
      match (List.nth branches i) with
      | Branch(id, es, tgt) -> begin
          if id=(from_some !variant_tag) then begin
            branch_id := Some id;
            branch_es := Some es;
            branch_tgt := Some tgt;
          end
        end
    done;
    if (!branch_id)=None then
      failwith "None of the branches match."
    else begin
      let branch_env = extend_env_list en (from_some !branch_es) (from_some !variant_es) in
      eval_expr branch_env (from_some !branch_tgt)
    end
  | Debug ->
    print_string "Environment:\n";
    print_string @@ string_of_env en;
    print_string "\nStore:\n";
    List.iteri (fun i s -> print_string (string_of_int i^"->"
                                                 ^s^"\n")) @@ List.map
      string_of_expval @@ Store.store_to_list g_store;
    UnitVal
  | _ -> failwith("Not implemented: "^string_of_expr e)
and
  eval_prog (Ast.AProg e) = eval_expr init_env e



(***********************************************************************)
(* Everything above this is essentially the same as we saw in lecture. *)
(***********************************************************************)

(* Parse a string into an ast *)


let parse s =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast


(* Interpret an expression *)
let interp (e:string) : exp_val =
  e |> parse |> eval_prog

(*let test (n:int) : string =
  Examples.example n |> parse |> eval_prog
*)
let ex1 = "
let x = 7
in let y = 2
   in let y = let x = x-1
              in x-y
      in (x-8)- y"

let ex2 = "
   let g =
      let counter = 0
      in proc(d) {
         begin
           set counter = counter+1;
           counter
         end
         }
   in (g 11)-(g 22)"

let ex3 = "
  let g =
     let counter = newref(0)
     in proc (d) {
         begin
          setref(counter, deref(counter)+1);
          deref(counter)
         end
       }
  in (g 11) - (g 22)"

let ex4 = "
   let g =
      let counter = 0
      in proc(d) {
         begin
           set counter = counter+1;
           counter
         end
         }
   in debug"

let ex5 = "
let a = 3
in let p = proc(x) { set x = 4 }
in begin
         (p a);
         a
       end"
