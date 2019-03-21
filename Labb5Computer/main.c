#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "/dev/ttyS0"
//#define PATH "/cygdrive/h/Kod/D0003E/Labb5Computer/output"
// #define PATH "/mnt/d/Mega/Kod/C/D0003E/Labb5Computer/output.txt"
 
#define SOUTH 1
#define NORTH 0
#define TIMETOGETON 1000

int openFile();
void printByte(int value);
void addCarToQueue(int* output, int* queue, int* incomming ,int instance );
void parseData(int* input, int* output, int* northQueue, int* southQueue, int* northIncomming, int* southIncomming, int* northLeft, int* southLeft);
int getLightState(int* input, int instance);
void letCarOverBridge(int* output, int* queue, int* tot ,int instance);
int carCrash(int* output);
void localTest();
void newLine();


int main (){
	//clock_t start_t, cur_t;
	time_t start_t , end_t, duration_t;
	start_t = time(0);
	//start_t = clock();
	int file = openFile();
	int input;
	int output;
	int southQueue = 0;
	int northQueue = 0;
	int southIncomming = 0;
	int northIncomming = 0;
	char inputChar = ' ';
	int northLeft = 0;
	int southLeft = 0;
	newLine();
	
	while(1){
		while(read(file, &input, 1) == -1);
		 
		end_t = time(0);
		duration_t = (end_t - start_t);
		printf("\nDIFF: %d\n", duration_t);
		if(duration_t >= 1){
			start_t = time(0);
			printf("TICK\n");
			parseData(&input, &output, &northQueue, &southQueue, &northIncomming, &southIncomming, &northLeft, &southLeft);
		}
		printf("Input: ");
		printByte(input);
		printf("\nOutput: ");
		printByte(output);
		
		printf("\nNorth incomming: %d, North queue: %d\nSouth incomming: %d, South queue: %d\n\nNorthLeft: %d, SouthLeft: %d\n", northIncomming, northQueue, southIncomming, southQueue,northLeft,southLeft);
		
		inputChar = getchar();
		printf("%c\n", inputChar);
		
		if(inputChar == 'n'){
			northIncomming++;
		}
		else if(inputChar == 's'){
			southIncomming++;
		}
		else if(inputChar == 'b'){
			southIncomming++;
			northIncomming++;
		}
		
		//printf("\nNorth incomming: %d, North queue: %d\nSouth incomming: %d, South queue: %d\n\n", northIncomming, northQueue, southIncomming, southQueue);
		
		newLine();
		write(file, &output, 1);
	
	}	
	
	return 0;
	
}


void localTest(){
	
	int input = 0b1010;
	int output= 0b0000;
	int southQueue = 1;
	int northQueue = 1;
	int southIncomming = 0;
	int northIncomming = 0;
	int southLeft = 0;
	int northLeft = 0;
	
	parseData(&input, &output, &northQueue, &southQueue, &northIncomming, &southIncomming, &northLeft, &southLeft);
	
	printByte(output);
	printf("\nNorth incomming: %d, North queue: %d\nSouth incomming: %d, South queue: %d\n", northIncomming, northQueue, southIncomming, southQueue);
	
} 

void parseData(int* input, int* output, int* northQueue, int* southQueue, int* northIncomming, int* southIncomming, int* northLeft, int* southLeft){
	
	*output = 0b0000;
	
	if(getLightState(input, NORTH) && *northQueue){
			
		letCarOverBridge(output, northQueue, northLeft, NORTH);
			
	}
	if(getLightState(input, SOUTH) && *southQueue){
			
		letCarOverBridge(output, southQueue, southLeft, SOUTH);
	}
	
	if(*northIncomming){
		addCarToQueue(output, northQueue, northIncomming, NORTH);
	}
	
	if(*southIncomming){
		addCarToQueue(output, southQueue, southIncomming, SOUTH);
	}
	
	if(carCrash(output)){
		printf("Full fart framåt o inga bromsar!!\n");
	}
	
}

int carCrash(int* output){
	
	return ((*output) == 0b1010);
	
}

void addCarToQueue(int* output, int* queue, int* incomming ,int instance ){
	if(instance == NORTH){
				
		*output |= (1 << 0);
	}
	else{
			
		*output |= (1 << 2); 
	}
	
	(*incomming)--;
	(*queue)++;
	
}

void letCarOverBridge(int* output, int* queue, int* tot ,int instance){
	
	*output |= (1 << (instance == NORTH ? 1 : 3));

	(*queue)--;
	(*tot)++;
}

int getLightState(int* input, int instance){
	
	if(instance == NORTH){
		if((*input) & (1 << 0) && (*input) & (1 << 1)){
			printf("Input for north is incorrect!\n");
		}
		else if ((*input) & (1 << 0)){
			
			return 1;
				
		}
		return 0;
				
		
	}
	if(instance == SOUTH){
		
		if((*input) & (1 << 2) && (*input) & (1 << 3)){
			printf("Input for south is incorrect!\n");
			
		}
		else if((*input) & (1 << 2) ){
			
			return 1;
		}
		 
		return 0;
					
	}
		
}

void printByte(int value){
	
	for(int i = 0; i < 4; i++){
		
		printf("%d", ((value & (1 << 3 - i)) ? 1 : 0));
			
	}
	
}

int openFile(){

    int temp = open(PATH, O_RDWR);
	
	if(temp >= 0){
		printf("Sucsess!\n");
	}
	else{
		printf("Could not open the file\n");
	}
	
	return temp;
}

void newLine(){
	
	for(int i = 0; i < 100; i++ ){
		
		printf("\n");
		
	}
	
}