/*
COP3223 Spring 2023 Assignment 3_2
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Include standard input and output library 
#include <stdlib.h> // Include standard information of memory allocation/freeing functions library

int init_array(int *array, int size); // Declare function initialize array
int search_array(int *array, int size, int search_number); // Declare fuction search array
int print_array(int *array, int size); // Declare function print array


int main() // Function main begins program execution  
{
    int size = 0; // Declare variable 
    int search_number = 0; // Declare variable search number
    int result = 0; // Declare variable result
    int *array = 0; // Declare variable pointer array
    
    printf("Please enter the size of the array: "); // Ask user to input the size of the array to create the dynamic array
    scanf_s("%d", &size); // Input size 

    array = (int*)malloc(size *sizeof(int)); // Allocate memory for the dynamic array

    init_array(array, size); // Ask user to input the numbers to initialize the array

    print_array(array, size); // Print array values 

    printf("What number you want to check: "); // Ask user to input the search number
    scanf_s("%d", &search_number); // Input search number  

    result = search_array(array, size, search_number); // Search for the number in the array

    if (result != -1) // If result is not equal to -1 then number the was found
    {
        printf("Find number %d array[%d] \n", search_number, result); // Print search number and result 
    }
    else // If result is something else than -1 then the number was not found
    {
        printf("%d not found in the array\n", search_number); // Print failed to find searched number 
    }

    free(array); // Free the memory allocated for the dynamic array

    return 0; // Return 0;
} // End function main

int init_array(int *array, int size) // Function definition for initialize array to nitialize the dynamic array
{
    for (int counter = 0; counter < size; counter++) // For loop to initialize array with the provided size 
    {
        printf("Please enter the array element: "); // Print asking for input for elements  
        scanf_s("%d", &array[counter]); // Input initialize array 
    }
}

int print_array(int *array, int size) // Function definition for print array to print all elements
{
    for (int counter = 0; counter < size; counter++) // For loop print all elements with the provided size
    {
        printf("Element: %d = %d \n", counter, array[counter]); // Print all array numbers and element values 
    }
}

int search_array(int *array, int size, int search_number) // Search the number in the array
{
    for (int counter = 0; counter < size; counter++) // For loop to search all the arrays with the provided size
    {
        if (array[counter] == search_number) // If an element of an array index equals search number then is true
        {
            return counter; // Return the index of the search number
        }
    }

    return -1; // return -1 if the search number is not found
}