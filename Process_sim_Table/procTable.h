//Alex Marlow
//Header file for procTable.c, the process table ADT

#define PROCTABLE_H

//define pointer to process table structure
typedef struct procTbl * procTblPtr;

//function headers for procTable.c
procTblPtr creatProcTbl(int partCount);
void addProc2ProcTbl(procTblPtr TblPtr,processPoint Pptr, int partCount);
void addFrame2Proc(procTblPtr TblPtr,int PiD, int frame);
void delProcAttProcTbl(procTblPtr TblPtr, int PiD);
void destroyProcTable(procTblPtr Tptr);
void printProcTable(procTblPtr Tptr);
