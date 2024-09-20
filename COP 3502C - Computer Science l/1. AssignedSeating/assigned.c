/*
COP3502C Fall 2023 Assignment 1 - Assigned Seating
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Include Standard Input And Output Library 
#include <stdlib.h> // Include Standard Memory Allocation Library
#include <string.h> // Include Standard Functuion Manipulataion For Strings And Arrays Library

struct Reservation // Struct For Reservation
{
    int start, end; // Start And End Of The Reservation
    char* name; // Name Of The Person Who Reserved This Range
};

struct Row // Struct For Row
{
    struct Reservation* array; // The Array Of Reservations
    int max_reservations; // The Spots In The Array
    int num_reservations; // Occupied Spots In The Array
};

struct Theater // Struct Theater
{
    struct Row* row; // The Array Of Rows In The Theater
};

struct Theater* initializeRow(int num_rows, int max_reservations_per_row) // Function To Initialize Row
{
    struct Theater* theater = malloc(sizeof(struct Theater));
    theater->row = malloc(num_rows * sizeof(struct Row));

}


void makePurchase(struct Theater* theater, int row_num, int start, int end, char* name) // Function To Make A Reservation
{
    if (row_num < 0 || row_num >= sizeof(theater->row) / sizeof(theater->row[0])) 
    {
        printf("FAILURE\n");
        return;
    }

    if (row_num < 0 || row_num >= sizeof(theater->row) / sizeof(theater->row[0]))
    {
        printf("SUCCESS\n");
    }

    else 
    {
        printf("FAILURE\n");
    }
}


void lookupReservations(struct Theater* theater, int row_num, int start, int end) // Function To LookUp Reservations For A Specific Seat Range
{
    if (row_num < 0 || row_num >= sizeof(theater->row) / sizeof(theater->row[0])) {
        printf("Invalid row number.\n");
    }
}

int main() 
{
    struct Theater* theater = initializeRow(5, 5); // Create A 2D Array For Theather 

    while (1) 
    {
        char option[10];
        printf("Select an Option BUY/LOOKUP/QUIT: ");
        scanf("%s", option);

        if (strcmp(option, "QUIT") == 0) // QUIT The Program
        {
            break; // Break The Loop
        }

        if (strcmp(option, "BUY") == 0) // Let The Customer BUY And Make A Purchase
        {
            int row, start, end;
            char name[20];

            printf("Row: ");
            scanf("%d", &row); // Ask Input For Start Of Row

            printf("Start: ");
            scanf("%d", &start); // Ask Input For Start Of column

            printf("End: ");
            scanf("%d", &end); // Ask Input For Start Of column

            printf("Name: ");
            scanf("%s", name); // Ask Input For Name

            makePurchase(theater, row - 1, start, end, name); // Make A Purchase Fuction
        }

        if (strcmp(option, "LOOKUP") == 0) // Let The Customer LOOKUP Who Reserved The Selected Spot
        {
            int row, start, end; // Reuse Variable To 0

            printf("Row: ");
            scanf("%d", &row); // Ask Input For Start Of Row

            printf("Start: ");
            scanf("%d", &start); // Ask Input For Start Of column

            printf("End: ");
            scanf("%d", &end); // Ask Input For End Of column

            lookupReservations(theater, row - 1, start, end); // Lookup A Reservation Fuction
        }
    }

    free(theater); // Free Theater Memory

    return 0; // Return 0 If There Is No Errors 
}