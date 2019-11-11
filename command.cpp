#include "command.h"

void gotopath(string &path) {
	flag = 0;
	if(path[0] == '/' || path[0] == '~') {
		if(path[0] == '~')
			path.erase(0, 1);
		path = root+path;
	}
	getdir(path.c_str());
	dirstack.pop();
}

void sch(char const *dir, char const *fil) {
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
		return;
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			if(strcmp(entry->d_name, fil) == 0) {
				char buff[PATH_MAX];
				getcwd(buff, sizeof(buff));
				string cpp(buff);
				string addend(fil);
				cpp = cpp + "/" + addend;
				char strng[100];
				int i;
				for(i = 0; i < (int)cpp.size(); i++)
					strng[i] = cpp[i];
				strng[i] = '\0';
				name.push_back(strng);
			}
			sch(entry->d_name, fil);
		}
		else if(strcmp(entry->d_name, fil) == 0) {
			char buff[PATH_MAX];
			getcwd(buff, sizeof(buff));
			string cpp(buff);
			string addend(fil);
			cpp = cpp + "/" + addend;
			char strng[100];
			int i;
			for(i = 0; i < (int)cpp.size(); i++)
				strng[i] = cpp[i];
			strng[i] = '\0';
			name.push_back(strng);
		}
	}
	chdir("..");
	closedir(dp);
}

void search(string s) {
	name.clear();
	char const *c = ".";
	sch(c, s.c_str());
	flag = 1;
}

void rec_mv(char const *dir, string des_dir) {
	flag = 0;
	string temproary(dir);
	string des;
	if(des_dir.back() != '/')
		des = des_dir + '/' + temproary;
	else
		des = des_dir + temproary;
	mkdir(des.c_str(), 00777);
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
		return;
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			rec_mv(entry->d_name, des);
		}
		else
			rename(entry->d_name, (des+entry->d_name).c_str());
	}
	chdir("..");
	closedir(dp);
}

void dmv(string source, string des_dir, string b) {
	flag = 0;
	if(des_dir[0] == '/' || des_dir[0] == '~') {
		if(des_dir[0] == '~')
			des_dir.erase(0, 1);
		des_dir = root+des_dir;
	}
	else {
		des_dir = b+"/"+des_dir;
	}
	des_dir += source;
	rec_mv(source.c_str(), des_dir);
}

void fmv(string source, string des_dir, string b) {
	flag = 0;
	if(des_dir[0] == '/' || des_dir[0] == '~') {
		if(des_dir[0] == '~')
			des_dir.erase(0, 1);
		des_dir = root+des_dir;
	}
	else {
		des_dir = b+"/"+des_dir;
	}
	if(des_dir.back() != '/')
		des_dir += '/';
	des_dir += source;
	rename(source.c_str(), des_dir.c_str());
}

void mov(string source, string des_dir) {
	flag = 0;
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	string b(buff);
	struct stat statbuf;
	if(source[0] == '/' || source[0] == '~') {
		if(source[0] == '~')
			source.erase(0, 1);
		source = root+source;
	}
	auto it = source.rfind('/');
	if((int)it == (int)source.size()-1)
		fmv(source, des_dir, b);
	else if(it == string::npos) {
		lstat(source.c_str(), &statbuf);
		if(S_ISDIR(statbuf.st_mode))
			dmv(source, des_dir, b);
		else
			fmv(source, des_dir, b);
	}
	else {
		string sub = source.substr(it+1);
		string p = source.substr(0, it);
		chdir(p.c_str());
		lstat(sub.c_str(), &statbuf);
		if(S_ISDIR(statbuf.st_mode))
			dmv(sub, des_dir, b);
		else
			fmv(sub, des_dir, b);
		chdir(buff);
	}
}

void move(string s) {
	flag = 0;
	string des_dir;
	des_dir = s.substr(s.rfind(' ')+1);
	string source;
	source = s.substr(s.find(' ')+1, s.rfind(' ')-s.find(' '));
	string t;
	int i = 0;
	while(i < (int)source.size()) {
		if(source[i] != ' ') {
			t += source[i];
		}
		else {
			mov(t, des_dir);
			t.clear();
		}
		i++;
	}
}

void copy(string s) {
	return;
}

void dirscan(char const *dir, int depth, FILE *fptr) {
	flag = 0;
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
		return;

	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			fprintf(fptr, "%*s%s/\n",depth," ",entry->d_name);
			dirscan(entry->d_name,depth+4, fptr);
		}
		else
			fprintf(fptr, "%*s%s\n",depth," ",entry->d_name);
	}
	chdir("..");
	closedir(dp);
}

void del(char const *dir) {
	flag = 0;
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
		return;

	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			del(entry->d_name);
		}
		else
			remove(entry->d_name);
	}
	chdir("..");
	rmdir(dir);
	closedir(dp);
}

void delete_dir(string s) {
	flag = 0;
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	string path = s.substr(s.find(' ')+1);
	if(path[0] == '/' || path[0] == '~') {
		if(path[0] == '~')
			path.erase(0, 1);
		path = root+path;
	}
	else {
		char buff[PATH_MAX];
		getcwd(buff, sizeof(buff));
		string t(buff);
		path = t+"/"+path;
	}
	del(path.c_str());
	int i = getdir(nbuff);
	if(i == -1)
		getdir(root);
}

