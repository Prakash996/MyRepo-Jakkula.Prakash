/*
filename: ParseIBMString.cpp
details: C++ Application program takes data from input text file and creates and updated text file.
author: J.P.Prakash
date: 22/04/2020
*/
#include "pch.h"
#include <iostream>
#include<string>
#include <fstream>
#include <regex>
using namespace std;

class IBM {
public:
	
	//function checks the either the given text line containes IBM in it or not
	bool HasIBM(string str, string searchString)
	{
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		transform(searchString.begin(), searchString.end(), searchString.begin(), ::toupper);
		if (str.find(searchString) != string::npos)
		{
			return true;
		}
		return false;
	}
};

class washtype : public IBM
{
protected:
	int pos, pos1, pos2;

public:
	
	//fuction Copyright checks the input file and returns "Copyright" if any of the given condition is true.
	string Copyright(string str)
	{
		if (HasIBM(str, "Confidential"))
		{
			return "Copyright";
		}
		else if (HasIBM(str, "Copyright") && HasIBM(str, "Corp"))
		{
			return "Copyright";
		}
		return "";
	}

	//fuction isMacro checks the input file and if any of the given condition is true it will returns statement.
	string isMacro(string str)
	{
		if (HasIBM(str, "#define"))
		{
			if (HasIBM(str, ".ibm.")) 
				return "MacroWith.com";
			else if (HasIBM(str, "KEY")) 
				return "MacroWithRegistry";
			else
				return "Macro";
		}
		return "";
	}

	//fuction url checks the input file and if the given condition is true it will returns "url".
	string url(string str)
	{
		if (HasIBM(str, "http:") || HasIBM(str, "https:"))
		{
			return "URL";
		}
		return "";
	}

	//fuction ServerName checks the input file and if the given condition is true it will returns "ServerName" statement.
	string ServerName(string str)
	{
		if (HasIBM(str, "O=IBM") && HasIBM(str, "CN="))
		{
			return "ServerName";
		}
		return "";
	}

	//fuction registry checks the input file and if the given condition is true it will returns "Registry" statement.
	string registry(string str)
	{
		if (HasIBM(str, "HKLM"))
		{
			return "Registry";
		}
		return "";
	}

	//fuction os checks the input file and if any of the given condition is true it will returns "OS Specific" statement.
	string os(string str)
	{
		if (HasIBM(str, "IBMRT") || HasIBM(str, "IBMPC") ||
			HasIBM(str, "ibmOS390") || HasIBM(str, "IBMCP") || HasIBM(str, "ibmAS400")
			|| HasIBM(str, "OS2") || HasIBM(str, "IBMC") || HasIBM(str, "IBMRT"))
		{
			return "OS Specific";
		}
		return "";
	}
	
	//fuction comment checks the input file and if any of the given condition is true it will returns "CommentedLine" statement.
	string comment(string str)
	{
		string pattern("(/\\*([^*]|[\r\n]|(\\*+([^*/]|[\r\n])))*\\*+/)|(//.*)");
		regex r(pattern, regex_constants::egrep);
		string s1("//");
		string s2("/*");
		string s3(" * ");
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		for (sregex_iterator it(str.begin(), str.end(), r), end;it != end;++it)
		{
			pos = str.find(s1);
			pos1 = str.find("IBM");
			pos2 = str.find(s2);
			if (pos == 0 || (pos > 0 && pos1 > pos))
			{
				return "CommentedLine";
			}
			else if (pos2 >= 0)
			{
				return "CommentedLine";
			}
		}
		pos = str.find(s2);
		pos1 = str.find("IBM");
		if (pos == 0 || (pos > 0 && pos1 > pos))
		{
			return "CommentedLine";
		}
		pos = str.find(s3);
		if (pos == 0)
		{
			return "CommentedLine";
		}
		return "";
	}

	//fuction debug checks the input file and if any of the given condition is true it will returns "debug" statement.
	string debug(string str)
	{
		string str1("xprintf");
		pos = str.find(str1);
		if (pos >= 0)
		{
			return "Debug";
		}
		return "";
	}

