/*
COP3223 Spring 2023 Assignment 1_2
Copyright 2023 Alex Reyes
*/

// Include C library
#include <stdio.h>

// Function main begins program execution 
int main()
{
	// Create the starting integer variable
	int hours_worked = 0;

	// Use a while loop to ask for multiple inputs and use -1 as an ending loop condition
	while (hours_worked != -1)
	{
		// Ask for input for hours worked 
		printf("Enter # of hours worked (-1 to end): ");
		scanf_s("%d", &hours_worked);

		// If hours worked equals loop ending condition return 0
		if (hours_worked == -1)
		{
			return 0;
		}
		else // Else proceeed with the statement 
		{
			// Assign float variables for future use
			float salary = 0;
			float hourly_rate = 0;

			//Ask for input for hourly rate
			printf("Enter hourly rate of the worker ($00.00): ");
			scanf_s("%e", &hourly_rate);

			//for statement to sum the each hour worked and the hourly salary
			for (int counter = 1; counter <= hours_worked; ++counter)
			{
				// if statement to find values below and equal to 40 hours
				if (counter <= 40)
				{
					salary = salary + hourly_rate;
				}
				else // else for overtime on worked hours over 40 hours
				{
					salary = salary + (hourly_rate * 1.5);
				}
			}
			// Output the salary
			printf("Salary is %.2f \n \n", salary);

		}
	}

} // End function main
