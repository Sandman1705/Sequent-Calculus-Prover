# Sequent Calculus Prover


## About
[C++] Command line tool for searching proofs of propositional calculus formulas using sequent calculus

* Language: C++
* Tools and Libs: Flex, Bison
* IDE: CodeBlocks (set up to use Makefile)

## Build and run

On windows:

	make mingw
	./prover.exe

On linux:

	make
	./prover

## Usage

	./prover [--ignore-structural] [--example] [--help] [--continuous | --continuous-ignore-syntax]

Formual are taken from standard input. See --help for input format.

Options:
+ -h, --help : instructions for properly inputting sequents
+ -e, --example : prints an example of input and proof output 
+ -i, --ignore-structural : ignores structural rules: thinning and contraction
+ -c, --continuous : allows input of multiple sequents; sequents are being read from standard input until first formula with incorrect syntax
+ -ci, --continuous-ignore-syntax : same as -c except it ignores formulas with incorrect syntax

## Other info

September 2017

This was a student project made for course <b>Automated reasoning</b> in Faculty of Mathematics, University of Belgrade of academic year 2016/2017.

Ovo je studentski projekat urađen za kurs <b>Automatsko rezonovanje</b> na Matematičkom fakultetu u Beogradu akademske 2016/2017.