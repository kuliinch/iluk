# Introduction

Welcome to the Iluk repository. Here I save the most recent progress made on the Ilukode Project. 
This project is something I've wanted to do for ages, and that includes designing a programming language and creating its compiler.
I've just started learning C to make this project possible, so in the process of making a new programming language, I'm learning another one.

> Note: I do not expect this programming language to be at all competent. But I would gladly accept any feedback - as this project was intended to be a learnign opportunity.

I make this repository public to share my journey with other people and - maybe - others will feel motivated to do so, or look at the commit history and learn something cool.

# Building and running

To _build_ the project you simply have to compile all the C files located in this directory

```terminal
gcc *.c -o iluk
```

To compile your Ulik code, simply run the compiler binary and specify the ```.iluk``` files you want to compile

```terminal
./iluk [.iluk files]
```

# TODO

- Design the programming language (syntax, features, etc) and **document** them
- Create a documentation/wiki
- Finish making the lexer - working on tokenisation after designing programming language
- Every other step into making a compiler.
- Learn about LLVM (and IR)

Once the first prototype for the compiler has been made, these will be introduced:
- Multithreadding
- Intermittent syntax reading

Happy programming!
