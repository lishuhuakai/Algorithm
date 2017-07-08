#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/**
 * 位向量法.
 *	 假定set的元素个数为n,那么用一个长度为n的bool数组来模拟位向量,数组的第i个元素为true,表示选择set
 *	 的第i个元素, 否则表示不选择.假定我们从二进制的 000....00 (n个0) 开始数数, 一直数到 111...11
 *	 (n个1)的话, 我们会发现我们数的每一个数,都对应了set的一个子集.利用这点,可以很快地写出子集寻找算法.
 *	 举个例子,假定set为[1, 2, 3], 位向量001表示选择第3个元素,即[3]是set的一个子集.
 *	 位向量111表示[1, 2, 3]为set的一个子集.
 */

/**
 * @brief 寻找所有的子集
 * @param[in] set 集合
 * @param[in] mask 位标记
 * @param[in] pos 当前已经处理到了第pos个位置了.
 * @param[in, out] subsets 用于记录结果的数组.
 */
void findSubSets(vector<int>& set, bool mask[], int pos, vector<vector<int>>& subsets)
{
	if (pos == set.size()) { /* 递归终止条件 */
		vector<int> subset;
		for (int i = 0; i < set.size(); i++) {
			if (mask[i]) subset.push_back(set[i]);
		}
		subsets.push_back(subset);
		return;
	}
	mask[pos] = true;
	findSubSets(set, mask, pos + 1, subsets);
	mask[pos] = false;
	findSubSets(set, mask, pos + 1, subsets);
}

/**
 * @brief 寻找set的所有子集.
 * @param[in] set 包含了所有元素的集合
 * @return 所有子集构成的数组
 */
vector<vector<int>> subSets(vector<int>& set)
{
	bool mask[1024];
	vector<vector<int>> subsets;  /* 用于记录所有的子集 */
	findSubSets(set, mask, 0, subsets);
	return subsets;
}

int main()
{
	vector<int> nums = { 1, 2, 3 };
	auto subsets = subSets(nums);
	for (auto &subset : subsets) {
		for (auto elem : subset) {
			cout << elem << " ";
		}
		cout << endl;
	}
	getchar();
}