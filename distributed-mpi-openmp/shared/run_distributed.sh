#!/bin/bash

# Derleme
mpicc -fopenmp -o mpi_program mpi_program.c -lgomp

# MPI programını başlat
mpirun --allow-run-as-root --hostfile hostfile -np 4 ./mpi_program
