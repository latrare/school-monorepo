open Ast
open Ds
open Interp


let _ = interp "let x = newref(0) in begin for i=1 to 10 ( setref(x, deref(x) - (-1)) ); deref(x) end"
