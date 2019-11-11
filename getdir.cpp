#include "getdir.h"

//comparator function for sorting file_names array
bool mycomp(char *string1, char *string2) {
	return strcmp(string1, string2) < 0;
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
	backward_stack.push(buff);
	file_names.clear();
	while((entry = readdir(dp)) != NULL) {
		if(strcmp(buff, root) == 0 && strcmp(entry->d_name, "..") == 0)
			continue;
		file_names.push_back(entry->d_name);
	}
	sort(file_names.begin(), file_names.end(), mycomp);
	len.resize(file_names.size());
	return 0;
}