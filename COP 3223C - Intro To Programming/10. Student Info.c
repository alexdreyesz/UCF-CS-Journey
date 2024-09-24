/*
COP3223 Spring 2023 Assignment 4_1
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Include standard input and output library 
#include <string.h> // Include standard functuion manipulataion for strings and arrays library

struct students_info // Define a structure to represent students Info
{
    char first_name[20]; // Define structure character variable for first name 
    char last_name[20]; // Define structure character variable for last name 
    char ID[10]; // Define structure character variable for ID
    char grade; // Define structure character variable for grade
};

// Define the student info to create a student record 
struct students_info students_record[] = {

    {"John", "Johnson", "895645", 'A'}, // Define student record for John Johnson 
    {"Jake", "Michaelson", "236598", 'A'}, // Define student record for Jake Michaelson 
    {"Sally", "Weber", "225584", 'C'}, // Define student record for Sally Weber 
    {"Tou", "Xiong", "364875", 'B'}, // Define student record for Tou Xiong
    {"Jacquelyn", "Jackson", "984587", 'D'}, // Define student record for Jacquelyn Jackson
    {"John", "White", "560258", 'C'} // Define student record for John White
};

int main() // Function main begins program execution 
{
    int search_type = 0; // Declare integer variable for search type
    char search_string[20]; // Declare character variable for search string 
    int students_number = sizeof(students_record) / sizeof(students_record[0]); // Declare integer variable for number of students 

    printf("Please enter your search type: "); // Print desired text
    scanf("%d", &search_type); // Input for search type. 0 for first name, 1 for last name, and 2 for ID

    switch (search_type) // Switch for search type 
    {
    case 0: // If search type equal 0
        printf("Please enter the first name you want to search: "); // Print desired text 
        break; // Break switch statement  
    case 1: // If search type equal 1
        printf("Please enter the last name you want to search: "); // Print desired text 
        break; // Break switch statement
    case 2: // If search type equal 2
        printf("Please enter the ID you want to search: "); // Print desired text 
        break; // Break switch statement
    default: // If search type is default 
        printf("Wrong Search Type");
        return 1; // Return 1
    }

    scanf("%s", search_string); // Input for selected string type 


    for (int counter = 0; counter < students_number; counter++)  // Search for students that match the search string
    {
        struct students_info student = students_record[counter]; // Create new structure for each student
        char* search_field; // Character pointer for search field  

        switch (search_type) // Switch statement for search type
        {
        case 0: // If search type equal 0
            search_field = student.first_name; // search field equals to students first name 
            break;// Break switch statement
        case 1: // If search type equal 1
            search_field = student.last_name; // search field equals to students last name
            break;// Break switch statement
        case 2: // If search type equal 2
            search_field = student.ID; // search field equals to students ID
            break;// Break switch statement
        default: // If search type is default 
            printf("Wrong Search Type");
            return 1; // Return 1
        }

        if (strcmp(search_field, search_string) == 0) // Compare search field string with search string and if equal 0 then print results 
        {
            printf("Find the record name %s %s, id %s, grade %c\n", student.first_name, student.last_name, student.ID, student.grade); // Print the results that where found   
        }
    }

    return 0; // return 0
}