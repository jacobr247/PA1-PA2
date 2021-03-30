#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include "version.h"

using namespace std;

extern string version = "1.2"; //version variable

int main(int argc, char *argv[])  {
  displayVersion();

  if (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "-b") != 0)  { //check for invalid option input
    cout << "Invalid option given. Please enter \"-d input\" for directories, \"-f input\" for files, or \"-b input\" for bytes.";
    return 0;
  }
  
  if (strcmp(argv[1], "-d") == 0)  { //check for directories given -d option
    //cout << "debugging for directories\n";
    string temp;
    bool found = false;
    
    while (getline(cin, temp))  {
      int pos = temp.find("directories");
      if (pos != string::npos)  {
        found = true;
        cout << temp << "\n";
      }
    }
    
    if (found == false) {
        cout << "Could not find the word directories.\n";
    }
    
    return 0;
  }
  
  if (strcmp(argv[1], "-f") == 0)  { //check for files given -f option
    //cout << "debugging for files\n";
    string temp;
    bool found = false;
    int i = 0;
    
    while (getline(cin, temp))  {
      i++;
      int pos = temp.find("files");
      if (pos != string::npos && i == 2)  {
        found = true;
        cout << temp << "\n";
      }
    }
    
    if (found == false) {
        cout << "Could not find the word files.\n";
      }
      
    return 0;
  }
  
  if (strcmp(argv[1], "-b") == 0)  { //check for bytes given -b option
    //cout << "debugging for bytes\n";
    string temp;
    bool found = false;
    
    while (getline(cin, temp))  {
      int pos = temp.find("bytes");
      if (pos != string::npos)  {
        found = true;
        cout << temp << "\n";
      }
    }
    
    if (found == false) {
        cout << "Could not find the word bytes.\n";
    }
    
    return 0;
  }
  
  return 0;
}