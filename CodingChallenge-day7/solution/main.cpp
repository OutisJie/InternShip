#include <iostream>
#include <string>
#include <vector>
#include "solution.h"
using namespace std;

int main() {
	string input;
	Solution *solution = new Solution();
	while (getline(cin, input))
	{
		vector<int> nums1 = solution->stringToVector(input);
		getline(cin, input);
		vector<int> nums2 = solution->stringToVector(input);

		double result = solution->getMedian(nums1, nums2);
		cout << to_string(result) << endl;
	}
}