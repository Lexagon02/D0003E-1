#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH "/mnt/d/Mega/Kod/C/D0003E/Labb5Computer/output.txt"
#define LEN 256

void openFile(int *file);

int main (){
	int file;

	openFile(&file);

	return 0;
}

void openFile(int *file){

        int temp = open(PATH, "O_RDWR");
	printf("%d\n", temp);
}


