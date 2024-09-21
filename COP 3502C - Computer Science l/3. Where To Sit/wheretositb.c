#include <stdio.h>
#include <string.h>

#define MAX_PEOPLE 10
#define MAX_NAME_LENGTH 20

void popcorn_case(int people_amount, int* popcorn_who);
void dislike_case(int people_dislike, int* dislike_chart, int* order);
void printPerm(int* perm, int n);
void permute(int n, int* perm, int* used, int index, int* popcorn_who, int people_amount, int* dislike_chart, int people_dislike);

int count = 0;
int popcorn_who[MAX_PEOPLE];
int people_amount = 0;
int people_dislike = 0;
char name[MAX_NAME_LENGTH];
char name_list[MAX_PEOPLE][MAX_NAME_LENGTH];
int dislike_chart[MAX_PEOPLE][MAX_PEOPLE] = { 0 };

int order[MAX_PEOPLE];
int order_dislike[MAX_PEOPLE];
char name_dislike[MAX_NAME_LENGTH];
char name_list_dislike[MAX_PEOPLE][MAX_NAME_LENGTH];

int main() {

    int index = 0;

    printf("Enter the number of people: ");
    scanf("%d", &people_amount);

    printf("Enter the number of people that dislike each other: ");
    scanf("%d", &people_dislike);

    people_dislike = people_dislike * 2;
    printf("%d \n", people_dislike);


    if (people_amount > MAX_PEOPLE) {
        printf("Too many people! Maximum allowed is %d\n", MAX_PEOPLE);
        return 1;  // Exit with an error code
    }

    for (int index = 0; index < people_amount; index++) {
        printf("Enter the name for person %d: ", (index + 1));
        scanf("%s", &name);

        order[index] = index;

        printf("Do they have popcorn: ");
        scanf("%d", &popcorn_who[index]);

        if (strlen(name) >= MAX_NAME_LENGTH) {
            printf("Name is too long! Maximum allowed length is %d\n", MAX_NAME_LENGTH - 1);
            return 1;  // Exit with an error code
        }

        strcpy(name_list[index], name);
    }

    printf("Entered names:\n");
    for (int i = 0; i < people_amount; i++) {
        printf("Name[%d]: %s,  Popcorn: %d \n", i, name_list[i], popcorn_who[i]);
    }



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    index = 0;


    if (people_dislike > MAX_PEOPLE) {
        printf("Too many people! Maximum allowed is %d\n", MAX_PEOPLE);
        return 1;  // Exit with an error code
    }

    for (int index = 0; index < people_dislike; index++) {
        printf("Who dislikes: ");
        scanf("%s", &name_dislike);


        if (strlen(name_dislike) >= MAX_NAME_LENGTH) {
            printf("Name is too long! Maximum allowed length is %d\n", MAX_NAME_LENGTH - 1);
            return 1;  // Exit with an error code
        }

        strcpy(name_list_dislike[index], name_dislike);
    }

    printf("Dislike Chart:\n");
    for (int i = 0; i < people_dislike; i++) {
        printf("Name[%d]: %s \n", i, name_list_dislike[i]);
    }


    int i;
    int compare = 0;
    index = 0;

    for (i = 0; i < people_dislike; i++) {
        compare = 10;
        index = 0;

        while (index < people_amount && compare != 0) {
            compare = strcmp(name_list[index], name_list_dislike[i]);
            order_dislike[i] = index;
            index++;
        }

        printf("Order Dislike[%d] \n", order_dislike[i]);

        if (compare == 0) {
            printf("The name %s is in [%d]\n", name_list_dislike[i], index - 1);
        }
        else {
            printf("The name %s is not found in name_list\n", name_list_dislike[i]);
        }
    }


    for (int counter = 0; counter < people_dislike; counter++) {

        dislike_chart[order_dislike[counter]][order_dislike[(counter + 1)]] = 1;
        dislike_chart[order_dislike[(counter + 1)]][order_dislike[counter]] = 1;

        counter++;

    }


    for (int i = 0; i < people_amount; i++) {
        for (int j = 0; j < people_amount; j++) {
            printf("%d ", dislike_chart[i][j]);
        }
        printf("\n");
    }

    // Initialize an array to store the permutation
    int perm[MAX_PEOPLE] = { 0 };
    int used[MAX_PEOPLE] = { 0 };

    // Call permute function to generate permutations and evaluate them
    permute(people_amount, perm, used, 0, popcorn_who, people_amount, dislike_chart, people_dislike);


    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popcorn_case(int people_amount, int* popcorn_who) {

    int amount = 0;
    int index = 0;
    int counter = 0;

    if ((popcorn_who[0] == 1) || (popcorn_who[1] == 1)) {

        for (int index = 1; index < people_amount; index++) {

            if ((popcorn_who[index - 1] == 1) || (popcorn_who[index] == 1) || (popcorn_who[index + 1] == 1)) {

                counter++;
            }

            if (((popcorn_who[people_amount - 2] == 1) || (popcorn_who[people_amount - 1] == 1)) && (counter == (people_amount - 1))) {

                amount++;

            }

        }

    }


    printf("%d \n", amount);


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dislike_case(int people_dislike, int* dislike_chart, int* order) {

    int counted = 0;

    int pass = 0;

    for (int counter = 0; counter <= (people_dislike / 2); counter++) {

        if (dislike_chart[order[counter] * people_dislike + order[(counter + 1)]] != 1) {

            pass++;

        }

        counter++;

        if (pass == (people_dislike / 2)) {

            counted++;
        }

    }

    printf("counted = %d", counted);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void permute(int n, int* perm, int* used, int index, int* popcorn_who, int people_amount, int* dislike_chart, int people_dislike) {
    // Base Case
    if (index == n) {
        // Call popcorn_case and dislike_case for the current permutation
        popcorn_case(people_amount, popcorn_who);
        dislike_case(people_dislike, dislike_chart, perm);
        return;
    }

    // Recursive Case: Try all unused values
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            // Use the i-th value in the permutation at the given index
            used[i] = 1;
            perm[index] = i + 1;

            // Generate a permutation of the remaining values
            permute(n, perm, used, index + 1, popcorn_who, people_amount, dislike_chart, people_dislike);

            // Unuse the i-th value in the permutation at the given index
            used[i] = 0;
            perm[index] = 0;
        }
    }
}