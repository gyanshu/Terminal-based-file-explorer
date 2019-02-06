#include "operate.h"
using namespace std;

void reset() {
	b = 0;
	printdir();
	printf("\033[H");
	ind = 0;
	currow = 1;
}

void operate() {
	ind = 0;
	currow = 1;
	printf("\033[H");
	while(1) {
		int ch;
		ch = getinput();
		if(ch == 'B') {
			if((int)ind < e) {
				currow += len[ind++];
				printf("\033[%d;1H", currow);
			}
			else if(e < (int)name.size()-1) {
				int temp = ++ind;
				int req = len[ind];
				int sum = 0,k = b;
				while(sum < req) {
					sum += len[k++];
				}
				b = k;
				printdir();
				sum = 1;
				for(int i = b; i < ind; i++)
					sum += len[i];

				currow = sum;
				ind = temp;
				printf("\033[%d;1H", currow);
			}
		}
		else if(ch == 'A') {
			if((int)ind > b) {
				currow -= len[--ind];
				printf("\033[%d;1H", currow);
			}
			else if(b > 0) {
				ind--;
				b--;
				printdir();
				currow = 1;
				printf("\033[H");
			}
		}
		else if(ch == 'D') {
			if(dirstack.size() == 1)
				continue;
			fwstack.push(dirstack.top());
			dirstack.pop();
			int ret = getdir((dirstack.top()).c_str());
			if(ret == -1)
				continue;
			reset();
			dirstack.pop();
		}
		else if(ch == 'C') {
			if(fwstack.empty()) {
				continue;
			}
			getdir((fwstack.top()).c_str());
			reset();
			fwstack.pop();
		}
		else if(ch == 'E') {
			int i = getdir(name[ind]);
			if(i == -1) {
				int pid = fork();
				if(pid == 0) {
					execl("/usr/bin/xdg-open", "xdg-open", name[ind]);
					exit(0);
				}
				wait(NULL);
				cls();
				printdir();
				printf("\033[%d;1H", currow);
				continue;
			}
			while(!fwstack.empty())
				fwstack.pop();
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
			status = 1;
			int row = screenlength();
			command();
			if(flag == 1) {
				cls();
				for(int i = 0; i < name.size(); i++)
					cout<<name[i]<<"\n";
				b = 0;
				printf("\033[H", row);
			}
			flag = 0;
			status = 0;
			printf("\033[%d;1H", row);
			printf("\033[2K");
			cout<<"NORMAL MODE";
			printf("\033[H");
			reset();
		}
	}
}
