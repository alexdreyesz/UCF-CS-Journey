#include <stdio.h> // Standard C Library 
#include <stdlib.h> // Declares Various Utility Functions For Type Conversions, Memory Allocation, Algorithms, And Other Similar Use Cases
#include <math.h> // Defines Various C Mathematical Functions
#include <assert.h> // File To Verify Assumptions Made By The Program
#include <limits.h> // Determines Numeric Limits Types And It Provides Information About The Properties Of Arithmetic Types


//Struct For Groups 
struct Group {
    double angle;
    int size;
};


// Functions Declaration
void swap(struct Group* a, struct Group* b);
int less_than(struct Group a, struct Group b);
void quick_sort_array(struct Group* group, int group_amount);
void mirror_array(struct Group* group, struct Group* group_mirror, int group_amount);
double get_angle(int x, int y);
double biggest_angle(struct Group* group, int group_amount);
int smallest_Group_Size(struct Group* group, struct Group* group_mirror, int group_amount, double projector_initial_angle);


// Main Program 
int main() {
    int group_amount = 0; // Integer For The Amount Of Groups 
    int projector_initial_angle = 0; // Integer For The Projection Initial Angle
    int x_coordinate = 0; // Integer For The X Coordinate
    int y_coordinate = 0; // Integer For The Y Coordinate
    int group_size = 0; // Integer For The Amount Of People Inside Of A Group
    int smallest_size = 0; // Integer For the Smallest Size Found In Groups Insede The Projection Given Angle
    double best_angle = 0.00; // double For The Best Posible Angle Found

   
    scanf("%d %d", &group_amount, &projector_initial_angle);  //Create The Struct Group 

    struct Group* group = (struct Group*)malloc(group_amount * sizeof(struct Group)); // Main Struct Group

    struct Group* group_mirror = (struct Group*)malloc(group_amount * sizeof(struct Group)); // Mirror Struct Group +360 On Angles 

    int index = 0; // Index For Traversal 

    while (index < group_amount) { // While Loop To Get All The Asked Inputs From The Group Amount 
        scanf("%d %d %d", &x_coordinate, &y_coordinate, &group_size);

        group[index].angle = get_angle(x_coordinate, y_coordinate);
        group[index].size = group_size;

        index++;
    }

    quick_sort_array(group, group_amount); // Quick Sort The Given Group

    mirror_array(group, group_mirror, group_amount); // Mirror The Quick Sortes Struct Array

    best_angle = biggest_angle(group, group_amount); // Find The Best Angle From the Struct Array

    smallest_size = smallest_Group_Size( group, group_mirror, group_amount, projector_initial_angle); // Find The Smallest Size From The Struct Array
    

    printf("\n%d\n", smallest_size); // Print Result For Smallest Size Found
    printf("%.4lf\n", best_angle); // Print Result For Biggest Angle Range Found

    free(group); // Free Dynamically Allocated Group 
    free(group_mirror); // Free Dynamically Allocated Group Mirror

    return 0;
}


// Function To Swap 2 Values Using References
void swap(struct Group* a, struct Group* b) {
    struct Group tmp = *a;
    *a = *b;
    *b = tmp;
}


// Function To Compare Two Group Elements Based On Angle
int less_than(struct Group a, struct Group b) {
    return a.angle < b.angle;
}


// Function To Quick Sort The Values
void quick_sort_array(struct Group* group, int group_amount) {
    if (group_amount <= 1) {
        return; // Already sorted
    }

    // Choose the pivot element, let's say the first element
    struct Group pivotValue = group[0];

    int fPtr = 1;
    int bPtr = group_amount - 1;

    while (1) {
        while (fPtr < group_amount && less_than(group[fPtr], pivotValue)) {
            fPtr++;
        }

        while (less_than(pivotValue, group[bPtr]) && bPtr > 0) {
            bPtr--;
        }

        if (fPtr < bPtr) {
            swap(&group[fPtr], &group[bPtr]);
        }
        else {
            break;
        }
    }

    // Move the pivot element to its correct position
    swap(&group[0], &group[bPtr]);

    // Recursively sort the sub-arrays
    quick_sort_array(group, bPtr);
    quick_sort_array(group + bPtr + 1, group_amount - (bPtr + 1));
}


