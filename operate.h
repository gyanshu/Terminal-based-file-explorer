#define cls() printf("\033[H\033[J")
#include "getdir.h"
#include "printdir.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "input.h"
#include "skeleton.h"
#include "command.h"
#ifndef INC_MODULE5_H
#define INC_MODULE5_H

void reset();
void operate();
#endif