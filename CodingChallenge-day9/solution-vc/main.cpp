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

void search(string pattern, string input, int *suffArr, int n) {
	int m = pattern.length();
	//¶þ·Ö²éÕÒ
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = left + (right - 1) / 2;
		int res = strncmp(&pattern[0], &input[suffArr[mid]], m);

		if (res == 0) {
			cout << "Pattern found at index: " << suffArr[mid];
			return;
		}
		else if (res < 0) {
			right = mid - 1;
		}
		else if (res > 0) {
			left = mid + 1;
		}
	}
	cout << "Pattern not found";
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
		string pattern;
		getline(cin, pattern);
		search(pattern, input, suffixArr, n);
		cout << endl;
	}
	return 0;
}