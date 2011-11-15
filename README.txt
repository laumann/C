laumann(1)
==========

NAME
----
laumann - A collection of C programs, created for/while learning C.

SYNOPSIS
--------
[verse]
'make' [help]

Use the Makefiles found in the different directories to get an idea, of what they are for. The default target for all these directories will be the help target, printing some sort of useful information.

DESCRIPTION
-----------
This ``library'' is written as an exercise in learning C, mostly from the *The C Book*, but other resources have also been in use.

The examples taken from *The C Book* are programs called *exampleX_Y* or *exerciseX_Y* where *X* and *Y* are integers. A few of them don't work, because they are erroneous in the book (checked and double checked). Some I've fixed -- others I've left broken.

Other programs are my own creations, like *redblacktree*, a red-black implementation, *binarytree* (a binary search tree) and *write*.

OVERVIEW
--------
Following is a list of the directories contained in this library and a short description of them:

*begin*:: To begin at the beginning. This directory contains a lot of simple ``Getting Started'' programs (``Hello, World!'' and the like).

*cbook*:: The next step. The exercises I deemed a bit more advanced, or only interesting if you were reading the book.

*trigrapher*:: Takes as input a C program and outputs the same program substituting all characters that can be represented by trigraphs by their trigraph equivalent.

*redblacktree*:: A red-black tree implementation.

*binarytree*:: A binary search tree implementation.

*linkedlist*:: A (doubly) linked list implementation.

*pattern*:: A pattern matching program. The code is taken from the penultimate section of *The C Book*, and is a simplistic grep-like program.

*write*:: A simple program that writes the given arguments to a file or to _stdout_ (default is _stdout_). The idea behind this program was to take some inspiration from _git_ about command line arguments and the use of bit operations to indicate set options.

*progress*:: A progress bar, shamelessly stolen from _git_, because I think it's cool and wanted to see if I could get it to work outside _git_.

*debug*:: A minimalistic debug library, inspired in part by the work I saw as a student programmer. It's neat to be able to compile printf-like statements out of any program (also, of course, included are different log levels).

REFERENCES
----------
*The C Book* from *GBdirect* (the book can be downloaded in PDF form from: http://publications.gbdirect.co.uk/c_book/)

Author
------
* Thomas Bracht Laumann Jespersen <laumann.thomas@gmail.com>
