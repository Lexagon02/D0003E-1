#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>
#include <io.h>

#define PATH "/dev/ttyS0"
#define DEBUG_PATH "/cygdrive/h/D0003E/D0003E/Labb5Computer/output.txt"
//#define PATH "/cygdrive/h/Kod/D0003E/Labb5Computer/output"
// #define PATH "/mnt/d/Mega/Kod/C/D0003E/Labb5Computer/output.txt"
 
#define SOUTH 1
#define NORTH 0
#define TIMETOGETON 1000

int openFile();
void printByte(int value);
void addCarToQueue(int* output, int* queue, int* incomming ,int instance );
void parseData(int* input, int* output, int* northQueue, int* southQueue, int* northIncomming, int* southIncomming, int* northLeft, int* southLeft, int *localChanged);
int getLightState(int* input, int instance);
void letCarOverBridge(int* output, int* queue, int* tot ,int instance);
int carCrash(int* output);
void newLine();
void *runSim();
void *readKeyboard();
void *ThreadRead();
void controllCarsOnBridge(int* c, int output);
void *carOffBridge(void* direction);
int checkTimeOut();
void carOnBridge(int direction);
void *timeCheck(void *vargp);
void writeToDebug(int output);

pthread_t runSim_id, readKeyboard_id, read_id, time_id,carsOnBridge_id[2][5];

char inputChar = ' ';
const char nwln = '\n';
int southIncomming = 0;
int northIncomming = 0;
int southBridge = 0;
int northBridge = 0;

int onBridge[2] = {0, 0};

int sent = 0;

int timeFlag = 1;
int globalChanged = 0;

int file;
int debugFile;
int output_g;
int input_g;
//Jag vet att det är olagligt
time_t start_t , end_t, duration_t;

pthread_mutex_t lock;

int main(){
	
	file = openFile();
	debugFile = open(DEBUG_PATH, O_RDWR);
	
	sleep(1);
	
	pthread_create(&runSim_id, NULL, runSim, NULL);
	pthread_create(&readKeyboard_id, NULL, readKeyboard, NULL);
	pthread_create(&read_id, NULL, ThreadRead, NULL);
	
	struct termios tio;
	struct termios tio_reset;
	int tty_fd;
	fd_set rdset;

	unsigned char c='D';
	
	tcgetattr(STDIN_FILENO, &tio_reset);
	
	tio = tio_reset;

	tio.c_lflag &= ~(ICANON) & ~(ECHO);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &tio);

	
	pthread_join(runSim_id,NULL);
	pthread_join(readKeyboard_id,NULL);
	
	//tcsetattr(STDIN_FILENO, TCSANOW, &tio_reset);
	printf("Goodbye");
	return 0;
	
}



void *readKeyboard(void *vargp){
	while(1){
		
		inputChar = getchar();
		pthread_mutex_lock(&lock);
		
		if(inputChar == 'b'){
			southIncomming++;
			northIncomming++;
		}
		if(inputChar == 'n'){
			northIncomming++;
		}
		if(inputChar == 's'){
			southIncomming++;
		}
		
		pthread_mutex_unlock(&lock);
	}
}

