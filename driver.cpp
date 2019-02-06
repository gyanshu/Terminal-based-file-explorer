#include "operate.h"

void termset() {
	tcgetattr(fileno(stdin),&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	if(tcsetattr(fileno(stdin), TCSANOW, &new_settings) != 0) {
		fprintf(stderr,"could not set attributes\n");
	}
}

int main()
{
	flag = 0;
	status = 0;
	termset();
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	root = buff;
	DIR *dp;
	if((dp = opendir(root)) == NULL) {
		printf("can't open directory\n");
		tcsetattr(fileno(stdin),TCSANOW,&initial_settings);
		exit(0);
	}
	getdir(root);
	cls();
	b = 0;
	len.resize(name.size());
	printdir();

	printf("\033[H");
	operate();
	tcsetattr(fileno(stdin),TCSANOW,&initial_settings);
	return 0;
}
