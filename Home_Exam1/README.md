-Use p2p-Gnutella05.txt to compare speed for 2D table vs CRS formats. (Max for 2D table)
-Use web-NotreDame.txt for CRS format.
-Use 8-webpages.txt to test that our functions perform as they should. Done in test_simple.c

*Windows:
Compile:
Terminal> gcc -O3 (-fopenmp) -o <"program".exe> <"program".c>
Execute:
Terminal> <"program".exe> <"text-file".txt> <Task> <n>

(-fopenmp) only used for parallel.
program = Test_program_OMP (parallel) / Test_program  / test_simple (cross-check)
Task = 2D or CRS
n only needed for CRS.

*File: ../8-webpages.txt for testing our functions:
-Works as expected

*File: ../p2p-Gnutella05.txt for 2D format:
-Parallel; Time taken reading: 29.000044 ms
	   Time taken counting: 180.999924 ms

-Normal;   Time taken reading: 32.000000 ms
	   Time taken counting: 530.000000 ms

*File: ../p2p-Gnutella05.txt for 2D vs CRS format (normal):
-2D;    Time taken reading: 29.000044 ms
	Time taken counting: 180.999924 ms

-CRS;   Time taken reading: 11.000000 ms
	Time taken counting: 0.000000 ms
	(Time taken sorting top webpages: 7.000000 ms)

*File: ../p2p-Gnutella05.txt for 2D vs CRS format (parallel):
-2D;	Time taken reading: 29.000044 ms
	Time taken counting: 180.999924 ms

-CRS;	Time taken reading: 9.999990 ms
	Time taken counting: 0.999928 ms
	Time taken sorting top webpages: 3.999949 ms

*File: ../web-NotreDame.txt for CRS format: (vary number of threads)
-Parallel; Time taken reading: 392.000198 ms
	   Time taken counting: 3.000021 ms              (threads = 2)
	   Time taken sorting top webpages: 6.000135 ms  (threads = 4)

-Normal;   Time taken reading: 391.000000 ms
	   Time taken counting: 3.000000 ms
	   Time taken sorting top webpages: 10.000000 ms

Delivery: Change name of programs according to report!!!!
-One *.c file for each function and test file
-README.txt file
-Makefile
-Report

