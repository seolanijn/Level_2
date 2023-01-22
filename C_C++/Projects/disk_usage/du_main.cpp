/*
author:     Seolan Jin
Date:       Aug. 9, 2021
Purpose:    To display allocation space for each file and directory contained in a given pathname

\file:      du_main.cpp
\version:   1.0.0
*/


#include <iostream>
#include <string>
#include <vector>

#include "du_functions.hpp"

using namespace std;

#include <filesystem>
using namespace std::filesystem;

int main(int argc, char* argv[])
{
	//Get input options
	Options options = parseInput(argc, argv);


    //Prints error message, help message, or version if any
	if (options.help)
	{
        cout << "\n\n===========================================================\n" <<
                "Version 1.0.0\n\n" <<
                "A disk usage utility inspired by the UNIX du command.\n\n" <<
                "Usage: du[-skhb][--help][--version][--block - size = dddd][folder] *\n\n" <<
                "Examples :\n" <<
                "  du\n" <<
                "    > display the sum of the cluster sizes of each directory\n" <<
                "      starting the cwd\n\n" <<
                "  du folder\n" <<
                "    > display the sum of the cluster sizes of each directory\n" <<
                "      starting with 'folder'\n\n" <<
                "  du -h\n" <<
                "    > display the results in a human readable form\n\n" <<
                "  du -s\n" <<
                "    > display only the final summary\n\n" <<
                "  du -b\n" <<
                "    > display in bytes\n\n" <<
                "  du -k\n" <<
                "    > cluster size is 1024\n\n" <<
                "  du -z\n" <<
                "    > display the list sorted by size\n\n" <<
                "  du -n\n" <<
                "    > display the list sorted by name\n\n" <<
                "  du -r\n" <<
                "    > display the list in reverse order\n\n" <<
                "  du --block - size = dddd\n" <<
                "    > set the cluster size to the specified integer > 0\n\n" <<
                "  du --help\n" <<
                "    > displays the help\n\n" <<
                "  du --version\n" <<
                "    > displays version number in the format d.d.d\n\n";
        return EXIT_SUCCESS;
	}
    if (options.version)
    {
        cout << "Version 1.0.0" << endl;
        return EXIT_SUCCESS;
    }
    if (options.unknownSwitch)
    {
        cout << "Error: unknown switches: <" << options.unknownChar << ">" << endl;
        return EXIT_FAILURE;
    }
    if (options.isDuplicate)
    {
        cout << "Error: duplicate switches" << endl;
        return EXIT_FAILURE;
    }
    if (options.invalidBlockSize)
    {
        cout << "Error: block-size value is invalid <" << options.invalidChar << ">" << endl;
        return EXIT_FAILURE;
    }
    if (options.badSwitch)
    {
        cout << "Error: bad switch" << endl;
        return EXIT_FAILURE;
    }
    if (options.tooSmallSize)
    {
        cout << "Error: user defined cluster size is too small" << endl;
        return EXIT_FAILURE;
    }
    if (options.bytes && options.humanReadable)
    {
        cout << "Error: cannot use both -b and -h";
        return EXIT_FAILURE;
    }
    if (options.kSwitch && options.blockSwitch)
    {
        cout << "Error: -k and --block-size are incompatible.";
        return EXIT_FAILURE;
    }
    if (options.sortBySize && options.sortByName)
    {
        cout << "Error: -n and -z switches are incompatible.";
        return EXIT_FAILURE;
    }


	//Populate ScanDate vector based on the switches
    vector<ScanData> data;
	collectData(options, data);

	//Prints the disk usage
	report(options, data);
}