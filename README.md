# Ulik
This project is made by Alexander Kulinich (kuliinch)
This is a gap-year project in which I learn C to develop a compiler for my programming language - Ulik
> I don't expect this to be the best programming language in any sense, I didn't design it to be good at anything, only good to learn from during its development

## Building and running

To _build_ the project you simply have to compile all the C files located in this directory

```terminal
gcc [files]
```

To compile your Ulik code, simply run the compiler binary and specify the $$.ulik$$ files you want to compile

```terminal
./compile [.ulik files]
```

## TODO:
    1. Create a much simpler process of building and running the compiler
    2. Write down requirements and features
    3. Other stuff

## To the code readers:

The structure of the Ilukode language compiler will look as followed:
	1. lexer.c -> Generates tokens from the source code
	2. parser.c -> Produces a parse tree/AST from the generated tokens
	3. seman.c -> Performs a semantic analysis of the AST
	4. irgen.c -> Generates intermediate representation (using LLVM)
	5. ogen.c -> Generates object file/s that can be executed by the user
