#include "skeleton.h"

struct termios initial_settings, new_settings;
vector<char*> name;
vector<int> len;
stack<string> dirstack, fwstack;
char* root;
int b, e;
unsigned int crow;
unsigned int ind, currow;
bool status, flag;