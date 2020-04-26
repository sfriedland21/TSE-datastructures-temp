/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
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

/**************** local types ****************/
typedef struct snode {
  char *key; // key in set
  void *item; // item in set
  struct snode *next; // link to next node
} snode_t;

/**************** global types ****************/
typedef struct set {
  struct snode *head; // head of the set
} set_t;

/**************** functions ****************/

/**************** local functions ****************/
/* not visible outside this file */
static snode_t *snode_new(const char *key, void *item);

/**************** set_new ****************/
set_t *set_new(void)
{
  set_t *set = malloc(sizeof(set_t));

  if (set == NULL) {
    return NULL; // error allocating set
  } else {
    set->head = NULL; // initialize set
    return set;
  }
}

/**************** set_insert ****************/ 
bool set_insert(set_t *set, const char *key, void *item)
{
  if (set != NULL && item != NULL && set_find(set, key) == NULL) {
    // check if item in set (prevent duplicate entries here)
    snode_t *nNode = snode_new(key, item);
    if (nNode != NULL) { // check if memory was allocated for the node
      nNode->next = set->head; // insert at head of list
      set->head = nNode;
      return true;
	  }
  }
  return false;
}

/**************** snode_new ****************/
/* Allocate and initialize an snode.
 * Function not visible outside this file */
static snode_t *snode_new(const char *key, void *item) {
  snode_t *newNode = malloc(sizeof(snode_t)); // create new node
  char *newKey = (char *)malloc((strlen(key) + 1)*sizeof(char)); // allocate space for the key

  if (newNode == NULL || newKey == NULL) { // check if memory was allocated
    free (newKey);
    free (newNode);
    return NULL;
  }
  else {
    newKey = (char *) strcpy(newKey, key);
    newNode->key = newKey; // add the key
    newNode->item = item; // add the item
    newNode->next = NULL;
    newKey = NULL;
    return newNode;
  }
}

/**************** set_find ****************/
void *set_find(set_t *set, const char *key)
{
  if (set == NULL || key == NULL) // bad set or key
    return NULL;
  else if (set->head == NULL) // set is empty
    return NULL;
  else {
    snode_t *temp = set->head;
    while (temp != NULL) {
	    if (strcmp (temp->key, key) == 0)
	      return temp->item; // return found item for existing key
      temp = temp->next;
    }
    return NULL;
  }
  return NULL;
}

/**************** set_print ****************/
/* prints in format: { (key,item),(key,item)... } */
void set_print(set_t *set, FILE *fp, 
               void (*itemprint)(FILE *fp, const char *key, void *item))
{
  if (fp != NULL) {
    if (set == NULL)
      fprintf(fp, "(null)");
    else {
      snode_t *temp = set->head;
      fprintf(fp, "{ "); // file contents will be overwritten each time function is called
      while(temp != NULL) { // traverse list
        if (itemprint != NULL) {
          (*itemprint)(fp, temp->key, temp->item); 
          if (temp->next != NULL)
            fputc(',',fp);
        }
        temp = temp->next;
      }
      fprintf(fp, " }"); // user is responsible for closing file
    }
  }
}

/**************** set_iterate ****************/
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (set != NULL && itemfunc != NULL) {
    // call itemfunc on each item
    snode_t *temp;
    for (temp = set->head; temp != NULL; temp = temp->next)
	    (*itemfunc)(arg, temp->key, temp->item);
  }
}

/**************** set_delete ****************/
void set_delete(set_t *set, void (*itemdelete)(void *item) ) 
{
  if (set != NULL) {
    snode_t *temp = set->head;
    while(temp != NULL) { // traverse list
      if (itemdelete != NULL)
	      (*itemdelete)(temp->item); // free the node's item
      snode_t *next = temp->next;
      free(temp->key); // free the node
      temp->key = NULL;
      free(temp);
      temp = next;
    }
    temp = NULL;
    free(set);
    set = NULL;
  }
}