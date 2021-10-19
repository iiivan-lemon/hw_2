#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prog.h"

typedef struct {
    int col_start;
    int col_end;
    int *array;
    double Sx;
    double Sy;
    double Sxx;
    double Sxy;
    int is_last_thread;
} pthr_data_t;


void *thread_func(void *thread_data) {
    pthr_data_t *data = (pthr_data_t *) thread_data;
    for (int i = 0; i < data->col_end - data->col_start; ++i) {
        data->Sx += data->col_start + i;
        data->Sy += data->array[i];
        data->Sxy += (data->col_start + i) * data->array[i];
        data->Sxx += (data->col_start + i) * (i + data->col_start);
    }


    return NULL;
}


res_coef *linear_regress(int *a, const int size) {

    int num_of_threads = sysconf(_SC_NPROCESSORS_ONLN);
    int num_array_thread = size / num_of_threads;
    if (size % num_of_threads != 0) {
        int add_num_threads = 0;
        int residue_array = size % num_of_threads;
        if (residue_array % num_array_thread == 0) {
            add_num_threads = residue_array / num_array_thread;
        } else {
            add_num_threads = (residue_array / num_array_thread) + 1;
        }
        num_of_threads += add_num_threads;
    }


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
        if( i == num_of_threads -1){
            thread_data[i].col_end = size;
        } else thread_data[i].col_end = num_array_thread * (i + 1);

        thread_data[i].col_start = num_array_thread * i;
        thread_data[i].array = a + num_array_thread * i;
        thread_data[i].Sx = 0;
        thread_data[i].Sy = 0;
        thread_data[i].Sxx = 0;
        thread_data[i].Sxy = 0;


        //запускаем поток
        pthread_create(&(threads[i]), NULL, thread_func, &thread_data[i]);
    }


    res_coef *res = malloc(sizeof(res_coef));


    double res_Sx = 0;
    double res_Sy = 0;
    double res_Sxy = 0;
    double res_Sxx = 0;
    for (size_t i = 0; i < num_of_threads; i++) {
        printf("%f --- SX%zu test\n", thread_data[i].Sx,i);
        printf("%f --- SY%zu test\n", thread_data[i].Sy,i);
        printf("%f --- SXX%zu test\n", thread_data[i].Sxx,i);
        printf("%f --- SXY%zu test\n", thread_data[i].Sxy,i);
        res_Sx += thread_data[i].Sx;
        res_Sy += thread_data[i].Sy;
        res_Sxx += thread_data[i].Sxx;
        res_Sxy += thread_data[i].Sxy;
        res_Sx /= size;
        res_Sy /= size;
        res_Sxx /= size;
        res_Sxy /= size;
        res->k = (res_Sx * res_Sy - res_Sxy) / (res_Sx * res_Sx - res_Sxx);
        res->b = (res_Sxy - res->k * res_Sxx) / res_Sx;
        if (pthread_join(threads[i], NULL) != 0) {
            // free(array);
            free(threads);
            free(thread_data);
            return NULL;
        }
    }

    free(threads);
    free(thread_data);
    return res;
}


