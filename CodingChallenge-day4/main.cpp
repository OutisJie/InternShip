#include <iostream>
#include <string>
#include "solution.h"
using namespace std;

int main() {
	string inputArray;
	int target;
	cin >> inputArray;
	cin >> target;
	vector<int> arr(4);
	arr[0] = 2; arr[1] = 7; arr[2] = 11; arr[3] = 15;
	Solution *solution = new Solution(arr, target);
	cout << solution->getResult() << end;
	return 0;
}