open OUnit2
open Ast
open Ds
open Interp

(* A few test cases *)
let tests = [
  "int"  >:: (fun _ -> assert_equal (NumVal 22) (interp "22"));
  "add"  >:: (fun _ -> assert_equal (NumVal 22) (interp "11+11"));
  "adds" >:: (fun _ -> assert_equal (NumVal 22) (interp "(10+1)+(5+6)"));
  "let"  >:: (fun _ -> assert_equal (NumVal 22) (interp "let x=22 in x"));
  "lets" >:: (fun _ -> assert_equal (NumVal 22) (interp "let x = 0 in let x = 22 in x"));
  "for"  >:: (fun _ -> assert_equal (NumVal 10) (interp "let x = newref(0) in begin for i=1 to 10 ( setref(x, deref(x) - (-1)) ); deref(x) end"));
  "for0" >:: (fun _ -> assert_equal (NumVal 0) (interp "let x = newref(0) in begin for i=10 to 1 ( setref(x, deref(x) - (-1))); deref(x) end"));
  "proc" >:: (fun _ -> assert_equal (NumVal 1) (interp "let a = newref(3) in let f = proc(x, y) { setref(x, deref(x) - y) } in begin (f a 2); deref(a) end"))
]

let _ = run_test_tt_main ("suite" >::: tests)
