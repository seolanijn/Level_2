/*!	\file	stats2021s.c
	\author	Seolan Jin
	\date	2020-06-28

	MSVC: /std:c17

	This program will prompt the user to enter numbers to create statistics and print out the results
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define A_TO_J 10

//declare variables to use for creating frequency table and histogram
int countVal[A_TO_J];
double percentVal[A_TO_J];

//compute minimum value
double cmptMinimum(double* numbers, size_t sizeArr) {
	double min = numbers[0];
	for (size_t i = 0; i < sizeArr; i++) {
		if (numbers[i] < min)// if the number is smaller than min, change the min to the number
			min = numbers[i];
	}
	return min;
}
//compute maximum value for type of double
double cmptMaximum(double* numbers, size_t sizeArr) {
	double max = numbers[0];
	for (size_t i = 0; i < sizeArr; i++) {
		if (numbers[i] > max)// if the number is greater than min, change the max to the number
			max = numbers[i];
	}
	return max;
}
//compute maximum value for type of int
int cmptMaximumInt(int* numbers, size_t sizeArr) {
	int max = numbers[0];
	for (size_t i = 0; i < sizeArr; i++) {
		if (numbers[i] > max)// if the number is greater than min, change the max to the number
			max = numbers[i];
	}
	return max;
}
//compute mean value 
double cmptMean(double* numbers, size_t sizeArr) {
	double sum = 0;
	for (size_t i = 0; i < sizeArr; i++) {
		sum += numbers[i];//add the numbers to sum
	}
	return sum / sizeArr; // devide by the number of numbers
}
//compute median
double cmptMedian(double* numbers, size_t sizeArr) {
	int n = sizeArr - 1;
	if (sizeArr % 2 == 0)
		return (numbers[n / 2] + numbers[(n + 1) / 2]) / 2;
	else
		return numbers[(n + 1) / 2];
}
//compute variance
double cmptVariance(double* numbers, size_t sizeArr, double mean) {
	double sum = 0;
	for (size_t i = 0; i < sizeArr; i++) {
		sum += pow(numbers[i] - mean, 2.0);
	}

	return sum / sizeArr;
}
//create merge function
void merge(double a[], int l, int middle, int r) {
	size_t arrSize = r + 1; // r stands for right
	double* sorted = (double*)calloc(arrSize, sizeof(double));

	int i = l;//l stands for left
	int j = middle + 1;
	int k = l;

	while (i <= middle && j <= r) {
		if (sorted != NULL) { // avoid dereferencing the pointer warning
			if (a[i] <= a[j]) {
				sorted[k] = a[i];
				i++;
			}
			else {
				sorted[k] = a[j];
				j++;
			}
			k++;
		}
	}
	//if i is greater than middle, generate the rest of values using j
	if (i > middle) {
		for (int t = j; t <= r; t++) {
			if (sorted != NULL) {// avoid dereferencing the pointer warning
				sorted[k] = a[t];
				k++;
			}
		}
	}
	//if not, generate the rest of values using i
	else {
		for (int t = i; t <= middle; t++) {
			if (sorted != NULL) {// avoid dereferencing the pointer warning
				sorted[k] = a[t];
				k++;
			}
		}
	}
	for (int t = l; t <= r; t++) {
		if (sorted != NULL)// avoid dereferencing the pointer warning
			a[t] = sorted[t];
	}
	free(sorted);
}
//sort the numbers using merge function
void mergeSort(double a[], int l, int r) {
	if (l < r) {
		int middle = (l + r) / 2;
		mergeSort(a, l, middle);
		mergeSort(a, middle + 1, r);
		merge(a, l, middle, r);
	}
}
//compute length for formatting outputs
int cmptLength(double val, int decimal) {
	char temp[100];
	sprintf(temp, "%.*lf", decimal, val);
	return strlen(temp);
}
//compute length for formatting outputs (accepts type of int)
int cmptLengthInt(int val) {
	char temp[100];
	sprintf(temp, "%d", val);
	return strlen(temp);
}
//a function that creates frequency table
void cmptFrequency(double* numbers, size_t sizeArr, double min, double max) {
	double range = max - min;
	double addVal = range / A_TO_J;
	char alphaVal = 'A';
	double beg = min;

	//initialize countVal to zero to use this function one more later(log)
	for (int i = 0; i < A_TO_J; i++)
		countVal[i] = 0;

	for (int i = 0; i < A_TO_J; beg += addVal, i++) {
		double end = beg + addVal;
		for (size_t j = 0; j < sizeArr; j++) {
			// if alphaVal is J, inclusive. if not, exclusive
			if ((alphaVal != 'J' && numbers[j] >= beg && numbers[j] < end) || (alphaVal == 'J' && numbers[j] >= beg && numbers[j] <= max))
				countVal[i]++;
		}
		alphaVal++;
	}
	//generate percentVal to use for printfing percentage
	for (int i = 0; i < A_TO_J; i++) {
		percentVal[i] = (double)countVal[i] * 100 / (double)sizeArr;
	}

	beg = min;
	alphaVal = 'A';
	double longestVal = max - addVal;
	int lengthBeg = cmptLength(longestVal, 1) + 1;
	int lengthEnd = cmptLength(max, 1);
	int lengthInt = cmptLengthInt(cmptMaximumInt(countVal, A_TO_J));
	//print out the frequency table
	for (int i = 0; i < A_TO_J; beg += addVal, i++) {
		if (alphaVal == 'J')
			printf("%c [%*.1lf .. %*.1lf] = %*d : %5.2lf%%\n", alphaVal, lengthBeg, beg, lengthEnd, beg + addVal, lengthInt, countVal[i], percentVal[i]);
		else
			printf("%c [%*.1lf .. %*.1lf) = %*d : %5.2lf%%\n", alphaVal, lengthBeg, beg, lengthEnd, beg + addVal, lengthInt, countVal[i], percentVal[i]);

		alphaVal++;
	}
}
//a function creating a histogram
void cmptHistogram() {
	//makes the maximum value of percentVal looks clear so that we can use the value to make a histogram;
	int percentMax = (int)ceil(cmptMaximum(percentVal, A_TO_J));
	while (!((percentMax % 5 == 0) || (percentMax % 10 == 0)))
		percentMax++;
	//generate histogramPrcnt
	double histogramPrcnt[11];
	histogramPrcnt[0] = 0;
	for (int i = 1; i < 11; i++) {
		histogramPrcnt[i] = ((double)percentMax / A_TO_J) * i;
	}
	//print 
	printf("Grp     %% 0");
	for (int i = 1; i < 11; i++) {
		printf("%6.1lf", histogramPrcnt[i]);
	}
	printf("\n--------- +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	char alphaVal = 'A';
	// generate unitVal for creating a graph bar
	double unitVal[60];
	for (int i = 0; i < 60; i++) {
		unitVal[i] = ((double)percentMax / 60) * ((double)i + 1);
	}
	//print
	for (int i = 0; i < A_TO_J; i++) {
		printf(" %c %5.2lf%% |", alphaVal, percentVal[i]);
		for (int j = 0; j < 60; j++) {
			if (percentVal[i] >= unitVal[j])
				printf("*");
		}
		printf("\n");
		alphaVal++;
	}
	printf("--------- +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
}

int main(int argc, char* argv[]) {

	char ch[20] = "";
	int chInt;
	double sum = 0;

	FILE* userFile;

	size_t sizeValNum = 1000;
	// allocate memory
	double* valNum = (double*)calloc(sizeValNum, sizeof(double));
	size_t numInput = 0;
	// if argc is 1, prompt the user to input from keyboard
	if (argc == 1) {
		userFile = stdin;
		printf("Enter a list of whitespace-separated real numbers terminated by EOF or 'end'.\n\n");
		for (int i = 0;; i++) {
			//if the numbers are same as the allocated array size, reallocate the memory
			if (i == sizeValNum) {
				double* newValNum = (double*)realloc(valNum, 2 * sizeValNum * sizeof(double));
				if (newValNum == NULL) {
					free(newValNum);
					printf("\nfail to expand the data capacity. try again\n\n");
				}
				//initialize valNum again
				valNum = newValNum;
				//double the sizeValNum
				sizeValNum *= 2;
			}
			// if user input invalid data, consider the input is for finishing input
			if (scanf("%lf", valNum + i) != 1) {
				// check EOF
				if ((chInt = getchar()) == EOF) {
					break;
				}
				// is not check 'end'
				else if (chInt == 'e') {
					(void)scanf("%s", ch);
					// if the input was 'end', break the loop
					if (strcmp(ch, "nd") == 0) {
						if (i == 0) {
							printf("empty data set!\nquitting...\n\n");
							return EXIT_FAILURE;
						}
						break;
					}
					else {
						i--;// if user entered bad inputs, skip the input
					}
				}
				else {
					i--;// if user entered bad inputs, skip the input
				}
			}
			else
				numInput++;// for calculating the number of elements
		}
		fclose(userFile);
	}
	// if argc is same as 2, consider the user entered filename
	else if (argc == 2) {
		userFile = fopen(argv[1], "r");
		// if userFile is null, exit the program
		if (userFile == NULL) {
			printf("Error <%s>  : No such file or directory", argv[1]);
			return EXIT_FAILURE;
		}
		for (int i = 0;; i++) {
			//reallocate the memory
			if (i == sizeValNum) {
				double* newValNum = (double*)realloc(valNum, 2 * sizeValNum * sizeof(double));
				if (newValNum == NULL) {
					free(newValNum);
					printf("fail to expand the data capacity. try again");
					return EXIT_FAILURE;
				}
				valNum = newValNum;
				sizeValNum *= 2;
			}
			if (fscanf(userFile, "%lf", valNum + i) != 1) {
				if ((chInt = fgetc(userFile)) == EOF) {
					if (i == 0) { // if first value is EOF, exit the program
						printf("empty data set!\nquitting...\n\n");
						return EXIT_FAILURE;
					}
					break;
				}
				else if (chInt == 'e') {
					(void)fscanf(userFile, "%s", ch);
					if (strcmp(ch, "nd") == 0) {
						break;
					}
					else {
						i--;// if user entered bad inputs, skip the input
					}
				}
				else {
					i--;// if user entered bad inputs, skip the input
				}
			}
			else
				numInput++;
		}
		fclose(userFile);
	}
	else {
		printf("Error: invalid command line.\nUsage: stats2021 [filename]");
		return EXIT_FAILURE;
	}

	mergeSort(valNum, 0, numInput - 1);
	double min = cmptMinimum(valNum, numInput);
	double max = cmptMaximum(valNum, numInput);
	double mean = cmptMean(valNum, numInput);
	double median = cmptMedian(valNum, numInput);
	double variance = cmptVariance(valNum, numInput, mean);

	// print first result
	printf("\n\n===============================================================================\n");
	printf("# elements%30zu\n", numInput);
	printf("minimum   %30.3lf\n", min);
	printf("maximum   %30.3lf\n", max);
	printf("range     %30.3lf\n", max - min);
	printf("mean      %30.3lf\n", mean);
	printf("median    %30.3lf\n", median);
	printf("variance  %30.3lf\n", variance);
	printf("std.dev.  %30.3lf\n", sqrt(variance));

	// if data range is zero, exit the proram
	if ((max - min) == 0) {
		printf("\nData range is zero!  Frequency/Histogram/Boxplot skipped.\n");
		return EXIT_SUCCESS;
	}

	// print the frequency table
	printf("===============================================================================\n");
	printf("Frequency Table\n\n");
	cmptFrequency(valNum, numInput, min, max);
	//print the histogram
	printf("===============================================================================\n");
	printf("Histogram\n\n");
	cmptHistogram();

	//copy the original array to an array that will store log values
	double* valLog = (double*)calloc(numInput, sizeof(double));
	//generate valLog using valNum
	for (size_t i = 0; i < numInput; i++) {
		valLog[i] = log(valNum[i]);
	}

	double minLog = cmptMinimum(valLog, numInput);
	double maxLog = cmptMaximum(valLog, numInput);

	//print the frequency table for log value
	printf("===============================================================================\n");
	printf("Log Frequency Table\n\n");
	cmptFrequency(valLog, numInput, minLog, maxLog);
	//print the histogram for log value
	printf("===============================================================================\n");
	printf("Log Histogram\n\n");
	cmptHistogram();

	free(valNum);
	free(valLog);

	return EXIT_SUCCESS;

}