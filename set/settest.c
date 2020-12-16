/* 
 * settest.c - test program for CS50 'set' module
 *
 * Command line usage
 * Option 1: ./settest
 * Option 2: make test &> testing.out
 *
 * CS50, Sydney Friedland, April 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

//function prototypes
void print_settofile();
void print_keypair();
void item_delete();

int main() {
    set_t *set;
    FILE * ifile = fopen("ofile","w"); // some testfile

    printf("Creating set...\n");
    set = set_new(); // create set
    if (set == NULL) {
        fprintf(stderr, "set_new failed\n");
        return 1;
    }
    
    char *key1 = "key1";
    char *key2 = "key2";
    char *key3 = "key3";
    char *key4 = NULL;
    int *item1 = (int *)malloc(sizeof(int));
    *item1 = 2;
    int *item2 = (int *)malloc(sizeof(int));
    *item2 = 4;

    printf("Testing set_insert:\n");
    if (set_insert(set, key1, (void*)item1)) {
        printf("First insert sucessful\n"); // should print
    }
    else printf("First insert not sucessful\n");
    if (set_insert(set, key2, (void*)item2)) {
        printf("Second insert sucessful\n"); // should print
    }
    else printf("Second insert not sucessful\n");
    if (set_insert(set, key4, (void*)item2)) {
        printf("Third insert (of null key) sucessful\n"); 
    }
    else printf("Third insert (of null key) not sucessful\n"); // should print, bc null key

    printf("Testing set_print:\n");
    set_print(set, ifile, print_settofile); // pass valid file pointer, check ofile for result
    fclose(ifile);

    printf("Testing set_iterate:\n");
    set_iterate(set, (void*)key1, print_keypair); // print key = key1 and item = 2
    set_iterate(set, (void*)key3, print_keypair); // should print nothing, b/c there is no item paired with key3

    printf("Deleting the set...\n"); // use valgrind to check
    set_delete(set, item_delete);

    printf("End of test.\n");

    return 0;
}

/**************** print_settofile ****************/
/* Formats printing of set_print. */
void print_settofile(FILE *fp, const char *key, int *item)
{
    fprintf(fp,"(%s,%d)", key, *item);
}

/**************** print_keypair ****************/
/* Prints key pair if key exists */
void print_keypair(void *arg, const char *key, int *item)
{
    if(strcmp((char *)arg, key) == 0)
        printf("Key found: Key = %s, item = %d\n", key, *item);
}

/**************** item_delete ****************/
/* Frees item memory at a node */
void item_delete(void *item)
{
    if (item != NULL) {
        free(item);
        item = NULL;
    }
}