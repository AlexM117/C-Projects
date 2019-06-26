// Alex Marlow          gcc on a linux VM was used to compile this code
//This is the driver for a program that mimicks tracking memory fragmentation with tables

//include ordering is important
#include "Process.h"
#include "procTable.h"
#include "partTable.h"
#include <stdio.h>
#include <stdlib.h>

//functions declerations
void prntVals(partTblPtr myPartTable, procTblPtr myProcTable);
void delProcess(partTblPtr myPartTable, procTblPtr myProcTable);
void addProcess(partTblPtr myPartTable, procTblPtr myProcTable, int * IDinc);

//main method drives program
void main() {

    //partition count, partition size, choice and PID index variables
    int partNumber, partSize,choice;
    int x = 1;
    int *IDinc = &x;

    //get values for tables
    printf("Enter the number of partitions:");
    scanf("%d",&partNumber);
    printf("\n");
    printf("Enter size of each partition:");
    scanf("%d",&partSize);
    printf("\n");

    //initialize tables
    partTblPtr myPartTable = createTblPtr(partNumber,partSize);
    procTblPtr myProcTable = creatProcTbl(partNumber);

    //main loop for program
    while(1) {
        //ask person what they want to do and get choice
        printf("Do you want to\n");
        printf("Add a process? Enter 1\n");
        printf("Delete a process? Enter 2\n");
        printf("Print values? Enters 3\n");
        printf("Quit? Enter 4\n");
        scanf("%d",&choice);
        //call method for correct choice
        //add process
        if(choice == 1){
            addProcess(myPartTable, myProcTable, IDinc);
        //delete a process
        } else if(choice == 2) {
            delProcess(myPartTable, myProcTable);
        //print tables
        } else if(choice == 3) {
            prntVals(myPartTable, myProcTable);
        //deallocate memory and close program
        } else if(choice == 4) {
            // deallocate tables
            destroyPartTable(myPartTable);
            destroyProcTable(myProcTable);
            return;
        }
    }
}

//function adds a process to the tables
void addProcess(partTblPtr myPartTable, procTblPtr myProcTable, int * IDinc) {
    int size;
    //get process information
    printf("Adding - enter process size:");
    scanf("%d",&size);
    printf("\n");
    //create a process struct
    processPoint newProc = creat(*IDinc, size);
    //increment process ID counter
    *IDinc = *IDinc + 1;
    //check if process will fit into the tables
    int fit = canFit(newProc, myPartTable);
    if(fit == 1) {
        //adds to both partition and process tables
        addP2T(newProc, myPartTable, myProcTable);
    } else {
        printf("cannot fit process\n");
    }
    //free memory for process ADT once tables have info
    destroyProcess(newProc);
}

//function deletes a process from the tables
void delProcess(partTblPtr myPartTable, procTblPtr myProcTable) {
    int PiD;
    //get PID to delete
    printf("Enter PID you want to delete:");
    scanf("%d",&PiD);
    printf("\n");
    //clear process form partition table
    clearPart(myPartTable, PiD);
    //clear process from process table
    delProcAttProcTbl(myProcTable, PiD);

}

//function prints both tables
void prntVals(partTblPtr myPartTable, procTblPtr myProcTable) {
    printf("Printing-\n----------------------------------------\n");
    //prints process table
    printProcTable(myProcTable);
    //prints partition table
    printPartTable(myPartTable);
}
