/*
COP3223 Spring 2023 Assignment 4_2
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Include standard input and output library 

int main() // // Function main begins program execution 
{
    int fahrenheit = 0; // Declare integer variable fahrenheit 
    float celsius = 0; // Declare float variable celcius 

    printf("Please enter the temperature in Fahrenheit: "); // Print desired text
    scanf("%d", &fahrenheit); // Ask for input for integer fahrenheit  

    celsius = 5.0 / 9.0 * (fahrenheit - 32); // Change Farenheit to Celcius

    printf("%-15s%s\n", "Fahrenheit", "Celsius"); // Print Fahrenheit and Celcius 
    printf("%-15d%+.3f\n", fahrenheit, celsius); // Print Fahrenheit and Celcius values 

    return 0; // Return 0
}

