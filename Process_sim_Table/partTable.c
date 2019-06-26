//Alex Marlow
// file for partition table ADT

//include order is important
#include "Process.h"
#include "procTable.h"
#include "partTable.h"
#include <stdlib.h>
#include <stdio.h>

//structure for a partition in the table
struct partition {

    int frag;
    int avalable;
    int Pid;

};

//structure for partition table
struct partTable {

    int partSize;
    int Tsize;
    struct partition * TblPtr;

};

//function creates a new partition table and initializes values
partTblPtr createTblPtr(int parCount, int parSize) {

    //allocate space for table and initialize
    partTblPtr newTbl = malloc(sizeof(struct partTable));
    newTbl->partSize = parSize;
    newTbl->Tsize = parCount;
    // allocate space for partitions
    newTbl->TblPtr = malloc(sizeof(struct partition)*parCount);
    int x;
    //initialize for each parition in table
    for(x = 0; x < parCount; x++) {
        newTbl->TblPtr[x].frag = -1;
        newTbl->TblPtr[x].avalable = 1;
        newTbl->TblPtr[x].Pid = -1;
    }
    return newTbl;

}

//function adds a process to the partition table and calls function for process table
void addP2T(processPoint Pptr,partTblPtr Tptr,procTblPtr PRptr) {

    // space is used for space still needed to be fit into a partition
    int space = getProSize(Pptr);
    int x = 0;
    //adds process to the process table
    addProc2ProcTbl(PRptr,Pptr, Tptr->Tsize);
    //loops through partitions, filling in empty ones needed
    while(space != 0) {
        if(Tptr->TblPtr[x].avalable == 1) {
            //fills in partition completely if needed
            if(Tptr->partSize <= space) {
                space -= Tptr->partSize;
                Tptr->TblPtr[x].avalable = 0;
                Tptr->TblPtr[x].frag = 0;
                Tptr->TblPtr[x].Pid = getPID(Pptr);
                //Adds partition frame to process on the process table
                addFrame2Proc(PRptr,Tptr->TblPtr[x].Pid,x);
            //makes a partialy filled partition
            } else {
                Tptr->TblPtr[x].avalable = 0;
                Tptr->TblPtr[x].frag = Tptr->partSize - space;
                space = 0;
                Tptr->TblPtr[x].Pid = getPID(Pptr);
                //Adds partition to process on the process table
                addFrame2Proc(PRptr,Tptr->TblPtr[x].Pid,x);
            }
        }
        //increment partition counter
        x++;

    }

}


//function checks if process will fit into memory
int canFit(processPoint Pptr,partTblPtr Tptr) {
    int x = 0;
    //space needed
    int space = getProSize(Pptr);

    //loop through the paritions
    while(x < Tptr->Tsize && !(space <= 0)) {
        //check if partition avalable
        if(Tptr->TblPtr[x].avalable == 1) {
            space -= Tptr->partSize;
        }
        x++;
    }
    //check if there is enough room for process
    if(!(space <= 0)) {
        return 0;
    }
    return 1;

}

//function prints the partition table
void printPartTable(partTblPtr Tptr) {
    int x;
    //print title column titles
    printf("Partition Table:\n");
    printf("Partition number   ProcessID   Frag    Avalability\n");
    //loop through table
    for(x = 0; x < Tptr->Tsize; x++) {
        //if parition is free
        if(Tptr->TblPtr[x].avalable){
            printf("%-18d ?           ?       Y\n",x);
        // if partition is not free
        } else {
            printf("%-18d %-11d %-7d N\n",x,Tptr->TblPtr[x].Pid,Tptr->TblPtr[x].frag);
        }
    }
    // end
    printf("----------------------------------------------------------\n");
}

//function clears a partition
void clearPart(partTblPtr Tptr, int PiD) {

    int x;
    //loops through partition table and clears paritions that have the correct PID
    for(x = 0; x < Tptr->Tsize; x++) {
        if(PiD == Tptr->TblPtr[x].Pid){
            Tptr->TblPtr[x].frag = -1;
            Tptr->TblPtr[x].avalable = 1;
            Tptr->TblPtr[x].Pid = -1;

        }

    }



}

//function deallocates partition table structure
void destroyPartTable(partTblPtr Tptr) {

    //free table partitions
    free(Tptr->TblPtr);
    //free table
    free(Tptr);

}
