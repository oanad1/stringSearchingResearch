DIACONESCU OANA - 323CD

PURPOSE
This project implements 3 of the most important string-processing algorithms:
KMP, Rabin-Karp and Aho-Corasick, examining their performance in different
conditions and their ability to solve specific problems.

IMPLEMENTATION DETAILS
In the implementation of this homework I followed the guidelines mentioned in the
assignment:
  - I solved the main problem associated with KMP and Rabin-Karp: single pattern
    matching and chose a reliable hashing function for RK
  - I solved the problem associated with the Aho-Corasick algorithm- multiple
    pattern matching- using Aho-Corasick and KMP (and RK), in order to compare their
    efficiency and results
  - I implemented 2 specific problems which could be solved more efficiently using
    KMP rather than Rabin-Karp:
       1.Determining if a string is a rotation of another string
       2.Determining if a substring forms a prefix and a suffix for a give string.

STRUCTURE
This archive contains the following:
* algo_test.cpp
  - used for input reading, output writing and calling the functions corresponding
    to each type of test and algorithm

* algo.cpp
  - contains functions which solve the following problems:
    1.Single pattern matching (can apply KMP or RK)
    2.Multiple pattern matching (can apply  KMP, RK or AC)
    3.Determining if a string is a rotation of another string (can apply KMP or RK)
    4.Determining if a substring forms a prefix and a suffix for a give string
    (can apply KMP or RK)

* algo.h
  - contains headers for the functions in algo.cpp and the functions for KMP, RK and AC

* algo1.cpp
  - contains an implementation of the Knuth-Morrris-Pratt algorithm:
    input: pattern + text
    output: array of occurrences for the pattern

* algo2.cpp
  - contains an implementation of the Rabin-Karp algorithm
    input: pattern + text
    output: array of occurrences for the pattern

* algo3.cpp
  - contains an implementation of the Aho-Corasick algorithm:
    input: array of patterns + text
    output: map containing the index of each pattern + an array of its occurrences

* /in folder
  - contains the input files for all tests
  - there is a total of 30 .in files:
    #tests1-12 are for single pattern-matching
    #tests12-20 are for multiple pattern-matching
    #tests rotation_test1-5 are applied only to the rotation problem
    #tests suffix_test1-5 are applied only to the suffix problem

* /out folder
  - contains the output files for all tests
  - each output file contains the results of applying each algorithm to its
    associated problem, if tested

* Makefile
  - for compiling all source files into an executable named test

* check.sh
  - checker which compiles the files and runs all the tests

INPUT SPECIFICATIONS

Also attached there is a TestSpecs.txt file which documents the evaluation
criteria for the first 20 tests.

The input files must have the following structure:
  - k patterns on the first k lines (with no blank lines in between)
  - A blank line
  - The text(which will be converted to a contiguous string; it can contain any
  number of blank lines)

  It's also important to note that the patterns cannot be repeated.
  In case of the rotation tests, both patterns must have the same size. One of
  the substrings is used as the pattern while the other as the text.

  In case of the suffix tests, the substring will be treated as the pattern:
  it should be placed on the first line and it must have a smaller size than the string.


REFERENCES
https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
https://brilliant.org/wiki/rabin-karp-algorithm/
https://www.toptal.com/algorithms/aho-corasick-algorithm
