/*
COP3223 Spring 2023 Assignment 1_1
Copyright 2023 Alex Reyes
*/

// Inlcude C Library
#include <stdio.h>

// Function main begins program execution 
int main()
{
	// Set the integer variables and then ask for input
	int integer1 = 0;
	int integer2 = 0;
	int integer3 = 0;

	printf("Enter three different integers: ");
	scanf_s("%d %d %d", &integer1, &integer2, &integer3);

	// Sum the 3 integers and then output the result
	int sum = 0;
	sum = integer1 + integer2 + integer3;
	printf("Sum is %0d \n", sum);

	// Grab the sum and divide it by the total of interger variables and then output the result
	int average = 0;
	average = (integer1 + integer2 + integer3) / 3;
	printf("Average is %0d \n", average);

	// Multiply the 3 integers and then output the result
	int product = 0;
	product = integer1 * integer2 * integer3;
	printf("Product is %0d \n", product);

	/* Use if else statement to compare the size of each indidual interger
	and find which value is smaller then output the result*/
	int smallest = 0;
	if (integer1 < integer2 && integer1 < integer3)
	{
		printf("Smallest is %0d \n", integer1);
	}
	else if (integer2 < integer3)
	{
		printf("Smallest is %0d \n", integer2);
	}
	else
	{
		printf("Smallest is %0d \n", integer3);
	}

	/* Use if else statement to compare the size of each indidual interger
	and find which value is larger then output the result*/
	int largest = 0;
	if (integer1 > integer2 && integer1 > integer3)
	{
		printf("Largest is %0d \n", integer1);
	}
	else if (integer2 > integer3)
	{
		printf("Largest is %0d \n", integer2);
	}
	else
	{
		printf("Largest is %0d \n", integer3);
	}

} // End function main


