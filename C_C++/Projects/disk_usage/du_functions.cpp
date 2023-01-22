/*
author:     Seolan Jin
Date:       Aug. 9, 2021
Purpose:    it has function definitions which are declared in a header file

\file:      du_functions.cpp
\version:   1.0.0
*/

#include <iostream>
#include <filesystem>
#include<locale>
#include<fstream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "du_functions.hpp"

using namespace std;
using namespace std::filesystem;


Options parseInput(int argc, char* argv[])
{
	Options o;
	vector<string> v(&argv[1], &argv[argc]);

	if (v.empty())
	{
		//default behaviour
		return o;
	}
	

	//get letter switches
	string switches;

	//find --help word switch and return
	vector<string>::iterator itArgs = find(v.begin(), v.end(), "--help");
	if (itArgs != v.end())
	{
		o.help = true;
		return o;
	}

	//find --version word switch and return
	itArgs = find(v.begin(), v.end(), "--version");
	if (itArgs != v.end())
	{
		o.version = true;
		return o;
	}

	//find --block-size
	string blockS;
	string findString = "--block-size=";
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i].at(0) == '-' && v[i].at(1) == '-')
		{
			blockS = v[i];
			//find bad switch and return
			if (blockS.find(findString) == string::npos)
			{
				o.badSwitch = true;
				return o;
			}
			else
			{
				blockS.erase(blockS.find(findString), blockS.find(findString) + findString.size());
				//find bad switch and return
				if (blockS.size() == 0)
				{
					o.badSwitch = true;
					return o;
				}
				v.erase(v.begin()+i);
				break;
			}
		}
	}
	//if there is a value
	if (blockS != "")
	{
		//store invalid char just in case
		o.invalidChar = blockS;

		stringstream str(blockS);
		unsigned long cluster = 0;

		//if errors occur, return
		if (!(str >> cluster))
		{
			o.invalidBlockSize = true;
			return o;
		}

		size_t currentLen = blockS.size();

		//determine tooSmallSize switch
		if (cluster == 0)
		{
			o.tooSmallSize = true;
			return o;
		}
		//determine invalidBlockSize switch
		if (currentLen != to_string(cluster).length())
		{
			o.invalidBlockSize = true;
			return o;
		}
		o.clusterSize = cluster;
		o.blockSwitch = true;
	}

	//if vector is not empty and the first character is '-'
	if (!v.empty() && v.front().at(0) == '-')
	{
		switches = v.front();
		v.erase(v.begin());
		//erase '-'
		switches.erase(switches.begin());

		//check duplicate switch
		if (checkDuplicate(switches) == 0)
		{
			o.isDuplicate = true;
			return o;
		}

			//find 'b' switch
			string::iterator findSwitch = find(switches.begin(), switches.end(), 'b');
			if (findSwitch != switches.end())
			{
				o.bytes = true;
				switches.erase(findSwitch);
			}
			//find 's' switch
			findSwitch = find(switches.begin(), switches.end(), 's');
			if (findSwitch != switches.end())
			{
				o.summary = true;
				switches.erase(findSwitch);
			}
			//find 'k' switch
			findSwitch = find(switches.begin(), switches.end(), 'k');
			if (findSwitch != switches.end())
			{
				o.clusterSize = 1024;
				o.kSwitch = true;
				switches.erase(findSwitch);
			}
			//find 'h' switch
			findSwitch = find(switches.begin(), switches.end(), 'h');
			if (findSwitch != switches.end())
			{
				o.humanReadable = true;
				switches.erase(findSwitch);
			}
			//find 'z' switch
			findSwitch = find(switches.begin(), switches.end(), 'z');
			if (findSwitch != switches.end())
			{
				o.sortBySize = true;
				switches.erase(findSwitch);
			}
			//find 'n' switch
			findSwitch = find(switches.begin(), switches.end(), 'n');
			if (findSwitch != switches.end())
			{
				o.sortByName = true;
				switches.erase(findSwitch);
			}
			//find 'r' switch
			findSwitch = find(switches.begin(), switches.end(), 'r');
			if (findSwitch != switches.end())
			{
				o.reverse = true;
				switches.erase(findSwitch);
			}

			//switch is not empty, true unknown switch and return
			if (switches.size() > 0)
			{
				o.unknownSwitch = true;
				o.unknownChar = switches;
				return o;
			}
	}

	//initialize folder name
	if (v.size() > 0)
		o.folder = v.front();


	return o;
}

int checkDuplicate(string switches)
{
	size_t len;

	//check 's' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 's'), switches.end());
	if (switches.size() + 1 < len)
		return 0;
	//check 'k' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 'k'), switches.end());
	if (switches.size() + 1 < len)
		return 0;
	//check 'h' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 'h'), switches.end());
	if (switches.size() + 1 < len)
		return 0;
	//check 'z' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 'z'), switches.end());
	if (switches.size() + 1 < len)
		return 0;
	//check 'n' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 'n'), switches.end());
	if (switches.size() + 1 < len)
		return 0;
	//check 'r' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 'r'), switches.end());
	if (switches.size() + 1 < len)
		return 0;
	//check 'b' switch duplicate
	len = switches.size();
	switches.erase(remove(switches.begin(), switches.end(), 'b'), switches.end());
	if (switches.size() + 1 < len)
		return 0;

	return 1;
}


