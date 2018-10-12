#include <iostream>
#include <string>
#include "solution.h"
using namespace std;

int main() {
	string input;
	while (getline(cin, input)) {
		Solution * solution = new Solution();
		cout << solution->longestPalindrome(input) << endl;
	}
}