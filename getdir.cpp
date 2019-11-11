#include "getdir.h"

bool mycomp(char *a, char *b) {
	return strcmp(a, b) < 0;
}

int getdir(char const *dir) {
	DIR *dp;
	struct dirent *entry;

	if((dp = opendir(dir)) == NULL)
		return -1;
	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));
	if(!strcmp(dir, "..") && !strcmp(buff, root)) {
		return -1;
	}
	chdir(dir);
	getcwd(buff, sizeof(buff));
	dirstack.push(buff);
	name.clear();
	while((entry = readdir(dp)) != NULL) {
		if(strcmp(buff, root) == 0 && strcmp(entry->d_name, "..") == 0)
			continue;
		name.push_back(entry->d_name);
	}
	sort(name.begin(), name.end(), mycomp);
	len.resize(name.size());
	return 0;
}