void collectData(Options const& o, vector<ScanData>& v)
{
	directory_iterator dir(o.folder);
	directory_iterator end;


	unsigned long long clusterS = 0;
	unsigned long long totalClusterS = 0;
	unsigned long long sizeC = 0;
	ScanData sd;

	unsigned byte = 1024;

	while (dir != end)
	{
		//if it is directory, use collectDataInside function
		if (is_directory(dir->status()))
		{
			clusterS = collectDataInside(dir->path(), o);
			if (o.bytes)
				clusterS *= o.clusterSize;

			//add size to total
			totalClusterS += clusterS;

			//populate vector
			sd = { dir->path().filename().string() , clusterS, "" };
			v.push_back(sd);
		}
		else if (is_regular_file(dir->status()))
		{
			sizeC = (unsigned)ceil(dir->file_size() / (double)byte);
			sizeC = (unsigned)ceil(sizeC * (double)byte / (double)o.clusterSize);
			clusterS = sizeC;
			if (o.bytes)
				clusterS *= o.clusterSize;
			//add size to total
			totalClusterS += clusterS;
		}
		++dir;
	}

	//populate the summary value
	sd = { "" , totalClusterS, "" };
	v.push_back(sd);

	//sort or make the value humanreadable
	if (o.sortBySize)
		sort(v.begin(), v.end());
	else if (o.sortByName)
		sort(v.begin(), v.end(), byFolder);
	else if (o.humanReadable)
		makeHumanReadable(v, o);

}

unsigned long long collectDataInside(path folderName, Options const& o)
{
	recursive_directory_iterator dir(folderName);
	recursive_directory_iterator end;
	
	unsigned long long clusterS = 0;
	unsigned long long sizeC = 0;
	unsigned byte = 1024;

	while (dir != end)
	{
		sizeC = (unsigned)ceil(dir->file_size() / (double)byte);
		sizeC = (unsigned)ceil(sizeC * (double)byte / o.clusterSize);
		//add the size
		clusterS += sizeC;
		++dir;
	}

	return clusterS;
}

/*
* 
*/
void report(Options const& o, vector<ScanData> const& v)
{
	int maxLen = 0;
	int currLen;

	//if humanreadable switch is off,
	if (!o.humanReadable)
	{
		//determine the longest value
		for (ScanData x : v)
		{
			currLen = to_string(x.clusterSize).length();
			if (currLen > maxLen)
				maxLen = currLen;
		}

		//if summary switch is on,
		if (o.summary)
		{
			cout << left << setw(maxLen) << v.back().clusterSize;
			cout << "   " << o.folder.string() << v.back().folder << endl;
		}
		//if summary reverse is on,
		else if (o.reverse)
		{
			for (size_t i = v.size(); i > 0; --i)
			{
				cout << left << setw(maxLen) << v[i - 1].clusterSize;
				cout << "   " << o.folder.string() << (i - 1 == v.size() - 1 ? "" : "\\") << v[i - 1].folder << endl;
			}
		}
		else
		{
			for (size_t i = 0; i < v.size(); ++i)
			{
				cout << left << setw(maxLen) << v[i].clusterSize;
				cout << "   " << o.folder.string() << (i == v.size() - 1 ? "" : "\\") << v[i].folder << endl;
			}
		}
	}
	else
	{
		//determine the longest value
		for (ScanData x : v)
		{
			currLen = x.humanReadableData.length();
			if (currLen > maxLen)
				maxLen = currLen;
		}

		//print
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << left << setw(maxLen) << v[i].humanReadableData;
			cout << "   " << o.folder.string() << (i == v.size() - 1 ? "" : "\\") << v[i].folder << endl;
		}
	}
	
	
}

bool operator<(ScanData const& lhs, ScanData const& rhs)
{
	return lhs.clusterSize < rhs.clusterSize;
}
bool operator>(ScanData const& lhs, ScanData const& rhs)
{
	return lhs.clusterSize > rhs.clusterSize;
}
bool byFolder(ScanData const& lhs, ScanData const& rhs)
{
	return lhs.folder < rhs.folder;
}
void makeHumanReadable(vector<ScanData>& v, Options const& o)
{
	size_t i = 1;
	long double clusterS;
	unsigned byte = 1024;
	for (size_t j = 0; j < v.size(); ++j)
	{
		//if the size 0, initialize as 0, too
		if (v[j].clusterSize == 0)
		{
			v[j].humanReadableData = "0";
			continue;
		}
		clusterS = static_cast<long double>(v[j].clusterSize * o.clusterSize);
		//divide by 1024 untill the value is greater than 1
		while (clusterS / byte > 1)
		{
			clusterS /= byte;
			++i;
		}
		long long integral = static_cast<int>(clusterS);
		long double decimal = clusterS - integral;
		
		unsigned long rounded = (unsigned long)round(clusterS);

		//if it is less than 10, one decimal place
		if (rounded < 10)
		{
			//round(one decimal place)
			long double roundedDouble = round(clusterS * 10) / 10;
			string roundedStr = to_string(roundedDouble).substr(0, 3);
			if (i <= 2)
				v[j].humanReadableData = roundedStr + 'K';
			else if (i <= 3)
				v[j].humanReadableData = roundedStr + 'M';
			else if (i <= 4)
				v[j].humanReadableData = roundedStr + 'G';
			else if (i <= 5)
				v[j].humanReadableData = roundedStr + 'T';
		}
		else
		{
			if (i <= 2)
				v[j].humanReadableData = to_string(rounded) + 'K';
			else if (i <= 3)
				v[j].humanReadableData = to_string(rounded) + 'M';
			else if (i <= 4)
				v[j].humanReadableData = to_string(rounded) + 'G';
			else if (i <= 5)
				v[j].humanReadableData = to_string(rounded) + 'T';
		}
			
		//re-set i
		i = 1;
	}
}