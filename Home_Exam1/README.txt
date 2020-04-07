*Compile and run manually in terminal (Windows):
# For Linux: use *.out instead of *.exe, and ./*.out when running executable. Maybe try gcc-9 when compiling for other version.

-Use 8-webpages.txt to test that our functions perform as they should.
Compile:
	Terminal> gcc -O3 -o Test_example.exe Test_example.c
Run:
	Terminal> Test_example.exe

-Use p2p-Gnutella05.txt to compare speed for 2D table vs CRS formats (Maximum size for 2D table).
-Use web-NotreDame.txt for CRS format serial vs parallel.
Compile:
	Terminal> gcc -O3 -o Test_functions.exe Test_functions.c
Run:
	Terminal> Test_functions.exe p2p-Gnutella05.txt 2D
	or
	Terminal> Test_functions.exe <filename>.txt CRS 8

-To run the parallel versions:
Compile:
	Terminal> gcc -O3 -fopenmp -o Test_functions_OMP.exe Test_functions_OMP.c
Run:
	Terminal> Test_functions.exe p2p-Gnutella05.txt 2D
	or
	Terminal> Test_functions.exe <filename>.txt CRS 8


*Compile with Makefile (On Windows with MinGW):
	Terminal> mingw32-make.exe all_win


*Compile with Makefile (Linux):
	Terminal> make all_lin
# Might have to change CC in Makefile if gcc version not compatible.