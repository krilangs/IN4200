CC := gcc
FLAGS = -Wall

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))

.PHONY : clean

all: Test_example.exe Test_functions.exe Test_functions_OMP.exe
	echo All done

example: Test_example.exe
	echo Test_example done

functions: Test_functions.exe
	echo Test_functions done

functions_OMP: Test_functions_OMP.exe
	echo Test_functions_OMP done

# Executables
Test_example.exe : Test_example.c
	$(CC) $< -o $@ -O3 $(FLAGS) -std=c99

Test_functions.exe : Test_functions.c
	$(CC) $< -o $@ -O3 $(FLAGS) -std=c99

Test_functions_OMP.exe : Test_functions_OMP.c
	$(CC) $< -o $@ -O3 -fopenmp $(FLAGS) -std=c99

clean :
	rm -f *.o $(PROGRAMS)
	echo All cleaned