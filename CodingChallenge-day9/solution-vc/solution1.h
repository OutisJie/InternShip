#pragma once
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct suffix1 Suffix1;
//structure to store information of a suffix
struct suffix1 {
	int index;
	char *suff;
};
class Solution1
{
public:
	Solution1();
	~Solution1();
	int *buildSuffixArray(string input, const int n);
private:
};

Solution1::Solution1()
{
}

Solution1::~Solution1()
{
}
//a comparison function used by sort() to compare two suffixes
int cmp(Suffix1 a, Suffix1 b) {
	return strcmp(a.suff, b.suff) < 0 ? 1 : 0;
}

int* Solution1::buildSuffixArray(string input, const int n) {
	//store suffixes
	vector<Suffix1> suffixes(n);
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

