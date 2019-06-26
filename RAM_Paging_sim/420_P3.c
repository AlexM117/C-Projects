//Alex Marlow  TCES 420 Project 3   Page Memory w/TLB    11/23/2018

//program simulates a paged memory with a TLB and using FIFO for both page management and the TLB


#include <stdio.h>
#include <stdbool.h>

//sizes for table and TLB
#define TABLE_SIZE 256
#define PAGE_SIZE 256
#define FRAME_COUNT 256  //make 128 for page handling to kick in
#define ADDR_NUM 1000
#define TLB_SIZE 16

//talbe,TLB, memory, and global variables
int Ptable[TABLE_SIZE];
bool Vtable[TABLE_SIZE];
char memory[PAGE_SIZE*FRAME_COUNT];
int tlb[2][TLB_SIZE];
int tlbPoint;
int point;
int miss;
int tlbHit;

//functions
int getAddr(FILE *address);
int getPhAddr(FILE *disk, int addr);


//main takes address file name as input and completes task of finding the value
void main(int argc, char *argv[]) {

	//initialize global varialbes
	tlbHit = 0;
	tlbPoint = 0;
	miss = 0;
	point = 0;
	//variables for virtual and physical address
	int addr;
	int Phaddr;

	//clear valid and pages for table
	for(int i = 0; i < TABLE_SIZE; i++) {
		Vtable[i] = false;
	}
	for(int i = 0; i <TABLE_SIZE; i++) {
		Ptable[i] = -1;
	}

	//open files
	FILE *address = fopen(argv[1],"r");
        if(address == NULL) {
                printf("error opening address file");
        }

        FILE *disk = fopen("BACKING_STORE.bin","r");
        if(disk == NULL) {
                printf("error opening disk file");
        }


	//loop through address file
	for(int i = 0; i < ADDR_NUM; i++) {
		//get virtual address from file and print
		addr = getAddr(address);
		printf("Virtual address: %d    ", addr);
		//get physical address from memory and print
		Phaddr = getPhAddr(disk, addr);
		printf("Physical address: %d    ", Phaddr);
		//print value at that location in physical memory
		printf("Value: %d\n", memory[Phaddr]);
	}
	//print page fualt rate and TLB hit rate
	printf("page fault rate: %f\n",(float)miss/(float)ADDR_NUM);
	printf("TLB hit rate: %f\n", (float)tlbHit/(float)ADDR_NUM);

}


//function takes pointer to storage disk and virtual address and returns physical address
int getPhAddr(FILE *disk, int addr) {

	//masks for address
        int pageMask = 65280;
        int offMask = 255;

	//variabls
        int page = 0;
        int offset = 0;

	//mask virtual addresss for page and offset
        page = ((addr & pageMask)>>8);
	offset = (addr & offMask);


	//check TLB for value
	for(int i = 0; i < TLB_SIZE; i++) {
		if(tlb[0][i] == page) {
			tlbHit++;
			return ((tlb[1][i]<<8) + offset);
		}
	}

	//if TLB miss

	//check table for page
	if(Vtable[page] == true) {
		//Update TLB with page
		tlb[0][tlbPoint] = page;
		tlb[1][tlbPoint] = Ptable[page];
		tlbPoint++;
		//reset TLB counter if needed
		if(tlbPoint == TLB_SIZE) {
			tlbPoint = 0;
		}
		//return physical address
		return ((Ptable[page]<<8) + offset);
	//if page table miss
	} else {
		miss++;
		//check if page table has a page pointing to the FIFO frame you are replacing
		for(int i = 0; i < TABLE_SIZE; i++) {
			if(Ptable[i] == point) {
				//turn that page off
				Vtable[i] = false;
			}
		}
		//turn new page on and make it point to current FIFO frame
		Vtable[page] = true;
		Ptable[page] = point;

		//Update TLB
		tlb[0][tlbPoint] = page;
               	tlb[1][tlbPoint] = Ptable[page];
              	tlbPoint++;
		//reset TLB counter if needed
               	if(tlbPoint == TLB_SIZE) {
               	       tlbPoint = 0;
	        }

		//set file pointer to corrent position in storage
		fseek(disk, page*PAGE_SIZE, SEEK_SET);
		//read storage into selected frame of memory
		fread(&memory[point<<8], 1, 256, disk);
		//change to next FIFO frame and reset if needed
		point++;
		if(point == FRAME_COUNT) {
			point = 0;
		}
		//return physical address
		return ((Ptable[page]<<8) + offset);
	}

	//error return
	return -1;
}


//converts line of char numbers from file to an int
int getAddr(FILE *address) {

	//array for max 32 bit number in characters
	int num[10] = {0,0,0,0,0,0,0,0,0,0};
	//variables
	int cnt = 0;
	int addr = 0;
	int place = 0;
	int temp = 0;
	bool lineEn = false;

	//get character numbers from file
	while(!lineEn) {
		fread(&num[cnt], 1, 1, address);
		//check for line end
		if(num[cnt] == 10) {
			lineEn = true;
		}
		cnt++;
	}
	//move back to ones place character
	cnt = cnt -2;
	//add numbers together in with proper place values
	while(cnt != -1) {
		//getfrom ascii to number
		temp = (num[cnt] - 48);
		//multiply by 10 apropriet number of times for place value
		for(int i = 0; i < place; i++) {
			temp = temp*10;
		}
		//add value to virtual address
		addr = addr + temp;
		//increase place value and more to next character number
		place++;
		cnt--;
	}
	//return virtual address
	return addr;

}
