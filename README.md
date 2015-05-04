# parallel
MPI and OPENMP programs shared here !

## To install MPI :

sudo apt-get install lam4-dev

## To run MPI :

1. lamboot
2. mpicc program.c -o program
3. mpirun -np <no. of processors> ./program

## To run OpenMP :

1. gcc -fopenmp program.c -o program
2. ./program
3. To change the number of processors : export OMP_NUM_THREADS=<number>
