#include <vector>
#include <stack>
#include <string>
#include <stdio.h>
#include <termios.h>
#include <algorithm>
#include <iostream>
using namespace std;

#ifndef INC_MODULE1_H
#define INC_MODULE1_H
extern struct termios initial_settings, new_settings;
extern vector<char*> name;
extern vector<int> len;
extern stack<string> dirstack, fwstack;
extern char* root;
extern int b, e;
extern unsigned int crow;
extern unsigned int ind, currow;
extern bool status, flag;
#endif
