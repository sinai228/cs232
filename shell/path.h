//
//  path.h
//  CS232 Command Shell
//
//  Created by Sinai Park (sp46) on 2/25/21
//  For Homework03, CS 232


#ifndef __CS232_Command_Shell__path__
#define __CS232_Command_Shell__path__

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Path
{
public:
    Path();
    int find(const string& program) const;
    string getDirectory (int i) const;
private:
    string aPath;
    vector<char*> directory;
};

#endif /* defined(__CS232_Command_Shell__path__) */
