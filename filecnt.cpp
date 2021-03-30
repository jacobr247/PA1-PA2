#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
void countDir(const char* directory);
int fileCount = 0;
int dirCount = 0;
int byteCount = 0;
static string version = "1.2"; //test for something irrelevant


int main(int argc, char *argv[]) {
	//count directory given by user
  if (argc != 2)  { 
    return 1;
  }
 
	countDir(argv[1]);

	cout << "The total number of directories in directory " << argv[1] << " is: " << dirCount << "\n";
	cout << "The total number of files in directory " << argv[1] << " is: " << fileCount << "\n";
	cout << "The total number of bytes occupied by all files in directory " << argv[1] << " is: " << byteCount << "\n";

	return 0;
}

void countDir(const char* directory) {
	DIR* currentDir = opendir(directory);
	struct dirent* total;
  char next[1000];

	if (!currentDir) { //if it cannot open directory
		cout << "Cannot open directory " << directory;
		exit;
	}

	while ((total = readdir(currentDir)) != NULL) { //while there are files existing
		if (total->d_type == DT_DIR && strcmp(total->d_name, "..") != 0 && strcmp(total->d_name, ".") != 0) { //if current file is a directory
			dirCount++;
			//recursively check sub-directories, excluding "." and ".." directories
      strcpy(next, directory);
      strcat(next, "/");
      strcat(next, total->d_name);
			countDir(next);
		}
		if (total->d_type == DT_REG) { //if current file is a regular file, not a directory
			fileCount++;
      struct stat bytes;
			if (stat(total->d_name, &bytes) == 0) { //gets current file size and adds it to byteCount
				byteCount += bytes.st_size;
			}
		}
	}
	
	closedir(currentDir);
  return;
}
