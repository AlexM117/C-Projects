pr1.out: driver.o Process.o procTable.o partTable.o
	gcc -o pr1.out driver.o  Process.o procTable.o partTable.o

driver.o: driver.c partTable.h procTable.h Process.h
	gcc -c driver.c

partTable.o: partTable.c partTable.h procTable.h Process.h
	gcc -c partTable.c

procTable.o: procTable.c procTable.h Process.h
	gcc -c procTable.c

Process.o: Process.c Process.h
	gcc -c Process.c


