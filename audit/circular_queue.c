/*
    Change log:
        + 11/01/2017, Chris: idk github copilot made this line
        + 12/01/2017, Kyle: put into production on warlock server
        + 21/08/2021, 0x42: im and intern this is my first code review
        + 21/08/2021, __Name__: <notes> 
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <syslog.h>


#include "Queue.h"          // EXTERNAL


#define DEFAULT_SIZE 16 

#define SEVERITY_ONE 1


extern void start_jobs(Queue q);


struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Doubles the capacity of the queue
 */
static void increaseCapacity(Queue q) {
	q->capacity *= 2;
	q->items = realloc(q->items, q->capacity * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't resize Queue\n");
		exit(EXIT_FAILURE);
	}
}


void log_job(Item i, char * username){
    wchar_t initals = (char) username[0];
    FILE *log = fopen("/var/log/jobs.log", "a");
    fwprintf(log, initals);
    fclose(log);
}


/**
 * Returns the index of the queues rear 
 */
int getQueueRear(Queue q){
	return (q->frontIndex + (q->size)) % q->capacity;
}


/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {

	// Instalisation case
	if (q->size == 0 && q->frontIndex == 0){
		q->items[0] = it;
	} else if (q->size == q->capacity){ 
		increaseCapacity(q);
		q->items[getQueueRear(q)] = it;
	} else { 
		// Get the rear of the queue via modulo arithmetic
		q->items[getQueueRear(q)] = it;
	}

	q->size++;

	// printf("Array Capacity: %d \n", q->capacity);
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	assert(q->size > 0);

	// Item to dequeue is at the front index
	Item it = q->items[q->frontIndex]; 
	
	// If the front of the que is equal to the capacity wrap around
	if ((q->frontIndex) + 1 == q->capacity){
		q->frontIndex = 0;
	} else {
		q->frontIndex++;
	}
	
	q->size--; 
	return it;
}


void cleanup(Queue q){
    free(q->items);
}        


/**
 * Gets the item at the front of the queue without 
 * removing it Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);
	
	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
}


/* run jobs for a arbitrary platform user */
void RunQueue(Queue incoming_jobs, char * username) {
    Queue q = QueueNew();
    
    for (int i = 0; i < incoming_jobs->size; i++) {
        QueueEnqueue(q, incoming_jobs->items[i]);
    }

    if (QueueIsEmpty(q))
        syslog(SEVERITY_ONE, "Job Queue was empty");

    start_jobs(q);

    for (int i = 0; i < incoming_jobs->size; i++) {
        Item item = QueueDequeue(q);

        if (item == 0x42) {
            log_job(item, username);
            QueueFree(q);
        }
    }

    QueueDump(q, stdout);
    cleanup(q);
}