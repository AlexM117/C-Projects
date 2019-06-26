//Alex Marlow
//file provides process table ADT

//include order is important
#include "Process.h"
#include "procTable.h"
#include <stdlib.h>
#include <stdio.h>



//structure for process in the table
struct proc {

    int Pid;
    int size;
    int * frames;
    int frameCnt;

};



//structure for process table
struct procTbl {

    int size;
    struct proc * Pptr;

};



// function initializes process table
procTblPtr creatProcTbl(int partCount) {

    //allocates memory for table and initializes size
    procTblPtr newTbl = malloc(sizeof(struct procTbl));
    newTbl->size = 0;
    //allocates space for processes
    newTbl->Pptr = malloc(sizeof(struct proc)*partCount);
    return newTbl;

}



// function adds a process to the process table
void addProc2ProcTbl(procTblPtr TblPtr,processPoint Pptr, int partCount) {

    //initialize values for process
    TblPtr->Pptr[TblPtr->size].Pid = getPID(Pptr);
    TblPtr->Pptr[TblPtr->size].size = getProSize(Pptr);
    TblPtr->Pptr[TblPtr->size].frameCnt = 0;
    //allocate memory used to store what frames and used for that process
    TblPtr->Pptr[TblPtr->size].frames = malloc(sizeof(int) * partCount);
    //increment table process count
    TblPtr->size++;


}



//function adds frames used by a process to its part in the table
void addFrame2Proc(procTblPtr TblPtr,int PiD, int frame) {

    int x = 0;
    //loops untill correct process is found
    while(TblPtr->Pptr[x].Pid != PiD && x < TblPtr->size) {
        x++;
    }
    //error if wrong process entered
    if(x == TblPtr->size) {
        printf("Error, attempting to add frame to PID that DNE");
    //adds frame to the process
    } else {
        TblPtr->Pptr[x].frames[TblPtr->Pptr[x].frameCnt] = frame;
        TblPtr->Pptr[x].frameCnt++;
    }

}



// function deletes a process from the table
void delProcAttProcTbl(procTblPtr TblPtr, int PiD) {

    int x = 0;
    //loops untill correct process is found
    while(TblPtr->Pptr[x].Pid != PiD && x < TblPtr->size) {
        x++;
    }
    //error if process does not exist
    if(x == TblPtr->size) {
        printf("Error, attempting to delete PID that DNE");
    } else {
        //changes all the values to the next process in the table
        TblPtr->Pptr[x].Pid = TblPtr->Pptr[x + 1].Pid;
        TblPtr->Pptr[x].size = TblPtr->Pptr[x + 1].size;
        TblPtr->Pptr[x].frameCnt = TblPtr->Pptr[x + 1].frameCnt;
        //deallocates memory for frames and points ppointer to frames of next process in table
        free(TblPtr->Pptr[x].frames);
        TblPtr->Pptr[x].frames = TblPtr->Pptr[x + 1].frames;
        x++;
        //loops through rest of the processes moving them back oneplace similar to previous couple lines
        while(x < TblPtr->size - 1) {
            TblPtr->Pptr[x].Pid = TblPtr->Pptr[x + 1].Pid;
            TblPtr->Pptr[x].size = TblPtr->Pptr[x + 1].size;
            TblPtr->Pptr[x].frameCnt = TblPtr->Pptr[x + 1].frameCnt;
            TblPtr->Pptr[x].frames = TblPtr->Pptr[x + 1].frames;
            x++;
        }
        // decrement table size
        TblPtr->size--;
    }

}



//function prints the process talbe
void printProcTable(procTblPtr Tptr) {

    int x,y;
    // print title and column titles
    printf("Process Table:\n");
    printf("ProcessID      Frames\n");
    //loops through table printing process information
    for(x = 0; x < Tptr->size; x++) {
        printf("%-15d",Tptr->Pptr[x].Pid);
        //prints frames
        for(y = 0;y < Tptr->Pptr[x].frameCnt; y++) {
            printf("%d,",Tptr->Pptr[x].frames[y]);
        }
        printf("\n");

    }
    //print ending
    printf("------------------------------------------\n");

}



//function deallocates emory for process table
void destroyProcTable(procTblPtr Tptr) {
    int x;
    //loops through table deallocating memory for frames
    for(x = 0; x < Tptr->size; x++) {
       free(Tptr->Pptr[x].frames);
    }
    //deallocates processes
    free(Tptr->Pptr);
    //deallocates table
    free(Tptr);

}
