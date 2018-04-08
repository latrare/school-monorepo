.PHONY: all clean byte test repl utop

OCB_FLAGS = -tag bin_annot -tag debug -use-menhir -use-ocamlfind -pkgs oUnit
OCB = ocamlbuild $(OCB_FLAGS)

all: byte

main:
	$(OCB) main.byte

clean:
	$(OCB) -clean

byte:
	$(OCB) repl.byte

repl: byte
	./repl.byte

utop: byte
	utop

test:
	$(OCB) test.byte && ./test.byte
