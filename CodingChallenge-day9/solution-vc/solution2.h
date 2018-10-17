#pragma once
#include <string>
#include <algorithm>
using namespace std;

typedef struct suffix2 Suffix2;
struct suffix2 {
	int index;
	int rank[2]; //to store ranks and next rank pair
};

class Solution2
{
public:
	Solution2() {};
	~Solution2() {};
	int* buildSuffixArray(char *txt, int n);
private:
};

// compare two pairs, return 1 if first pair is smaller
int cmp2(Suffix2 a, Suffix2 b) {
	return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
}

// takes a string 'txt' of size n as an argument, builds and return the suffix array for the given string 
int* Solution2::buildSuffixArray(char *txt, int n) {
	Suffix2 *suffixes = new Suffix2[n];
	// initial
	for (int i = 0; i < n; i++) {
		suffixes[i].index = i;
		suffixes[i].rank[0] = txt[i] - 'a';
		suffixes[i].rank[1] = (i + 1 < n) ? txt[i + 1] - 'a' : -1;
	}
	// sort 
	sort(suffixes, suffixes + n, cmp2);
	// all suffix are sorted according to first 2 characters.
	// let us sort suffixes according to first 4 characters, then 8 characters
	int *ind = new int[n];
	for (int k = 4; k < 2 * n; k = k * 2) {
		int rank = 0;
		int prev_rank = suffixes[0].rank[0];
		suffixes[0].rank[0] = rank;
		ind[suffixes[0].index] = 0;

		// assigning rank to suffixes
		for (int i = 1; i < n; i++) {
			if (suffixes[i].rank[0] == prev_rank  && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = rank;
			}else {
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}
			ind[suffixes[i].index] = i;
		}
		// assign next rank to every suffix
		for (int i = 0; i < n; i++) {
			int nextindex = suffixes[i].index + k / 2;
			suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
		}
		// sort
		sort(suffixes, suffixes + n, cmp2);
	}
	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++) {
		suffixArr[i] = suffixes[i].index;
	}
	delete suffixes;
	delete ind;

	return suffixArr;
}