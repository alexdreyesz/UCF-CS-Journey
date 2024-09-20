//Alex Reyes
//Jesus Molina

How To Compile and Run the parsercodegen.c:
1. Head to the directory in terminal where the lex source code is stored
2. run command gcc parsercodegen.c -o <insert name for file>
3. run command ./<choosen file name>.out(or ./<choosen file name>.exe if your system created .exe file) <name of input file> or Run BASH script
4. Output will appear on terminal screen

Example:
C:\Users\student>cd HW3
C:\Users\student\HW2>gcc parsercodegen.c -o parsercodegen
C:\Users\student\HW2>parsercodegen input.txt

OR

Example:
C:\Users\student>cd parsercodegen
C:\Users\student\HW2>gcc parsercodegen.c -o parsercodegen
C:\Users\student\HW2>./parsercodegen.out input.txt

Output If Done Correctly:
LINE    OP    L   M
0       JMP   0   3
1       INC   0   5
2       LOD   0   4
3       LIT   0   2
4       MUL   0   3
5       STO   0   3
6       SYS   0   3


Symbol Table:

Kind | Name       | Value | Level | Address | Mark
---------------------------------------------------
   2 |          x |     0 |     0 |       3 |    1
   2 |          y |     0 |     0 |       4 |    1