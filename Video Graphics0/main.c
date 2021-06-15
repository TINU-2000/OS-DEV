void cls();
void setMonitorColor(char);

void printString(char*);
void printChar(char);

void scroll();

void printColorString(char* , char);
void printColorChar(char , char);

void getDecAscii(int);

char* TM_START;
char NumberAscii[10];
int CELL;

int start(){
	TM_START = (char*) 0xb8000;
	CELL = 0;

	cls();
	setMonitorColor(0xa5);

	char Welcome[] = "Welcome To OS0 : Copyright 2021\n";
	char Welcome2[] = "Command Line Version 1.0.0.0\n\n";
	char OSM[] = "OS0 > ";

	printString(Welcome);
	printString(Welcome2);
	printColorString(OSM , 0xa8);
}


void cls(){
	int i = 0;
	CELL = 0;
	while(i < (2 * 80 * 25)){
		*(TM_START + i) = ' '; // Clear screen
		i += 2;
	}
}

void setMonitorColor(char Color){
	int i = 1;
	while(i < (2 * 80 * 25)){
		*(TM_START + i) = Color;
		i += 2;
	}
}

void printString(char* cA){
	int i = 0;
	while(*(cA + i) != '\0'){
		printChar(*(cA + i));
		i++;
	}
}

void printChar(char c){
	if(CELL == 2 * 80 * 25)
		scroll();
	if(c == '\n'){
		CELL = ((CELL + 160) - (CELL % 160));
		return;
	}
	*(TM_START + CELL) = c;
	CELL += 2;	
}

void scroll(){
	int i = 160 , y = 0;
	while(i < 2 * 80 * 25){
		*(TM_START + y) = *(TM_START + i);
		i += 2;
		y += 2;
	}
	CELL = 2 * 80 * 24;
	i = 0;
	while(i < 160){
		*(TM_START + CELL + i) = ' ';
		i += 2;
	}
}

void printColorString(char* c , char co){
	int i = 0;
	while(*(c + i) != '\0'){
		printColorChar(*(c + i) , co);
		i++;
	}
}

void printColorChar(char c , char co){
	if(CELL == 2 * 80 * 25)
		scroll();
	if(c == '\n'){
		CELL = ((CELL + 160) - (CELL % 160));
		return;
	}
	*(TM_START + CELL) = c;
	*(TM_START + CELL + 1) = co;
	CELL += 2;	
}

void getDecAscii(int num){
	if(num == 0){
		NumberAscii[0] = '0';
		return;
	}
	char NUM[10];
	int i = 0 , j = 0;
	while(num > 0){
		NUM[i] = num % 10;
		num /= 10;
		i++;
	}
	i--;
	while(i >= 0){
		NumberAscii[j] = NUM[i];
		i--;
		j++;
	}
	NumberAscii[j] = 'J';
	j = 0;
	while(NumberAscii[j] != 'J'){
		NumberAscii[j] = '0' + NumberAscii[j];
		j++;
	}
	NumberAscii[j] = 0;
}