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

}
