#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 19
#define TABLESIZE 300007

//Global Variables
int complexity = 0;
int total_cash = 100000;

// Items Struct
typedef struct item {
	char name[MAXLEN + 1];
	int quantity;
	int saleprice;
} item;

// Link List Node
typedef struct node {
	item* iPtr;
	struct node* next;
} node;

// Hashtable Struct
typedef struct hashtable {
	node** lists;
	int size;
} hashtable;

// Functions To Handle The Hashtable
int hashfunc(char* word, int size);
void createHashtable(hashtable* table, int table_size);
void insertItem(hashtable* table, item* new_item);

// Functions To The Handle Data
int findItem(hashtable* table, char* name);
void modifyBuy(hashtable* table, char* name, int quantity, int total_price);
void modifySell(hashtable* table, char* name, int quantity);
void modifyChangePrice(hashtable* table, char* name, int saleprice);
void freeHashtable(hashtable* table);

int main() {
	// Create The Hashtable With The Specified Size
	hashtable* table = (hashtable*)malloc(sizeof(hashtable));

	// Initialize The Hashtable
	createHashtable(table, TABLESIZE);

	int found_item = 0;
	int index = 0;

	char item_name[MAXLEN + 1] = { 0 };
	int quantity = 0;
	int saleprice = 0;
	int total_price = 0;

	int processes = 0;
	char options[MAXLEN + 1] = { 0 };

	scanf("%d", &processes);

	// Create the amount of items 
	item* myItems = (item*)malloc(processes * sizeof(item));

	for (int counter = 1; counter <= processes; counter++) {
		scanf("%s", &options);

		// Buy Food
		if (strcmp(options, "buy") == 0) {
			scanf("%s", &item_name);

			scanf("%d", &quantity);

			scanf("%d", &total_price);

			found_item = findItem(table, item_name);

			// Find If the Item Is In The Hashtable
			if (found_item == 0) {
				strcpy(myItems[index].name, item_name);
				myItems[index].quantity = 0;
				myItems[index].saleprice = 1;

				// Create An Item And Insert It Into The Hashtable
				insertItem(table, &myItems[index]);

				modifyBuy(table, item_name, quantity, total_price);

				index++;
			} else {
				modifyBuy(table, item_name, quantity, total_price);
			}

		}

		// Sell Food
		if (strcmp(options, "sell") == 0) {
			scanf("%s", &item_name);

			scanf("%d", &quantity);

			modifySell(table, item_name, quantity);
		}

		// Change Price Of Food
		if (strcmp(options, "change_price") == 0) {
			scanf("%s", &item_name);

			scanf("%d", &saleprice);

			modifyChangePrice(table, item_name, saleprice);
		}

	}

	printf("%d\n", total_cash);
	printf("%d\n", complexity);

	free(table);

	return 0;
}

// Function For Hash Function
int hashfunc(char* word, int size) {
	int len = strlen(word);
	int res = 0;
	for (int i = 0; i < len; i++)
		res = (1151 * res + (word[i] - 'a')) % size;
	return res;
}

// Function To Initialize A Hashtable
void createHashtable(hashtable* table, int table_size) {
	table->size = table_size;
	table->lists = (node**)malloc(sizeof(node*) * table_size);
	for (int i = 0; i < table_size; i++)
		table->lists[i] = NULL;
}

// Function To Insert An Item Into The Hashtable
void insertItem(hashtable* table, item* new_item) {
	int index = hashfunc(new_item->name, table->size);

	node* new_node = (node*)malloc(sizeof(node));
	new_node->iPtr = new_item;
	new_node->next = table->lists[index];
	table->lists[index] = new_node;
}

// Function To Find If There Is Already A Node Of The Specific Item
int findItem(hashtable* table, char* name) {
	int index = hashfunc(name, table->size);

	int counter = 0;
	node* current = table->lists[index];

	while (current != NULL && strcmp(current->iPtr->name, name) != 0) {
		current = current->next;
		counter++;
	}

	if (current == NULL) {
		complexity = complexity + counter;
		return 0;
	}
	else {
		return 1;
	}
}

// Function To Modify Values When Buying 
void modifyBuy(hashtable* table, char* name, int quantity, int total_price) {
	int counter = 0;
	int index = hashfunc(name, table->size);

	node* current = table->lists[index];

	while (current != NULL && strcmp(current->iPtr->name, name) != 0) {
		current = current->next;
		counter++;
	}

	counter++;
	complexity = complexity + counter;

	current->iPtr->quantity = current->iPtr->quantity + quantity;

	total_cash = total_cash - total_price;

	printf("%s %d %d\n", current->iPtr->name, current->iPtr->quantity, total_cash);
}

// Function To Modify Values When Selling
void modifySell(hashtable* table, char* name, int quantity) {
	int counter = 0;
	int temp = 0;
	int index = hashfunc(name, table->size);

	node* current = table->lists[index];

	while (current != NULL && strcmp(current->iPtr->name, name) != 0) {
		current = current->next;
		counter++;
	}

	counter++;
	complexity = complexity + counter;

	temp = current->iPtr->quantity - quantity;

	if (temp < 0) {
		current->iPtr->quantity = (current->iPtr->quantity - quantity) - temp;
	} else {
		current->iPtr->quantity = current->iPtr->quantity - quantity;
	}

	if (temp < 0) {
		total_cash = total_cash + (current->iPtr->saleprice * (quantity + temp));
	} else {
		total_cash = total_cash + (current->iPtr->saleprice * quantity);
	}

	printf("%s %d %d\n", current->iPtr->name, current->iPtr->quantity, total_cash);
}

// Function To Modify Values When Changing Price
void modifyChangePrice(hashtable* table, char* name, int saleprice) {
	int counter = 0;
	int index = hashfunc(name, table->size);

	node* current = table->lists[index];

	while (current != NULL && strcmp(current->iPtr->name, name) != 0) {
		current = current->next;
		counter++;
	}

	counter++;
	complexity = complexity + counter;

	current->iPtr->saleprice = saleprice;
}

// Function To Free The Allocated Memory From The Hashtable
void freeHashtable(hashtable* table) {
	for (int i = 0; i < table->size; i++) {
		node* current = table->lists[i];

		while (current != NULL) {
			node* next = current->next;
			free(current->iPtr);
			free(current);
			current = next;
		}
	}

	free(table->lists); 
	free(table);
}