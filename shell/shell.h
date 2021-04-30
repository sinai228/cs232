//
//  shell.h
//  CS232 Command Shell
//
//  Edited by Sinai Park (sp46) on 2/28/21
//  For Homework03, CS 232

#ifndef Shell__
#define Shell__


#include "prompt.h"
#include "path.h"
#include "commandline.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
using namespace std;

class Shell {
    public:
        Shell() {};
        void run();

    private: 
        Prompt prompt;
        Path path;
};

#endif