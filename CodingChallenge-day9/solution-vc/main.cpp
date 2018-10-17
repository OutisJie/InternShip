#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "solution1.h"
#include "solution2.h"
using namespace std;

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
	Solution1 *solution1 = new Solution1();
	Solution2 *solution2 = new Solution2();
	while (getline(cin, input))
	{
		int n = input.length();
		int *suffixArr1 = solution1->buildSuffixArray(input, n);
		int *suffixArr2 = solution2->buildSuffixArray((char*)input.c_str(), n);
		cout << "solution1: ";
		for (int i = 0; i < n; i++) {
			cout << suffixArr1[i] << " ";
		}
		cout << endl;
		cout << "solution2: ";
		for (int i = 0; i < n; i++) {
			cout << suffixArr2[i] << " ";
		}
		cout << endl;

		string pattern;
		getline(cin, pattern);
		search(pattern, input, suffixArr1, n);
		search(pattern, input, suffixArr2, n);
		cout << endl;
	}
	return 0;
}