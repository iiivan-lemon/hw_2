#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prog.h"
#define TBB_PREVIEW_CONCURRENT_LRU_CACHE true
typedef struct {
    size_t col_start;
    size_t col_end;
    int *array;
    //size_t size;
    double Sx;
    double Sy;
    double Sxx;
    double Sxy;
    int is_last_thread;
} pthr_data_t;


void *thread_func(void *thread_data) {
    pthr_data_t *data = (pthr_data_t *) thread_data;
    for (size_t i = 0; i < data->col_end - data->col_start; ++i) {
        data->Sx += (data->col_start + i);
        data->Sy += data->array[i] ;
        data->Sxy += (data->col_start + i) * data->array[i] ;
        data->Sxx += (data->col_start + i) * (i + data->col_start) ;

    }
    return NULL;
}


res_coef *run_prog(int *a, const int size) {

    if (size <= 1) {
        return NULL;
    }
    size_t num_of_threads = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_of_threads > size) {
        num_of_threads = size;
    }
    size_t num_array_thread = size / num_of_threads;
    /*if (size % num_of_threads != 0 && size > num_of_threads) {
        size_t add_num_threads = 0;
        size_t residue_array = size % num_of_threads;
        if (residue_array % num_array_thread == 0) {
            add_num_threads = residue_array / num_array_thread;
        } else {
            add_num_threads = (residue_array / num_array_thread) + 1;
        }
        num_of_threads += add_num_threads;
    }*/


    pthread_t *threads = malloc(num_of_threads * sizeof(pthread_t));
    if (!threads) {
        //free(array);
        return NULL;
    }

    pthr_data_t *thread_data = malloc(num_of_threads * sizeof(pthr_data_t));
    if (!thread_data) {
        //free(array);
        free(threads);
        return NULL;
    }
    for (int i = 0; i < num_of_threads; i++) {
        if (i == num_of_threads - 1) {
            thread_data[i].col_end = size;
        } else thread_data[i].col_end = num_array_thread * (i + 1);

        thread_data[i].col_start = num_array_thread * i;
        thread_data[i].array = a + num_array_thread * i;
        thread_data[i].Sx = 0;
        thread_data[i].Sy = 0;
        thread_data[i].Sxx = 0;
        thread_data[i].Sxy = 0;
        //thread_data[i].size = size;



        pthread_create(&(threads[i]), NULL, thread_func, &thread_data[i]);
    }


    res_coef *res = malloc(sizeof(res_coef));
    if(!res){
        return NULL;
    }

    double res_Sx = 0;
    double res_Sy = 0;
    double res_Sxy = 0;
    double res_Sxx = 0;
    for (size_t i = 0; i < num_of_threads; i++) {

        if (pthread_join(threads[i], NULL) != 0) {
            free(threads);
            free(thread_data);
            return NULL;
        }
    }

    free(threads);


    for (size_t i = 0; i < num_of_threads; i++) {
        /*printf("%f --- SX%zu test\n", thread_data[i].Sx,i);
        printf("%f --- SY%zu test\n", thread_data[i].Sy,i);
        printf("%f --- SXX%zu test\n", thread_data[i].Sxx,i);
        printf("%f --- SXY%zu test\n", thread_data[i].Sxy,i);*/
        res_Sx += thread_data[i].Sx ;
        res_Sy += thread_data[i].Sy ;
        res_Sxx += thread_data[i].Sxx;
        res_Sxy += thread_data[i].Sxy;
    }
    free(thread_data);
    res->k = (res_Sxy * size - res_Sx*res_Sy) / (res_Sxx * size - res_Sx*res_Sx);
    res->b = (res_Sy - res->k * res_Sx) / size;
    return res;
}


