#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	switch (ALUControl) {
		case 0: // (000 = 0)  // Z = A + B
			*ALUresult = A + B;
			break;

		case 1: // (001 = 1) // Z = A – B
			*ALUresult = A - B;
			break;

		case 2: // (010 = 2) // If A < B, Z = 1; otherwise, Z = 0
			if ((int*)A < (int*)B) {
				*ALUresult = 1;
			} else {
				*ALUresult = 0;
			}
			break;

		case 3: // (011 = 3) //  If A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
			if (A < B) {
				*ALUresult = 1;
			} else {
				*ALUresult = 0;
			}
			break;

		case 4: // (100 = 4) // Z = A AND B
			*ALUresult = A & B;
			break;

		case 5: // (101 = 5) // Z = A OR B
			*ALUresult = A | B;
			break;

		case 6: // (110 = 6) // Z = Shift B left by 16 bits
			*ALUresult = B << 16;
			break;

		case 7: // (111 = 7) // Z = NOT A
			*ALUresult = ~A;
			break;
	}
	if (*ALUresult == 0)
		*Zero = 1;
	else
		*Zero = 0;

}


/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	if (PC % 4 != 0) { // Check for word alignment
		
		return 1; // Halt if not aligned 
	}

	*instruction = Mem[PC >> 2]; // PC >> 2 to get the actual location

	return 0; 
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	*op = (instruction >> 26) & 63;	// instruction [31-26]		// (0x3F = 0011 1111)
	*r1 = (instruction >> 21) & 31;   // instruction [25-21]		// (0x1F = 0001 1111)
	*r2 = (instruction >> 16) & 31;   // instruction [20-16]		// (0x1F = 0001 1111)
	*r3 = (instruction >> 11) & 31;   // instruction [15-11]		// (0x1F = 0001 1111)
	*funct = instruction & 63;        // instruction [5-0]		// (0x3F = 0011 1111)  
	*offset = instruction & 0xFFFF;     // instruction [15-0]		// (0xFFFF = 1111 1111 1111 1111) 
	*jsec = instruction & 0x3FFFFFF;    // instruction [25-0]		// (0x3FFFFFF = 0000 0011 1111 1111 1111 1111 1111 1111) 
}	


/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	printf("%d  ", op);
	// Initialize control signals to default values
	controls->RegDst = 0;  
	controls->Jump = 0;    
	controls->Branch = 0;   
	controls->MemRead = 0;  
	controls->MemtoReg = 0;
	controls->ALUOp = 0;   
	controls->MemWrite = 0; 
	controls->ALUSrc = 0;   
	controls->RegWrite = 0; 

	// For MemRead, MemWrite or RegWrite, the value 1 means that enabled, 0 means that disabled, 2 means “don’t care”.	
	// For RegDst, Jump, Branch, MemtoReg or ALUSrc, the value 0 or 1 indicates the selected path of the multiplexer; 2 means “don’t care”.

	// Decode the opcode and set control signals accordingly
	switch (op) { // SET 111 TO HEX
	case 0: // (0x0 = 0) // R-type Instruction (rt)									
		controls->RegDst = 1; //  Selected path of the multiplexer = 1
		controls->ALUOp = 7; // (111 = 7) // Determine the appropriate value based on the function code
		controls->RegWrite = 1; // Enabled
		break;

	case 2: // (0x2 = 2) // Jump (j)
		controls->Jump = 1; //  Selected path of the multiplexer = 1
		break;

	case 4: // (0x4 = 4) // Branch On Equal (beq)
		controls->RegDst = 2; // Don’t care
		controls->Branch = 1; //  Selected path of the multiplexer = 1
		controls->MemtoReg = 2; // Don’t care
		controls->ALUOp = 1;
		break;
	
	case 8: // (0x8 = 8) // Quick Addition (Addi)
		controls->ALUOp = 0; // (000 = 0)  // Determine the appropriate value based on the function code
		controls->ALUSrc = 1; //  Selected path of the multiplexer = 1
		controls->RegWrite = 1; // Enabled
		break;

	case 10: // (0xA = 10) // Set On Less Than Immediate (slti)
		controls->ALUOp = 2; // (010 = 2) // Determine the appropriate value based on the function code
		controls->ALUSrc = 1; //  Selected path of the multiplexer = 1
		controls->RegWrite = 1; // Enabled
		break;

	case 11: // (0xB = 11) // Set On Less Than Immediate Unsigned (sltiu)
		controls->ALUOp = 3;  // (010 = 2) // Enabled
		controls->ALUSrc = 1; //  Selected path of the multiplexer = 1
		controls->RegWrite = 1; // Enabled
		break;

	case 15: // (0xF = 15) // Load Upper Immediate (lui)
		controls->ALUOp = 6; //6 (110 = 6) // You need to determine the appropriate value based on the function code
		controls->ALUSrc = 1; //  Selected path of the multiplexer = 1
		controls->RegWrite = 1; // Enabled
		break;

	case 35: // (0x23 = 35) // Load Word (lw)
		controls->MemRead = 1; // Enabled
		controls->MemtoReg = 1; //  Selected path of the multiplexer = 1
		controls->ALUSrc = 1; //  Selected path of the multiplexer = 1
		controls->RegWrite = 1; // Enabled
		break;
	
	case 43: // (0x2B = 43) // Store Word (sw)
		controls->RegDst = 2; // Don’t care
		controls->MemtoReg = 2; // Don’t care
		controls->MemWrite = 1; // Enabled
		controls->ALUSrc = 1; // Selected path of the multiplexer = 1
		break;

	default:
		
		return 1; // Halt program if wrong input was provided 
	}

	return 0;
}


