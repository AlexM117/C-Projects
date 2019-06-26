// Aelx Marlow
// Header file for partTable.c, the partition table ADT file

#define PARTTABLE_H

//define pointer to partition table structure
typedef struct partTable * partTblPtr;

//function headers for partTable.c
partTblPtr createTblPtr(int parCount, int parSize);
void addP2T(processPoint Pptr,partTblPtr Tptr,procTblPtr PRptr);
int canFit(processPoint Pptr,partTblPtr Tptr);
void clearPart(partTblPtr Tptr, int PiD);
void destroyPartTable(partTblPtr Tptr);
void printPartTable(partTblPtr Tptr);
