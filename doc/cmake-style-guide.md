# CPD CMake Style Guide

Use this style guide when writing and editing CMakeLists.txt files in the cpd repository:

- two spaces
- commands should be in lowercase: `include_directories` not `INCLUDE_DIRECTORIES` or `Include_Directories`
- empty `else()` and `endif()` macros: `else()` not `else(A_CONDITION)`
- no space between `if`, `else`, and `endif` and the parenthesis: `if()` not `if ()`
- prefer ON and OFF over TRUE and FALSE

As usual for this sort of thing, defer to the file you're editing over these conventions — if you open a file that uses four spaces, stick to four spaces for that file.
Don't mix pure stylistic cmake changes in with your functional changes, split those changes into two seperate commits.
