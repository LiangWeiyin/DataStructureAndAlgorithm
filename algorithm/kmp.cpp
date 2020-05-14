#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 生成前缀后缀表 简单起见用 prefix 表示
// 这是 kmp 算法的关键
void prefix_table(vector<int>& prefix, const string& pattern) {
	prefix[0] = 0;
	int m = pattern.size();
	int i = 1, j = 0;
	while (i < m) {
		if (pattern[j] == pattern[i]) {
			++j;
			prefix[i] = j;
			++i;
		}
		else {
			if (j == 0) {
				prefix[i] = 0;
				++i;
			}
			// 难点是这一步的理解
			else {
				j = prefix[j - 1];	
			}
		}
	}
}

// kmp 子串查找
void kmp_serach(const string& text, const string& pattern) {
	int m = text.size();
	int n = pattern.size();
	vector<int> prefix(n);
	prefix_table(prefix, pattern);

	int i = 0, j = 0;
	while (i < m) {
		if (text[i] == pattern[j]) {
			++i;
			++j;
		}
		else {
			if (j == 0) {
				++i;
			}
			else {
				j = prefix[j - 1];
			}
		}

		if (j == n) {
			cout << "found at " << i - j << endl;
			// 为了找出所有可能的子串的位置
			// 只需要第一个出现的位置的话可以直接 break
			j = prefix[j - 1];
		}
	}
}

int main() {
	string text    = "bacdbacdba";
	string pattern = "bacdba";
	kmp_serach(text, pattern);
	return 0;
}