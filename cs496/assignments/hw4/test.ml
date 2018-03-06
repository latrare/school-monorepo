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

  "letreceven0" >:: (
    fun _ -> assert_equal
        (NumVal 1)
        (interp "letrec even(x) = if zero?(x) then 1 else (odd (x - 1)) odd (x) = if zero?(x) then 0 else (even (x - 1)) in (even 0)")
  );
  "letreceven1" >:: (
    fun _ -> assert_equal
        (NumVal 0)
        (interp "letrec even(x) = if zero?(x) then 1 else (odd (x - 1)) odd (x) = if zero?(x) then 0 else (even (x - 1)) in (even 1)")
  );
  "letrecodd0" >:: (
    fun _ -> assert_equal
        (NumVal 0)
        (interp "letrec even(x) = if zero?(x) then 1 else (odd (x - 1)) odd (x) = if zero?(x) then 0 else (even (x - 1)) in (odd 0)")
  );
  "letrecodd1" >:: (
    fun _ -> assert_equal
        (NumVal 1)
        (interp "letrec even(x) = if zero?(x) then 1 else (odd (x - 1)) odd (x) = if zero?(x) then 0 else (even (x - 1)) in (odd 1)")
  );
  "letreceven99" >:: (
    fun _ -> assert_equal
        (NumVal 0)
        (interp "letrec even(x) = if zero?(x) then 1 else (odd (x - 1)) odd (x) = if zero?(x) then 0 else (even (x - 1)) in (even 99)")
  );
  "letrecodd99" >:: (
    fun _ -> assert_equal
        (NumVal 1)
        (interp "letrec even(x) = if zero?(x) then 1 else (odd (x - 1)) odd (x) = if zero?(x) then 0 else (even (x - 1)) in (odd 99)")
  );
]

let _ = run_test_tt_main ("suite" >::: tests)
