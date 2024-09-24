/*
COP3223 Spring 2023 Assignment 3_1
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Inlcude standard input and output library
#include <string.h> // Include standard String library
#include <stdlib.h> // Inlcude standard memory allocation/freeing functions library 
#include <time.h> // Inlcude standard access to time/date manipulation and formatting library

#define BOLD "\x1B[1m" //Bold Text Formula
#define RESET "\x1B[0m" //Reset Formula

int costumer_number(int plane_section, int first_class_amount, int economy_class_amount, int plane_amount); // Declare function search costumer number
int print_boarding_pass(int plane_section, int assigned_seat); // Declare function for print boarding pass
int search_seat(int plane_section); // Declare function search seat 


int main() // Function main begins program execution 
{
    int plane_seats[6] = {0}; // Declare array plane seats
    int plane_section = 0; // Declare variable plane section
    int assigned_seat = 0; // Declare variable assigned seat
    int everyone_boarded = 0; // Declare vairable everyone boarded 
    int change_seat = 0; // // Declare vairable change seat
    int first_class_amount = 0; // Declare variable first class amount
    int economy_class_amount = 0; // Declare variable economy class amount 
    int plane_amount = 0; // Declare variable plane amount 

    while(everyone_boarded != 1) // If everyone boarded the plane then input 1  
    {
        int no_boarding = 0; // Declare variable no boarding and set it to 0 every loop 

        printf("Please type 1 for \"first class\" \n"); // Print desired text
        printf("Please type 2 for \"economy\" \n"); // Print desired text
        scanf_s("%d", &plane_section); // Input plane section

        if ((plane_amount) >= 6) // If plane amount greather or equal to 6 plane is full but more people are checking in  
        {
            plane_amount++; // increment plane amount  
        }

        if (plane_section == 1) // If plane section equals 1 then is first class
        {
            first_class_amount++; // Increment first class 
        }

        if (plane_section == 2) // If plane section equals 2 then is economy class
        {
            economy_class_amount++; // Increment economy class 
        }

        costumer_number(plane_section, first_class_amount, economy_class_amount, plane_amount); // Use fuction costumer number to see his number in the line

        for (int counter = 0; counter < 1;) // For loop to assign an appropiate seat in the plane
        {
            assigned_seat = search_seat(plane_section); // Assign seat in the appropiate plane section

            if (plane_amount == 7) // If plane is full then no more seats available 
            {
                printf("Next flight leaves in 3 hours \n"); // Print desired text

                no_boarding++; // Increment no boarding 

                break; // Break loop
            }

            if(plane_section == 1 && (plane_seats[0] + plane_seats[1] + plane_seats[2]) == 3) // If first class is full ask if they want economy
            {
                if (plane_section == 1 && (plane_seats[3] + plane_seats[4] + plane_seats[5]) == 3)// If all seats are taken then plane is full
                {
                    printf("Next flight leaves in 3 hours \n"); // Print desired text

                    no_boarding++; // Increment no boarding 

                    break; // Break loop
                }

                printf("no seat available first class, do you want a seat in economy class? "); // Print desired text
                scanf_s("%d", &change_seat); // Input change seat

                if (change_seat == 0) // If input is 0 then no change in seat 
                {
                    printf("Next flight leaves in 3 hours \n"); // Print desired text

                    no_boarding++; // Increment no boarding 

                    break; // Break loop
                }

                if (change_seat == 1) // If input is 1 then change seat 
                {
                    plane_section = 2; // Change plane section to economy
                }
            }

            if(plane_section == 2 && (plane_seats[3] + plane_seats[4] + plane_seats[5]) == 3) // If economy class is full ask if they want first class
            {
                if (plane_section == 2 && (plane_seats[0] + plane_seats[1] + plane_seats[2]) == 3) // If all seats are taken then plane is full
                {
                    printf("Next flight leaves in 3 hours \n"); // Print desired text

                    no_boarding++; // Increment no boarding 

                    break; // Break loop
                }

                printf("no seat available economy, do you want a seat in first class? "); // Print desired text
                scanf_s("%d", &change_seat); // Input change seat

                if(change_seat == 0) // If input is 0 then no change in seat 
                {
                    printf("Next flight leaves in 3 hours \n"); // Print desired text 

                    no_boarding++; // Increment no boarding 

                    break; // Break loop
                }

                if(change_seat == 1) // If input is 1 then change seat 
                {
                    plane_section = 1; // Change plane section to first class 
                }
            }

            if (plane_seats[assigned_seat - 1] == 0) // If plane seats are not taken then assaign seat 
            {
                counter++; // Increment counter to exit loop
            }
        }

        if (no_boarding == 0) // If no boarding equals 1 then the person didn't board the plane   
        {
            plane_amount = plane_seats[0] + plane_seats[1] + plane_seats[2] + plane_seats[3] + plane_seats[4] + plane_seats[5] + 1; // Count how many people are in the plane 
            print_boarding_pass(plane_section, assigned_seat); // Use fuction print boarding pass 
            plane_seats[assigned_seat - 1] = 1; // Set plane seat to 1 if seat is already taken 
        }

        printf("Does everyone boarded? "); // Print desired text
        scanf_s("%d", &everyone_boarded); // Ask for input if everyone boarded 
        printf("\n"); // Print new line 
    }
} // End function main

int costumer_number(int plane_section, int first_class_amount, int economy_class_amount, int plane_amount) // Function definition for costumer number 
{
    char costumer_position[6][6] = {"First","2nd","3rd","4th","5th","6th"};  // Declare character costumer position
    char first_class[] = "customer with first class"; // Declare character first class 
    char economy_class[] = "customer with economy class"; // Declare character economy_class
    char first_no_seats[]  = ", no seat available in first class, ask if he/she want seat in economy class"; // Declare character first class no seats
    char economy_no_seats[] = ", no seat available in economy, ask if he/she want seat in first class"; // Declare character economy no seats
    char first_full[] = ", as one economy passenger take first class seat, no first class seat available"; // Declare character first full
    char economy_full[] = ", as one first class passenger take economy seat, no economy seat available"; // Declare character economy full
    char plane_full[] = ", all seats are book, no seat available"; // Declare character plane full
     
    if (plane_section == 1) // If plane section is 1 then is first class
    {
        if (first_class_amount <= 3 && !(plane_amount >= 7))// If Statement to print costumer number
        {
            printf("%s(%s %s)%s\n", BOLD, costumer_position[first_class_amount - 1], first_class, RESET); // Print costumer number information for first class
        }

        if (first_class_amount >= 4 && !(plane_amount >= 7))// If Statement to print costumer number
        {
            printf("%s(%s %s%s)%s\n", BOLD, costumer_position[first_class_amount - 1], first_class, first_no_seats, RESET); // Print costumer number information for first class
        }
        
        if(plane_amount == 7 && economy_class_amount >= 4)// If Statement to print if seat was taken by another person
        {
            printf("%s(%s %s%s)%s\n", BOLD, costumer_position[first_class_amount - 1], first_class, first_full, RESET); // Print costumer number information for first class
        }

        if(plane_amount >= 8) // If plane amount equals 7 then plane is full
        {
            printf("%s(%s %s%s)%s\n", BOLD, costumer_position[first_class_amount - 1], first_class, plane_full, RESET); // Print costumer number information for first class
        }
    } 
    
    if (plane_section == 2) // If plane section is 2 then is economy class
    {
        if (economy_class_amount <= 3 && !(plane_amount >= 7)) // If Statement to print costumer number
        {
            printf("%s(%s %s)%s \n", BOLD, costumer_position[economy_class_amount - 1], economy_class, RESET); // Print costumer number information for economy class
        }

        if (economy_class_amount >= 4 && !(plane_amount >= 7)) // If Statement to print costumer number
        {
            printf("%s(%s %s%s)%s \n", BOLD, costumer_position[economy_class_amount - 1], economy_class, economy_no_seats, RESET); // Print costumer number information for economy class
        }

        if (plane_amount == 7 && first_class_amount >= 4) // If Statement to print if seat was taken by another person
        {
            printf("%s(%s %s%s)%s \n", BOLD, costumer_position[economy_class_amount - 1], economy_class, economy_full, RESET); // Print costumer number information for economy class
        }

        if (plane_amount >= 8) // If plane amount equals 7 then plane is full
        {
            printf("%s(%s %s%s)%s \n", BOLD, costumer_position[economy_class_amount - 1], economy_class, plane_full, RESET); // Print costumer number information for economy class
        }
    }
}

int print_boarding_pass(int plane_section, int assigned_seat) // Function definition for print boarding pass
{
    if (plane_section == 1) // If plane section is 1 then is first class
    {
        printf("Your seat is assigned to first class seat %d \n", assigned_seat); // Print boarding pass information for first class
    }

    if (plane_section == 2) // If plane section is 2 then is economy class
    {
        printf("Your seat is assigned to economy seat %d \n", assigned_seat); // Print boarding pass information for economy class
    }
}


int search_seat(int plane_section) // Function definition for search seat
{
    int first_lower = 1, first_upper = 3; // Declare variables for first class range number of seats
    int economy_lower = 4, economy_upper = 6; // Declare variables for first economy range number of seats

    if (plane_section == 1) // If plane section is 1 then is first class assign random number
    {
        srand(time(NULL)); // Use of the computer's internal clock to control the choice of the seed
        plane_section = (rand() % (first_upper - first_lower + 1)) + first_lower; // Generate random number range 1 to 3
        return plane_section;// Return variable x random seat as search seat
    }

    if (plane_section == 2) // If plane section is 2 then is economy class assign random number
    {
        srand(time(NULL)); // Use of the computer's internal clock to control the choice of the seed
        plane_section = (rand() % (economy_upper - economy_lower + 1)) + economy_lower; // Generate random number range 4 to 6
        return plane_section; // Return variable x random seat as search seat
    }
}