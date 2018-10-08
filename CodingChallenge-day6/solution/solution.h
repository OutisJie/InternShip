#pragma once
#include <string>
#include <algorithm>
#include <set>
#include <hash_set>
using namespace std;

class Solution
{
public:
	Solution();
	~Solution();
	int lengthOfLongestSubstr1(string input);
	int lengthOfLongestSubstr2(string input);
	int lengthOfLongestSubstr3(string input);
private:
	bool allUnique(int start, int end, string input);
};

Solution::Solution()
{
}

Solution::~Solution()
{
}
//O(n^3)
int Solution::lengthOfLongestSubstr1(string input) {
	int result = 0;
	for (int i = 0; i < input.length(); i++) {
		for (int j = i + 1; j <= input.length(); j++) {
			if (allUnique(i, j, input)) {
				result = max(result, j - i);
			}
			else {
				break;
			}
		}
	}
	return result;
}

bool Solution::allUnique(int start, int end, string input) {
	string substr = input.substr(start, end - start);
	set<char> sub;
	string::iterator iter;
	for (iter = substr.begin(); iter != substr.end(); ++iter) {
		if (sub.find(*iter) == sub.end()) {
			sub.insert(*iter);
		}
		else
		{
			return false;
		}
	}
	return true;

}
//O(2n),因为ij都只走了一轮
int Solution::lengthOfLongestSubstr2(string input) {
	int n = input.length();
	int result = 0, i = 0, j = 0;
	hash_set<char> hashset;
	while (i < n && j < n) {
		if (hashset.find(input[j]) == hashset.end()) {
			hashset.insert(input[j]);
			j++;
			result = max(result, j - i);
		}
		else {
			hashset.erase(input[i]);
			i++;
		}
	}
	return result;
}

//这比上一个方法还要快，应为当出现abcdvd这种子字符串时，上一个方法是将start从“a”处往后移动，然而实际上不需要，因为bcdvd、cdvd、dvd都会被判断一遍；
//实际上，只需要直接将start跳到v所在的位置即可。
int Solution::lengthOfLongestSubstr3(string input) {
	vector<int> dic(256, -1);
	int result = 0, start = 0, i = 0;
	while (i < input.length()) {
		if (dic[input[i]] < start) {
			result = max(result, i - start + 1);
		}
		else {
			start = dic[input[i]] + 1;
		}
		dic[input[i]] = i++;
	}
	return result;
}