#include "input.h"
char getinput() {
	char ch;
	ch = getchar();
	if(ch == 0x001b) {
		ch = getchar();
		if(ch == '[') {
			ch = getchar();
			if(ch == 'B')
				return 'B';
			if(ch == 'A')
				return 'A';
			if(ch == 'C')
				return 'C';
			if(ch == 'D')
				return 'D';
		}	
	}
	else if(ch == '\n' || ch == '\r')
		return 'E';
	else if(ch == 127)
		return 'b';
	else if(ch == 'h' || ch == 'H')
		return 'h';
	else if(ch == ':')
		return ':';
	return -1;
}
