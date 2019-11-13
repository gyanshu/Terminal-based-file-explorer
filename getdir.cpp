#include "getdir.h"

/*comparator function for sorting file_names array*/
bool mycomp(char *string1, char *string2) {
	return strcmp(string1, string2) < 0;
}

/*stores all the file names from the given directory to the file_names vector*/
int getdir(char const *dir) {
	DIR *dp;
	struct dirent *entry;

	if((dp = opendir(dir)) == NULL)						//couldn't open directory, returning
		return -1;

	char buff[PATH_MAX];
	getcwd(buff, sizeof(buff));

	chdir(dir);											//change directory to dir
	getcwd(buff, sizeof(buff));

	backward_stack.push(buff);

	file_names.clear();
	while((entry = readdir(dp)) != NULL) {
		if(strcmp(buff, root) == 0 && strcmp(entry->d_name, "..") == 0)		//If we are at root node, ignore file ".."
			continue;
		file_names.push_back(entry->d_name);
	}
	sort(file_names.begin(), file_names.end(), mycomp);
	len.resize(file_names.size());
	return 0;
}