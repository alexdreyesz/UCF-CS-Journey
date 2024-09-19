//Alex Reyes
//Jesus Molina

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 500

typedef struct {
    int OP; // Operation Code
    int L;  // Lexicographical Level
    int M;  // Modifier
} Instruction;

typedef struct {
    int BP;         // Base Pointer
    int SP;         // Stack Pointer
    int PC;         // Program Counter
    Instruction IR; // Instruction Register
} CPU;

// PAS Array Stack Initiliaze All Values As to 0's
int pas[ARRAY_SIZE] = { 0 };

//Base Function
int base(int BP, int L) {
    int arb = BP; // arb = Activation Record Base

    while (L > 0) { // Find Base L Levels Down
        arb = pas[arb];
        L--;
    }
    return arb;
}

int main(int argc, char* argv[]) {

    //Activation Record Line Position Tracker " | " Array
    int arArray[ARRAY_SIZE] = { 0 };

    // arArray Counter To Keep Track Of The Index
    int arCount = 0;

    // Keep Track Of The Pas Array Index & Size
    int instructionIndex = 0;

    // File Pointer
    FILE* fp;

    //FIle Opener
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable To Open The File\n");
        return 1;
    }

    int op, l, m; // Temp Values To Read In

    // Read Integers From The File And Store Them In The Array
    while (fscanf(fp, "%d %d %d", &op, &l, &m) == 3) {
        pas[instructionIndex++] = op;
        pas[instructionIndex++] = l;
        pas[instructionIndex++] = m;
    }

    fclose(fp); // Close The File After Reading

    CPU cpu; // CPU Stack Pointer

    // Initial Cpu Regs
    cpu.BP = ARRAY_SIZE - 1; // Array Amount Minus One To Place The Pointer Accordingly One Spot Less Than Max Array Thise Case 499
    cpu.SP = cpu.BP + 1;
    cpu.PC = 0;

    // Initial Instruction Register
    cpu.IR.OP = 0;
    cpu.IR.L = 0;
    cpu.IR.M = 0;

    int eop = 1; // Eop Flag

    printf("\t\t PC  BP  SP   stack\n");
    printf("Initial values:  %d   %d %d\n\n", cpu.PC, cpu.BP, cpu.SP);

    while (eop != 0) {

        // Fetch Cycle
        cpu.IR.OP = pas[cpu.PC];
        cpu.IR.L = pas[cpu.PC + 1];
        cpu.IR.M = pas[cpu.PC + 2];
        cpu.PC += 3; // Move PC Pointing Position By 3 To Move To The Start Of The Next Set Of Instructions

        switch (cpu.IR.OP) {
            // LIT
        case 1:
            cpu.SP = cpu.SP - 1;
            pas[cpu.SP] = cpu.IR.M;
            printf("    LIT %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
            break;

            // OPR & RTN
        case 2:
            switch (cpu.IR.M) {
                // RTN
            case 0: //Returns From A Dubroutine Is Encoded 0 0 0 And Restores The Caller’s AR
                cpu.SP = cpu.BP + 1;
                cpu.BP = pas[cpu.SP - 2];
                cpu.PC = pas[cpu.SP - 3];
                printf("    RTN %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arCount--; // Decrease arArray Counter To Delete Last Activation Record Position
                break;

                // ADD
            case 1:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] + pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    ADD %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // SUB
            case 2:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] - pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    SUB %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // MUL
            case 3:
                pas[cpu.SP + 1] = (pas[cpu.SP + 1] * pas[cpu.SP]);
                cpu.SP = cpu.SP + 1;
                printf("    MUL %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // DIV
            case 4:
                pas[cpu.SP + 1] = (pas[cpu.SP + 1] / pas[cpu.SP]);
                cpu.SP = cpu.SP + 1;
                printf("    DIV %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // EQL
            case 5:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] == pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    EQL %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // NEQ
            case 6:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] != pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    NEQ %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // LSS
            case 7:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] < pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    LSS %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // LEQ
            case 8:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] <= pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    LEQ %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // GTR
            case 9:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] > pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    GTR %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // GEQ
            case 10:
                pas[cpu.SP + 1] = pas[cpu.SP + 1] >= pas[cpu.SP];
                cpu.SP = cpu.SP + 1;
                printf("    GEQ %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // ODD
            case 11:
                pas[cpu.SP] = pas[cpu.SP] % 2;
                printf("    ODD %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;
            }
            break;

            // LOD
        case 3:

            cpu.SP = cpu.SP - 1;
            pas[cpu.SP] = pas[base(cpu.BP, cpu.IR.L) - cpu.IR.M];
            printf("    LOD %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
            break;

            // STO
        case 4:
            pas[base(cpu.BP, cpu.IR.L) - cpu.IR.M] = pas[cpu.SP];
            cpu.SP = cpu.SP + 1;
            printf("    STO %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
            break;

            // CAL
        case 5:
            pas[cpu.SP - 1] = base(cpu.BP, cpu.IR.L); // Static Link (SL)
            pas[cpu.SP - 2] = cpu.BP;                 // Dynamic Link (DL)
            pas[cpu.SP - 3] = cpu.PC;                 // Return Address (RA)
            cpu.BP = cpu.SP - 1;
            cpu.PC = cpu.IR.M;

            arArray[arCount] = cpu.SP - 1; //Store Stack Index at Beginning of Every Activation Record This Marks The End Of The Previous Activation Record And The Beginning Of A New One
            arCount++; // Increment arArray Counter To Store New Activation Record Position

            printf("    CAL %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            break;

            // INC
        case 6:
            cpu.SP = cpu.SP - cpu.IR.M;
            printf("    INC %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
            break;

            // JMP
        case 7:
            cpu.PC = cpu.IR.M;
            printf("    JMP %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
            break;

            // JPC
        case 8:
            if (pas[cpu.SP] == 0) {
                cpu.PC = cpu.IR.M;  // Jump To The Instruction At Address M
            }
            cpu.SP = cpu.SP + 1;// Pop The Top Stack Element Regardless Of The Jump
            printf("    JPC %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
            arArray[arCount] = cpu.SP - 1;  // Update arArray Pointing Position At Index arCount
            break;

            // SYS
        case 9:
            switch (cpu.IR.M) {

                // SOU
            case 1: // Write Top Stack Elemt To Screen
                printf("Output result is: %d\n", pas[cpu.SP]);
                cpu.SP = cpu.SP + 1;
                printf("    SOU %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // SIN
            case 2: // Read In Input From User And Store On Top Of Stack
                cpu.SP = cpu.SP - 1;
                // Ask For User Input 
                printf("Please Enter an Integer: ");
                fscanf(stdin, "%d", &pas[cpu.SP]);
                printf("    SIN %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount
                break;

                // END  
            case 3:  // End Program(Set eop To 0)
                printf("    EOP %-4d %-3d %-3d %d %d ", cpu.IR.L, cpu.IR.M, cpu.PC, cpu.BP, cpu.SP);
                arArray[arCount] = cpu.SP - 1; // Update arArray Pointing Position At Index arCount 
                eop = 0; //Set eop Flag To 0 Halt Program
                break;
            }
        }

        int x = 0; //Counter To Access The Activation Record At Index X

        //Loop Through The Top Of Stack Down Towards Stack Pointer
        for (int i = (ARRAY_SIZE - 1); i >= cpu.SP; i--) {
            // Check If The Current Index 'i' Matches The Value Stored In arArray[x]
            if (i == arArray[x]) {
                printf("| ");
                x++; //Increment 'x' To Move To The Next Activation Record Start Index
            }
            printf("%d ", pas[i]); //Print Stack Items  
        }
        printf("\n"); // Add Newline To Each End Of The Line
    }
}