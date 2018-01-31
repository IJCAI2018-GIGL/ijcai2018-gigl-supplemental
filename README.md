# Supplemental Material for IJCAI submission of GIGL paper

Containing 4 examples, Monster, Quiz, LSystemTree and Dungeon_BSP. In each example:

1. *.xc is the source file in GIGL
2. *.generated.h is the C++ file that is translated from GIGL using an automated translator
3. *.manual.h is the handwritten C++ with mostly same semantics as the GIGL source file
4. GiglDefaultInclude.h and all files in the commons folder are GIGL libary files. They are the same in the four examples.
5. Other .cpp and .h files are example specific C++ source files that interfaces with GIGL, which can compile with either the *.generated.h or *.manual.h (see main.cpp for how to do the two alternatives) to generate the excutable.

NOTE: LSystemTree and Dungeon_BSP example needs OpenGL and SDL library to compile and execute.
