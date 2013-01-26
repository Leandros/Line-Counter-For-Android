#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char** argv)
{
	const char * help[] = { "--help", "-h" };
	const char * commands[] = { "--no-files", "-nf", "--version" };
	const char * empty[] = { "" };
	const char * input[1];

	if (argv[1] == NULL) {
		input[0] = "";

	} else {
		input[0] = argv[1];
	}

	if (strcmp(input[0], help[0]) == 0 || strcmp(input[0], help[1]) == 0) {
		cout << "Usage: lcfa [option] \n";
		cout << "\n";
		cout << "Commands: \n";
		cout << "--no-files / -nf: " << "Don't print the file names, only print line count. \n";
		cout << "--version: " << "Print the version and exits. \n";

	} else if (strcmp(input[0], commands[0]) == 0 || strcmp(input[0], commands[1]) == 0) {
		char javacommand[1000];
    	sprintf(javacommand, "( find src/ -name '*.java' -print0 | xargs -0 cat ) | wc -l");

    	char xmlcommand[1000];
    	sprintf(xmlcommand, "( find . -path './.sonar' -prune -o -path './.idea' -prune -o -path './bin' -prune -o -name '*.xml' -print0 | xargs -0 cat ) | wc -l");

		cout << "Java Lines: \n";
		system(javacommand);
		cout << "\n";
		cout << "XML Lines: \n";
		system(xmlcommand);

	} else if (strcmp(input[0], commands[2]) == 0) {
		cout << "Version: 0.1 \n";
		cout << "Source on GitHub (https://github.com/Leandros/Line-Counter-For-Android) \n";
		cout << "Copyright 2013 by Arvid Gerstmann \n";

	} else {
		char javacommand[1000];
    	sprintf(javacommand, "find src/ -name '*.java' | xargs wc -l");

    	char xmlcommand[1000];
    	sprintf(xmlcommand, "find . -path './.sonar' -prune -o -path './.idea' -prune -o -path './bin' -prune -o -name '*.xml' | xargs wc -l");

		cout << "Java Lines: \n";
		system(javacommand);
		cout << "\n";
		cout << "XML Lines: \n";
		system(xmlcommand);
	}
}