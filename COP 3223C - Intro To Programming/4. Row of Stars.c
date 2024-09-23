/*
COP3223 Spring 2023 Assignment 2_1
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Inlcude standard input and output library 

int main() // Function main begins program execution 
{

    int number = 0; // declare variable number  
    int row = 0; // declare variable  row
    int column = 0; // declare variable column
    int count = 0; // declare variable  count

    printf("Please enter number of rows (odd nummber): "); // Print desired text for rows
    scanf_s("%d", &number); // Ask input for number of rows

    for (count = 0; count < 1;) // For loop to count if the number is odd
    {

        if (number % 2 == 0 || number > 19) // If statemnt to verify if the number is odd and less than 19
        {
            printf("Please enter number of rows (odd nummber): "); // Print desired text for rows
            scanf_s("%d", &number); // Ask input for number of rows
        }
        else // Else keep going with the program 
        {
            
            for (row = 1; row <= (number / 2) + 1; row++) // For loop to determine top shape of the diamond
            {
                for (column = 1; column <= number - row; column++) // For loop to allocate specific empty spaces
                {
                    printf(" "); // Print the empty spaces
                }
                for (column = 1; column <= 2 * row - 1; column++) // For loop to allocate specific asterisks spaces
                {
                    printf("*"); // Print the asterisks
                }
                printf("\n"); // Print next line
            }
            
            for (row = number / 2; row >= 1; row--) // For loop to determine bottom shape of the diamond
            {
                for (column = 1; column <= number - row; column++) // For loop to allocate specific empty spaces
                {
                    printf(" "); // Print the empty spaces
                }
                for (column = 1; column <= 2 * row - 1; column++) // For loop to allocate specific asterisks spaces
                {
                    printf("*"); // Print the asterisks
                }
                printf("\n"); // Print next line
            }

            count++; // Increment the count variable to end loop
        }
    }

} // End function main


