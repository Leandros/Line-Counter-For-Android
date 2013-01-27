#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

using namespace std;

void listdir(const char *path)
{
	DIR *pdir = NULL;
	pdir = opendir(path);
	struct dirent *pent = NULL;
	const char * comp[] = { ".", ".." };

	if (pdir == NULL)
	{
		printf("\nERROR! pdir could not be initialised correctly");
		return;
	}

	while (pent = readdir(pdir))
	{
		if (pent == NULL)
		{
			printf("\nERROR! pent could not be initialised correctly");
			return;
		}

		if (strcmp(pent->d_name, comp[0]) == 0 || strcmp(pent->d_name, comp[1]) == 0)
		{
			// Exclude from list.
		}
		else 
		{
			struct stat st;
			lstat(pent->d_name, &st);
			// Not working. Don't know why. Maybe I should use boost.
			if(S_ISDIR(st.st_mode) == 0)
			{
				printf("\t DIRECTORY\n");
			}
			else
			{
			   printf("\t FILE\n");
			}
			printf("%s\n", pent->d_name);
		}
		
	}

	closedir(pdir);
}

int main(int argc, char** argv)
{

	const char * help[] = { "--help", "-h" };
	const char * commands[] = { "--no-files", "-nf", "--version", "-t" };
	const char * empty[] = { "" };
	const char * input[1];

	if (argv[1] == NULL) {
		input[0] = "";

	} else {
		input[0] = argv[1];
	}

	if (strcmp(input[0], help[0]) == 0 || strcmp(input[0], help[1]) == 0)
	{
		cout << "Usage: lcfa [option] \n";
		cout << "\n";
		cout << "Commands: \n";
		cout << "--no-files / -nf: " << "Don't print the file names, only print line count. \n";
		cout << "--version: " << "Print the version and exits. \n";

	}
	else if (strcmp(input[0], commands[0]) == 0 || strcmp(input[0], commands[1]) == 0)
	{
		char javacommand[1000];
    	sprintf(javacommand, "( find src/ -name '*.java' -print0 | xargs -0 cat ) | wc -l");

    	char xmlcommand[1000];
    	sprintf(xmlcommand, "( find . -path './.sonar' -prune -o -path './.idea' -prune -o -path './bin' -prune -o -name '*.xml' -print0 | xargs -0 cat ) | wc -l");

		cout << "Java Lines: \n";
		system(javacommand);
		cout << "\n";
		cout << "XML Lines: \n";
		system(xmlcommand);

	}
	else if (strcmp(input[0], commands[2]) == 0)
	{
		cout << "Version: 0.1 \n";
		cout << "Source on GitHub (https://github.com/Leandros/Line-Counter-For-Android) \n";
		cout << "Copyright 2013 by Arvid Gerstmann \n";

	}
	else if (strcmp(input[0], commands[3]) == 0)
	{
		// Bare code for getting the line count of one file.
		int numLines = 0;
		string line;
		ifstream file("AndroidManifest.xml");
		while (getline(file, line))
		{
			++numLines;
		}
		cout << "AndroidManifest has " << numLines << " lines. \n";

		listdir("src");
		cout << "\n \n \n \n \n";
		listdir("res");

	}
	else
	{
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