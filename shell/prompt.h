//
//  prompt.h
//  CS232 Command Shell
//
//  Created by Victor Norman on 1/20/15.
//  Copyright (c) 2015 Victor Norman. All rights reserved.

//  Sinai Park(sp46)
//  For Homework03, CS 232
//

#ifndef __CS232_Command_Shell__prompt__
#define __CS232_Command_Shell__prompt__

#include <iostream>
#include <string>
using namespace std;

class Prompt
{
public:
    Prompt();
    string get() const { return cwd + " $ "; }
    string getCwd() const { return cwd; }
    void set();
private:
    string cwd;
};

#endif /* defined(__CS232_Command_Shell__prompt__) */
