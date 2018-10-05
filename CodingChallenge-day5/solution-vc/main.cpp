#include <iostream>
#include <string>
#include "solution.h"
using namespace std;

int main() {
	string line;
	Solution *solution = new Solution();
	while (getline(cin, line)){
		ListNode *list1 = solution->stringToListNode(line);
		getline(cin, line);
		ListNode *list2 = solution->stringToListNode(line);
		ListNode *result = solution->addTwoList(list1, list2);
		string out = solution->listNodeToString(result);
		cout << out << endl;
		cout << "¼ÌÐø" << endl;
	}

	system("pause");
	return 0;
}