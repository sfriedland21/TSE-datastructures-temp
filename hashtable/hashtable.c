/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Sydney Friedland, April 2020
 * 
 * Based on code by:
 * David Kotz, April 2016, 2017, 2019
 * updated by Xia Zhou, July 2016
 * updated by Temi Prioleau, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "hashtable.h"
#include "jhash.h"

/**************** functions ****************/

/**************** global types ****************/
typedef struct hashtable { 
    set_t **array; // head of the list of items in a set
    int size;
} hashtable_t;
/**************** functions ****************/

/**************** hashtable_new ****************/
hashtable_t *hashtable_new(const int num_slots) 
{
  hashtable_t *hashtable = malloc(sizeof(hashtable_t));

  if (hashtable == NULL)
    return NULL; // error allocating hashtable
  else {
    hashtable->array = malloc(num_slots*sizeof(set_t *)); // initialize hashtable
    int i;
    for (i = 0; i < num_slots; i++) {
	  hashtable->array[i] = set_new(); // using set module
	}
    hashtable->size = num_slots;
    return hashtable;
  }
}

/**************** hashtable_insert ****************/
bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
  if (ht != NULL && key != NULL && item != NULL) {
    char *keycopy = (char *)malloc((strlen(key) + 1)*sizeof(char));
	if (keycopy == NULL) {
	    fprintf(stderr, "could not allocate memory for keycopy");
		return false;
	}
    int hashcode = JenkinsHash(key, ht->size); // get hash code
    keycopy = (char *)strcpy(keycopy, key); // since memory was allocated
    if (ht->array[hashcode] == NULL) { // if no set at location, create new set
        ht->array[hashcode] = set_new();
        if (set_insert(ht->array[hashcode], keycopy, item)) { // check set insert
            free(keycopy); // module responsible for deallocating keycopy
            return true;
        }
        else {
            free(keycopy); // module responsible for deallocating keycopy
            return false;
        }
	}
    else {
        if (set_insert(ht->array[hashcode], keycopy, item)) { // otherwise insert item into existing set
            free(keycopy); // module responsible for deallocating keycopy
            return true;
        }
        else {
		    free(keycopy); // module responsible for deallocating keycopy
	        return false;
        }
	}
  }
  else
    return false;
}

/**************** hashtable_find ****************/
void *hashtable_find(hashtable_t *ht, const char *key)
{
  if (ht == NULL || key == NULL)
    return NULL; // bad hashset or bad key
  else {
    int hashcode = JenkinsHash(key, ht->size); // get hash code
    if (ht->array[hashcode] != NULL) {
	  return set_find(ht->array[hashcode], key); // get item
	}
    else
	  return NULL;
  }
  return NULL;
}

/**************** hashtable_print ****************/
void hashtable_print(hashtable_t *ht, FILE *fp, 
                     void (*itemprint)(FILE *fp, const char *key, void *item)) 
{
    if (fp == NULL)
        fprintf(fp, "(null)");
    else {
        if (ht != NULL) {
            for (int i = 0; i < ht->size; i++) {
                fprintf (fp, "Slot %d: ", i);
                if (itemprint != NULL && ht->array[i] != NULL) { // print valid sets to file
                    set_print(ht->array[i], fp, itemprint);
                    fprintf(fp, "\n");
                }
            }
	    }	    
    }
}

/**************** hashtable_iterate ****************/
void hashtable_iterate(hashtable_t *ht, void *arg,
                       void (*itemfunc)(void *arg, const char *key, void *item) )
{
    if (ht != NULL && itemfunc != NULL) {
        // call itemfunc on each item
        int i;
        for (i = 0; i < ht->size; i++) {
            if (ht->array[i] != NULL) {
                set_iterate (ht->array[i], arg, itemfunc);
            }
	    }
    }   
}

/**************** hashtable_delete ****************/
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) )
{
    int i;
    for (i = 0; i < ht->size; i++) {
        set_delete(ht->array[i], itemdelete); // delete all sets in hashtable
    }
    free(ht->array);
    ht->array = NULL;
    free(ht);
    ht = NULL;
}