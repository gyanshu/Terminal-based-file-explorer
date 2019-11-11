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
		if(ch == 'B') {
			if((int)ind < last) {
				cur_row += len[ind++];
				printf("\033[%d;1H", cur_row);
			}
			else if(last < (int)file_names.size()-1) {
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
		else if(ch == 'A') {
			if((int)ind > beg) {
				cur_row -= len[--ind];
				printf("\033[%d;1H", cur_row);
			}
			else if(beg > 0) {
				ind--;
				beg--;
				printdir();
				cur_row = 1;
				printf("\033[H");
			}
		}
		else if(ch == 'D') {
			if(backward_stack.size() == 1)
				continue;
			forward_stack.push(backward_stack.top());
			backward_stack.pop();
			int ret = getdir((backward_stack.top()).c_str());
			if(ret == -1)
				continue;
			reset();
			backward_stack.pop();
		}
		else if(ch == 'C') {
			if(forward_stack.empty()) {
				continue;
			}
			getdir((forward_stack.top()).c_str());
			reset();
			forward_stack.pop();
		}
		else if(ch == 'E') {
			int i = getdir(file_names[ind]);
			if(i == -1) {
				int pid = fork();
				if(pid == 0) {
					execl("/usr/bin/xdg-open", "xdg-open", file_names[ind]);
					exit(0);
				}
				wait(NULL);
				cls();
				printdir();
				printf("\033[%d;1H", cur_row);
				continue;
			}
			while(!forward_stack.empty())
				forward_stack.pop();
			reset();
		}
		else if(ch == 'b') {
			int test = getdir("..");
			if(test == -1)
				continue;
			reset();
		}
		else if(ch == 'h') {
			getdir(root);
			reset();
		}
		else if(ch == ':') {
			mode = 1;
			int row = screenlength();
			command();
			mode = 0;
			printf("\033[%d;1H", row);
			printf("\033[2K");
			cout<<"NORMAL MODE";
			printf("\033[H");
			reset();
		}
	}
}
