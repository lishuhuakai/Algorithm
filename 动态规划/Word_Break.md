# 题目描述
给定一个非空的字符串s以及一个包含了很多非空词语的字典,判断s是否能够拆解为一个以及多个词典词语,你可以假定,字典中不会包含重复的词语.

下面是一个例子:
```cpp
s = "leetcode",
dict = ["leet", "code"]
```
这个例子应该返回true,因为`leetcode`可以被拆解成为`leet code`.

#题目扩展
给定一个非空的字符串s和一个包含了很多非空词语的字典,在s中添加空格来构建一个句子,我们的要求是,空格切分s得到的词语应该出现在字典之中,这里的测试样例中,字典里不会包含重复的词语.

返回所有可能的结果.

举个例子:
```cpp
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"]
```
返回的结果应该是:
```cpp
["cats and dog", "cat sand dog"]
```
# 题目解析
这两个问题其实是一个问题,解决了其中一个,另外一个其实也没有多么大的难度了.不得不说,这是很有意思的一道题目.

我这里稍微说一下我的思路,然后提供一份参考代码.

这里其实最重要的是确定在s字符的i位置,有那些字符可以匹配成功,计算出这个之后,可以大大方便后面的代码.

我这里用`match[i][j]`表示字符串s中长度为`j`,以`s[i]` (索引从1开始)结尾的子串在字典中的索引(索引从1开始),如果不存在,则为0.

当前面一步完成之后,我们就可以动态规划了,`dp[i]`表示以字符串s中从开始到`s[i]` (索引从1开始)的子串是否可以被拆解,很明显如果存在某个`j`,`j从1取到i`,可以使得`dp[i - j]`为真,并且`match[i][j]`不为0,那么`dp[i]`也为真.

说成人话,就是`dp[i -j]`为真表示,字符串s的开始到`s[i-j]` (下标从1开始)这一部分是可以拆解的,而且`s[i - j + 1] ~ s[i]` (下标从1开始计算)这一部分子串在字典中是存在的,即`match[i][j]`不为0,那么自然`dp[i]`为真.

最终的结果就是`dp[s.size()]`.

至于如何输出所有可能的结果,其实非常简单,我之前已经构造了match这个数组,记录了词语的索引,有了这个东西,一切就好办了.

如果`dp[i]`为真,查找`match[i][j] (j = 1, ..., i)` ,如果`match[i][j]`不为0,并且`dp[i-j]`为真,`match[i][j]`所指代的那个词语即为组成的句子的一部分.



```cpp
class Solution {
	const static int SIZE = 1024;
	const static int STRLEN = 250;
	static int match[SIZE][STRLEN];
	static bool dp[SIZE];
private:
	void makeSentences(vector<string>& sentences, vector<string>& wordDict, int idx, string s) {
		/* 开始构建sentences */
		if (idx == 0) {
			sentences.push_back(s.substr(1, s.size() - 1)); /* 移除最开始的空格 */
			return;
		}
		/* dp[idx]肯定为true */
		for (int len = 1; len <= idx; len++) {
			if (match[idx][len] != 0 && dp[idx - len]) {
				makeSentences(sentences, wordDict, idx - len, " " + wordDict[match[idx][len] - 1] + s);
			}
		}
	}
public:
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		/* 第一步,初始化 */
		vector<string> sentences;
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < s.size() + 1; i++) {
			memset(match[i], 0, sizeof(match[i]));
		}
		/* 第二步,计算匹配位置 */
		for (int i = 0; i < wordDict.size(); i++) {
			string &pat = wordDict[i];
			int len = pat.size();
			size_t offset = 0;
			for (; ; ) {
				offset = s.find(pat, offset);
				if (offset != string::npos) {
					match[offset + len][len] = i + 1; /* 使用了第i+1个word进行匹配 */
					offset += 1; /* 匹配的末尾 */
				}
				else break;
			}
		}
		/* 第三步,开始动态规划 */
		/* 为了计算的方便,我们下标从1开始 */
		dp[0] = true;
		for (int i = 1; i <= s.size(); i++) {
			for (int j = 1; j <= i; j++) { /* j代表字符的长度 */
				if (match[i][j] != 0 && dp[i - j] == true) {
					dp[i] = true; break;
				}
			}
		}
		if (dp[s.size()]) {
			makeSentences(sentences, wordDict, s.size(), "");
		}
		return sentences;
	}
};

int Solution::match[SIZE][STRLEN];
bool Solution::dp[SIZE];
```