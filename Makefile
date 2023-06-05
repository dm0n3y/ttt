all:
	dune build @src/fmt --auto-promote || true
	dune build src --profile dev

deps:
	opam switch import opam.lock

change-deps:
	opam switch export opam.lock

clean:
	dune clean

.PHONY: all clean