/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	// Read the registers addressed by r1 and r2 from Reg, and write the read values to data1and data2 respectively.

	*data1 = Reg[r1];
	*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value) // good
{
	// Assign the sign-extended value of offset to extended_value.

	// Check the sign bit (16th bit)
	if (offset & 0x8000) { // (0x8000 = 16th bit position)
		*extended_value = offset | 0xFFFF0000; // If it's negative, sign extend by setting upper bits to 1 (0x0000FFFF = 1111 1111 1111 1111 0000 0000 0000 0000)
	}
	else {
		*extended_value = offset & 0x0000FFFF; // If it's non-negative, sign extend by setting upper bits to 0 (0x0000FFFF = 0000 0000 0000 0000 1111 1111 1111 1111)
	}
}


/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero) //switch cases wrong op code, remove alup == 1;
{
	// Setting parameters for A, B, and ALUControl
	unsigned A, B;
	char ALUControl;

	// Apply ALU operations on data1, and data2 or extended_value (determined by ALUSrc).
	if (ALUSrc == 0) {
		A = data1;
		B = data2;
		//B = (ALUOp == '1') ? data2 : extended_value; // Select either data2 or extended_value based on ALUOp
	}
	else {
		A = data1;
		B = extended_value;
	}

	if (ALUOp == 7) { // If R-type instruction
		// Use the funct field to determine ALUControl for R-type instruction
		switch (funct) {
		case 32: // Operation code
			ALUControl = 0; 
			break;

		case 34: // First source register
			ALUControl = 1; 
			break;

		case 36: // Second source register
			ALUControl = 4; 
			break;

		case 37: // Destination register
			ALUControl = 5; 
			break;

		case 42: // Shift amount
			ALUControl = 2; 
			break;

		case 43: // Function bits
			ALUControl = 3; 
			break;
		default:
			return 1; // Halt program if wrong input was provided 
		}
	}
	else { // I-type or other instruction types
		ALUControl = ALUOp;
	}

	// Call the ALU function
	ALU(A, B, ALUControl, ALUresult, Zero);

	return 0;
}


/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	// Check if a memory write operation is requested
	if (MemWrite == 1) {
		// Check word alignment
		if (ALUresult % 4 == 0) {
			Mem[ALUresult / 4] = data2; // Write data2 to the memory location addressed by ALUresult
		}
		else {
			return 1; // Halt if not aligned
		}
	}

	// Check if a memory read operation is requested
	if (MemRead == 1) {
		// Check word alignment
		if (ALUresult % 4 == 0) {
			*memdata = Mem[ALUresult / 4]; // Read the content of the memory location addressed by ALUresult to memdata
		}
		else {
			return 1; // Halt if not aligned
		}
	}

	return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	unsigned writeData;

    if (RegWrite == 1 && MemtoReg == 1)
    {
		writeData = memdata; // Write data is coming from memory
    }

	if (RegWrite == 1 && MemtoReg == 0)
	{
		writeData = ALUresult; // Write data is coming from ALU_result
	}

	if (RegWrite == 1 && RegDst == 1)
	{
		Reg[r3] = writeData; // Write data to r3
	}

	if (RegWrite == 1 && RegDst == 0)
	{
		Reg[r2] = writeData; // Write data to r2
	}
}


/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	*PC += 4; // Increment the PC by 4

	// Update PC based on conditions
	if (Branch == 1 && Zero == 1) {
		*PC += (extended_value << 2); // Branch
	}

	if (Jump == 1) {
		*PC = (*PC & 0xF0000000) | (jsec << 2); // Jump		// ( 0xF0000000 = 1111 0000 0000 0000 0000 0000 0000 0000)
	}
}

