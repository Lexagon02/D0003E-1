#include <avr/io.h>
#include <stdint-gcc.h>

#include "LCD.h"

// Hacks up a long and writes them as chars to the screen

void writeLong(long i){

	int pos = 5;

	while(i > 0){
		
		writeChar((i % 10) + '0', pos-- );
		i = i / 10;
	}

}

// Writes a char to the screen on a given possition

void writeChar(char ch, int pos){
	
	if (pos >= 0 && pos <= 5){
		
		switch (ch){
			
			case '0':
			
			LCDWritePackage(pos, 0b1001, 0b0101, 0b0101, 0b0101);
			
			break;
			
			case '1':
			
			LCDWritePackage(pos, 0b0000, 0b0001, 0b0001, 0b0000);
			
			break;
			
			case '2':
			
			LCDWritePackage(pos, 0b0001, 0b0001, 0b1000, 0b0101);
			
			break;
			
			case '3':
			
			LCDWritePackage(pos, 0b0001, 0b0001, 0b1011, 0b0001);
			
			break;
			
			case '4':
			
			LCDWritePackage(pos, 0b0000, 0b0101, 0b1011, 0b0000);
			
			break;
			
			case '5':
			
			LCDWritePackage(pos, 0b0001, 0b0100, 0b1011, 0b0001);
			
			break;
			
			case '6':
			
			LCDWritePackage(pos, 0b0001, 0b0100, 0b1111, 0b0001);
			
			break;
			
			case '7':
			
			LCDWritePackage(pos, 0b1001, 0b0000, 0b0000, 0b0100);
			
			break;
			
			case '8':
			
			LCDWritePackage(pos, 0b0001, 0b0101, 0b1111, 0b0001);
			
			break;
			
			case '9':
			
			LCDWritePackage(pos, 0b0001, 0b0101, 0b1011, 0b0001);
			
			break;
			
			case 'A':
			
			LCDWritePackage(pos, 0b0001, 0b0101, 0b1111, 0b0000);
			
			break;

			case 'B':
	
			LCDWritePackage(pos, 0b0001, 0b0101, 0b1111, 0b0001);
				
			break;
				
			case 'C':	

			LCDWritePackage(pos, 0b0001, 0b0100, 0b0100, 0b0001);
				
			break;

			case 'D':

			LCDWritePackage(pos, 0b0000, 0b0110, 0b0100, 0b0100);

			break;

			case 'E':
			
			LCDWritePackage(pos, 0b0001, 0b0100, 0b0110, 0b0001);

			break;

			case 'F':
		
			LCDWritePackage(pos, 0b0001, 0b0100, 0b1110, 0b0000);
	
			break;

			case 'G':
		
			LCDWritePackage(pos, 0b0001, 0b0100, 0b1101, 0b0001);

			break;

			case 'H':
		
			LCDWritePackage(pos, 0b0000, 0b0101, 0b1111, 0b0000);
				
			break;

			case 'I':	// With bits J and N active
			
			LCDWritePackage(pos, 0b0000, 0b1000, 0b0000, 0b0010);
	
			break;
				
			case 'J':

			LCDWritePackage(pos, 0b0000, 0b0001, 0b0001, 0b0001);

			break;

			case 'K':

			LCDWritePackage(pos, 0b1000, 0b0100, 0b0110, 0b1000);

			break;

			case 'L':

			LCDWritePackage(pos, 0b0000, 0b0100, 0b0100, 0b0001);
				
			break;
				
			case 'M':

			LCDWritePackage(pos, 0b1000, 0b0111, 0b0101, 0b0000);

			break;
				
			case 'N':
			
			LCDWritePackage(pos, 0b0000, 0b0111, 0b0101, 0b1000);
				
			break;

			case 'O':
	
			LCDWritePackage(pos, 0b0001, 0b0101, 0b0101, 0b0001);

			break;

			case 'P':

			LCDWritePackage(pos, 0b0001, 0b0101, 0b1110, 0b0000);

			break;

			case 'Q':

			LCDWritePackage(pos, 0b0001, 0b0101, 0b0101, 0b1001);

			break;
				
			case 'R':

			LCDWritePackage(pos, 0b0001, 0b0101, 0b1110, 0b1000);

			break;

			case 'S':

			LCDWritePackage(pos, 0b0001, 0b0100, 0b1011, 0b0001);

			break;

			case 'T':

			LCDWritePackage(pos, 0b0001, 0b1000, 0b0000, 0b0010);
					
			break;

			case 'U':

			LCDWritePackage(pos, 0b0000, 0b0101, 0b0101, 0b0001);

			break;

			case 'V':

			LCDWritePackage(pos, 0b1000, 0b0100, 0b0100, 0b0100);
		 
			break;
			
			case 'W':

			LCDWritePackage(pos, 0b0000, 0b0101, 0b0101, 0b0011);
			
			break;
			
			case 'X':

			LCDWritePackage(pos, 0b1000, 0b0010, 0b0000, 0b1100);
			
			break;
			
			case 'Y':

			LCDWritePackage(pos, 0b1000, 0b0010, 0b0000, 0b0010);
			
			break;
			
			case 'Z':

			LCDWritePackage(pos, 0b1001, 0b0000, 0b0000, 0b0101);
			
			break;
			
			default:
			
			LCDWritePackage(pos, 0b0001, 0b0001, 0b1000, 0b0010);	//Questionmark
			
			break;
		}
		
	}
	
}

