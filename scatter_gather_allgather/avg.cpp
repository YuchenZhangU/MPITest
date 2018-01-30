// Program that computes the average of an array of elements in parallel using MPI_Scatter and MPI_Gather


#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>

float *create_rand_nums(int num_elements){
    float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
    assert(rand_nums != NULL);
    for(int i=0; i< num_elements; i++){
        rand_nums[i] = rand()/(float)RAND_MAX;
    }
    return rand_nums;
}


float compute_avg(float *array, int num_elements){
    float sum = 0.0f;
    for(int i=0;i<num_elements; i++){
        sum += array[i];
    }
    return sum / num_elements;
}

int main(int argc, char** argv){
    if(argc!=2){
        fprintf(stderr, "Usage: please input a num_elements_per_proc\n");
        exit(1);
    }

    int num_elements_per_proc = atoi(argv[1]);
    srand(time(0));

    MPI_Init(NULL,NULL);
    
    int cup_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &cup_id);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    float *rand_nums = NULL;
    if(cup_id==0){
        rand_nums =  create_rand_nums(num_elements_per_proc * world_size);
    }
    
    float *sub_rand_nums = (float*)malloc(sizeof(float)* num_elements_per_proc);
    assert(sub_rand_nums != NULL);
    
    MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, 
            sub_rand_nums, num_elements_per_proc, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);
    float *sub_avgs = NULL;
    if(cup_id == 0){
       sub_avgs = (float *)malloc(sizeof(float) * world_size);
       assert(sub_avgs != NULL);
    }
    
    MPI_Gather(&sub_avg, 1, MPI_FLOAT,
            sub_avgs, 1, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    float avg;
    if(cup_id == 0){
        avg = compute_avg(sub_avgs, world_size);
        printf("Avg computed using parallel method is %f\n", avg);
        float original_avg = 
            compute_avg(rand_nums, num_elements_per_proc * world_size);
        printf("Avg computed across original data is %f\n", original_avg);
    }

    if(cup_id == 0){
        free(rand_nums);
        free(sub_avgs);
    }
    free(sub_rand_nums);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}

