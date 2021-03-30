#define _GLIBCXX_USE_C99 1
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "version.h"

using namespace std;

string mainUrl = "https://scs.utdallas.edu:80/directory/faculty/people.html?name=Robert";
string protocol; //required
int protocolError = 0;
string domain; //required
string tempDomain; //keeps track of <z> portion of <x>.<y>.<z> of the domain
int domainError = 0;
string port = "Not given"; //optional
int portError = 0;
string filepath; //required
int filepathError = 0;
string parameters = "Not given"; //optional
extern string version = "1.2";

void parseProtocol();
void parseDomain();
void parsePort();
void parseFilepath();
void parseParameters();
void invalidUrl();
void checkErrors();

int main() {
  displayVersion(); //displays current version
  
	cout << "Enter url: ";
	cin >> mainUrl;
	printf("\n");

	parseProtocol();
	parseDomain();
	parseFilepath();
	parseParameters();
	checkErrors();

	cout << "Protocol: " << protocol << "\n";
	cout << "Domain: " << domain << "\n";
	cout << "Port: " << port << "\n";
	cout << "Filepath: " << filepath << "\n";
	cout << "Parameters: " << parameters << "\n";

	//cout << protocolError << "\n" << domainError << "\n" << portError << "\n" << filepathError << "\n"; //debugging
	//cout << mainUrl //debugging
	return 0;
}

void parseProtocol() { //parses protocol section
	string protocolDelim = "://";
	size_t found = mainUrl.find(protocolDelim);

	if (found == string::npos) { //if no delimiter is found, URL is ivnalid
		invalidUrl();
		return;
	}

	protocol = mainUrl.substr(0, found); 
	if (protocol.compare("http") != 0 && protocol.compare("https") != 0 && protocol.compare("ftp") != 0 && protocol.compare("ftps") != 0) { //if protocol is not equal to requirements
		protocolError = 1;
		mainUrl = mainUrl.erase(0, found + protocolDelim.length());
		return;
	}

	mainUrl = mainUrl.erase(0, found + protocolDelim.length());

	return;
}

void parseDomain() { //parses domain section and port section (if it exists)
	string domainDelim = "/";
	string domainDelim2 = ":"; //test for optional port existence
	size_t found = mainUrl.find(domainDelim2);
	
	if (found != string::npos) { //if port exists
		domain = mainUrl.substr(0, found);
		tempDomain = domain; //sets tempDomain to <z> in <x>.<y>.<z> type domain
		tempDomain = tempDomain.erase(0, tempDomain.find(".") + 1);
		tempDomain = tempDomain.erase(0, tempDomain.find(".") + 1);

		if (tempDomain.compare("com") != 0 && tempDomain.compare("net") != 0 && tempDomain.compare("edu") != 0 && tempDomain.compare("biz") != 0 && tempDomain.compare("gov") != 0) {
			domainError = 1;
			mainUrl = mainUrl.erase(0, found + 1);
			return;
		}

		mainUrl = mainUrl.erase(0, found + 1);
		parsePort();

		return;
	}
	else { //if there is no port
		found = mainUrl.find(domainDelim);

		if (found == string::npos) { //if there is no filepath, URL is invalid
			invalidUrl();
			return;
		}

		domain = mainUrl.substr(0, found);
		tempDomain = domain; //sets tempDomain to <z> in <x>.<y>.<z> type domain
		tempDomain = tempDomain.erase(0, tempDomain.find(".") + 1);
		tempDomain = tempDomain.erase(0, tempDomain.find(".") + 1);

		if (tempDomain.compare("com") != 0 && tempDomain.compare("net") != 0 && tempDomain.compare("edu") != 0 && tempDomain.compare("biz") != 0 && tempDomain.compare("gov") != 0) {
			domainError = 1;
			mainUrl = mainUrl.erase(0, found + 1);
			return;
		}

		mainUrl = mainUrl.erase(0, found + 1);

		return;
	}

	return;
}

void parsePort() { //parses port
	string portDelim = "/";
	size_t found = mainUrl.find(portDelim);

	if (found == string::npos) { //if no delimiter is found, URL is ivnalid
		invalidUrl();
		return;
	}

	port = mainUrl.substr(0, found);
	//cout << "test port: " << port;
	int portNum = atoi(port.c_str());
	if (portNum < 1 || portNum > 65535) {
		portError = 1;
		mainUrl = mainUrl.erase(0, found + 1);
		return;
	}

	mainUrl = mainUrl.erase(0, found + 1);

	return;
}

void parseFilepath() { //parses filepath
	string filepathDelim = ".htm";
	string filepathDelim2 = ".html"; //test if ends if htm or html
	size_t found = mainUrl.find(filepathDelim2);

	if (found != string::npos) { //if it ends in ".html"
		filepath = mainUrl.substr(0, found + 5);

		mainUrl = mainUrl.erase(0, found + filepathDelim2.length());

		return;
	}
	else { //if it ends in ".htm"
		found = mainUrl.find(filepathDelim);

		if (found == string::npos) { //if there is no ".htm" or ".html", URL is invalid
			filepathError = 1;
			return;
		}

		filepath = mainUrl.substr(0, found + 4);

		mainUrl = mainUrl.erase(0, found + filepathDelim.length());

		return;
	}

	return;
}

void parseParameters() { //parses parameters (if they exist)
	if (mainUrl.substr(0, 1).compare("?") == 0) {
		parameters = mainUrl.substr(1); //if parameters exist, set the rest of the string to parameters, as it is the only thing left
		return;
	}

	return;
}

void checkErrors() { //checks for errors and displays them
	if (protocolError == 1 || domainError == 1 || portError == 1 || filepathError == 1) {
		cout << "Invalid URL with following erroneous components:\n";
		if (protocolError == 1) {
			cout << "Protocol: " << protocol << " is not a valid protocol.\n";
		}
		if (domainError == 1) {
			cout << "Domain: " << tempDomain << " is an invalid domain name.\n";
		}
		if (portError == 1) {
			cout << "Port: Invalid port number (must be between 1 and 65535).\n";
		}
		if (filepathError == 1) {
			cout << "Filepath: Invalid filepath (make sure it ends in \".htm\" or \".html\").\n";
		}

		exit(EXIT_FAILURE);
		return;
	}

	return; //if no errors, do nothing
}

void invalidUrl() { //for errors that are not from main problems. Ex: ":/" instead of "://", or if program cant find a delimiter
	cout << "The given URL is invalid (unspecified syntax error). \n";
	exit(EXIT_FAILURE);
	return;
}