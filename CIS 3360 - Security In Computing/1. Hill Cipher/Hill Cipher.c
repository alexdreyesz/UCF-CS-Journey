/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Alex Reyes
| Language: c
|
| To Compile: gcc -o pa01 pa01.c 
|
| To Execute: c -> ./pa01 kX.txt pX.txt
|
| Where kX.txt is the keytext file and pX.txt is plaintext file
|
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: 10/08/2023
+===========================================================================*/

#include <stdio.h> // Include the standard library 
#include <stdlib.h> // Include the library for dynamic memory allocation
#include <string.h> // Include the string library 
#define TextLength 10000 // Define a static lenght for the text lenght

void modify_string(int matrix_initialize, char* plain_text);
void string_to_number(char* plain_text, int* plain_text_cypher_number);
void cypher_hill_conversion(int matrix_initialize, int matrix_size, char* plain_text, int* final_cypher, int* plain_text_cypher_number, int* matrix_chart);
void number_to_string(int plain_text_lenght, int* final_cypher, char* cipher_text);

int main( int argc, char** argv) {

    int matrix_initialize = 0; // Variable for matrix size initializer 
    int matrix_size = 0; // Variable to set the matrix grid size with matrix_initialize variable

    char plain_text[TextLength];
    size_t plain_text_lenght = 0;
    char cipher_text[TextLength];
    int plain_text_cypher_number[TextLength] = { 0 };
    int final_cypher[TextLength] = { 0 };

    FILE* f_pointer;
    char* file_name;
    int* numbers = NULL; // Initialize the pointer to NULL



    //////////////////////////////////////////////////////// Process The First File (k#.txt)  ////////////////////////////////////////////////////////

    file_name = argv[1];
    f_pointer = fopen(file_name, "r");
    if (f_pointer == NULL) {
        printf("Unable to open the file k1.txt.\n");
        return 1;
    }

    int num;
    int capacity = 10;
    int size = 0;
    numbers = malloc(capacity * sizeof(int));

    if (numbers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    while (fscanf(f_pointer, "%d", &num) != EOF) {
        if (size == capacity) {
            capacity *= 2;
            numbers = realloc(numbers, capacity * sizeof(int));

            if (numbers == NULL) {
                printf("Memory reallocation failed.\n");
                return 1;
            }
        }

        numbers[size] = num;
        size++;
    }

    matrix_initialize = numbers[0];

    matrix_size = matrix_initialize * matrix_initialize; // Set the matrix grid size

    int* matrix_chart = (int*)malloc(matrix_size * sizeof(int)); // Dynamically allocate memory for matrix_chart

    if (matrix_chart == NULL) { // If dynamically memory allocation fail return error code
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int counter = 0; counter < matrix_size; counter++) {
            matrix_chart[counter] = numbers[counter + 1];
    }

    free(numbers);
    fclose(f_pointer);


    //////////////////////////////////////////////////////// Process The Second File (p#.txt)  //////////////////////////////////////////////////////// 

    file_name = argv[2];
    f_pointer = fopen(file_name, "r");
    if (f_pointer == NULL) {
        printf("Unable to open the file p1.txt.\n");
        return 1;
    }

    size_t num_bytes_read = fread(plain_text, 1, sizeof(plain_text), f_pointer);

    if (num_bytes_read == 0) {
        printf("Failed to read file p1.txt.\n");
        return 1;
    }

    plain_text[num_bytes_read] = '\0';

    fclose(f_pointer);


    //////////////////////////////////////////////////////// Process The Hill Cipher Calculations  ////////////////////////////////////////////////////////

    modify_string(matrix_initialize, plain_text);

    plain_text_lenght = strlen(plain_text);

    string_to_number(plain_text, plain_text_cypher_number);

    cypher_hill_conversion(matrix_initialize, matrix_size, plain_text, final_cypher, plain_text_cypher_number, matrix_chart);

    number_to_string(plain_text_lenght, final_cypher, cipher_text);

    
    //////////////////////////////////////////////////////// Print The Corresponding Values  ///////////////////////////////////////////////////////////////

    printf("Key matrix: \n");
    
    int i = 0;
    int j = 0;

    for (int i = 0; i < matrix_size; i++) {

        printf("%3d ", matrix_chart[i]);

        j++;

        if (j == matrix_initialize) {
            printf("\n");
            j = 0;
        }

    }

    printf("\n");
    
    int next_line = 0;

    printf("Plaintext: \n");

    for (int counter = 0; counter < plain_text_lenght; counter++) {
        
        printf("%c", plain_text[counter]);
        
        next_line++;

        if (next_line == 80) {
            printf("\n");
            next_line = 0;
        }

    }

    printf("\n \n");

    next_line = 0;

    printf("Ciphertext: \n");

    for (int counter = 0; counter < plain_text_lenght; counter++) {

        printf("%c", cipher_text[counter]);

        next_line++;

        if (next_line == 80) {
            printf("\n");
            next_line = 0;
        }

    }

    printf("\n \n");

    free(matrix_chart); // Free matrix_chart allocated memory

    return 0; // Return 0 if the project didn't failed
}


void modify_string(int matrix_initialize, char* plain_text) { // Function to modify the plain text string to lower case character, remove special characters and add the corresponding padding

    int plain_text_lenght = strlen(plain_text);

    int counter = 0;
    int recipient = 0;

    for (int counter = 0; counter < plain_text_lenght; counter++) {

        if ((plain_text[counter] >= 'A' && plain_text[counter] <= 'Z') || (plain_text[counter] >= 'a' && plain_text[counter] <= 'z')) {

            plain_text[recipient] = plain_text[counter];
            recipient++;
        }

    }

    plain_text[recipient] = '\0';

    plain_text_lenght = strlen(plain_text);

    for (int counter = 0; counter < plain_text_lenght; counter++) {

        if (plain_text[counter] >= 'A' && plain_text[counter] <= 'Z') {

            plain_text[counter] = plain_text[counter] + 32;
        }

    }

    int i = 0;
    int missing = 0;

    if ((plain_text_lenght % matrix_initialize) != 0) {

        missing = matrix_initialize - (plain_text_lenght % matrix_initialize);

        for (i = 0; i < missing; i++) {

            plain_text[plain_text_lenght + i] = 'x';
        }

        plain_text[plain_text_lenght + i] = '\0';

    }

}


void string_to_number(char* plain_text, int* plain_text_cypher_number) { // Function to transform the string plain text character to integer values  

    int i = 0;

    int plain_text_lenght = strlen(plain_text);

    for (int i = 0; i < plain_text_lenght; i++) {
        plain_text_cypher_number[i] = plain_text[i] - 97;
    }

}


void cypher_hill_conversion(int matrix_initialize, int matrix_size, char* plain_text, int* final_cypher, int* plain_text_cypher_number, int* matrix_chart) { // Function to perform the hill cipher conversion with the plain text cipher value and the matrix values 

    int x = 0;
    int j = 0;
    int counter_chart = 0;
    int counter_text = 0;
    int counter_matrix = 0;

    int plain_text_lenght = strlen(plain_text);

    for (x = 0; x < plain_text_lenght; x++) {


        for (j = 0; j < matrix_initialize;) {

            final_cypher[x] = final_cypher[x] + (matrix_chart[j + counter_chart] * plain_text_cypher_number[j + counter_text]);
            j++;
        }

        final_cypher[x] = final_cypher[x] % 26;

        counter_chart = counter_chart + matrix_initialize;

        counter_matrix++;

        if (counter_matrix >= matrix_initialize) {
            counter_text = counter_text + matrix_initialize;
            counter_matrix = 0;
        }

        if (counter_chart >= matrix_size) {
            counter_chart = 0;
        }


    }

}


void number_to_string(int plain_text_lenght, int* final_cypher, char* cipher_text) { // Fuction to trasform integer values from the cipher integer to character values to form a string for the final cipher result

    int i = 0;
    int alphabet = 26;
    char cypher_character[26];

    for (int counter = 0; counter < alphabet; counter++) {

        cypher_character[counter] = ('A' + 32) + counter;

    }

    for (int i = 0; i < plain_text_lenght; i++) {

        cipher_text[i] = cypher_character[final_cypher[i]];
    }

    cipher_text[plain_text_lenght + i] = '\0';

}


/*=============================================================================
| I Alex Reyes 5505625 affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/