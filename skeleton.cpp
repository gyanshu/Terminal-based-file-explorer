#include "skeleton.h"

struct termios initial_settings, new_settings;
vector<char*> file_names;
vector<int> len;
stack<string> backward_stack, forward_stack;
char* root;
int beg, last;
unsigned int ind, cur_row;
bool mode, flag;