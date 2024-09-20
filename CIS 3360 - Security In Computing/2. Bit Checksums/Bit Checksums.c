/*============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
|					 checksum on an ASCII input file
|
| Author: Alex Reyes
| Language: c
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: c -> ./pa02 kX.txt pX.txt
|
| Where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: 10/12/2023
+===========================================================================*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TextLength 10000

char* binary_addition(char* binary_p1, char* binary_p2, int bit_size);
void char_to_binary(char checksum_input, char binary_representation[]);
char* binary_to_hex(const char* binary_string);
char* concatenate_strings(const char* strintg_first, const char* string_second);
void result_to_hex(char* checksum_input, int bit_size);
void lower_case(char* hex_word);


// Main function
int main(int argc, char** argv) {
    
    char checksum_input[TextLength] = { 0 };

    //////////////////////////////////////////////////////// Process The First File  ////////////////////////////////////////////////////////

    const char* file_name = argv[1];

    FILE* f_pointer = fopen(file_name, "r");
    
    if (f_pointer == NULL) {
        printf("Unable to open the file\n");
        return 1;
    }

    size_t bytes_read = fread(checksum_input, 1, sizeof(checksum_input) - 1, f_pointer);

    if (bytes_read == 0) {
        if (feof(f_pointer)) {
            printf("The end of the file was reached.\n");
        }
        else if (ferror(f_pointer)) {
            perror("There was an error while reading the file");
        }
    }

    fclose(f_pointer);

    //////////////////////////////////////////////////////// Process The Size Bit   ////////////////////////////////////////////////////////   

    int bit_size = atoi(argv[2]);

    if ((bit_size != 8) && (bit_size != 16) && (bit_size != 32)) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    //////////////////////////////////////////////////////// Process The Result To Hex   ////////////////////////////////////////////////////
  
    result_to_hex(checksum_input, bit_size);

	return 0; 
}

// Process The Binary Addition 
char* binary_addition(char* binary_p1, char* binary_p2, int bit_size) {
    int lenght_first = strlen(binary_p1);
    int lenght_second = strlen(binary_p2);

    int max_length = (lenght_first > lenght_second) ? lenght_first : lenght_second;

    char* result = (char*)malloc((max_length + 1) * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int carry = 0;
    int index = max_length;

    for (int i = lenght_first - 1, j = lenght_second - 1; i >= 0 || j >= 0; i--, j--) {
        int bit_1 = (i >= 0) ? (binary_p1[i] - '0') : 0;
        int bit_2 = (j >= 0) ? (binary_p2[j] - '0') : 0;

        int sum = bit_1 + bit_2 + carry;
        result[index] = (sum % 2) + '0';
        carry = sum / 2;

        index--;
    }

    char* result_final = (char*)malloc((max_length + 1) * sizeof(char));

    for (int i = 1; i < (bit_size + 1); i++) {

        result_final[i - 1] = result[i];

    }

    result_final[bit_size] = '\0';

    return result_final;

}


// Convert Character To Binary 
void char_to_binary(char checksum_input, char binary_representation[]) {
    for (int i = 7; i >= 0; i--) {
        binary_representation[7 - i] = ((checksum_input >> i) & 1) + '0'; 
    }
    binary_representation[8] = '\0'; 
}


// Convert Binary To Hexadecimal
char* binary_to_hex(const char* binary_string) {
    int binary_length = strlen(binary_string);

    int padded_length = (binary_length % 4 == 0) ? binary_length : binary_length + (4 - binary_length % 4);

    char* padded_binary = (char*)malloc((padded_length + 1) * sizeof(char));
    if (padded_binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < padded_length - binary_length; ++i) {
        padded_binary[i] = '0';
    }
    strcpy(padded_binary + (padded_length - binary_length), binary_string);
    padded_binary[padded_length] = '\0';

    int hex_length = padded_length / 4;

    char* hex_string = (char*)malloc((hex_length + 1) * sizeof(char));
    if (hex_string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < hex_length; ++i) {
        int decimal_value = 0;
        for (int j = 0; j < 4; ++j) {
            decimal_value = decimal_value * 2 + (padded_binary[i * 4 + j] - '0');
        }

        if (decimal_value < 10) {
            hex_string[i] = '0' + decimal_value;
        }
        else {
            hex_string[i] = 'A' + decimal_value - 10;
        }
    }
    hex_string[hex_length] = '\0';

    free(padded_binary);

    return hex_string;
}


// Mix Two Strings In One
char* concatenate_strings(const char* strintg_first, const char* string_second) {
    size_t lenght_first = strlen(strintg_first);
    size_t lenght_second = strlen(string_second);
    size_t lenght_total = lenght_first + lenght_second;

    char* result = (char*)malloc(lenght_total + 1);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }

    strcpy(result, strintg_first);
    strcat(result, string_second);

    return result;
}


// Calculate And Print The Results To The Screen
void result_to_hex(char* checksum_input, int bit_size) {

    char binary_first[100];
    char binary_second[100];
    char binary_third[100];
    char binary_fourth[100];
    char* binary_temporary_first;
    char* binary_temporary_second;
    char* binary_temporary_third;
    char* binary_temporary_fourth;
    char* binary_p1;
    char* binary_p2;
    char* result;
    char* result_summation = "00000000";
    char* result_hexadecimal;

    int i = 0;
    int missing = 0;
    int bumper = 0;
    int  next_line = 0;

    int string_length;
    string_length = strlen(checksum_input);

    //////////////////////////////////8 Bits////////////////////////////////////

    if (bit_size == 8) {

        string_length = strlen(checksum_input);

        for (int counter = 0; counter < string_length; counter += 2) {
            char_to_binary(checksum_input[counter], binary_first);
            char_to_binary(checksum_input[counter + 1], binary_second);

            binary_p1 = binary_first;
            binary_p2 = binary_second;

            result = binary_addition(binary_p1, binary_p2, bit_size);

            result_summation = binary_addition(result, result_summation, bit_size);
        }

        result_hexadecimal = binary_to_hex(result_summation);;

        next_line = 0;

        for (int counter = 0; counter < string_length; counter++) {

            fprintf(stdout, "%c", checksum_input[counter]);

            next_line++;

            if (next_line == 80) {
                fprintf(stdout, "\n");
                next_line = 0;
            }

        }

        lower_case(result_hexadecimal);

        fprintf(stdout, " %d bit checksum is       %s for all  %d chars", bit_size, result_hexadecimal, string_length);
    }


    //////////////////////////////////16 Bits///////////////////////////////////

    if (bit_size == 16) {

        if ((string_length % 2) != 0) {

            missing = 2 - (string_length % 2);

            for (i = 0; i < missing; i++) {
                checksum_input[string_length + i] = 'X';
            }

            checksum_input[string_length + i] = '\0';

        }

        string_length = strlen(checksum_input);

        for (int counter = 0; counter < string_length; counter += 4) {
            char_to_binary(checksum_input[counter], binary_first);
            char_to_binary(checksum_input[counter + 1], binary_second);

            binary_p1 = concatenate_strings(binary_first, binary_second);

            char_to_binary(checksum_input[counter + 2], binary_first);
            char_to_binary(checksum_input[counter + 3], binary_second);

            binary_p2 = concatenate_strings(binary_first, binary_second);

            result = binary_addition(binary_p1, binary_p2, bit_size);

            result_summation = binary_addition(result, result_summation, bit_size);
        }

        result_hexadecimal = binary_to_hex(result_summation);

        next_line = 0;

        for (int counter = 0; counter < string_length; counter++) {

            fprintf(stdout, "%c", checksum_input[counter]);

            next_line++;

            if (next_line == 80) {
                fprintf(stdout, "\n");
                next_line = 0;
            }

        }

        if (checksum_input[string_length - 1] == 'X') {
            fprintf(stdout, "\n");
        }

        lower_case(result_hexadecimal);

        fprintf(stdout, " %d bit checksum is       %s for all  %d chars", bit_size, result_hexadecimal, string_length);
    }


    //////////////////////////////////32 Bits///////////////////////////////////

    if (bit_size == 32) {

        if ((string_length % 4) != 0) {

            missing = 4 - (string_length % 4);

            for (i = 0; i < missing; i++) {
                checksum_input[string_length + i] = 'X';
            }

            checksum_input[string_length + i] = '\0';

        }

        string_length = strlen(checksum_input);

        for (int counter = 0; counter < string_length; counter += 8) {
            char_to_binary(checksum_input[counter], binary_first);
            char_to_binary(checksum_input[counter + 1], binary_second);
            char_to_binary(checksum_input[counter + 2], binary_third);
            char_to_binary(checksum_input[counter + 3], binary_fourth);


            binary_temporary_first = concatenate_strings(binary_first, binary_second);
            binary_temporary_second = concatenate_strings(binary_third, binary_fourth);
            binary_temporary_third = concatenate_strings(binary_temporary_first, binary_temporary_second);

            bumper += 8;

            if (bumper <= string_length && string_length > 4) {
                char_to_binary(checksum_input[counter + 4], binary_first);
                char_to_binary(checksum_input[counter + 5], binary_second);
                char_to_binary(checksum_input[counter + 6], binary_third);
                char_to_binary(checksum_input[counter + 7], binary_fourth);


                binary_temporary_first = concatenate_strings(binary_first, binary_second);
                binary_temporary_second = concatenate_strings(binary_third, binary_fourth);
                binary_temporary_fourth = concatenate_strings(binary_temporary_first, binary_temporary_second);

            }
            else {
                binary_temporary_fourth = "00000000000000000000000000000000";
            }

            result = binary_addition(binary_temporary_third, binary_temporary_fourth, bit_size);

            result_summation = binary_addition(result, result_summation, bit_size);
        }

        result_hexadecimal = binary_to_hex(result_summation);

        next_line = 0;

        for (int counter = 0; counter < string_length; counter++) {

            fprintf(stdout, "%c", checksum_input[counter]);

            next_line++;

            if (next_line == 80) {
                fprintf(stdout, "\n");
                next_line = 0;
            }

        }

        if (checksum_input[string_length - 1] == 'X') {
            fprintf(stdout, "\n");
        }

        lower_case(result_hexadecimal);

        fprintf(stdout, " %d bit checksum is       %s for all  %d chars", bit_size, result_hexadecimal, string_length);
    }


}


// Lower Case Hexadecimal Values 
void lower_case(char* hex_word) {

    int string_lenght = strlen(hex_word);

    for (int counter = 0; counter < string_lenght; counter++) {

        if (hex_word[counter] >= 'A' && hex_word[counter] <= 'Z') {

            hex_word[counter] = hex_word[counter] + 32;
        }

    }

}


/*=============================================================================
| I Alex Reyes 5505625 affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/