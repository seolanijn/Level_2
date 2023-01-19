#pragma once

/*
author:     Seolan Jin
Date:       Aug. 9, 2021
Purpose:    it has function declarations which will be used to build du_main.cpp

\file:      du_functions.hpp
\version:   1.0.0
*/

#include <vector>
#include <filesystem>
#include <string>

using namespace std::filesystem;


/*
* struct:	Options
* brief:	store options given by user
*/
struct Options
{
	//switches
	bool bytes = false;
	bool humanReadable = false;
	bool summary = false;
	bool sortBySize = false;
	bool sortByName = false;
	bool reverse = false;
	bool blockSwitch = false;
	bool kSwitch = false;
	
	bool help = false;
	bool version = false;

	//cluster size
	unsigned long clusterSize = 4096;

	//error switches
	bool unknownSwitch = false;
	std::string unknownChar;
	bool isDuplicate = false;
	bool invalidBlockSize = false;
	std::string invalidChar;
	bool badSwitch = false;
	bool tooSmallSize = false;

	path folder = ".";
};

/*
* struct:	ScanData
* brief:	store data to print the usage
*/
struct ScanData
{
	std::string folder;
	unsigned long long clusterSize = 0;
	std::string humanReadableData;
};

/*
* fn:		Options parseInput(int argc, char* argv[]);
* brief:	it collects switches that user entered and folder name
* param:	int argc, char* argv[] will be used to populate vector
* return:	Options struct will store the switches user entered and folder name
*/
Options parseInput(int argc, char* argv[]);

/*
* fn:		int checkDuplicate(std::string switches);
* brief:	it checks the duplicate switches
* param:	string switches 
* return:	returns 0 if duplicate, 1 if not
*/
int checkDuplicate(std::string switches);

/*
* fn:		void collectData(Options const& o, std::vector<ScanData>& v);
* brief:	collects cluster size
* param:	Options read-only, vector<ScanData> will store the size and path name
* return:	void
*/
void collectData(Options const& o, std::vector<ScanData>& v);

/*
* fn:		unsigned long long collectDataInside(path folderName, Options const& o);
* brief:	it will be used in collectData function
* param:	folder path will be used with recursive_directory_iterator
* return:	size
*/
unsigned long long collectDataInside(path folderName, Options const& o);

/*
* fn:		void report(Options const& o, std::vector<ScanData> const& v);
* brief:	it prints out the disk usage
* param:	Options const& o, std::vector<ScanData> const& v
* return:	void
*/
void report(Options const& o, std::vector<ScanData> const& v);

/*
* fn:		bool operator<(ScanData const& lhs, ScanData const& rhs);
* brief:	it will determine the greater value
* param:	ScanData const& lhs, ScanData const& rhs
* return:	true if lhs < rhs, false if lhs > rhs
*/
bool operator<(ScanData const& lhs, ScanData const& rhs);

/*
* fn:		bool operator>(ScanData const& lhs, ScanData const& rhs);
* brief:	it will determine the greater value
* param:	ScanData const& lhs, ScanData const& rhs
* return:	true if lhs > rhs, false if lhs < rhs
*/
bool operator>(ScanData const& lhs, ScanData const& rhs);

/*
* fn:		bool byFolder(ScanData const& lhs, ScanData const& rhs);
* brief:	it will determine the greater value by folder name
* param:	ScanData const& lhs, ScanData const& rhs
* return:	true if lhs < rhs, false if lhs > rhs
*/
bool byFolder(ScanData const& lhs, ScanData const& rhs);

/*
* fn:		void makeHumanReadable(std::vector<ScanData>& v, Options const& o);
* brief:	it will populate the vector as humanreadable value
* param:	std::vector<ScanData>& v, Options const& o
* return:	void
*/
void makeHumanReadable(std::vector<ScanData>& v, Options const& o);