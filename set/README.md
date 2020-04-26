# Sydney Friedland
## cs50 Spring 2020, Lab 3, `set` module

### set

A *set* maintains an unordered collection of (key,item) pairs any given key can only occur in the set once. It starts out empty and grows as the caller inserts new (key,item) pairs. The caller can retrieve items by asking for their key, but cannot remove or update pairs. Items are distinguished by their key.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `void*` with `char*` keys, and exports the following functions through `set.h`:

```c
/* Create a new (empty) set; return NULL if error.
 * Caller is responsible for later calling set_delete */
set_t *set_new(void);

/* Insert item, identified by a key (string), into the given set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true if new item was inserted. Caller is responsible for
 * later calling set_delete to free the memory used by key strings. */
bool set_insert(set_t *set, const char *key, void *item);

/* Return the item associated with the given key.
 * Ignore if NULL set, NULL key, or key is not 
 * found. */
void *set_find(set_t *set, const char *key);

/* Print the whole set; provide the output file 
 * and func to print each item. Ignore if NULL fp.
 * If NULL set, print (null). Prints in format:
 * { (key,item),(key,item)... }. */
void set_print(set_t *set, FILE *fp, 
               void (*itemprint)(FILE *fp, const char *key, void *item) );

/* Iterate over the set; call given a function on each item,
 * passing (arg, key, item). Ignore if NULL set or NULL
 * itemfunc */
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete set, calling a delete function on each item;
 * ignore if NULL set or NULL itemfunc. */
void set_delete(set_t *set, void (*itemdelete)(void *item) );
```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct snode`, a type defined internally to the module.
Each snode includes a pointer to a `void*` item, its `char*` key, and a pointer to the next snode on the list.

To insert a new key in the set we create a new snode to hold a key and item, and insert it at the head of the list.

The `set_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `set_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing snodes as it proceeds.

### Assumption

Memory must be allocated for each occurrence of an item (e.g. an integer item equal to 2 may be paired with more than one key, but memory must be allocated for each occurence of the integer item in a key pair).

### Compilation

To compile, simply `make`.

To test, simply `make test` or `make test &> testing.out`.
Details of test run commented in `settest.c`.
Test treats items as integers.

To clean up directory, simply `make clean`.