#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct suffix Suffix;
//structure to store information of a suffix
struct suffix {
	int index;
	char *suff;
};

//a comparison function used by sort() to compare two suffixes
int cmp(Suffix a, Suffix b) {
	return strcmp(a.suff, b.suff) < 0 ? 1 : 0;
}

int *buildSuffixArrary(string input, const int n) {
	//store suffixes
	vector<Suffix> suffixes(n);
	for (int i = 0; i < n; i++) {
		suffixes[i].index = i;
		suffixes[i].suff = &input[i];
	}
	//sort the suffixes using the comparison function
	sort(suffixes.begin(), suffixes.end(), cmp);
	//store indexes of all sorted suffixes in the suffix array
	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++) {
		suffixArr[i] = suffixes[i].index;
	}
	return suffixArr;
}

int main() {
	string input;
	while (getline(cin, input))
	{
		int n = input.length();
		int *suffixArr = buildSuffixArrary(input, n);
		for (int i = 0; i < n; i++) {
			cout << suffixArr[i] << " ";
		}
		cout << endl;
	}
	return 0;
}