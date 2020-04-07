CC := gcc
#CC := gcc-9
FLAGS := -Wall -g

PROGRAMS_win := Test_example.exe Test_functions.exe Test_functions_OMP.exe

PROGRAMS_lin := Test_example.out Test_functions.out Test_functions_OMP.out

.PHONY : all clean

all_win: $(PROGRAMS_win)
	@echo Compiled all: Windows

all_lin: $(PROGRAMS_lin)
	@echo Compiled all: Linux

# Executables
# -Windows:
Test_example.exe : Test_example.c
	$(CC) $(FLAGS) $< -o $@ -O3 -std=c99

Test_functions.exe : Test_functions.c
	$(CC) $(FLAGS) $< -o $@ -O3 -std=c99

Test_functions_OMP.exe : Test_functions_OMP.c
	$(CC) $(FLAGS) $< -o $@ -O3 -fopenmp -std=c99

# -Linux:
Test_example.out : Test_example.c
	$(CC) $(FLAGS) $< -o $@ -O3 -std=c99

Test_functions.out : Test_functions.c
	$(CC) $(FLAGS) $< -o $@ -O3 -std=c99

Test_functions_OMP.out : Test_functions_OMP.c
	$(CC) $(FLAGS) $< -o $@ -O3 -fopenmp -std=c99


clean :
	rm -f *.o $(PROGRAMS_win)
	rm -f *.o $(PROGRAMS_lin)
	@echo All cleaned
