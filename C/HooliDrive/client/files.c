/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * October 7, 2015
 * files.c is a supporting class for client that contains the functions to traverse a file tree and print its file contents and checksums to a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <zlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <syslog.h>
#include <dirent.h>
#include "files.h"
#include "checksums.h"

#define MAX_PATH 1024

/*
 * searchDirectory method
 * This method traverses every file in a specified file directory and writes each file with its corresponding checksum to a specified file
 * Input parameters:
        name - The path of the directory in which will be searched
        prev - Pass as "" to start at the root of the passed direcotry
        output - The file to output the files with their corresponding checksums to
 * Output: None
 */
void searchDirectory(char *name, char *prev, FILE *outfile) {
    
    // declare a directory stream dir
    DIR *dir;
    // declare a dirent structure to later read the directory to
    struct dirent *start;
    // declare an array r for the root directory path
    char root[MAX_PATH];
    // declare an array p for the previously visited directory path
    char path[MAX_PATH];
    // if the directory is not null, open it
    if ((dir = opendir(name)) != NULL) {
        // loop until we reach a directory that reads in as null
        while ((start = readdir(dir)) != NULL) {
            // if statement to skip the . and .. directories
            if (strcmp(start->d_name,"..") && strcmp(start->d_name,".")) {
                // if the located directory read in a folder directory
                if (start->d_type == DT_DIR) {
                    // populate the string array r with the root path/new found dir
                    strcpy(root, name);
                    strcat(root, "/");
                    strcat(root, start->d_name);
                    // add the directory to string array p for previously visited
                    strcpy(path, prev);
                    strcat(path, start->d_name);
                    strcat(path, "/");
                    // make recursive call for the new directory found
                    searchDirectory(root, path, outfile);
                }
                // if the located directory is a single file
                else {
                    // construct the file path temporarily
                    char temp[MAX_PATH];
                    strcpy(temp, name);
                    strcat(temp, "/");
                    strcat(temp, start->d_name);
                    // if the file has read permissions, write its checksum to file
                    if (access(temp, R_OK) == 0) {
                        // write the file found and its checksum to the output file
                        saveFileCheck(name, prev, start->d_name, outfile);
                    }
                    else {
                        // error message for the unopened file because of permissions
                        syslog(LOG_WARNING, "Warning: File %s%s did not have read permission", prev, start->d_name);
                    }
                }
            }
        }
        // close the directory stream
        closedir (dir);
    }
    else {
        // error message for the unopened file because of permissions
        syslog(LOG_ERR, "Error: The directory %s/ does not exist, please try a different parameter", name);
        exit(EXIT_FAILURE);   
 }
}

/*
 * saveFileCheck method
 * This method writes the passed file and its checksum to an output file
 * Input parameters:
        n - The path of the file
        p - The location of the file inside the home root
        s - The file name found
 * Output: None
 */
void saveFileCheck(char *n, char *p, char *s, FILE *outfile) {
    // declare two string arrays for the full path and checksum path
    char fullPath[MAX_PATH];
    char writePathOut[MAX_PATH];
    // populate the string array full with the path to file needing a checksum
    strcpy(fullPath, n);
    strcat(fullPath, "/");
    strcat(fullPath, s);
    // add the directory to string array cs for previously visited
    strcpy(writePathOut, p);
    strcat(writePathOut, s);
    strcat(writePathOut, ",");
    
    // write the line of the file and checksum to file
    syslog(LOG_DEBUG, "* %s%s (%08X)", p, s, checksum(fullPath));
    fprintf(outfile, "%s%08X\n", writePathOut, checksum(fullPath));
    //printf("%s%08X\n", writePathOut, checksum(fullPath));
}
