/*
Write a multithreaded program that calculates various statistical values for a
list of numbers. This program will be passed a series of numbers on the
command line and will then create three separate worker threads. One thread
will determine the average of the numbers, the second will determine the
maximum value, and the third will determine the minimum value. For
example, suppose your program is passed the integers
90 81 78 95 79 72 85
The program will report
A.​ The average value is 82
B.​ The minimum value is 72
C.​ The maximum value is 95
The variables representing the average, minimum, and maximum values will
be stored globally. The worker threads will set these values, and the parent
thread will output the values once the workers have exited.
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global result variables
double average;
int minimum;
int maximum;

// Global variables to pass data to threads
int *numbers;
int count;

// Thread function to calculate average
void* calculate_average(void* arg) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    average = (double)sum / count;
    pthread_exit(NULL);
}

// Thread function to calculate minimum
void* calculate_minimum(void* arg) {
    minimum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < minimum) {
            minimum = numbers[i];
        }
    }
    pthread_exit(NULL);
}

// Thread function to calculate maximum
void* calculate_maximum(void* arg) {
    maximum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments into integer array
    count = argc - 1;
    numbers = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    // Thread declarations
    pthread_t avg_thread, min_thread, max_thread;

    // Create threads
    pthread_create(&avg_thread, NULL, calculate_average, NULL);
    pthread_create(&min_thread, NULL, calculate_minimum, NULL);
    pthread_create(&max_thread, NULL, calculate_maximum, NULL);

    // Wait for threads to finish
    pthread_join(avg_thread, NULL);
    pthread_join(min_thread, NULL);
    pthread_join(max_thread, NULL);

    // Output results
    printf("A. The average value is %.2f\n", average);
    printf("B. The minimum value is %d\n", minimum);
    printf("C. The maximum value is %d\n", maximum);

    // Free memory
    free(numbers);

    return 0;
}

