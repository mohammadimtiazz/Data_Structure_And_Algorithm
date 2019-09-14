#include <iostream>
#include <stdlib.h>
#include <string>

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




int main() {
	string pattern = "26535";
	//string text = "3141592653589793";
	string text = "265353141592653589793";
	long key = 997;		//this key have to be a large random prime number

	RobinKarpSubStringSearch(text,pattern,key);

	return 1;
}