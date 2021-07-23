unsigned char inportb(unsigned short _port){
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb(unsigned short _port, unsigned char _data){
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void irq_install_handler(){

	// Initialize IRQ12 in IDT and load it

}

void mouse_wait(unsigned char a_type){
	int _time_out=100000;
	if(a_type==0){
		while(_time_out--){
			if((inportb(0x64) & 1) == 1){
        			return;
      			}
    		}
    		return;
 	}
	else{
		while(_time_out--){
			if((inportb(0x64) & 2) == 0){
        			return;
      			}
		}
		return;
  	}
}

void ProcessMouse(){

}

void mouse_write(unsigned char a_write){
	mouse_wait(1);
	outportb(0x64, 0xD4);

	mouse_wait(1);
  	outportb(0x60, a_write);
}

unsigned char mouse_read(){
	mouse_wait(0);
	return inportb(0x60);
}

void initMouse(){
	unsigned char status;
  	mouse_wait(1);
  	outportb(0x64, 0xA8);
 

	mouse_wait(1);
	outportb(0x64, 0x20);
  
	mouse_wait(0);
	status = (inportb(0x60) | 2);
	mouse_wait(1);
	outportb(0x64, 0x60);
	mouse_wait(1);
	outportb(0x60, status);
 
	// Use default settings
	mouse_write(0xF6);
	mouse_read();
 
	mouse_write(0xF4);
	mouse_read();

	irq_install_handler(12 , &ProcessMouse);
}

int start(){
	initMouse();
}
