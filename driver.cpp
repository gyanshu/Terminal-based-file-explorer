#include "operate.h"

void termset() {
	/*It gets the parameters associated with the terminal referred to by file desciptor(stdin here) and stores them in a
	  termios structure(intial_settings)*/
	tcgetattr(fileno(stdin),&initial_settings);
	new_settings = initial_settings;
	/*switch to non-canonical mode, in this mode input given is read byte-by-byte istead of line-by-line. Now user doesn't
	  have to press enter for the input to be read.*/
	new_settings.c_lflag &= ~ICANON;
	/*When echo flag is off terminal won't print characters(on the screen for instance) entered by you*/
	new_settings.c_lflag &= ~ECHO;
	/*below setting of vmin and vtime enables terminal to wait until 1 byte is available to read*/
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	/*It sets the parameters associated with the terminal referred to by a file desciptor(stdin here) from the
	  termios structure(new_settings)*/
	if(tcsetattr(fileno(stdin), TCSANOW, &new_settings) != 0) {
		fprintf(stderr,"could not set attributes\n");
	}
}

int main()
{
	mode = 0;
	termset();
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));								//absolute pathname of current working directory is saved in buff array
	root = buff;
	DIR *dp;
	if((dp = opendir(root)) == NULL) {						//trying to open the directory stream "root" and returning a pointer to it
		printf("can't open directory\n");
		tcsetattr(fileno(stdin),TCSANOW,&initial_settings); //upon exiting set terminal attributes to as they were
		exit(0);
	}
	getdir(root);											//loads the file names from the root directory into file_names vector
	beg = 0;												//used by printdir() to start printing file entries from beg index in file_names vector
	printdir();												//prints file entries on screen

	printf("\033[H");										//moves cursor to the top of the screen
	operate();												//driver function for all the operations
	tcsetattr(fileno(stdin),TCSANOW,&initial_settings);		//upon exiting set terminal attributes to as they were
	return 0;
}
