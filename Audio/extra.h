void setMonitorColor(char);
void cls();
void printString(char*);
void vid();
void put();
void get();

void scream(int);

extern void read();
extern void write();

unsigned char inportb(unsigned short);
void outportb(unsigned short , unsigned char);



int blockAddr;
char At[1024];

char* TM_START;

void blink(){
	setMonitorColor(0x59);
	int TIME_OUT = 0x10fffff;
	while(--TIME_OUT);
	setMonitorColor(0xa5);
}

char strcmp(char* sou , char* dest){
	int i = 0;
	while(*(sou + i) == *(dest + i)){
		if(*(sou + i) == 0 && *(dest + i) == 0)
			return 1;
		i++;
	}
	return 0;
}

void strEval(char* CMD){
	char cmd1[] = "CLS";
	char cmd2[] = "COLORA";
	char cmd3[] = "COLORB";
	char cmd4[] = "COLORC";
	char cmd5[] = "COLORDEF";
	char cmd6[] = "VID";
	char cmd7[] = "HI";
	char cmd8[] = "PUT";
	char cmd9[] = "GET";
	char cmd10[] = "PLAY";

	char msg1[] = "\nHELLO , HAVE A GOOD JOURNEY LEARNING\n";

	if(strcmp(CMD , cmd1))
		cls();

	else if(strcmp(CMD , cmd2))
		setMonitorColor(0x3c);

	else if(strcmp(CMD , cmd3))
		setMonitorColor(0x5a);

	else if(strcmp(CMD , cmd4))
		setMonitorColor(0x2a);

	else if(strcmp(CMD , cmd5))
		setMonitorColor(0xa5);	

	else if(strcmp(CMD , cmd6))
		vid();
	else if(strcmp(CMD , cmd7))
		printString(msg1);
	else if(strcmp(CMD , cmd8)){
		blockAddr = 0;
		int i = 0;
		
		while(i < 511){
			At[i] = 'J'; // Fill with J
			i++;
		}
		At[i] = 0; // Null character

		put(); // Writes to Hard disk
		
		i = 0;
		while(i < 511){
			At[i] = 0;  // Clears the content
			i++;
		}
	}		
	else if(strcmp(CMD , cmd9)){
		blockAddr = 0;
		get();
		printString(At);
	}
	else if(strcmp(CMD , cmd10)){
		int stone = 15000;
		while(stone--){
			scream(stone);
		}
	}
		
}

void vid(){
	char clr = 'A';
	while(1){
		int i = 0;
		while(i < 2 * 80 * 25){
			*(TM_START + i) = clr;
			clr++;
			i++;
		}
	}
}

void put(){
	write();
}

void get(){
	read();
}

void play(unsigned int fr) {
 	unsigned int Div;
 	unsigned char tmp;
 
 	Div = 1193180 / fr;
 	outportb(0x43, 0xb6);
 	outportb(0x42, (unsigned char) (Div) );
 	outportb(0x42, (unsigned char) (Div >> 8));
 
 	tmp = inportb(0x61);
  	if (tmp != (tmp | 3)) {
 		outportb(0x61, tmp | 3);
 	}
}
 
void stop() {
 	unsigned char fr = inportb(0x61) & 0xFC;
 	outportb(0x61, fr);
}
 
void scream(int fr) {
	play(fr);
	int stone = 0xffff;
	while(stone--);
	stop();          
}