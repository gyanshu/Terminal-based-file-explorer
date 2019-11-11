#include "printdir.h"
using namespace std;
void printdir() {
	struct tm *foo;
	struct stat fileStat;
	int col = screenwidth();
	int row = screenlength();
	int lines = 0;
	last = -1;
	int i, space;
	unsigned int crow = 1;
	printf("\033[H\033[J");
	for(i = beg; i < (int)file_names.size(); i++) {
		string sr;
		int ret = lstat(file_names[i], &fileStat);
		if(ret == -1)
			continue;
		sr += (S_ISDIR(fileStat.st_mode)) ? "d" : "-";
		sr += (fileStat.st_mode & S_IRUSR) ? "r" : "-";
		sr += (fileStat.st_mode & S_IWUSR) ? "w" : "-";
		sr += (fileStat.st_mode & S_IXUSR) ? "x" : "-";
		sr += (fileStat.st_mode & S_IRGRP) ? "r" : "-";
		sr += (fileStat.st_mode & S_IWGRP) ? "w" : "-";
		sr += (fileStat.st_mode & S_IXGRP) ? "x" : "-";
		sr += (fileStat.st_mode & S_IROTH) ? "r" : "-";
		sr += (fileStat.st_mode & S_IWOTH) ? "w" : "-";
		sr += (fileStat.st_mode & S_IXOTH) ? "x" : "-";
		sr += " ";
		struct passwd *pw = getpwuid(fileStat.st_uid);
    	struct group  *gr = getgrgid(fileStat.st_gid);
    	char buff[100];
    	sprintf(buff, "%7s %7s ", pw->pw_name, gr->gr_name);
    	string n(buff);
    	sr += n;
    	char al[100];
		sprintf(al, "%8ld ",fileStat.st_size);
		string o(al);
		sr += o;
		foo = localtime(&(fileStat.st_mtime));
		int a = foo->tm_mon;
		string s;
		switch(a) {
			case 0:
				s = "Jan";
				break;
			case 1:
				s = "Feb";
				break;
			case 2:
				s = "Mar";
				break;
			case 3:
				s = "Apr";
				break;
			case 4:
				s = "May";
				break;
			case 5:
				s = "Jun";
				break;
			case 6:
				s = "Jul";
				break;
			case 7:
				s = "Aug";
				break;
			case 8:
				s = "Sep";
				break;
			case 9:
				s = "Oct";
				break;
			case 10:
				s = "Nov";
				break;
			case 11:
				s = "Dec";
				break;
		}
		std::ostringstream stringStream;
		stringStream.width(3);
		stringStream<<s<<" ";
		sr += stringStream.str();
		char aq[100];
		sprintf(aq, "%2d ", foo->tm_mday);
		string qw(aq);
		sr += qw;
		char aw[100];
		sprintf(aw, "%02d:", foo->tm_hour);
		string qe(aw);
		sr += qe;
		char ae[100];
		sprintf(ae, "%02d ", foo->tm_min);
		string qs(ae);
		sr += qs;
		char ar[100];
		sprintf(ar, "%4d ", 1900+foo->tm_year);
		string qa(ar);
		sr += qa;
		char at[100];
		sprintf(at, "%s", file_names[i]);
		string ql(at);
		sr += ql;
		if(S_ISDIR(fileStat.st_mode) && strcmp(file_names[i], ".") != 0 && strcmp(file_names[i], "..") != 0)
			sr += "/";
		sr += "\n";
		int siz = sr.size()-1;
		space = (int)ceil(siz/(float)col);
		len[i] = space;
		lines += space;
		if(lines < row)
			cout<<sr;
		else
			break;
		crow += space;
	}
	printf("\033[%d;1H", row);
	cout<<((mode == 0) ? "NORMAL MODE" : "COMMAND MODE: ");
	last = i-1;
	if(cur_row > crow) {
		cur_row = crow;
		ind = last;
	}
}