void delete_file(string s) {
	flag = 0;
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	string filename = s.substr(s.find(' ') + 1);
	string path;
	auto it = filename.rfind('/');
	if(filename[0] == '/' || filename[0] == '~') {
		if(filename[0] == '~')
			filename.erase(0, 1);
		path = filename.substr(0, it);
		path = root+path;
	}
	else if(filename.find('/') != string::npos)
		path = filename.substr(0, it);
	else
		path = ".";
	getdir(path.c_str());
	dirstack.pop();
	int siz = filename.size();
	if(it != string::npos)
		filename = filename.substr(it+1, siz-it);
	remove(filename.c_str());
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	getdir(root);
	dirstack.pop();
	getdir(nbuff);
	if(strcmp(buff, nbuff) == 0)
		dirstack.pop();
}

void snapshot(string s) {
	flag = 0;
	string snapdir, fl;
	string temp = s.substr(s.find(' ') + 1);
	snapdir = temp.substr(0,temp.find(' '));
	fl = temp.substr(temp.find(' ')+1);
	if(fl[0] == '/' || fl[0] == '~') {
		if(fl[0] == '~')
			fl.erase(0, 1);
		fl = root+fl;
	}
	FILE *fptr;
    fptr = fopen(fl.c_str(), "w");
    if(snapdir[0] == '/' || snapdir[0] == '~') {
		if(snapdir[0] == '~')
			snapdir.erase(0, 1);
		snapdir = root+snapdir;
	}
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	dirscan(snapdir.c_str(), 0, fptr);
	fclose(fptr);
	getdir(buff);
	dirstack.pop();
}

void gt(string s) {
	flag = 0;
	string path;
	path = s.substr(s.find(' ')+1);
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	gotopath(path);
	getdir(path.c_str());
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	if(strcmp(buff, nbuff) == 0)
		dirstack.pop();

}

void create(string s) {
	flag = 0;
	if(s.size() < 13)
		return;
	string fn, path, temp;
	temp = s.substr(s.find(' ')+1);
	fn = temp.substr(0,temp.find(' '));
	path = temp.substr(temp.find(' ')+1);
	char abuff[PATH_MAX];
	getcwd(abuff, sizeof(abuff));
	gotopath(path);
	if(s.substr(7, 4) == "file")
		creat(fn.c_str(), 0666);
	else if(s.substr(7, 3) == "dir")
		mkdir(fn.c_str(), 00777);
	else
		return;
	b = 0;
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	getdir(root);
	dirstack.pop();
	getdir(buff);
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	if(strcmp(abuff, nbuff) == 0)
		dirstack.pop();
}

void rnm(string s) {
	flag = 0;
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	if(s.size() < 10)
		return;
	string o, n;
	string temp = s.substr(s.find(' ') + 1);
	o = temp.substr(0,temp.find(' '));
	n = temp.substr(temp.find(' ')+1);
	if(o.back() == '/')
		o.pop_back();
	if(n.back() == '/')
		n.pop_back();
	string path;
	if(o[0] == '/' || o[0] == '~') {
		if(o[0] == '~')
			o.erase(0, 1);
		auto it = o.rfind('/');
		path = o.substr(0, it);
		path = root+path;
		getdir(path.c_str());
		int siz = o.size();
		o = o.substr(it+1, siz-it);
		siz = n.size();
		it = n.rfind('/');
		n = n.substr(it+1, siz-it);
	}
	else if(o.find('/') != string::npos) {
		auto it = o.rfind('/');
		path = o.substr(0, it);
		getdir(path.c_str());
		int siz = o.size();
		o = o.substr(it+1, siz-it);
		siz = n.size();
		it = n.rfind('/');
		n = n.substr(it+1, siz-it);
	}
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	if(strcmp(buff, nbuff) == 0)
		dirstack.pop();
	rename(o.c_str(), n.c_str());
}

void command() {
	char ch;
	while(1) {
		printf("\033[%d;1H", screenlength());
		printf("COMMAND MODE: ");
		string s;
		while((ch = getchar()) != '\r' && ch != '\n') {
			if(ch == 27)
				return;
			if(ch == 127) {
				int a = s.size()-1;
				s = s.substr(0, a);
				printf("\033[2K");
				printf("\033[%d;1H", screenlength());
				cout<<"COMMAND MODE: "<<s;
				continue;
			}
			s += ch;
			cout<<ch;
		}
		if(s.substr(0, 6) == "rename")
			rnm(s);
		else if(s.substr(0, 6) == "create")
			create(s);
		else if(s.substr(0, 4) == "goto")
			gt(s);
		else if(s.substr(0, 11) == "delete_file")
			delete_file(s);
		else if(s.substr(0, 8) == "snapshot")
			snapshot(s);
		else if(s.substr(0, 10) == "delete_dir")
			delete_dir(s);
		else if(s.substr(0, 4) == "move")
			move(s);
		else if(s.substr(0, 6) == "search")
			search(s);
		else if(s.substr(0, 4) == "copy")
			copy(s);
		
		char buff[PATH_MAX];
		getcwd(buff, sizeof(buff));
		getdir(buff);
		printdir();
		printf("\033[2K");
	}
}