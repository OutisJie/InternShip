#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct ListNode
{
	int value;
	ListNode *next;
	ListNode(int x) :value(x), next(NULL) {};
};

class Solution
{
private:
public:
	Solution();
	~Solution();
	ListNode* stringToListNode(string input);
	ListNode* addTwoList(ListNode* list1, ListNode* list2);
	string listNodeToString(ListNode *input);
	vector<int> stringToVector(string input);
	void trimLeftTrailingSpaces(string &input);
	void trimRightTrailingSpaces(string &input);
};

Solution::Solution()
{
}

Solution::~Solution()
{
}
string Solution::listNodeToString(ListNode* node) {
	if (node == nullptr) {
		return "[]";
	}
	string result;
	while (node) {
		result += to_string(node->value) + ", ";
		node = node->next;
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}

ListNode* Solution::addTwoList(ListNode* list1, ListNode* list2) {
	ListNode *resultHead = new ListNode(0);
	ListNode *p = list1, *q = list2, *ptr = resultHead;
	int carry = 0;
	while (p ||q )
	{
		int x = (p) ? p->value : 0;
		int y = (q) ? q->value : 0;
		int sum = x + y + carry;
		carry = sum < 10 ? 0 : 1;
		ptr->next = new ListNode(sum % 10);
		ptr = ptr->next;
		if (p) p = p->next;
		if (q) q = q->next;
	}
	if (carry > 0) {
		ptr->next = new ListNode(carry);
	}
	ptr = resultHead->next;
	delete resultHead;
	return ptr;
}

ListNode* Solution::stringToListNode(string input) {
	vector<int> list = stringToVector(input);

	ListNode* root = new ListNode(0);//头指针
	ListNode* ptr = root;
	for (int item : list) {
		ptr->next = new ListNode(item);
		ptr = ptr->next;
	}
	ptr = root->next;//删除头指针
	delete root;
	return ptr;
}

void Solution::trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}
void Solution::trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}
vector<int> Solution::stringToVector(string input) {
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)){
		output.push_back(stoi(item));
	}
	return output;
}

