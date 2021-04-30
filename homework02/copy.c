/* Sinai Park (sp46)
CS 232_homework02
February 21, 2021

Making system calls from a c program to copy program taking two arguments from the command line 
*/

// import C library
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

  int is_reg(const char *path)
  {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
  }

// Taking files as arguments in command line
// source code from https://stackoverflow.com/questions/16869467/command-line-arguments-reading-a-file
int main(int argc, char *argv[])
{

  // file pointers for src dest
  FILE
      *fptr1,
      *fptr2;

  //initiating file content char
  char ch;



  // checking if source file exists --- print out errors
  // source code from https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
  if (is_reg(argv[1]) == 1)
  {
    if (access(argv[2], F_OK) == -1)
    {
      fprintf(stderr, "Error: Unable to read file: %s\nPlease check that filename exists and is not a directory/symlink.\n", argv[1]);

      // if src file does not exist or is not a regular file, return -1
      return -1;
    }
  }

  // source code from https://dyclassroom.com/c/c-command-line-argumentss
  // checking if the destination file exists, print error
  if ((fptr2 = fopen(argv[2], "r")) != NULL)
  {
    fprintf(stderr, "Error: File %s already exists.\nPlease enter another destination filename.\n", argv[2]);

    //fclose(fptr1);
    fclose(fptr2);

    return -1;
  }
  // source code from https://www.guru99.com/c-file-input-output.html
  // new file is created, or if file is present, data inside is truncated
  fptr1 = fopen(argv[1], "r");
  fptr2 = fopen(argv[2], "w");

  // source code from https://codeforwin.org/2018/02/c-program-to-copy-file.html
  // copy the content of source to destination

  while (!feof(fptr1))
  {
    ch = fgetc(fptr1);
    if (ch != EOF)
    {
      //writes the copied content to dest
      fputc(ch, fptr2);
    }
  }

  // file closing operation
  fclose(fptr1);
  fclose(fptr2);

  //return 0 if successful
  return 0;
}