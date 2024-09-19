/*
COP3502C Fall 2023 Assignment 0 - Sign of Trouble
Copyright 2023 Alex Reyes
*/

#include <stdio.h> 
#include <string.h> 
#define MaxSize 1000

int get_spare_letters(char* old_sign, char* new_sign);

int main()
{
	char old_sign[MaxSize] = { 0 };
	char new_sign[MaxSize] = { 0 };

	int total_letters = 0;

	// Get The Input From USer
	fgets(old_sign, sizeof(old_sign), stdin);
	old_sign[strcspn(old_sign, "\n")] = '\0';

	fgets(new_sign, sizeof(new_sign), stdin);
	new_sign[strcspn(new_sign, "\n")] = '\0';

	// Get The Values For Each Total
	total_letters = get_spare_letters(old_sign, new_sign);

	printf("%d\n", total_letters);

	return 0; // Finish Program With No Errors 
}

int get_spare_letters(char* old_sign, char* new_sign) {
	int shared_letters = 0;
	int empty_slot = 0;
	int empty_spaces = 0;
	int total_letters = 0;
	int lenght_new_sign = 0;
	int x = 0;

	lenght_new_sign = strlen(new_sign);

	for (int i = 0; x < lenght_new_sign; i++) // Loop To Find What Characters Are The Same
	{

		if (old_sign[i] == ' ') // Help Runtime By Not Looping Empty Character
		{
			i++;
		}

		if (new_sign[x] == ' ') // Help Runtime By Not Looping Empty Character
		{
			x++;
			empty_spaces++;
		}

		if (old_sign[0] == new_sign[x]) // Condition For Equal Characters And Avoid Empty Spaces
		{
			old_sign[0] = ' ';
			new_sign[x] = ' ';
			shared_letters++;
			x++;
			i = 0;
		}

		if ((old_sign[i] == new_sign[x]) != (old_sign[i] == ' ' && new_sign[x] == ' ')) // Condition For Equal Characters And Avoid Empty Spaces
		{
			old_sign[i] = ' ';
			new_sign[x] = ' ';
			shared_letters++;
			x++;
			i = 0;
		}


		if (old_sign[i] == '\0') // If The End Of The String Was Reached Repeat
		{
			x++;
			i = 0;
		}

	}

	total_letters = lenght_new_sign - empty_spaces - shared_letters; // Calculate Value With String Length The Empty Spaces And The Shared Letters

	return total_letters;
}