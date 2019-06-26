//Alex Marlow
//header file for Process.c

#define PROCESS_H

//define pointer to process structure
typedef struct process *processPoint;

//function headers
processPoint creat(int Id, int newSize);
void destroyProcess(processPoint pro);
int getProSize(processPoint pro);
int getPID(processPoint pro);
