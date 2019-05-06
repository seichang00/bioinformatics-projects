#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <unordered_map>

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
using namespace std;

unordered_map<char, int> FirstOccurence(string first_col);


struct rotation
{
	int index;
	char *suffix;
};


int cmpfunc(const void *x, const void *y)
{
	struct rotation *rx = (struct rotation *)x;
	struct rotation *ry = (struct rotation *)y;
	return strcmp(rx->suffix, ry->suffix);
}


int *computeSuffixArray(char *input_text, int len_text)
{
	struct rotation suff_arr[len_text];

	for (int i = 0; i < len_text; i++)
	{
		suff_arr[i].index = i;
		suff_arr[i].suffix = (input_text + i);
	}
	qsort(suff_arr, len_text, sizeof(struct rotation), cmpfunc);

	// Stores the indexes 
	int* suffix_arr = new int[len_text];
	for (int i = 0; i < len_text; i++)
		suffix_arr[i] = suff_arr[i].index;

	// Returns suffix array 
	return suffix_arr;
}

char *findLastChar(char *input_text, int *suffix_arr, int n)
{
	char *bwt = new char[n];
	int i;
	for (i = 0; i < n; i++)
	{
		int j = suffix_arr[i] - 1;
		if (j < 0)
			j = j + n;

		bwt[i] = input_text[j];
	}
	bwt[i] = '\0';
	return bwt;
}


int betterBWMatching(string last_col, int* suffix_arr, string pattern){
    int top = 0;
    int bottom = last_col.size() - 1;
    
	string first_col = last_col;
	
	sort(first_col.begin(), first_col.end());
	unordered_map<char, int> first_occ = FirstOccurence(first_col);

	while (top <= bottom) {
		if (pattern.size() > 0) {
			char symbol = pattern[pattern.size() - 1];
			pattern = pattern.substr(0, pattern.size() - 1);
			string curr_last_col = last_col.substr(top, bottom + 1);
			bool isinLastCol = false;
			for (int i = 0; i < curr_last_col.size(); i++) {
				if (curr_last_col[i] == symbol) {
					isinLastCol = true;
					break;
				}
			}
			if (isinLastCol) {
				string lctemp = last_col.substr(0, top);
				top = first_occ[symbol] + count(lctemp.begin(), lctemp.end(), symbol);
				lctemp = last_col.substr(0, bottom + 1);
				bottom = first_occ[symbol] + count(lctemp.begin(), lctemp.end(), symbol) - 1;
			}
			else 
				return 0;
		}
		else 
			return (bottom - top) + 1;
	}
}

unordered_map<char, int> FirstOccurence(string first_col) {
	unordered_map<char, int> first_occ;
	first_occ[first_col[0]] = 0;
	for (int i = 1; i < first_col.size(); i++) {
		if (first_occ.count(first_col[i]) == 0) {
			first_occ[first_col[i]] = i;
		}
	}
	return first_occ;
}

int main()
{
	/*
	//BWTest
	char input_text[] = "banana$";
	int len_text = strlen(input_text);

	int *suffix_arr = computeSuffixArray(input_text, len_text);
	char *bwt_arr = findLastChar(input_text, suffix_arr, len_text);

	cout << "Input: " << input_text << "\n";
	cout << "Burrows - Wheeler: " << bwt_arr << "\n";*/
	/*
	//FIRST OCCURENCE TEST
	string test = "$aaaaaabmnnnps";
	unordered_map<char, int> result;
	result = FirstOccurence(test);
	unordered_map<char, int>::iterator it;
	for (it = result.begin(); it != result.end(); it++) {
		cout << "first: " << (*it).first << "        second: " << (*it).second << endl;
	}*/

	//IMPLEMENT BETTERBWMATCHING
	string str = "TCCTCTATGAGATCCTATTCTATGAAACCTTCA$GACCAAAATTCTCCGGC";
	string pattern = "CAC";

	char input_text[] = "banana$";
	int len_text = strlen(input_text);

	int *suffix_arr = computeSuffixArray(input_text, len_text);
	char *bwt_arr = findLastChar(input_text, suffix_arr, len_text);


	cout << betterBWMatching(str, pattern) << endl;
}