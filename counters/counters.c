/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 * Sydney Friedland, April 2020
 * 
 * Based on code by:
 * David Kotz, April 2016, 2017, 2019
 * updated by Xia Zhou, July 2017
 * updated by Temi Prioleau, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct cnode {
  int key; // key in counter set
  int value; // count value corresponding to key in counter set
  struct cnode *next; // link to next node
} cnode_t;

/**************** global types ****************/
typedef struct counters {
  struct cnode *head; // head of the counter
} counters_t;

/**************** functions ****************/

/**************** counters_new ****************/
counters_t *counters_new(void) 
{
  counters_t *ctrs = malloc(sizeof(counters_t));

  if (ctrs == NULL) {
      return NULL; // error allocating counter
  } else {
      ctrs->head = NULL; // initialize counter
      return ctrs;
  }
}

/**************** counters_add ****************/
int counters_add(counters_t *ctrs, const int key) 
{
  if (ctrs != NULL && key >= 0) {
    // if key exists, increment value
    cnode_t *temp = ctrs->head;
    while(temp != NULL) { // traverse list
      if (temp->key == key) { 
        temp->value++;
        return temp->value;
      }
      else
        temp = temp->next;
    }
    // if loop did not return a value, key did not exist
    cnode_t *newNode = (cnode_t*) malloc(sizeof(cnode_t)); // create new node
    if (newNode != NULL) { // check if memory was allocated
      newNode->key = key; // add the key
      newNode->value = 1; // initialize as 1
      newNode->next = ctrs->head; // insert at head of list
      ctrs->head = newNode;
      return newNode->value;
    }
  }
  return 0;
}

/**************** counters_get ****************/
int counters_get(counters_t *ctrs, const int key) 
{
  if (ctrs != NULL && key >= 0) {
    cnode_t *temp = ctrs->head;
    if (temp != NULL) { // check of node exists
      while(temp != NULL) { // traverse list
        if (temp->key == key) { // if key exists, increment
          return temp->value;
        }
        else
          temp = temp->next;
      }
    }
  }
  return 0;
}

/**************** counters_set ****************/
bool counters_set(counters_t *ctrs, const int key, const int count) 
{
  if (ctrs != NULL && key >= 0 && count >= 0) {
    int * ptr = (int *) malloc(sizeof(int)); 
    if (ptr == NULL) { // check if out of memory
      return false;
    }
    else {
      free(ptr); // free test ptr if successfully created
      cnode_t *temp = ctrs->head;
      if (temp != NULL) { // check if node exists
        while(temp != NULL) { // traverse list
          if (temp->key == key) { // if key exists, set to given value
            temp->value = count;
            return true;
          }
          else
            temp = temp->next;
        }
      }
      // if loop did not return true, key did not exist
      cnode_t *newNode = (cnode_t*) malloc(sizeof(cnode_t));
      newNode->key = key; // add the key
      newNode->value = count; // initialize as given value
      newNode->next = ctrs->head; // insert at head of list
      ctrs->head = newNode;
      return true;
    }
  }
  else 
    return false;
}

/**************** counters_print ****************/
/* prints in format: { (key,count),(key,count)... } */
void counters_print(counters_t *ctrs, FILE *fp)
{
  if (fp != NULL) { // check if valid file pointer, user responsible for opening in write mode
    if (ctrs == NULL)
      fprintf(fp, "(null)");
    else {
      cnode_t *temp = ctrs->head;
      fprintf(fp, "{ "); // file contents will be overwritten each time function is called
      while(temp != NULL) { // traverse list
        fprintf(fp,"(%d,%d)", temp->key, temp->value); 
        if (temp->next != NULL)
          fputc(',',fp);
        temp = temp->next;
      }
      fprintf(fp, " }");
    } // user is responsible for closing file
  }
}

/**************** counters_iterate ****************/
void counters_iterate(counters_t *ctrs, void *arg, 
                      void (*itemfunc)(void *arg, 
                                       const int key, const int count)) 
{
  if (ctrs != NULL && itemfunc!= NULL) {
    cnode_t *temp = ctrs->head;
    while(temp != NULL) {
      (*itemfunc)(arg, temp->key, temp->value);
      temp = temp->next;
    }
  }
}

/**************** counters_delete ****************/
void counters_delete(counters_t *ctrs) 
{
  if (ctrs != NULL) {
    cnode_t *temp = ctrs->head;
    while(temp != NULL) { // traverse list
      cnode_t *next = temp->next;
      free(temp);
      temp = next; // move onto next node
    }
    temp = NULL;
    free(ctrs); // free counter set
    ctrs = NULL;
  }
}