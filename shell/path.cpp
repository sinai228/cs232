//
//  path.cpp
//  CS232 Command Shell
//
//  Created by Sinai Park (sp46) on 2/25/21
//  For Homework03, CS 232

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <dirent.h>
#include <vector>
#include "path.h"
#include "prompt.h"
using namespace std;

// #define DEBUGME 1

/**
 * Constructing PATH environment variable
 */

//getenv found in https://www.tutorialspoint.com/c_standard_library/c_function_getenv.htm
Path::Path()
{
    vector<char*> directory;
    aPath = getenv("PATH");
}

/**
 * param: string, program 
 * return: index of the directory with the name of the program
 *         -1, if not found
 * create a struct 
 */

int Path::find(const string& program) const
{
    DIR *tempdir;
    struct dirent *dit;

    for (unsigned i = 0; i < directory.size(); i++)  //if i is less than size of diretory, valid
    {
        if ((tempdir = opendir(directory[i])) != NULL) //directory is not empty
        {
            while ((dit = readdir(tempdir)) != NULL) //file is not emmpty
            {
                if (dit-> d_name == program) //if file name equals the program name
                {
                    return i;
                }
            }
            closedir(tempdir);
        }
    }
    return -1;
}

/**
 * returns a string, name of directory of index i
 * param: integer i
 * 
 */

string Path::getDirectory(int i) const
{
    if (i > directory.size())
    {
        throw range_error("Invalid range of indexes.");
    }
    else
    {
        char* dir = directory[i];
        return dir;
        
    }
}