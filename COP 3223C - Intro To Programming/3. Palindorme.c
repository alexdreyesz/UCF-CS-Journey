/*
COP3223 Spring 2023 Assignment 1_3
Copyright 2023 Alex Reyes
*/

// Include C library
#include <stdio.h>

// Function main begins program execution 
int main() 
{
    // for statement to create 2 palindrome searches
    for (int counter = 1; counter <= 2; ++counter)
    {
        // Create the intial integer variables 
        int number = 0;
        int original = 0;
        int remainder = 0;
        int mirrored = 0;

        // Ask for input on the desire number and then set it to the default original value
        printf("Please enter a five digit integer: ");
        scanf_s("%d", &number);
        original = number;

        // While loop to find that the reminder is not 0
        while (number != 0) {
            /* Equation to get the remainderand of the integer to use 
            its properties to mirror the integer variable */
            remainder = number % 10;
            mirrored = mirrored * 10 + remainder;
            number = (number / 10);
        }

        /* if statement to find if original variable equals the mirrored variable,
        this will tell us if both variables are a palindrome of each other. Therefore, if false 
        then their are not a palindrome of each other. At last output the result*/
        if (original == mirrored)
            printf("%d is a palindrome. \n \n", original);
        else
            printf("%d is not a palindrome. \n \n", original);
        
    }
} // End function main
