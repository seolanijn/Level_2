/*!	\file	bytecount.c
	\author	Seolan Jin
	\date	2020-05-28

	MSVC: /std:c17

	This program will prompt the user to enter a number followed by a unit type
	and print out the number of bytes represented, followed by a table of the equivalent multi-byte units.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>	
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>

#define MAX_IDX 50

int main()
{
   #if defined(_DEBUG) && defined(_WIN32)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;		// frequent validity checks of memory
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;		// only use new allocation (don't recycle memory)
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;			// check for leaks at process termination
	_CrtSetDbgFlag(dbgFlags);
#endif
	printf("Enter # units: ");

	double userNum = -1;
	char userWord[MAX_IDX];


	// ------- get user's numeric input and validate
	if (scanf("%lf", &userNum) != 1) {
		printf("Error: you did not enter a recognizable number.");
		exit(EXIT_FAILURE);
	}
	if (userNum < 0) {
		printf("Error: the input value must be a non-negative value.");
		exit(EXIT_FAILURE);
	}
	// ------------
	
	// ---------- prompt the user input until the user input something except for '\n'
	bool isInput = 0;
	do {
		fgets(userWord, 50, stdin); // get user's word
		if (userWord[0] != '\n')
			isInput = 1;
	} while (!isInput);
	// ----------

	// ---------- eliminate extra space
	char fUserWord[100];

	// for userWord 
	int lenU = strlen(userWord); // lenU = length of UserWord
	int spaceH;
	for (int spaceI = 0; spaceI < lenU; spaceI++) {
		if (userWord[0] == ' ') {
			for (spaceI = 0; spaceI < (lenU - 1); spaceI++)
				userWord[spaceI] = userWord[spaceI + 1];
			lenU--;
			userWord[spaceI] = 0;
			spaceI = -1;
			continue;
		}
		if (((userWord[spaceI] == ' ') && (userWord[spaceI + 1] == ' ')) || (userWord[spaceI] == '\n') || (userWord[spaceI] == '\t')) {
			for (spaceH = spaceI; spaceH < (lenU - 1); spaceH++)
				userWord[spaceH] = userWord[spaceH + 1];
			userWord[spaceH] = 0;
			spaceI--;
			lenU--;
		}
		if (userWord[lenU - 1] == ' ') {
			userWord[lenU - 1] = 0;
		}
	}
	// --------------



	// for fUserWord to make the words be insensitive
	strcpy(fUserWord, userWord);
	int len = strlen(fUserWord);
	int spaceK;
	for (int spaceI = 0; spaceI < len; spaceI++) {
		if (fUserWord[0] == ' ') {
			for (spaceI = 0; spaceI < (len - 1); spaceI++)
				fUserWord[spaceI] = fUserWord[spaceI + 1];
			len--;
			fUserWord[spaceI] = 0;
			spaceI = -1;
			continue;
		}
		if (((fUserWord[spaceI] == ' ') && (fUserWord[spaceI + 1] == ' ')) || (fUserWord[spaceI] == '\t')) {
			for (spaceK = spaceI; spaceK < (len - 1); spaceK++)
				fUserWord[spaceK] = fUserWord[spaceK + 1];
			fUserWord[spaceK] = 0;
			spaceI--;
			len--;
		}
		if (fUserWord[len - 1] == ' ') {
			fUserWord[len - 1] = 0;
		}
	}
	// -------------

	// ---------- make input(fUserWord) be case insensitive
	for (int i = 0; fUserWord[i] != '\0'; i++) {
		if (fUserWord[i] >= 'a' && fUserWord[i] <= 'z') {
			fUserWord[i] = fUserWord[i] - 32;
		}
	}
	// ----------
	

	
	// ---------- convert the data to byte unit
	long double b = 0.0;
	long double kb, mb, kib, mib;
    double gb, tb, pb, eb, gib, tib, pib, eib;


	if ((strcmp(fUserWord, "B") == 0) || (strcmp(fUserWord, "BS") == 0)) {
		b = userNum;
		printf("\"%.3lf %s\"", userNum, "B");
	}
	else if ((strcmp(fUserWord, "KB") == 0) || (strcmp(fUserWord, "KBS") == 0)) {
		b = userNum * 1000;
		printf("\"%.3lf %s\"", userNum, "KB");
	}
	else if ((strcmp(fUserWord, "MB") == 0) || (strcmp(fUserWord, "MBS") == 0)) {
		b = userNum * 1000 * 1000;
		printf("\"%.3lf %s\"", userNum, "MB");
	}
	else if ((strcmp(fUserWord, "GB") == 0) || (strcmp(fUserWord, "GBS") == 0)) {
		b = userNum * 1000 * 1000 * 1000;
		printf("\"%.3lf %s\"", userNum, "GB");
	}
	else if ((strcmp(fUserWord, "TB") == 0) || (strcmp(fUserWord, "TBS") == 0)) {
		b = userNum * 1000 * 1000 * 1000 * 1000;
		printf("\"%.3lf %s\"", userNum, "TB");
	}
	else if ((strcmp(fUserWord, "PB") == 0) || (strcmp(fUserWord, "PBS") == 0)) {
		b = userNum * 1000 * 1000 * 1000 * 1000 * 1000;
		printf("\"%.3lf %s\"", userNum, "PB");
	}
	else if ((strcmp(fUserWord, "EB") == 0) || (strcmp(fUserWord, "EBS") == 0)) {
		b = userNum * 1000 * 1000 * 1000 * 1000 * 1000 * 1000;
		printf("\"%.3lf %s\"", userNum, "EB");
	}
	else if ((strcmp(fUserWord, "KIB") == 0) || (strcmp(fUserWord, "KIBS") == 0)) {
		b = userNum * 1024;
		printf("\"%.3lf %s\"", userNum, "KiB");
	}
	else if ((strcmp(fUserWord, "MIB") == 0) || (strcmp(fUserWord, "MIBS") == 0)) {
		b = userNum * 1024 * 1024;
		printf("\"%.3lf %s\"", userNum, "MiB");
	}
	else if ((strcmp(fUserWord, "GIB") == 0) || (strcmp(fUserWord, "GIBS") == 0)) {
		b = userNum * 1024 * 1024 * 1024;
		printf("\"%.3lf %s\"", userNum, "GiB");
	}
	else if ((strcmp(fUserWord, "TIB") == 0) || (strcmp(fUserWord, "TIBS") == 0)) {
		b = userNum * 1024 * 1024 * 1024 * 1024;
		printf("\"%.3lf %s\"", userNum, "TiB");
	}
	else if ((strcmp(fUserWord, "PIB") == 0) || (strcmp(fUserWord, "PIBS") == 0)) {
		b = userNum * 1024 * 1024 * 1024 * 1024 * 1024;
		printf("\"%.3lf %s\"", userNum, "PiB");
	}
	else if ((strcmp(fUserWord, "EIB") == 0) || (strcmp(fUserWord, "EIBS") == 0)) {
		b = userNum * 1024 * 1024 * 1024 * 1024 * 1024 * 1024;
		printf("\"%.3lf %s\"", userNum, "EiB");
	}
	else if ((strcmp(fUserWord, "CHAR") == 0) || (strcmp(fUserWord, "CHARS") == 0)) {
		b = userNum;
		printf("\"%.3lf %s\"", userNum, "char");
	}
	else if ((strcmp(fUserWord, "UNSIGNED CHAR") == 0) || (strcmp(fUserWord, "UNSIGNED CHARS") == 0)) {
		b = userNum;
		printf("\"%.3lf %s\"", userNum, "unsigned char");
	}
	else if ((strcmp(fUserWord, "SHORT") == 0) || (strcmp(fUserWord, "SHORTS") == 0)) {
		b = userNum * 2;
		printf("\"%.3lf %s\"", userNum, "short");
	}
	else if ((strcmp(fUserWord, "UNSIGNED SHORT") == 0) || (strcmp(fUserWord, "UNSIGNED SHORTS") == 0)) {
		b = userNum * 2;
		printf("\"%.3lf %s\"", userNum, "unsigned short");
	}
	else if ((strcmp(fUserWord, "INT") == 0) || (strcmp(fUserWord, "INTS") == 0)) {
		b = userNum * 4;
		printf("\"%.3lf %s\"", userNum, "int");
	}
	else if ((strcmp(fUserWord, "UNSIGNED INT") == 0) || (strcmp(fUserWord, "UNSIGNED INTS") == 0)) {
		b = userNum * 4;
		printf("\"%.3lf %s\"", userNum, "unsigned int");
	}
	else if ((strcmp(fUserWord, "LONG") == 0) || (strcmp(fUserWord, "LONGS") == 0)) {
		b = userNum * 4;
		printf("\"%.3lf %s\"", userNum, "long");
	}
	else if ((strcmp(fUserWord, "UNSIGNED LONG") == 0) || (strcmp(fUserWord, "UNSIGNED LONGS") == 0)) {
		b = userNum * 4;
		printf("\"%.3lf %s\"", userNum, "unsigned long");
	}
	else if ((strcmp(fUserWord, "LONG LONG") == 0) || (strcmp(fUserWord, "LONG LONGS") == 0)) {
		b = userNum * 8;
		printf("\"%.3lf %s\"", userNum, "long long");
	}
	else if ((strcmp(fUserWord, "UNSIGNED LONG LONG") == 0) || (strcmp(fUserWord, "UNSIGNED LONG LONGS") == 0)) {
		b = userNum * 8;
		printf("\"%.3lf %s\"", userNum, "unsigned long long");
	}
	else if ((strcmp(fUserWord, "FLOAT") == 0) || (strcmp(fUserWord, "FLOATS") == 0)) {
		b = userNum * 4;
		printf("\"%.3lf %s\"", userNum, "float");
	}
	else if ((strcmp(fUserWord, "DOUBLE") == 0) || (strcmp(fUserWord, "DOUBLES") == 0)) {
		b = userNum * 8;
		printf("\"%.3lf %s\"", userNum, "double");
	}
	else { // in this case, print out userWord not fUserWord
		printf("Error: the unit type '%s' is not recognized.", userWord);
		exit(EXIT_FAILURE);
	}
	// ------------

	b = ceil(b);// round up the byte value

	// ----------calculate unit
	kb = b / 1000;
	mb = b / 1000 / 1000;
	gb = b / 1000 / 1000 / 1000;
	tb = b / 1000 / 1000 / 1000 / 1000;
	pb = b / 1000 / 1000 / 1000 / 1000 / 1000;
	eb = b / 1000 / 1000 / 1000 / 1000 / 1000 / 1000;

	kib = b / 1024;
	mib = b / 1024 / 1024;
	gib = b / 1024 / 1024 / 1024;
	tib = b / 1024 / 1024 / 1024 / 1024;
	pib = b / 1024 / 1024 / 1024 / 1024 / 1024;
	eib = b / 1024 / 1024 / 1024 / 1024 / 1024 / 1024;
	// -------------

	// -----------print out the results
	char chKb[100], chKib[100];

	sprintf(chKb, " %.3Lf", kb); // use the longest number to generate char[]  (KB)
	sprintf(chKib, "    %.3Lf", kib); // use the longest number to generate char[]  (KiB)

	int kbLen = strlen(chKb); // initialize the length of char[]  (KB)
	int kibLen = strlen(chKib); // initialize the length of char[]  (KiB)


	printf(" is %.0Lf bytes.\n\n", b);

	printf("%*s      %*s\n", kbLen, "Metric", kibLen, "IEC");
	printf("%*s      %*s\n", kbLen, "======", kibLen, "===");

	printf("%*.3Lf KB   %*.3Lf KiB\n", kbLen, kb, kibLen, kib);
	printf("%*.3Lf MB   %*.3Lf MiB\n", kbLen, mb, kibLen, mib);
	printf("%*.3lf GB   %*.3lf GiB\n", kbLen, gb, kibLen, gib);
	printf("%*.3lf TB   %*.3lf TiB\n", kbLen, tb, kibLen, tib);
	printf("%*.3lf PB   %*.3lf PiB\n", kbLen, pb, kibLen, pib);
	printf("%*.3lf EB   %*.3lf EiB\n", kbLen, eb, kibLen, eib);
	// -----------

	exit(EXIT_SUCCESS);
	
}
