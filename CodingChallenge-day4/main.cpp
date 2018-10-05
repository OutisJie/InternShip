#include <iostream>
#include <string>
#include <iterator>
#include "solution.h"
using namespace std;

vector<int> getVector(string input) {
	vector<int> arr;
	input.erase(0, 1);
	input.erase(input.size() - 1, 1);
	while (input.size() > 0)
	{
		int pos = input.find(" ");
		arr.push_back(stoi(input.substr(0, pos)));

		if (pos != -1) {
			input.erase(0, pos + 1);
		}
		else {
			input.erase(0, input.size());
		}
	}
	return arr;
}

int main() {
	string inputArray;
	int target;
	vector<int> result;
	getline(cin, inputArray);
	cin >> target;

	Solution *solution = new Solution(getVector(inputArray), target);
	result = solution->getResult();
	cout << "[";
	/*
	ostream_iterator<int, char> out_iter(cout, " ");
	copy(result.begin(), result.end(), out_iter);*/
	for (vector<int>::iterator iter = result.begin(); iter != result.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << "]" << endl;
	system("pause");
	return 0;
}