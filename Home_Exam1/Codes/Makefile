CC := gcc
FLAGS = -Wall

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))

.PHONY : all clean

all: $(PROGRAMS)

Test_example.exe : Test_example.c
	$(CC) $< -o $@ -O3 $(FLAGS)

Test_functions.exe : Test_functions.c
	$(CC) $< -o $@ -O3 $(FLAGS)

Test_functions_OMP.exe : Test_functions_OMP.c
	$(CC) $< -o $@ -O3 -fopenmp $(FLAGS)

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)