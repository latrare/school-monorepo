
(* This file defines expressed values and environments *)


(* expressed values and environments are defined mutually recursively *)

type exp_val =
  | NumVal of int
  | BoolVal of bool
  | ProcVal of string*Ast.expr*env
  | RefVal of int
  (* TODO: PairVal *)
  | PairVal of exp_val*exp_val
  (* TODO: ListVal *)
  | ListVal of exp_val
  (* TODO: TreeVal *)
  | TreeVal of exp_val
  (* TODO: UnitVal *)
  | UnitVal
and
  env =
  | EmptyEnv
  | ExtendEnv of string*exp_val*env
  | ExtendEnvRec of string*string*Ast.expr*env
and
  btree =
  | EmptyNodeVal of Ast.texpr
  | NodeVal of exp_val*btree*btree


(* Operations on environments *)

let empty_env (x:unit):env = EmptyEnv

let extend_env (env:env) (id:string) (v:exp_val):env = ExtendEnv(id,v,env)

let rec apply_env (env:env) (id:string):exp_val option =
  match env with
  | EmptyEnv -> None
  | ExtendEnv (key,value,env) ->
    if id=key
    then Some value
    else apply_env env id
  | ExtendEnvRec(key,param,body,en) ->
    if id=key
    then Some (ProcVal(param,body,env))
    else apply_env en id


(* operations on expressed values *)

let numVal_to_num =  function
  | NumVal n -> n
  | _ -> failwith "Expected a number!"

let boolVal_to_bool =  function
  | BoolVal b -> b
  | _ -> failwith "Expected a boolean!"

let refVal_to_int =  function
  | RefVal n -> n
  | _ -> failwith "Expected a reference!"

let unitVal_to_unit = function
  | UnitVal -> ()
  | _ -> failwith "Expected a unit!"

(* TODO: pairVal_to_fst *)
let pairVal_to_fst = function
  | PairVal (exp_val1, _) -> exp_val1
  | _ -> failwith "Expected a pair!"

(* TODO: pairVal_to_snd *)
let pairVal_to_snd = function
  | PairVal (_, exp_val2) -> exp_val2
  | _ -> failwith "Expected a pair!"

(* TODO: listVal_to_list *)
let listVal_to_list = function
  | ListVal xs -> xs
  | _ -> failwith "Expected a list!"

(* TODO: treeVal_to_tree *)
let treeVal_to_tree = function
  | TreeVal t -> t
  | _ -> failwith "TODO: Implement me!"

let rec string_of_expval = function
  | NumVal n -> "NumVal " ^ string_of_int n
  | BoolVal b -> "BoolVal " ^ string_of_bool b
  | ProcVal (id, body, env) -> "ProcVal (" ^ id ^ "," ^ Ast.string_of_expr body ^ "," ^ string_of_env env ^ ")"
  | RefVal i -> "RefVal (" ^ string_of_int i ^ ")"
  (* TODO: PairVal *)
  | PairVal (e1, e2) -> "PairVal (" ^ string_of_expval e1 ^ "," ^ string_of_expval e2 ^ ")"
  (* TODO: ListVal *)
  | ListVal e -> "ListVal " ^ string_of_expval e
  (* TODO: TreeVal *)
  | TreeVal e -> "TreeVal " ^ string_of_expval e
  (* TODO: UnitVal *)
  | UnitVal -> "UnitVal"
and
  string_of_env  = function
  | EmptyEnv -> ""
  | ExtendEnv(id,v,env) -> "("^id^","^string_of_expval v^")"^string_of_env env
  | ExtendEnvRec(id,param,body,env) -> "("^id^","^param^","^Ast.string_of_expr body^")"^string_of_env env
and
  string_of_btree = function
  | EmptyNodeVal t -> "EmptyNode"
  | NodeVal(data, lst, rst) -> "NodeVal(" ^ (string_of_expval data) ^ "," ^ (string_of_btree lst) ^ "," ^ (string_of_btree rst) ^ ")"
