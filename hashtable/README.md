# Sydney Friedland
## cs50 Spring 2020, Lab 3, `hashtable` module

### hashtable

A *hashtable* is a set of (key,item) pairs. It acts just like a set, but is far more efficient for large collections. This module utilizes the Jenkins' hash function, define in `jhash.h` and implemented in `jhash.c`, to create hash codes. 

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a set of `void*` with `char*` keys, and exports the following functions through `hashtable.h`:

```c
/* Create a new (empty) hashtable; return null if error.
 * Caller is responsible for later calling hashtable_delete. */
hashtable_t *hashtable_new(const int num_slots);

/* Insert item, identified by key (string), into the given hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true if new item was inserted. Caller is responsible for
 * later calling hashtable_delete to free the memory used by key strings. */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);

/* Return the item associated with the given key.
 * Ignore if NULL hashtable, NULL key, or key is not 
 * found. */
void *hashtable_find(hashtable_t *ht, const char *key);

/* Print the whole table; provide the output file 
 * and func to print each item. Ignore if NULL fp.
 * If NULL ht, print (null). Prints in format (e.g. for ht of size 10):
 * Slot 0: {  }
 * Slot 1: {  }
 * Slot 2: { (key1,2) }
 * Slot 3: {  }
 * Slot 4: {  }
 * Slot 5: {  }
 * Slot 6: {  }
 * Slot 7: { (key2,4) }
 * Slot 8: {  }
 * Slot 9: {  }. */
void hashtable_print(hashtable_t *ht, FILE *fp, 
                     void (*itemprint)(FILE *fp, const char *key, void *item));

/* Iterate over all items in the table, in undefined order; 
 * call given a function on each item, passing (arg, key, item). 
 * Ignore if NULL ht or NULL itemfunc */
void hashtable_iterate(hashtable_t *ht, void *arg,
                       void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete hashtable, calling a delete function on each item;
 * ignore if NULL ht or NULL itemfunc. */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );
```

### Implementation

We implement this hashtable as a linked list.
The *hashtable* itself is represented as a `struct hashtable` containing a pointer to the head of the list; the head pointer is NULL when the hashtable is empty.

The `hashtable_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `hashtable_delete` method calls `set_delete` and an `itemdelete` function on each item by scanning the linked list, freeing nodes in each set as it proceeds.

### Compilation

To compile, simply `make`.

To test, simply `make test` or `make test &> testing.out`.
Details of test run commented in `hashtabletest.c`.
Test treats items in a set as integers.

To clean up directory, simply `make clean`.