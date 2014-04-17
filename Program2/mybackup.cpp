/*
 * Author: Joshua Tower
 * Modified by: Mike Rogers
 * Email: Joshua.Tower@gmail.com
 *        mrogers@tntech.edu
 * Tennessee Tech University 2011-2013
 * Part of NSF Award NO. DUE - 1140864
 *
 * Adapted from "Safe coding: Race conditions" 
 * by Frédéric Raynal, Christophe Blaess, and Christophe Grenier
 * URL: http://www.cgsecurity.org/Articles/SecProg/Art5/index.html
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main (int argc, char* argv [])
{
    struct stat st;// Holds file information

    // First we call stat to get the file data and place it inside st. If
    // the file fails to open -1 will be returned. If there is a problem,
    // a message is displayed and the program exits.
    if (stat(argv[1], &st) < 0)  {
      cout<<"Can't find "<<argv[1]<<endl;
      exit(EXIT_FAILURE);
    }
    
    // Now we compare the id of the source file owner to the current user. 
    // We only want to allow users to copy files (read) that they own.
    if (st.st_uid != getuid ()) {
      cout<<"Not the owner of "<<argv[1]<<endl;
      exit(EXIT_FAILURE);
    }

    // Check the destination file.  If it exists, it must be owned by
    // the user.
    if (stat(argv[2], &st) < 0) {
      // Now we compare the id of the file owner to the current user. We only
      // want to allow users to write over files that they own.
      if (st.st_uid != getuid ()) {
        cout<<"Not the owner of "<<argv[1]<<endl;
        exit(EXIT_FAILURE);
      }
      
    }


    // Now pause to allow attacker to switch files.
    sleep(45);
    ssize_t bytes;
    int fps, fpd;
    char buffer[500];
    
    if((fps = open(argv[1], O_RDONLY)) == -1) {
      perror("opening source");
      exit(EXIT_FAILURE);
    }
    if((fpd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
      perror("opening destination");
      exit(EXIT_FAILURE);
    }
    
    while((bytes = read(fps, buffer, 500)) > 0)
      write(fpd, buffer, bytes);
    
    close(fpd);
    close(fps);
    
    exit(EXIT_SUCCESS);
}

