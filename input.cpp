#include "input.h"
char getinput(char c) {
	char ch;
	if(c == -1)
		ch = getchar();
	else
		ch = c;
	
	if(ch == 27) {
		ch = getchar();
		if(ch == '[') {
			ch = getchar();
			if(ch == 'B')
				return 'B';
			else if(ch == 'A')
				return 'A';
			else if(ch == 'C')
				return 'C';
			else if(ch == 'D')
				return 'D';
			else
				return getinput(ch);
		}
		else
			return getinput(ch);
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
