//
// Created by liu_property on 2022/10/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 6
int value[NUM_THREADS];


/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
    int tid;
    double stuff;
} thread_data_t;

/* thread function */
void * thr_func(void *arg) {
//    thread_data_t *data = (thread_data_t *) arg;
//    printf("hello from thr_func, thread id: %d\n", data->tid);
//    pthread_exit(NULL);
    int thread_id = (int) arg;
    printf("hello from thr_func, thread id: %d\n", thread_id);
//    pthread_exit((void *)value[thread_id]);
 pthread_exit(NULL);
}
#include "useful_function.h"

int main(int argc, char **argv) {
    printf("judge: %d\n", NULL==0);
    pthread_t thr[NUM_THREADS];
    int i, rc;
    /* create a thread_data_t argument array */
    thread_data_t thr_data[NUM_THREADS];

    /* create threads */
    for (i = 0; i < NUM_THREADS; ++i) {
        thr_data[i].tid = i;
//        if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
//        if ((rc = pthread_create(thr+i, NULL, thr_func, thr_data+i))) {
        if ((rc = pthread_create(&thr[i], NULL, thr_func, (void *) i))) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
        }
    }

    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
//        pthread_join(thr[i], (void  **)value[i]);
    }
        print_mat_1(NUM_THREADS, value);
    printf("SUCCESS\n");

    print_mat_1(NUM_THREADS, value);
    return EXIT_SUCCESS;
}