	//fuction calls the above functions and appends data into the destination file.
	string washType(string str)
	{
		string type;
		type.append(Copyright(str));
		type.append(isMacro(str));
		type.append(os(str));
		type.append(registry(str));
		type.append(ServerName(str));
		type.append(url(str));
		type.append(comment(str));
		type.append(debug(str));
		return type;
	}
};

class parser : public washtype
{
protected:
	string path;
	int found;
public:
	
	//fuction FileName checks the file path where the end of path "/\\" is considered as the filename and returns the path.
	string FileName(const string& str)
	{
		found= str.find_last_of("/\\");
		path = str.substr(found + 1); // check that is OK
		return path;
	}

	//fuction dirnameOf checks the file path where the text before end of path "\\/" is considered as the directory name and returns the position.
	string dirnameOf(const string& fname)
	{
		pos = fname.find_last_of("\\/");
		return (string::npos == pos)? " ": fname.substr(0, pos);
	}

	//fuction fileType checks the input file and if any of the given condition is true it will returns "filetype" statement.
	string fileType(string filename, string filepath)
	{
		string filetype;
		if (HasIBM(filename, "IBM"))
		{
			filetype = "FileNameHasIBM";
		}
		if (HasIBM(filepath, "IBM"))
		{
			filetype = "PathNameHasIBM";
		}
		if (HasIBM(filename, "IBM") && HasIBM(filepath, "IBM"))
		{
			filetype = "File&PathNameHasIBM";
		}
		if (filename.substr(filename.length() - 3) == ".rc" || filename.substr(filename.length() - 4) == ".dlg")
		{
			filetype = "UI";
		}
		if (filename.substr(filename.length() - 4) == ".def")
		{
			filetype = "External API";
		}
		if (filename.substr(filename.length() - 3) == ".sh")
		{
			filetype = "Script";
		}
		return filetype;
	}

	//fuction getIBM writes the input text file and reads it into _update.txt file
	//calls the functions accordingly 
	bool getIBM(string fileName)
	{
		ifstream file(fileName);
		ofstream myfile;
		string newFile = fileName.c_str();
		string toReplace(".txt");
		int pos = newFile.find(toReplace);
		newFile.replace(pos, toReplace.length(), "_updated.txt");
		myfile.open(newFile);
		if (file.is_open()) 
		{
			string line;
			string filename;
			string LineNumber;
			string filepath;
			string existingFormat;
			string filetype;
			string type;
			regex r("[0-9]: +");
			printf("\nFileName File Path LineNumber Existing Format\n");
			while (getline(file, line))
			{
				cmatch results;
				if (regex_search(line.c_str(), results, r)) //if condition is true it will print/append the data 
				{
					string delimiter = ":";
					size_t pos = 0;

					pos = line.find(delimiter);
					LineNumber = line.substr(0, pos);
					line.erase(0, pos + delimiter.length());
					existingFormat = line;
					type = washType(line);
					cout << filetype.c_str() << filename.c_str() << filepath.c_str() << LineNumber.c_str() << existingFormat.c_str() << type.c_str();
					myfile << filetype.c_str() << " ^ " << filename.c_str()
						<< " ^ " << filepath.c_str() << " ^ " << LineNumber.c_str() << " ^ "
						<< existingFormat.c_str() << " ^ " << type.c_str() << endl;
					cout<< "\n-----------------------------------------------------\n";
				}
				else  		//searches for the filetype and returns the filename, filepath.
				{
					filetype = "---";
					filename = FileName(line.c_str());
					filepath = dirnameOf(line.c_str());
					if (filepath.empty())
					{
						filepath = "*****";
					}
					else
					{
						filetype = fileType(filename, filepath);
					}
				}

			}
			myfile.close();
			file.close();
		}
		return false;
	}

};


int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Usage PerselIBMString:parserstring.exe  <<inputFileName>>.txt" << endl;
		return -1;
	}
	else if (strcmp(argv[2], "-h") == 0)     //created a help command
	{
		cout << "\n usage of file --> \n"
			"\t Enter ParseIBMString + FilePath in command line arugments" << endl;
	}
	else
	{
		parser p;
		p.getIBM(argv[2]);
	}
	return 0;
}
