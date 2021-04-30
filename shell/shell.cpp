//
//  shell.cpp
//  CS232 Command Shell
//
//  Created by Sinai Park (sp46) on 2/25/21
//  For Homework03, CS 232

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

/**
 * param: null
 * return: index of the directory with the name of the program
 *         -1, if not found
 * forever loop to display the prompt,
 * wait for the user to type in command
 * parse it and handle other things like:
 *  cd 
 *  pwd
 *  exit
 * 
 */
void Shell::run()
{

    while (true)
    {

        cout << prompt.get() << flush; //display the prompt in the terminal

        //read from the command line;
        CommandLine input = CommandLine(cin);

        // source code from https://stackoverflow.com/questions/5157337/c-reading-command-line-parameters
        // and https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
        if (strcmp("cd", input.getCommand()) == 0)
        {
            int curr_dir = chdir(input.getArgVector(1));
            if (curr_dir == -1)
            {
                cout << "Is not a valid command..." << endl;
            }
            else
            {
                prompt = Prompt();
            }
            continue;
        }

        // handle the pwd command
        if (strcmp("pwd", input.getCommand()) == 0)
        {
            cout << prompt.get() << endl; //print the current working directory
            continue;
        }
        // exit out of the shell command line
        if (strcmp("exit", input.getCommand()) == 0)
        {
            //return directory
            cout << "Exiting..." << endl;
            return;
        }

        // handle null cases as well
        if ( input.getCommand() == NULL)
        {
            cout << "Please enter a command..." << endl;
            continue;
        }

        if (path.find(input.getCommand()) == 0)
        {
            cout << "Please enter a valid command..." << endl;
        }

        
        else
        {
            // use fork and exec to handle everything
            // source code from https://www.geeksforgeeks.org/difference-fork-exec/ and https://brennan.io/2015/01/16/write-a-shell-in-c/
            pid_t pid, wpid;
            int status;

            pid = fork();
            if (pid == 0) //i am the child
            {
                if (execvp(input.getCommand(), input.getArgVector()) == -1)
                {
                   // cout << "Could not execute command..." << endl;
                   perror("Error...");
                }
                exit(EXIT_FAILURE);
            }

            else if (input.noAmpersand())
            {
                waitpid(pid, &status, 0);
            }
            cout << endl;
        }
    }
}
