#include "command.h"

void gotopath(string &path) {
	if(path[0] == '/' || path[0] == '~') {
		if(path[0] == '~')
			path.erase(0, 1);
		path = root+path;
	}
	getdir(path.c_str());
	backward_stack.pop();
}

void getpath(string &filename) {
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	string curr_dir(buff);
	if(filename[0] == '/' || filename[0] == '~') {
		if(filename[0] == '~')
			filename.erase(0, 1);
		filename = root+filename;
	}
	else {
		filename = curr_dir+"/"+filename;
	}
	if(filename.back() == '/')
		filename.pop_back();
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
				file_names.push_back(strng);
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
			file_names.push_back(strng);
		}
	}
	chdir("..");
	closedir(dp);
}

void search(string s) {
	file_names.clear();
	char const *c = ".";
	sch(c, s.c_str());
}

void dmv(string source, string des_dir) {
	string dirname = source.substr(source.rfind("/") + 1);
	des_dir += "/" + dirname;
	mkdir(des_dir.c_str(), 00777);
	
	DIR *dp;																		//going inside directory
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(des_dir.c_str())) == NULL)
		return;
	chdir(des_dir.c_str());
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			dmv(entry->d_name, des_dir);
		}
		else
			rename(entry->d_name, (des_dir+entry->d_name).c_str());
	}
	chdir("..");
	closedir(dp);
}

void fmv(string source, string des_dir) {
	string filename = source.substr(source.rfind("/") + 1);
	des_dir += "/" + filename;
	rename(source.c_str(), des_dir.c_str());
}

void mov(string source, string des_dir) {
	getpath(source);
	getpath(des_dir);

	struct stat statbuf;
	lstat(source.c_str(), &statbuf);
	if(S_ISDIR(statbuf.st_mode))
		dmv(source, des_dir);	
	else
		fmv(source, des_dir);
}

void move(string s) {
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
				file_names.push_back(strng);
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
			file_names.push_back(strng);
		}
	}
	chdir("..");
	closedir(dp);
}

void del(char const *dir) {
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
	backward_stack.pop();
	int siz = filename.size();
	if(it != string::npos)
		filename = filename.substr(it+1, siz-it);
	remove(filename.c_str());
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	getdir(root);
	backward_stack.pop();
	getdir(nbuff);
	if(strcmp(buff, nbuff) == 0)
		backward_stack.pop();
}

void dirscan(char const *dir, int depth, FILE *fptr) {
	string direc(dir);
	getpath(direc);
	dir = direc.c_str();
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
		return;

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
	closedir(dp);
}

void snapshot(string s) {
	string snapdir, fl;
	string temp = s.substr(s.find(' ') + 1);
	snapdir = temp.substr(0,temp.find(' '));
	fl = temp.substr(temp.find(' ')+1);
	getpath(fl);
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
}

void gt(string s) {
	string path;
	path = s.substr(s.find(' ')+1);
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	gotopath(path);
	getdir(path.c_str());
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	if(strcmp(buff, nbuff) == 0)
		backward_stack.pop();

}

void create(string s) {
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
	beg = 0;
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	getdir(root);
	backward_stack.pop();
	getdir(buff);
	char nbuff[PATH_MAX];
	getcwd(nbuff, sizeof(nbuff));
	if(strcmp(abuff, nbuff) == 0)
		backward_stack.pop();
}

void rnm(string s) {
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
		backward_stack.pop();
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