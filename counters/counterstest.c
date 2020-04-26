/* 
 * counterstest.c - test program for CS50 'counters' module
 *
 * Command line usage
 * Option 1: ./counterstest
 * Option 2: make test &> testing.out 
 *
 * CS50, Sydney Friedland, April 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"

// function prototypes
void print_key(); 

int main() {
    counters_t *ctrs;
    int val = 0;
    FILE * ifile = fopen("ofile","w"); // some testfile

    printf("Creating counter set...\n");
    ctrs = counters_new(); // create counter set
    if (ctrs == NULL) {
        fprintf(stderr, "counters_new failed\n");
        return 1;
    }

    printf("Testing counters_add:\n");
    counters_add(ctrs, 2); // create counter1
    counters_add(ctrs, 2); // create counter1
    counters_add(ctrs, -1); // should not increment counter 1
    counters_add(ctrs, 2); // increment counter1 by 1
    fprintf(stdout, "Counter value: %d\n", val); // val should print 2
    counters_add(ctrs, 2); // increment counter1 by 1
    counters_add(ctrs, 3); // create counter2
    
    printf("Testing counters_get:\n");
    val = counters_get(ctrs, 2); // get value for key = 2
    printf("Counter value: %d\n", val); // should print 3
    val = counters_get(ctrs, 4); // get value for nonexistent key = 4
    printf("Counter value for nonexistent key: %d\n", val); // should print 0
    
    printf("Testing counters_set:\n");
    if (counters_set(ctrs, 2, 10)) // true case
        printf("Key has been set\n");
    else
        printf("Key not set\n");
    
    if (counters_set(ctrs, 2, -2)) // false case
        printf("Key has been set\n");
    else
        printf("Key not set\n");
    
    printf("Testing counters_print:\n");
    counters_print(ctrs, ifile); // pass valid file pointer, check ofile for result
    fclose(ifile);

    printf("Testing counters_interate:\n");
    counters_iterate(ctrs, (void*)2, print_key); // print key = 2 and count = 10
    counters_iterate(ctrs, (void*)5, print_key); // key does not exist, prints nothing

    printf("Deleting the counter set...\n");
    counters_delete(ctrs); // use valgrind to check if successful

    printf("End of test.\n");

    return 0;
}

/**************** print_key ****************/
/* Check if key exists in counter set, if so,
 * print key and corresponding count. If key
 * does not exist, do nothing.
 */
void print_key(int arg, int key, int count)
{
    if(arg == key)
        printf("Key found: key %d, count = %d\n", key, count);
}
