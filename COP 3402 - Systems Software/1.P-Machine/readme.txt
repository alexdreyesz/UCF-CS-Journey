//Alex Reyes
//Jesus Molina

How To Compile and Run the VM:
1. Head to the directory in terminal where the VM source code is stored
2. run command gcc vm.c -o <insert name for file>
3. run command ./<choosen file name>.out(or ./<choosen file name>.exe if your system created .exe file) <name of input file> or Run BASH script
4. Output will appear on terminal screen

Example:
C:\Users\student>cd HW1
C:\Users\student\HW1>gcc vm.c -o vm
C:\Users\student\HW1>vm input.txt

                 PC  BP  SP   stack
Initial values:  0   499 500

    JMP 0    45  45  499 500
    INC 0    5   48  499 495 0 0 0 0 0
Please Enter an Integer: 3 //// User Input ////
    SIN 0    2   51  499 494 0 0 0 0 0 3
    CAL 0    6   6   493 494 0 0 0 0 0 3
    INC 0    4   9   493 490 0 0 0 0 0 3 | 499 499 54 0
    LIT 0    4   12  493 489 0 0 0 0 0 3 | 499 499 54 0 4
    LIT 0    3   15  493 488 0 0 0 0 0 3 | 499 499 54 0 4 3
    MUL 0    3   18  493 489 0 0 0 0 0 3 | 499 499 54 0 12
    STO 1    4   21  493 490 0 0 0 0 12 3 | 499 499 54 0
    LIT 0    14  24  493 489 0 0 0 0 12 3 | 499 499 54 0 14
    LOD 1    4   27  493 488 0 0 0 0 12 3 | 499 499 54 0 14 12
    LSS 0    7   30  493 489 0 0 0 0 12 3 | 499 499 54 0 0
    JPC 0    39  39  493 490 0 0 0 0 12 3 | 499 499 54 0
    LIT 0    5   42  493 489 0 0 0 0 12 3 | 499 499 54 0 5
    RTN 0    0   54  499 494 0 0 0 0 12 3
Output result is: 3
    SOU 0    1   57  499 495 0 0 0 0 12
    EOP 0    3   60  499 495 0 0 0 0 12
