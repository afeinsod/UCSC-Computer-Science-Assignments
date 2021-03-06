/*Alix Feinsod*/
/*CruzID: afeinsod*/
/*Class: CMPS 12B/M*/
/*queue.c*/
/*Queue for Lab 4*/

#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

#define MAXSIZE 100

int tests_run = 0; // keep track of number of unit tests run

typedef enum q_status {
    /* Enumerated status codes for queue operations */
    q_success = 0,
    q_failure
} q_status;

int list[MAXSIZE];
int back;
int size;
int front;
int isInitialized = 1; /* Variable to tell if the queue is initialized */

/**** Functions on queues ****/

q_status q_init(void) {
		isInitialized = 0;
		back = 0;
		front = 0;
		size = 0;
		return q_success;
}

q_status q_insert(int value) {
	if (size >= MAXSIZE) {
		return q_failure;
	}
	else {
		list[back] = value;
		if (back == MAXSIZE - 1) {
			back = 0;
		}
		else {
			back ++;
		}
		size ++;
		return q_success;
	}
}

q_status q_remove(int *value) {
	if (size <= 0 || value == NULL)
  	{
    		return q_failure;
  	}
	else if(size == 1)
  	{
		*value = list[front];
    		list[front]=0;
		size --;
		return q_success;
  	}
	else
  	{
   		*value = list[front];
		if (front == MAXSIZE - 1) {
			front = 0;
		}
		else { 
			front ++;
		}
		size --;
		return q_success;  	
	}
}

q_status q_peek(int *value) {
	if (size <= 0 || value == NULL) {
		return q_failure;
	}
	else {	
		*value = list[front];
		return q_success;
	}
}

q_status q_destroy(void) {
	if (isInitialized == 1) {
		return q_failure;
	}
	else { 
		for (int i = 0; i < 100; i++) {
		list[i] = 0;
		}
		isInitialized = 1;
		back = 0;
		front = 0;
		size = 0;
		return q_success;
	}
}

q_status q_is_empty(void) {
	if (size == 0) {
		return q_success;
	}
	else {
		return q_failure;
	}
}

/**** Unit tests ****/

char * test_lifecycle(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_one_insert(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(7) == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_one_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(16) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 16);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_two_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("insert", q_insert(91) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 91);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_multi_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("insert", q_insert(91) == q_success);
    for(int i = 0; i < 1000; i++) {
        mu_assert("insert", q_insert(8) == q_success);
        mu_assert("insert", q_insert(91) == q_success);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == 8);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == 91);
    }
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_indexed_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 1000; i++) {
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("insert", q_insert(30 + i) == q_success);
    }
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_too_many_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("remove", q_remove(&v) == q_failure);
    return NULL;
}

char * test_insert_too_many_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 30; i++) {
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
    }
    mu_assert("remove", q_remove(&v) == q_failure);
    return NULL;
}

char * test_peek(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_peek(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_peek_two(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("peek", q_peek(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_peek_deep(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 1000; i++) {
        mu_assert("peek", q_peek(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("insert", q_insert(30 + i) == q_success);
    }
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_peek_empty(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("peek", q_peek(&v) == q_failure);
    return NULL;
}

char * test_peek_two_empty(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("peek", q_peek(&v) == q_failure);
    return NULL;
}

char * test_remove_null(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_remove(NULL) == q_failure);
    return NULL;
}

char * test_peek_null(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_peek(NULL) == q_failure);
    return NULL;
}

char * test_insert_three_remove_three(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(3) == q_success);
    mu_assert("insert", q_insert(5) == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 3);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 5);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}


char * test_true_is_empty(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("isEmpty", q_is_empty() == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_false_is_empty(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(3) == q_success);
    mu_assert("isEmpty", q_is_empty() == q_failure);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * all_tests(void) {
    /* Run all unit tests */
    mu_run_test(test_lifecycle);
    mu_run_test(test_one_insert);
    mu_run_test(test_one_insert_remove);
    mu_run_test(test_two_insert_remove);
    mu_run_test(test_multi_insert_remove);
    mu_run_test(test_indexed_insert_remove);
    mu_run_test(test_too_many_remove);
    mu_run_test(test_insert_too_many_remove);
    mu_run_test(test_peek);
    mu_run_test(test_peek_two);
    mu_run_test(test_peek_deep);
    mu_run_test(test_peek_empty);
    mu_run_test(test_peek_two_empty);
    mu_run_test(test_remove_null);
    mu_run_test(test_peek_null);
    mu_run_test(test_insert_three_remove_three);
    mu_run_test(test_true_is_empty);
    mu_run_test(test_false_is_empty);
    return NULL;
}

/**** Main unit test runner ****/

int main(int argc, char *argv[]) {
    printf("Queue Module unit tests\n");
    char *result = all_tests();
    if (result) {
        printf("FAILURE at %s\n", result);
    } else {
        printf("ALL TESTS PASS\n");
    }
    printf("Tests run: %d\n", tests_run);
    return EXIT_SUCCESS;
}
 
