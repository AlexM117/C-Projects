//Alex Marlow
// file for Process ADT

#include "Process.h"
#include <stdlib.h>
#include <stdio.h>

//structure for a process
struct process {

int Pid;
int size;

};

//function allocates space and initializes a process structure
processPoint creat(int Id, int newSize) {

    processPoint newPointer = malloc(sizeof(struct process));
    newPointer->Pid = Id;
    newPointer->size = newSize;
    return newPointer;

}

//deallocates process structure
void destroyProcess(processPoint pro) {

    free(pro);

}

// returns the size of the process
int getProSize(processPoint pro) {

    return pro->size;

}

//returns the ID of the process
int getPID(processPoint pro) {

    return pro->Pid;

}
