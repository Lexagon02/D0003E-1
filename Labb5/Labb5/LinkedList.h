/*
 * LinkedList.h
 *
 * Created: 15-Mar-19 11:50:14
 *  Author: josef
 */ 


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct{
	int prevCar;
	int nextCar;
	};

int getPrevCar();
int getNextCar();
void removeCar();

#endif /* LINKEDLIST_H_ */