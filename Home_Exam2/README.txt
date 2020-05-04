*Compile and run manually in terminal (Windows):
# For Linux: use *.out instead of *.exe, and ./*.out when running executable. Maybe try gcc-9 if compilation failes with wrong version.
 <N> = integer, number of columns
 <M> = integer, number of rows
 <p> = integer, number of processors to use with MPI-parallelization

- To run the serial program for counting triple-friends of 10:
Compile:
	Terminal> gcc -O3 -o serial_main.exe serial_main.c
Run:
	Terminal> serial_main.exe <N> <M>

- To run the MPI-parallelized program for counting triple-friends of 10:
Compile:
	Terminal> mpicc -O3 -o MPI_main.exe MPI_main.c
Run:
	Terminal> mpiexec -n <p> MPI_main.exe <N> <M>
# Linux: Terminal> mpirun -n <p> ./MPI_main.out <N> <M> 


*Compile with Makefile (On Windows with MinGW):
	Terminal> mingw32-make.exe all_win


*Compile with Makefile (Linux):
	Terminal> make all_lin
# Might have to change CC in Makefile if gcc version not compatible.


# NOTE: In my MPI download on Windows, there were no mpicc included. So to link and compile with MPI, I had to create a static library to 
be used together with Mingw and the gcc compiler to work as a mpicc compiler. The compilation was then:

	Terminal> gcc -O3 -o MPI_main.exe MPI_main.c -I...\MPI\Include -L...\MPI\Lib -lmsmpi

where Include contains the mpi.h file, and Lib contains the library file at the end above.
