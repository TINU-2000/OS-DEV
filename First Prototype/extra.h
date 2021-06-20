void setMonitorColor(char);
void cls();
void printString(char*);
void vid();

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