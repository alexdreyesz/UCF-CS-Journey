/*
COP3223 Spring 2023 Assignment 2_2
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Inlcude standard input and output library 
#include <stdlib.h> // Inlcude standard memory allocation/freeing functions library 
#include <time.h> // Inlcude standard access to time/date manipulation and formatting library

int main() // Function main begins program execution 
{
	int difficulty = 0; // Declare variable difficulty level
	int random_number_gen = 0; // Declare variable for random number value
	int guesses = 0; // Declare variable for number of guesses
	int guess_number = 0; // Declare variable for input guess number
	int play_again = 0; // Declare variable to play again

	do // Declare do while loop to decide to play again or not 
	{

		printf("Let's plan Guess the Number \n"); // Print desired text for game title 

		printf("Pick a difficulty level (1,2,3): "); // Print desired text for difficulty level
		scanf_s("%d", &difficulty); // Ask input for diffculty variable 


		switch (difficulty) // Switch stament for difficulty level 
		{
		case 1: // Difficulty level 1
			srand(time(NULL)); // Use of the computer's internal clock to control the choice of the seed
			random_number_gen = rand() % 10; // Difficuly 1 range to 2 digits
			if (random_number_gen == 0) // If random number is 0 increment it
			{
				random_number_gen = 1; // random number = 1
			}
			break; // Break loop

		case 2: // Difficulty level 2
			srand(time(NULL)); // Use of the computer's internal clock to control the choice of the seed
			random_number_gen = rand() % 100; // Difficuly 1 range to 3 digits
			if (random_number_gen == 0)// If random number is 0 increment it
			{
				random_number_gen = 1; // random number = 1
			}
			break; // Break loop

		case 3: // Difficulty level 3
			srand(time(NULL)); // Use of the computer's internal clock to control the choice of the seed
			random_number_gen = rand() % 1000; // Difficuly 1 range to 4 digits
			if (random_number_gen == 0) // If random number is 0 increment it
			{
				random_number_gen = 1; // random number = 1
			}
			break; // Break loop

		default: // Difficulty Unknown
			return 0; // Return 0;
		}

		//printf("%d \n", random_number_gen); // PRINT THE RANDOM NUMBER FOR EASY ACCESS 

		printf("I have my number. What's your guess? "); // Print desired text for random number

		for (guesses = 1; guesses <= 8; guesses++) // For loop to check number of guesses to a maximum of 8
		{
			
			scanf_s("%d", &guess_number); // Ask input for guess number variable

			if (guess_number < random_number_gen) // Check if guess number is less than random number
			{
				if (guesses <= 7)
				{
					printf("Too low: Guess again: "); // Print to low
				}
			}
			else if (guess_number > random_number_gen) // Check if guess number is greater than random number
			{
				if (guesses <= 7)
				{
					printf("Too high: Guess again: "); // Print to high
				}
			}
			else if (guess_number == random_number_gen) // Check if guess number is equal to random number
			{
				printf("You got it in %d guesses! \n", guesses); // Print number of tries
				break; // break to end loop
			}

		}

		if (guess_number != random_number_gen) // Check if guess number is not equal to random number
		{
			printf("Better luck next time \n"); // Print better luck next time
		}

		printf("Play Again? "); // Print want to play again 
		scanf_s("%d", &play_again); // Ask for input if they want to play again 1 for yes 0 or else for no 

	} while (play_again == 1); // While to keep looping if variable play_again equals 1

	return 0; // Return 0

} // End function main
