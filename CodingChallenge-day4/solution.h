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
	vector<int> result;
	for (int i = 0; i < nums.size(); i++) {
		int num1 = nums[i];
		for (int j = i + 1; j < nums.size(); j++) {
			int num2 = target - num1;
			if (num2 == nums[j]) {
				result.push_back(num1);
				result.push_back(num2);
				break;
			}
		}
	}
	return result;
}

Solution::~Solution()
{
}
