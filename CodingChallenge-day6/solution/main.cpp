#include <iostream>
#include <string>
#include "solution.h"
using namespace std;

int main() {
	string line;
	while (getline(cin, line))
	{
		/*int result = Solution().lengthOfLongestSubstr1(line);*/
		//int result = Solution().lengthOfLongestSubstr2(line);
		int result = Solution().lengthOfLongestSubstr3(line);
		cout << to_string(result) << endl;
	}
	system("pause");
	return 0;
}