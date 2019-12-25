#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int radix = 256;	// Radix is 256 as the characters can be only representable by 8 bit values


//Follwoing is a modular Hash function
long ModularHash(string pattern, long key, long length) {
	long index = 0;
	for (int i = 0; i < length; i++) {
		index = (index * radix + pattern[i]) % key;
	}

	//cout << "Map val::: " << index << endl;
	return index;
}


int RobinKarpSubStringSearch(string text, string pattern, long key) {
	long patternLen = pattern.length();					//Pattern Length
	long textLen = text.length();						//text Length

	long patternKey = 0, textKey = 0;					//Map keys for pattern and text

	patternKey = ModularHash(pattern, key, patternLen);	//compute the pattern key
	textKey = ModularHash(text, key, patternLen);		//compute the text key for first portion of the string that has similar size of the pattern

	// compute the pre processing linear value R^M-1
	long R = 1;
	for (int i = 0; i < patternLen-1; i++) {
		R = (radix * R) % key;
	}

	bool MatchResult = false;

	for (int i = 0; i < textLen - patternLen; i++) {

		// check if the current sliding window and the pattern are matched or not
		if (textKey == patternKey) {

			for (int j = 0; j < patternLen; j++) {
				if (text[i + j] != pattern[j])
					break;

				MatchResult = true;
			}

			if (MatchResult) {
				cout << "Found Match in Index::: " << i << endl;
			}
		}

		MatchResult = false;

		//Now compute Next Sliding Window
		if (i < textLen - patternLen) {
			textKey = ((textKey - text[i] * R) * radix + text[i + patternLen]) % key;
		}

		//textKey can be negative and to tackle that condition
		if (textKey < 0) {
			textKey = textKey + key;
		}

	}

	return 1;
}




int BruteSearch(string pattern, string text) {
	int count = 0;

	// first for loop for pointing from start to end length
	for (int i = 0; i <= text.length() - pattern.length(); i++) {

		// Next for loop used for slicing word from the text in same length as pattern size
		for (int j = i; j < pattern.length()+i; j++) {
			
			count = 0;

			//Matching the pattern with the sliced word from text
			while (count < pattern.length()) {
				if (pattern[count] != text[j + count]) {
					break;
				}
				count++;
			}

			
			if (count == pattern.length()) {	//Match condition
				cout << "found a match at index " << j << endl;
				break;
			}
			else {	//No match condition
				break;		
			}
						
		}

	}

	return 1;
}



vector<int> LongestSuffixPreffixTable(string pattern) {
	long patterLen = pattern.length();
	vector<int> table(patterLen, 0);

	long j = 0;

	for (int i = 1; i < patterLen; i++) {

		//Matched condition
		if (pattern[j] == pattern[i]) {
			table[i] = j + 1;
			j++;
		}
		else {
			//Non-match condition
			while (j > 0) {
				j = j - 1;
				j = table[j];
				if (pattern[j] == pattern[i]) {
					table[i] = j + 1;
					break;
				}
			}
		}
	}

	return table;
}


int KnuthMorrisPrattSubStringSearch(string text, string pattern, vector<int> &table) {
	signed int i = 0, j = 0; 
	long matchLen = 0;
	while (i < text.length()){
		if (text[i] != pattern[j]) {

			//move backward at table
			while ((text[i] != pattern[j])) {
				j = j - 1;
				if (j < 0) {
					j = 0;
					break;
				}
				else
					j = table[j];
			}
			//If this while loop can't find any match that means there are no prefix to match for next one
			i++; // so look for next pattern match

			//But if got matched in prefix or suffix
			if ((text[i] == pattern[j])) {
				j++;
			}
			else {
				j = 0;
			}

		}
		else {		// move forward with text and table pattern
			i++;
			j++;
		}

		if (j == pattern.length())
			cout << "found a match at index " << i+ 1 - j << endl;
	}


	return 1;
}





int main() {
	//string pattern = "26535";
	//string text = "265353141592653589793";

	string pattern = "abcaby";
	string text = "abxabcabcaby";

	cout << "Given pattern is ::: " << pattern << endl;
	cout << "Given text is :::: " << text << endl;
	
	cout << "Executing pattern search in text using Brute Force method" << endl;
	BruteSearch(pattern, text);



	cout << "Executing pattern search in text using Rabin-karp method" << endl;
	long key = 997;		//this key have to be a large random prime number
	RobinKarpSubStringSearch(text,pattern,key);


	cout << "Executing pattern search in text using Knuth–Morris–Pratt(KMP) method" << endl;
	vector<int> Table = LongestSuffixPreffixTable(pattern);

	for (int i = 0; i < Table.size(); i++)
		cout << Table[i] << " ";
	KnuthMorrisPrattSubStringSearch(text, pattern, Table);
	cout << endl;

	return 1;
}