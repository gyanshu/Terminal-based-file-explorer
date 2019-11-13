#include "operate.h"
using namespace std;

/*This function prints all the file entries on terminal again, also setting cursor to the first file at the top*/
void reset() {
	beg = 0;
	printdir();
	printf("\033[H");
	ind = 0;
	cur_row = 1;
}

void operate() {
	ind = 0;
	cur_row = 1;
	printf("\033[H");
	while(1) {
		int ch;
		ch = getinput();
		if(ch == 'B') {														//when bottom key is pressed
			if((int)ind < last) {											//if we are not on the last file on screen
				cur_row += len[ind++];
				printf("\033[%d;1H", cur_row);
			}
			else if(last < (int)file_names.size()-1) {						//if we are on the last file on screen but there are more files in the directory
				int temp = ++ind;
				int req = len[ind];
				int sum = 0,k = beg;
				while(sum < req) {
					sum += len[k++];
				}
				beg = k;
				printdir();
				sum = 1;
				for(int i = beg; i < (int)ind; i++)
					sum += len[i];

				cur_row = sum;
				ind = temp;
				printf("\033[%d;1H", cur_row);
			}
		}
		else if(ch == 'A') {												//when up key is pressed
			if((int)ind > beg) {											//if we are not on the first file on screen
				cur_row -= len[--ind];										
				printf("\033[%d;1H", cur_row);
			}
			else if(beg > 0) {												//if we are on the first file on screen
				ind--;
				beg--;
				printdir();
				cur_row = 1;
				printf("\033[H");
			}
		}
		else if(ch == 'D') {												//when left key is pressed
			if(backward_stack.size() == 1)									//if backward stack only contains the root directory do nothing
				continue;
			forward_stack.push(backward_stack.top());						
			backward_stack.pop();
			int ret = getdir((backward_stack.top()).c_str());
			if(ret == -1)
				continue;
			reset();
			backward_stack.pop();
		}
		else if(ch == 'C') {												//when right key is pressed
			if(forward_stack.empty()) {										//if forward stack is empty do nothing
				continue;
			}
			getdir((forward_stack.top()).c_str());
			reset();
			forward_stack.pop();
		}
		else if(ch == 'E') {												//when enter key is pressed	
			int i = getdir(file_names[ind]);
			if(i == -1) {													//if it is a file
				int pid = fork();
				if(pid == 0) {
					execl("/usr/bin/xdg-open", "xdg-open", file_names[ind]);
					exit(0);
				}
				wait(NULL);
			}
			else {
				while(!forward_stack.empty())								//clear the earlier forward_stack if it is a directory we entered in
					forward_stack.pop();
			}
			reset();
		}
		else if(ch == 'b') {												//when backspace key is pressed
			int test = getdir("..");										//go to previous directory
			if(test == -1)
				continue;
			reset();
		}
		else if(ch == 'h') {												//when 'h' or 'H' key is pressed
			getdir(root);													//goto root directory
			reset();
		}
		else if(ch == ':') {												//when ":" key is pressed switch to command mode
			mode = 1;
			int row = screenlength();
			command();														//for handling the command mode
			mode = 0;
			printf("\033[%d;1H", row);
			printf("\033[2K");
			cout<<"NORMAL MODE";
			printf("\033[H");
			reset();
		}
	}
}
