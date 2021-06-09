int start(){
	char* video_memory = (char*) 0xb8000;
	*video_memory = 'K';
}