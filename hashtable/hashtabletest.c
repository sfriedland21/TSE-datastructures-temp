/* 
 * hashtabletest.c - test program for CS50 'hashtable' module
 *
 * Command line usage
 * Option 1: ./hashtabletest
 * Option 2: make test &> testing.out
 *
 * CS50, Sydney Friedland, April 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "hashtable.h"
#include "jhash.h"

//function prototypes
void print_settofile();
void print_keypair();
void item_delete();

int main() {
    hashtable_t *ht;
    const int numslots = 10;
    FILE *ifile = fopen("ofile","w"); // some testfile
    
    printf("Creating hashtable...\n");
    ht = hashtable_new(numslots); // create hashtable
    if (ht == NULL) {
        fprintf(stderr, "hashtable_new failed\n");
        return 1;
    }

    char *key1 = "key1";
    char *key2 = "key2";
    int *item1 = (int *)malloc(sizeof(int));
    *item1 = 2;
    int *item2 = (int *)malloc(sizeof(int));
    *item2 = 4;
    int founditem;

    printf("Testing hashtable_insert:\n");
    if (hashtable_insert(ht, key1, (void*)item1))
        printf("Insert sucessful\n"); // should print
    else
        printf("Insert not sucessful\n");
    hashtable_insert(ht, key2, (void*)item2);
    hashtable_insert(ht, key2, (void*)item1);

    printf("Testing hashtable_find:\n");
    founditem = *((int*)hashtable_find(ht, key1));
    printf("Found item: %d\n", founditem); // prints found item, item = 2

    printf("Testing hashtable_print:\n");
    hashtable_print(ht, ifile, print_settofile); // pass valid file pointer, check ofile for result
    fclose(ifile);

    printf("Testing hashtable_iterate:\n");
    hashtable_iterate(ht, (void*)key1, print_keypair); // should print key = key1, item = 2

    printf("Deleting hashtable...\n");
    hashtable_delete(ht, item_delete);
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
        printf("Key found: key = %s, item = %d\n", key, *item);
}

/**************** item_delete ****************/
/* Frees item memory in hashtable */
void item_delete(void *item)
{
    if (item != NULL) {
        free(item);
        item = NULL;
    }
}