void *runSim(void *vargp){
	//clock_t start_t, cur_t;
	
	time(&start_t);
	//start_t = clock();
	
	int input = 0b0000;
	int output;
	int southQueue = 0;
	int northQueue = 0;
	
	int northLeft = 0;
	int southLeft = 0;
	
	int lastInput = input;
	int lastOutput = output;
	int outputOverZero = output;
	
	
	int localChanged;
	
	while(1){
		pthread_mutex_lock(&lock);
		input = input_g;
		
		pthread_mutex_lock(&lock);
		
		//printf("\nDuration: %d\n", duration_t);
		parseData(&input, &output, &northQueue, &southQueue, &northIncomming, &southIncomming, &northLeft, &southLeft, &localChanged);

		if(lastInput != input){
			localChanged = 1;
			lastInput = input;
		}
		if(lastOutput != output){
			localChanged = 1;
			lastOutput = output;
		}
		if(output != 0){
			outputOverZero = output;
		}
		
		pthread_mutex_lock(&lock);
		localChanged += globalChanged;
		globalChanged = 0;

		if(localChanged){
			
			printf("\x1b[2J");
			printf("Input: ");
			printByte(input);
			printf("\nOutput: ");
			printByte(outputOverZero);
			
			printf("\nNorth incomming: %d, North queue: %d\nSouth incomming: %d, South queue: %d\n\nNorthLeft: %d, SouthLeft: %d\n", northIncomming, northQueue, southIncomming, southQueue,northLeft,southLeft);
			printf("North cars on bridge: %d \nSouth cars on bridge: %d \n",onBridge[NORTH], onBridge[SOUTH]);
			printf("Time flag: %d\n", timeFlag);
			
		}

		southIncomming = 0;
		northIncomming = 0;
		
		output_g = output;
		
		sent = 0;	
		localChanged = 0;
		
		pthread_mutex_unlock(&lock);
		
		output = 0;
		while(1){
		
			pthread_mutex_lock(&lock);
			if(sent){
				break;
			}
			pthread_mutex_unlock(&lock);
			
		}
		
		
	}

}
	
	
void *ThreadRead(void *vargp){
	
	while(1){
		
		pthread_mutex_lock(&lock);
		write(file, &output_g, 1);
		writeToDebug(output_g);
		
		output_g = 0;
		sent = 1;
		pthread_mutex_unlock(&lock);
		
		pthread_mutex_lock(&lock);
		while(read(file, &input_g, 1) == -1);
		pthread_mutex_unlock(&lock);
		
		
	}
	
	
}
	
	
void *carOffBridge(void* direction){
	sleep(5);
	pthread_mutex_lock(&lock);

	onBridge[(int)direction]--;
	globalChanged = 1;
	
	pthread_mutex_unlock(&lock);
}

void carOnBridge(int direction){
	
	pthread_mutex_lock(&lock);
	
	if(onBridge[direction] < 5){
		
		pthread_create(&(carsOnBridge_id[direction][(onBridge[direction])++]), NULL, carOffBridge, direction);
		globalChanged = 1;

	}

	pthread_mutex_unlock(&lock);
	
}


void parseData(int* input, int* output, int* northQueue, int* southQueue, int* northIncomming, int* southIncomming, int* northLeft, int* southLeft, int *localChanged){
	
	*output = 0b0000;
	
	if(checkTimeOut()){
		if(getLightState(input, NORTH) && *northQueue){
			carOnBridge(NORTH);
			letCarOverBridge(output, northQueue, northLeft, NORTH);
			*localChanged = 1;
			
		}
		if(getLightState(input, SOUTH) && *southQueue){
			carOnBridge(SOUTH);
			letCarOverBridge(output, southQueue, southLeft, SOUTH);
			*localChanged = 1;
		}
	}
	
	if(*northIncomming){
		addCarToQueue(output, northQueue, northIncomming, NORTH);
		*localChanged = 1;
	}
	
	if(*southIncomming){
		addCarToQueue(output, southQueue, southIncomming, SOUTH);
		*localChanged = 1;
	}
	
	if(carCrash(output)){
		printf("Full fart framåt o inga bromsar!!  ÅÅÅÅNEEEEJ BARN FAMILJEN\n");
		*localChanged = 1;
	}
	
}

int carCrash(int* output){
	
	if(northBridge && southBridge){
		return 1;
	}
	return 0;
	
	
}

void addCarToQueue(int* output, int* queue, int* incomming ,int instance ){
	if(instance == NORTH){
				
		*output |= (1 << 0);
	}
	else{
			
		*output |= (1 << 2); 
	}
	//Ändrat
	if((*incomming) > 0){
		(*queue)++;
	}
	
	
}

void *timeCheck(void *vargp){
	sleep(1);
	pthread_mutex_lock(&lock);
	timeFlag = 1;
	globalChanged = 1;
	pthread_mutex_unlock(&lock);
	
	
}

int checkTimeOut(){
	pthread_mutex_lock(&lock);
	if(timeFlag){
		timeFlag = 0;
		pthread_mutex_unlock(&lock);
		pthread_create(&time_id, NULL, timeCheck, NULL);
		
		return 1;
	}
	pthread_mutex_unlock(&lock);
	return 0;
};

void letCarOverBridge(int* output, int* queue, int* tot ,int instance){
	
	printf("\nTICK\n");
	//start_t = time(0);
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

void writeToDebug(int output){
	
	char temp[4];
	for(int i = 0; i < 4; i++ ){
		
		temp[3 - i] = '0' + (output & 1);
		
		output = output >> 1;
	}
	
	for(int i = 0; i < 4; i++ ){
		
		write(debugFile, &(temp[i]), 1);
		
		
	}
	
	write(debugFile, &nwln, 1);	
	
}