#pragma once
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
class Solution
{
public:
	Solution();
	~Solution();
	vector<int> stringToVector(string input);
	double getMedian(vector<int> &nums1, vector<int> &nums2);
private:
	void trimLeft(string& input);
	void trimRight(string& input);
	double getMedianIndex(int size1, int size2, vector<int>& nums1, vector<int>& nums2);
};

Solution::Solution()
{
}

Solution::~Solution()
{
}
void Solution::trimLeft(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](char ch) {
		return !isspace(ch);
	}));
}
void Solution::trimRight(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](char ch) {
		return !isspace(ch);
	}).base(), input.end());
}

vector<int> Solution::stringToVector(string input) {
	vector<int> output;
	trimLeft(input);
	trimRight(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	string item;
	ss.str(input);
	char delim = ',';
	while (getline(ss, item, delim))
	{
		output.push_back(stoi(item));
	}
	return output;
}

double Solution::getMedian(vector<int> &nums1, vector<int> &nums2) {
	int m = nums1.size(), n = nums2.size();
	double result;
	if (m > n) {
		result = getMedianIndex(n, m, nums2, nums1);
	}
	else
	{
		result = getMedianIndex(m, n, nums1, nums2);
	}
	return result;
}

double Solution::getMedianIndex(int size1, int size2, vector<int> &nums1, vector<int> &nums2) {
	int iMin = 0, iMax = size1, halfLen = (size1 + size2 + 1) / 2;
	while (iMin <= iMax) {
		int i = (iMin + iMax) / 2, j = halfLen - i;
		if (i < iMax && nums2[j - 1] > nums1[i]) {
			iMin = i + 1;
		}
		else if (i > iMin && nums1[i - 1] > nums2[j]) {
			iMax = i - 1;
		}
		else {
			int maxLeft = 0;
			if (i == 0) {
				maxLeft = nums2[j - 1];
			}
			else if (j == 0) {
				maxLeft = nums1[i - 1];
			}
			else {
				maxLeft = max(nums1[i - 1], nums2[j - 1]);
			}
			if ((size1 + size2) % 2 == 1) {
				return maxLeft;
			}
			int minRight = 0;
			if (i == size1) {
				minRight = nums2[j];
			}
			else if (j == size2) {
				minRight = nums1[i];
			}
			else {
				minRight = min(nums1[i], nums2[j]);
			}
			return (maxLeft + minRight) / 2.0;
		}
	}
}
