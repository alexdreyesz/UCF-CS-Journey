/*
COP3223 Spring 2023 Assignment 2_3
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Inlcude standard input and output library 

int gcd(int, int); // Declare function gcd


int main()	// Function main begins program execution 
{

	int x = 0;	// Declare variable x
	int y = 0;  // Declare  variable y

	printf("Please input the first number : "); // Ask input for x
	scanf_s("%d", &x); // Input x

	printf("Please input the second number : "); // Ask input for y
	scanf_s("%d", &y); // Input y

	gcd(x, y); // Initialize gcd function
	
	printf("The commom divisor for %d and %d is %d ", x, y, gcd(x, y)); // Print x, y, and gcd(x,y)  

} // End function main


int gcd(int x, int y) // Fucntion definition for gcd
{
	if (x == 0) // If x equal 0 return y
	{
		return y; // return y
	}
	
	if (y == 0) // If y equal 0 return x
	{
		return x; // return x
	}

	if (x > y) // Fuction calling to see if x is greater than y if so return gcd  (x = x % y) and (y)
	{
		return gcd(x % y, y); //  return gcd  (x = x % y) and (y)
	}
	else // Function calling to see if y is less than x if so return gcd (y = y % x) and (x)
	{
		return gcd(x, y % x); // return gcd (y = y % x) and (x)
	}
}