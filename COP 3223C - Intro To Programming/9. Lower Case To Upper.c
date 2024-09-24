#include <stdio.h> // Include standard input and output library 
#include <string.h> // Include standard string handling and memory handling library 
#include <ctype.h> // Include standard input and output library 

void print_upper_case(char *text); // Function declaration for print upper case
void reverse_string(char *text); // Function declaration for reverse string
void each_word(char *text); // Function declaration for each word
int count_words(char *text); // Function declaration for count words

int main()
{
    char text[100]; // Declare cariable text
    char word_amount[100]; // Declare variable word amount 

    printf("Enter a line of text: \n"); // Print the desired text 

    fgets(text, 100, stdin);

    strcpy(word_amount, text); // Use strcpy to store text value in word amount to later calculate the amount of words in the string

    printf("=====Change the string to upper case=====\n"); // Print desired text
    print_upper_case(text); // use fuction print upper case to uppercase each character 

    printf("=====Reverse string====="); // Print desired text
    reverse_string(text); // Use fuction reverse string with text to reverse the string  

    printf("\n=====Print the tokens=====\n"); // Print desired text
    each_word(text); // Use fuction each word with text to print each individual word in separete lines 

    printf("There are %d words in the input text", count_words(word_amount)); // Print and use fuction count words to count the amount of words in the string 

    return 0; // Return 0
}


void print_upper_case(char *text) // Function definition for function print upper case to print a stiring in upper case
{
    int lenght = strlen(text); // Declare vairable for lenght with fuction string lenght to determine the string length of text

    for (int counter = 0; counter < lenght; counter++) // For loop with lenght character to upper case all characters and rewrite original text 
    {
        for (int counter = 0; text[counter] != '\0'; counter++)
        {
            if (text[counter] >= 'a' && text[counter] <= 'z')
            {
                text[counter] = text[counter] - 'a' + 'A';
            }
        }
    }

    printf("%s", text);
}

void reverse_string(char *text) // Function definition for function reverse string to reverse easch word and letter of a string 
{
    int lenght = strlen(text); // Declare vairable for lenght with fuction string lenght to determine the string length of text

    for (int counter = lenght - 1; counter >= 0; counter--) // For loop with lenght character to reverse string  
    {
        putchar(text[counter]); // Print all character 
    }
}

void each_word(char *text) // Function definition for each word to print each word in a separate line 
{
    char *token = strtok(text, " "); // Declare vairable token with string tokenization function of text and " "
   
    while (token) // While loop until token equals null
    {
        printf("%s\n", token); // Print each word
        token = strtok(NULL, " "); // Search until token equals null
    }
}

int count_words(char *text) // Function definition for count words to count how many words are int the string 
{
    int counter = 0; // Declare vairable counter 
    char *token = strtok(text, " "); // Declare vairable token with string tokenization function of text and " "

    while (token != NULL) // While loop for token is not equal to null
    {
        counter++; // Increment token 
        token = strtok(NULL, " "); // Search until token equals null 
    }

    return counter; // Return counter
}