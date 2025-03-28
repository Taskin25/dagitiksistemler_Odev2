#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h> // INT_MIN

#define ARRAY_SIZE 10000000
#define MASTER 0

int main(int argc, char** argv) {
    int world_size, world_rank;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int chunk_size = ARRAY_SIZE / world_size;
    int *data = NULL;
    int *sub_array = (int*) malloc(chunk_size * sizeof(int));

    if (world_rank == MASTER) {
        data = (int*) malloc(ARRAY_SIZE * sizeof(int));
        srand(time(NULL));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            data[i] = rand() % 1000;
        }
        printf("Veri kümesi oluşturuldu. Paralel işlem başlatılıyor...\n");
    }

    start_time = MPI_Wtime();

    MPI_Scatter(data, chunk_size, MPI_INT, sub_array, chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    int local_sum = 0;
    int local_max = INT_MIN;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp for reduction(+:local_sum) reduction(max:local_max)
        for (int i = 0; i < chunk_size; i++) {
            local_sum += sub_array[i];
            if (sub_array[i] > local_max) {
                local_max = sub_array[i];
            }
        }

        printf("MPI Süreci %d - OpenMP Thread %d / %d çalışıyor\n", world_rank, thread_id, num_threads);
    }

    int global_sum = 0;
    int global_max = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, MASTER, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    if (world_rank == MASTER) {
        printf("Toplam Değer: %d\n", global_sum);
        printf("Maksimum Değer: %d\n", global_max);
        printf("Toplam Süre: %f saniye\n", end_time - start_time);
    }

    free(sub_array);
    if (world_rank == MASTER) free(data);

    MPI_Finalize();
    return 0;
}
