.PHONY: all clean byte test repl utop

OCB_FLAGS = -tag bin_annot -use-ocamlfind -pkgs oUnit
OCB = ocamlbuild $(OCB_FLAGS)

all: check

clean:
	$(OCB) -clean

main:
	$(OCB) hw1.byte

check:
	$(OCB) hw1.byte

repl: byte
	./repl.byte

utop: byte
	utop

test:
	$(OCB) test.byte && ./test.byte
