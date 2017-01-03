/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

int binarySearch(int value, int values[], int start, int end)
{
    if (end < start) {
        return -1;
    }
    int midpoint = (start + end) / 2;
        
    if (values[midpoint] < value) {
        return binarySearch(value, values, midpoint + 1, end);
    } else if (values[midpoint] > value) {
        return binarySearch(value, values, start, midpoint - 1);
    }
    return midpoint;
}

bool search(int value, int values[], int n)
{
    if (binarySearch(value, values, 0, n) != -1) {
        return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 1; i < n; i++) {
        int element = values[i];
        int j = i;
        while(j > 0 && values[j - 1] > element) {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = element;
    }
    return;
}