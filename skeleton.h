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
/*Saves terminal intial settings and new settings(needed for our application) respectively 
so that after program is run terminal can be reset to its intial settings*/
extern struct termios initial_settings, new_settings;	
//Stores the list of files in the current directory
extern vector<char*> file_names;
//Stores length of every file's entry(as it is shown on terminal)
extern vector<int> len;
/*backward_stack is used for going back in the directory structure(left key and backspace key), and
  forward_stack is used for going forward in the directory structre(right key)*/
extern stack<string> backward_stack, forward_stack;
//Stores path of the root directory(Directory where the application is run)
extern char* root;
/*beg stores the index of the topmost displayed filename on the screen, and
  last stores the index of the last displayed filename on the terminal in the file_names vector*/
extern int beg, last;	
/*ind stores the index of the file at which the cursor is present currently, and
  cur_row stores row number of the cursor position*/					
extern unsigned int ind, cur_row;
//mode is 0 for Normal mode and 1 for Command mode 
extern bool mode, flag;
#endif
