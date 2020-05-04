CC := gcc
#CC := gcc-9 -std=c99
MPICC := mpicc
FLAGS := -Wall -g -O3

PROGRAMS_win := serial_main.exe MPI_main.exe 

PROGRAMS_lin := serial_main.out MPI_main.out 

DEP = common.h

.PHONY : clean

all_win: $(PROGRAMS_win)
	@echo Compiled all: Windows

all_lin: $(PROGRAMS_lin)
	@echo Compiled all: Linux

# Executables
# -Windows:
serial_main.exe : serial_main.c $(DEP)
	$(CC) $< -o $@ $(FLAGS)

MPI_main.exe : MPI_main.c $(DEP)
	$(MPICC) $< -o $@ $(FLAGS)


# -Linux:
serial_main.out : serial_main.c $(DEP)
	$(CC) $< -o $@ $(FLAGS) 

MPI_main.out : MPI_main.c $(DEP)
	$(MPICC) $< -o $@ $(FLAGS)

clean :
	rm -f *.o $(PROGRAMS_win)
	rm -f *.o $(PROGRAMS_lin)
	@echo All cleaned
