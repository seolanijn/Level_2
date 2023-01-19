/*
author:		Seolan Jin
Date:		July 19, 2021
Purpose:	This program converts a source file from .txt file to .html file.

\file:		txt2html.cpp
\author:	Seolan Jin
\date:		July 19, 2021
\brief:		This program converts a source file from .txt file to .html file.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <locale>


using namespace std;

/*
\fn:		string find_title(string txtFileName);
\brief:		This function will get the filename with extension and
			return the filename without the extension.
\param:		txtFileName will be used to return the name without extension
\return:	htmlFileName will be returned which has no extension
*/
string find_title(string txtFileName);

int main(int argc, char* argv[]) {

	bool isReport = false;
	bool isBinary = false;
	bool isPar = false;

	vector<string> args(&argv[1], &argv[argc]);

	if (args.empty())
	{
		//report and exits if input file is missing
		cerr << "Error: there must be a .txt file in order to convert to a .html file." << endl;
		return EXIT_FAILURE;
	}

	// check for -r switch
	vector<string>::iterator itr = find(args.begin(), args.end(), "-r");
	if (itr != args.end())
	{
		isReport = true;
		args.erase(itr);
	}
	// check for -b switch
	itr = find(args.begin(), args.end(), "-b");
	if (itr != args.end())
	{
		isBinary = true;
		args.erase(itr);
	}
	// check for -p switch
	itr = find(args.begin(), args.end(), "-p");
	if (itr != args.end())
	{
		isPar = true;
		args.erase(itr);
	}
	// check for both -b and -p switch
	if (isBinary && isPar)
	{
		//report and exits if both -b and -p switches are present
		cerr << "Error: cannot have binary and paragraph switches together.\n"
			<< "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
		return EXIT_FAILURE;
	}

	ifstream txtFile;
	ofstream htmlFile;

	if (args[0].find(".txt") != string::npos)
	{
		//Creates an input file object in either read or binary mode with a name given as 
		//an argument on the command line
		if (isBinary)
			txtFile.open(args[0], ios::binary);
		else
			txtFile.open(args[0]);

		//Creates an output file object
		if (args.size() == 1)
		{
			//creates with same name portion as the input filename
			htmlFile.open(find_title(args[0]) + ".html");
		}
		else if (args.size() == 2)
		{
			//creates with a name given as an argument on the command line
			if (args[1].find(".html") != string::npos)
				htmlFile.open(args[1]);
			else
			{
				//report and exits if a provided output file name is invalid
				cerr << "Error: there must be a valid outfile name with a .html extension.\n"
					<< "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			//report and exits if invalid input or incorrect number of parameters is entered
			cerr << "Error: Invalid input. Incorrect number of parameters [" << argc << "].\n"
				<< "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
			return EXIT_FAILURE;
		}
	}
	else
	{
		//report and exits if input file is not entered before .html file
		cerr << "Error: there must be a.txt file before a.html file.\n"
			<< "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
		return EXIT_FAILURE;
	}

	if (!txtFile)
	{
		//report and exits if file is bad and cannot be opened
		cerr << "Error: could not open <" << args[0] << "> for input.";
		return EXIT_FAILURE;
	}

	unsigned int lineCount = 0;
	unsigned int parCount = 0;

	//place <html>, <head> and <body> tags
	//use <title> tag with filename without extension
	htmlFile << "<html>\n<head>\n<title>" << find_title(args[0]) << "</title>\n</head>\n<body>\n";

	//count the newline character
	char chForCount;
	while (txtFile.get(chForCount))
	{
		if (chForCount == '\n' || chForCount == '\r')
			lineCount++;
	}

	//re-set for next streaming
	txtFile.clear();
	txtFile.seekg(0, ios::beg);

	//in order to do thousands separator when print
	locale here("");
	cout.imbue(here);

	//when paragraph switch is on
	if (isPar)
	{
		vector<char> htmlVector;
		char ch;
		char peekCh;
		bool isStart = true;
		bool isEnd = true;
		bool isFirstLoop = true;

		while (txtFile.get(ch))
		{
			//if it is first loop, print <p>
			if (isFirstLoop)
			{
				isFirstLoop = false;
				htmlFile << "<p>\n";
				parCount++;
			}
			peekCh = txtFile.peek();
			//if '\n'(now) + not '\n'(next) and the next value is not the end of file + it is start of the paragraph, print <p> to html file
			if (ch == '\n' && peekCh != '\n' && peekCh != EOF && isStart)
			{
				htmlFile << "\n<p>\n";
				isStart = false;
				isEnd = true;
				parCount++;
			}
			//if '\n'(now) + '\n'(next) + it is end of the paragraph, print </p> to html file
			else if (ch == '\n' && peekCh == '\n' && isEnd)
			{
				htmlFile << "\n</p>";
				isStart = true;
				isEnd = false;
				parCount++;
			}
			//if just '\n'(now) + '\n'(next), print <br> to html file
			else if (ch == '\n' && peekCh == '\n')
			{
				htmlFile << "\n<br>";
			}
			//if the condision is none of above, just print the character to html file
			else
				htmlFile.put(ch);
		}


		htmlFile << "</body>\n</html>";

		//when report switch is on
		if (isReport)
		{
			cout << "Input lines processed, counting translated newline character: " << lineCount << endl;
			cout << "Output paragraphs processed, counting <p></p> tags: " << parCount << endl;
		}
	}
	//when binary switch is on
	else if (isBinary)
	{
		vector<char> txtChar;
		char ch;
		bool lastBrFlag = false;

		//populate txtChar vector to check further index than using peek() function for later
		while (txtFile.get(ch))
		{
			txtChar.push_back(ch);
		}

		size_t ten = 10;

		// push back 10 more character so that out of range error dosen't occur
		for (size_t i = 0; i < ten; i++)
		{
			txtChar.push_back(' ');
		}

		//substract 10 to read only the size of the txt file 
		for (size_t i = 0; i < txtChar.size() - ten; i++)
		{
			//if "\r\n\r\n", print \n<br>
			if ((txtChar[i] == '\r' && txtChar[i + 1] == '\n') && (txtChar[i + 2] == '\r' && txtChar[i + 3] == '\n'))
			{
				lastBrFlag = true;
				htmlFile << "\n<br>";
				i++;
			}
			//if "\r\n" + last <br> flag is on, print \n<br>\n
			else if ((txtChar[i] == '\r' && txtChar[i + 1] == '\n') && lastBrFlag)
			{
				htmlFile << "\n<br>\n";
				lastBrFlag = false;
				i++;
				parCount++;
			}
			//if "\r\n" + last <br> flag is off, just put the character and increment the index
			else if ((txtChar[i] == '\r' && txtChar[i + 1] == '\n') && !lastBrFlag)
			{
				htmlFile.put(txtChar[i]);
				i++;
			}
			//if the condision is none of above, just print the character to html file
			else
				htmlFile.put(txtChar[i]);
		}

		htmlFile << "</body>\n</html>";

		//when report switch is on
		if (isReport)
		{
			cout << "Input lines processed, counting untranslated newline character: " << lineCount << endl;
			cout << "Output paragraphs processed: " << parCount << endl;
		}
	}
	//when any switch is not on
	else
	{
		char ch;
		char peekCh;
		bool lastBrFlag = false;

		while (txtFile.get(ch))
		{
			peekCh = txtFile.peek();

			//if '\n'(now) + '\n'(next), print \n<br>
			if (ch == '\n' && peekCh == '\n')
			{
				lastBrFlag = true;
				htmlFile << "\n<br>";
			}
			//if '\n'(now) + last <br> flag is on, print \n<br>\n
			else if (ch == '\n' && lastBrFlag)
			{
				htmlFile << "\n<br>\n";
				lastBrFlag = false;
				parCount++;
			}
			//if the condision is none of above, just print the character to html file
			else
				htmlFile.put(ch);
		}
		htmlFile << "</body>\n</html>";

		//when report switch is on
		if (isReport)
		{
			cout << "Input lines processed, counting translated newline character: " << lineCount << endl;
			cout << "Output paragraphs processed: " << parCount << endl;
		}
	}


}

string find_title(string txtFileName)
{
	string htmlFileName;
	for (size_t i = 0; i < txtFileName.size(); i++)
	{
		//if '.' is detected, return the filename
		if (txtFileName[i] == '.')
		{
			return htmlFileName;
		}
		else
		{
			htmlFileName += txtFileName[i];
		}
	}
	return "";
}