// Takes 4 nibbles and masks them in on there corresponding possitions registers

void LCDWritePackage(int offcet, uint16_t pos0, uint16_t pos1, uint16_t pos2, uint16_t pos3){

	if(offcet < 0){
		
		return;
		
	}
	// Digit 0 and 1 on the display
	else if(offcet < 2){
		
		// Shifts the nibbles up to the second part of the byte if the position is the
		// second one in the digit-pair
		
		LCDDR0  = (LCDDR0  & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 1 ? 4 : 0));
		LCDDR5  = (LCDDR5  & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 1 ? 4 : 0));
		LCDDR10 = (LCDDR10 & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 1 ? 4 : 0));
		LCDDR15 = (LCDDR15 & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 1 ? 4 : 0));

	}
	
	// Digit 2 and 3 on the display
	else if(offcet < 4){
		
		LCDDR1  = (LCDDR1  & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 3 ? 4 : 0));
		LCDDR6  = (LCDDR6  & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 3 ? 4 : 0));
		LCDDR11 = (LCDDR11 & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 3 ? 4 : 0));
		LCDDR16 = (LCDDR16 & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 3 ? 4 : 0));

	}
	
	// Digit 4 and 5 on the display
	else if(offcet < 6){
		
		LCDDR2  = (LCDDR2  & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 5 ? 4 : 0));
		LCDDR7  = (LCDDR7  & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 5 ? 4 : 0));
		LCDDR12 = (LCDDR12 & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 5 ? 4 : 0));
		LCDDR17 = (LCDDR17 & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 5 ? 4 : 0));

	}
	
	// The Different symbols on the screen that is not included in the digits bytes
	
	else if(offcet < 8){
		
		LCDDR3  = (LCDDR3  & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 7 ? 4 : 0));
		LCDDR7  = (LCDDR7  & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 7 ? 4 : 0));
		LCDDR13 = (LCDDR13 & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 7 ? 4 : 0));
		LCDDR18 = (LCDDR18 & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 7 ? 4 : 0));

	}

	
}

// Clears the screen

void clear(){
	
	LCDDR0 = 0x00;
	LCDDR1 = 0x00;
	LCDDR2 = 0x00;
	LCDDR3 = 0x00;

	LCDDR5 = 0x00;
	LCDDR6 = 0x00;
	LCDDR7 = 0x00;
	LCDDR8 = 0x00;

	LCDDR10 = 0x00;
	LCDDR11 = 0x00;
	LCDDR12 = 0x00;
	LCDDR13 = 0x00;
	
	LCDDR15 = 0x00;
	LCDDR16 = 0x00;
	LCDDR17 = 0x00;
	LCDDR18 = 0x00;
	
}

// Inits the LCD by using some magic

void initLCD(){
	
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	LCDFRR = (0<<LCDPS2) | (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	LCDCCR = (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
	LCDCRA = (1<<LCDEN);
	
}
