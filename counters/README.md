# Sydney Friedland
## cs50 Spring 2020, Lab 3, `counters` module

### counters

A *counter set* is a set of counters, each distinguished by an integer key. Each key can only occur once in the set and the set tracks a counter for each key. Counter set starts empty. Each time `counters_add` is called on a given key, the corresponding counter is incremented. The current counter value can be retrieved by asking for the relevant key.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a set of non-negative integer counters with `int` keys, and exports the following functions through `counters.h`:

```c
/* Create a new (empty) counter structure; return
 * NULL if error. */
counters_t *counters_new(void);

/* Increment the counter indicated by key; return
 * value of counter related to indicated key; a 
 * NULL counter set is ignored; a negative key is  
 * ignored */ 
int counters_add(counters_t *ctrs, const int key);

/* Return current value of counter associated with 
 * the given key, if present; a null counter set is 
 * ignored. */
int counters_get(counters_t *ctrs, const int key);

/* Set the current value of counter associated with 
 * the given key to a given value; if the key does 
 * not exist, create the key and update its counter 
 * value to the given value; return false if NULL 
 * counter set, or if key < 0, or if count < 0, or 
 * if out of memory, otherwise return true. */
bool counters_set(counters_t *ctrs, const int key, const int count);

/**************** counters_print ****************/
/* Print all counters; provide the output file.
 * Ignore if NULL fp. If NULL counter set, print
 * (null). Prints in format: { (key,count),(key,count)... } */
void counters_print(counters_t *ctrs, FILE *fp);

/* Iterate over all counters in the set; call the 
 * given function once for each item, passing 
 * (arg, key, count). Ignore if NULL counter set or 
 * NULL itemfunc */
void counters_iterate(counters_t *ctrs, void *arg, 
                      void (*itemfunc)(void *arg, 
                                       const int key, const int count));

/* Delete the whole counterset; ignore NULL counter 
 * set. */
void counters_delete(counters_t *ctrs);
```

### Implementation

We implement this counter set as a linked list.
The *counter set* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counter set is empty.

Each node in the list is a `struct cnode`, a type defined internally to the module.
Each cnode includes an `int key`, `int value`, and a pointer to the next cnode on the list.

To insert a new counter in the counter set we create a new cnode to hold a `key`, and insert it at the head of the list.

The `counters_iterate` method calls the `itemfunc` function on each key by scanning the linked list.

### Compilation

To compile, simply `make`.

To test, simply `make test` or `make test &> testing.out`.
Details of test run commented in `counterstest.c`.

To clean up directory, simply `make clean`.