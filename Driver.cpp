#include <iostream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include "SCA.h"

using namespace std;

string matchedSuggestions;
string htmlFilePath;
string treeTxtFilePath;
string errorTxtFilePath;
string templateTableFile = "/SCA/core/dat/rules.txt";
string sourceFileDir = "/SCA/user/source-code";
char *homeDir;

void explore(char *dir_name);

int main() {
	// get user home directory
	struct passwd *pw = getpwuid(getuid());
	homeDir = pw->pw_dir;

	// update absolute paths for templateTableFile and sourceFileDir
	sourceFileDir = string(homeDir) + sourceFileDir;
	templateTableFile = string(homeDir) + templateTableFile;
	
	explore((char*)sourceFileDir.c_str());

	return 0;
}

void explore(char *dir_name) {
	DIR *dir;
	struct dirent *entry;
	struct stat info;

	// open directory
	dir = opendir(dir_name);
	if (!dir) {
		cout << "Unable to open directory => " << dir_name << endl;
		return;
	}
	else {
		while((entry = readdir(dir)) != NULL) {
			string cppFilePath = sourceFileDir + "/" + string(entry->d_name);
			
			if (cppFilePath.substr(cppFilePath.length() - 3, 3) == "cpp") {
				SCA* sca = new SCA(cppFilePath, templateTableFile);
				Node* rt;

				sca->existsFile(cppFilePath);
				cout << "File exists\n";
				
				sca->loadTemplateTable(templateTableFile);
				cout << "Loaded template table\n";
				
				cppFilePath = sca->loadSourceCode(cppFilePath);
				cout << "Loaded Source Code\n";
				cout << cppFilePath << endl;

				if (cppFilePath == "failed") {
					cout << "Loading source code failed... exiting..." << endl;
					return;
				}
				sca->serveCodeToANTLR(treeTxtFilePath, errorTxtFilePath);
				cout << "Served code to ANTLR\n";

				// get root
				rt = sca->readANTLROutputTree(treeTxtFilePath);
				cout << "Read tree text file into memory\n";

				sca->readANTLROutputErrors(errorTxtFilePath);
				cout << "Read output error file\n";

				matchedSuggestions = sca->matchTemplateWithTree();
				cout << "Matched suggestions with tree\n";

				htmlFilePath = sca->createHTMLFile();
				cout << "Created html file\n";
			}
		}
	}
	closedir(dir);
}