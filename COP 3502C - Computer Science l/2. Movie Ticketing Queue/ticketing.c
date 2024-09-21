/*
COP3502C Fall 2023 Assignment 2 - Movie Ticketing Queue 
Copyright 2023 Alex Reyes
*/

#include <stdio.h> // Include Standard Input And Output Library 
#include <stdlib.h> // Include Standard Memory Allocation Library
#include <string.h> // Include Standard Functuion Manipulataion For Strings And Arrays Library

struct List {
    Node* head, * tail;
};

struct Queue {
    List* lst;
};

struct Node {
    Node* nxt;
    int data;
};

int main()
{
    int customer_amount = 0;
    int booth_amount = 0;
    char name[20];

    scanf("%d", &customer_amount);
    scanf("%d", &booth_amount);
    scanf("%s", &name);

    printf("%d\n", customer_amount);
    printf("%d\n", booth_amount);
    printf("%s\n", name);

}