// Function To Populate The Mirror Group With The Angle Value +360 For Special Cases
void mirror_array(struct Group* group, struct Group* group_mirror, int group_amount) {
    for (int i = 0; i < group_amount; i++) {
        group_mirror[i].angle = group[i].angle + 360;
        group_mirror[i].size = group[i].size;
    }
}


// Function To Calculate The Angle In Degrees With x And y
double get_angle(int x, int y) {
    double angle = atan2(y, x) * (180 / M_PI); // Mathematical Formula To Change Radians To Degrees 
    if (angle < 0) { // If Statement to Verify For Negative Values 
        angle += 360.0;
    }
    return angle;
}


// Function To Find Biggest Angle
double biggest_angle(struct Group* group, int group_amount) {
    int index = 0;
    double current_angle = 0.00;
    double biggest_angle = 0.00;

    while (index < group_amount) { // While Loop To Find The Biggest Agle Possible 

        if (index < group_amount - 1) { // Index To Find The Values Inside Of +360

            current_angle = group[index + 1].angle - group[index].angle;

        }

        if (index == group_amount - 1) { // Index To Keep Find The Values Outside Of +360

            current_angle = (360 + group[0].angle) - group[index].angle;

        }

        if (current_angle > biggest_angle) { // If Statement To Verify If A Bigger Angle Was Found 
            biggest_angle = current_angle;
        }

        index++; // Update to Traverse The Array
    }

    return biggest_angle;
}


// Function To Find The Smallest Size Of Groups Inside Of The Projection Range 
int smallest_Group_Size(struct Group* group, struct Group* group_mirror, int group_amount, double projector_initial_angle) {
    int size_summation = 0;
    int smallest_size = INT_MAX;
    double epsilon = 1e-9;
    double back_pointer = 0;
    double front_pointer = 0;


    int index = 0; // Index For Angle
    int i = 0; // Index For Mirror Angle


    while (index < group_amount) { // While Loop To Check All Groups Inside Of The Angle Projection Range

        back_pointer = group[index].angle + epsilon; // Ancle Back Pointer To The First Given Angle Plus Epsilon To Take The First Angle Out Of The Equation 
        front_pointer = group[index].angle + projector_initial_angle - epsilon; // Ancle Front Pointer To The Angle Projection Size Plus The Initial Angle Minus Epsilon To Take Out Of The Equation Any Boundaries 


        for (int counter = 0; counter < group_amount; counter++) {

            if (front_pointer > 359) { // If Statement To Verify If Front Pointer Is More Than +360 Meaning It Resets The Circle 

                if (front_pointer > 720) { // If Statement To Verify If Front Pointer Is More Than +720 Meaning It Resets The Circle A Second Time 

                    front_pointer -= 360;

                }

                if (group[counter].angle >= back_pointer) { // Update The Summation For The Projection Angle Range Provided From The Back Pointer 

                    size_summation += group[counter].size;


                }

                if (group_mirror[i].angle <= front_pointer) { // Update The Mirror Angle Summation For The Projection Angle Range Provided From The Front Pointer 

                    size_summation += group_mirror[i].size;

                }

                i++;

                if (i == group_amount) { // If Statement To Reset The Traversal Of The Group Mirror Angle Array If It Goes Out Of Bounds When Goind Past +720
                    i = 0;
                }

            }

            else if ((group[counter].angle >= back_pointer) && (group[counter].angle <= front_pointer)) { // Update The Summation For The Projection Angle Range Provided From The Back And Front Pointer 

                size_summation += group[counter].size;

            }

        }

        if (smallest_size >= size_summation) { // If Statement to Update Smallest Size if a Smallest Size Was Found By Size Summation  
            smallest_size = size_summation;
        }

        size_summation = 0; // Update To Reset Size Summation To Use Again

        index++; // Update To Traverse The Group Angle Array
    }


    return smallest_size;
}