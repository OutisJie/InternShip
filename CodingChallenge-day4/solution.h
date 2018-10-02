#pragma once
#include <vector>
using namespace std;
class Solution
{
private:
	vector<int> nums;
	int target;
public:
	Solution(vector<int>& nums, int target);
	vector<int> getResult();
	~Solution();
};

Solution::Solution(vector<int>& nums, int target)
{
	this->nums = nums;
	this->target = target;
}

vector<int> Solution::getResult() {
	vector<int> result(this->nums);

	return result;
}

Solution::~Solution()
{
}
