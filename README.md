laumann(1) "May 2011" "Version 0.1" "Laumann C Library"
=======================================================

NAME
----
Laumann C Library \- A library of C programs, created for/while learning C by Thomas B. Laumann Jespersen

SYNOPSIS
--------

**make** [help]

Use the _Makefile_ s found in the different directories to get an idea, of what they are for. The default target for all these directories will be the _help_ target, printing some sort of useful information.

DESCRIPTION
-----------

This "library" is written as an exercise in learning C, mostly using **The C Book**, but other resources have also been in use.

This collection has developed alongside the reading of **The C Book** and all of the programs called **exampleX_Y** or **exerciseX_Y** where **X** and **Y**
are integers, are taken directly from the aforementioned book. A few of these programs don't work, which is because is because they are erroneous in the book (I have checked and double checked).

Other programs are my own creations, like **redblacktree**, a red-black tree implementation (which, as of version 0.1 doesn't work properly - I haven't found the error yet), **binarytree** (actually a binary search tree) and **write**.

LIBRARY OVERVIEW
----------------

Here is a list of the directories contained in this library and a short description of them.

- **begin** To begin at the beginning. This directory has a lot of simple "Getting Started" programs ("Hello, World!" and the like).
- **cbook** The next step. The exercises I deemed a bit more advanced, or only interesting if you were reading the book.
- **trigrapher** Take as input a C program and output the same program substituting all characters that can be represented by trigraphs with their trigraph equivalents.
- **redblacktree** A red-black tree implementation. This implementation is faulty, because printing an in-order traversal of the tree might not yield its elements in a sorted order. The bug (I believe) is found in the rotations, maybe it's a race condition of a kind.
- **binarytree** A binary search tree implementation.
- **linkedlist** A (doubly) linked list implementation.
- **recursive_descent_parser** or **rdep**, a recursive descent expression parser (for standard C integer expressions).
- **pattern** A pattern matching program. This program is taken from the penultimate section of **The C Book**, and is a simplistic grep-like program.
- **write** A simple program that writes the given arguments to a file or to _stdout_ (default is _stdout_). The idea behind this program was to take some inspiration from **git** about command line arguments and the use of bit operations to indicate set options.
- **progress** A progress bar, shamelessly stolen from **git**, because I think it's cool and wanted to see if I could get it to work outside **git**.

AUTHOR
------
Thomas Bracht Laumann Jespersen <laumann.thomas@gmail.com>

SEE ALSO
--------

**The C Book** from **GBdirect** (the book can be downloaded in PDF form from: http://publications.gbdirect.co.uk/c_book/ )
