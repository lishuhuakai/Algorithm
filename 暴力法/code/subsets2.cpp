#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 增量构造法
 *	这种方法比位向量法稍微要复杂一些.事实上,我并不推荐这种方法,它并没有比位向量法效率更高或者
 *	更容易理解.
 */

/**
 * @brief 寻找所有长度为subsetIdx + 1的子集
 * @param[in] set 要求子集的集合
 * @param[in] setIdx 用于表示集合的下标从0~setIdx-1的元素即前setIdx个元素在这轮迭代中不能再取.
 * @param[in] subset 由集合的前setIdx元素组合而成的长度为subsetIdx的子集.
 * @param[in] subsetIdx 子集的长度.
 * @param[in/out] subsets 用于记录所有的子集的数组
 * @return 无
 */
void findSubsets(vector<int>& set, int setIdx, int* subset, int subsetIdx, 
vector<vector<int>>& subsets)
{
	/**
	 * 前一个子集长度为subsetIdx,且该子集由集合的前setIdx个元素组合而成,如何经由该子集生成长度为
	 * subsetIdx+1的子集呢?
	 */	 
	for (int i = setIdx; i < set.size(); i++) {
		/* 此时的subset是由集合前i个元素构成的一个子集,如何生成由集合的前i+1个元素构成的子集呢? */
		/* 选择set的第i+1个元素作为subset的subsetIdx位置上的元素 */
		subset[subsetIdx] = set[i];
		/* 将新生成的,长度为subsetIdx+1的子集加入subsets */
		subsets.push_back(vector<int>(subset, subset + subsetIdx + 1));
		/* 如果不取第i个元素, 那么subset的长度为subsetIdx,它已经在subsets中了 */
		/**
		 * 正如前面所见,我们已经生成了一个由前i+1个元素组合而成的,长度为subsetIdx+1的子集,
		 * 接下来的递归要在这个已经生成的子集的基础上继续生成.i+1表示对于后面的位来说,set从
		 * 0~i位置的元素都不能取了.
		 * subsetIdx+1表示第subsetIdx位置的元素已经取好,然后要往下一个位置填充元素.
		 */
		findSubsets(set, i + 1, subset, subsetIdx + 1, subsets);
	}
}

/**
* @brief 寻找set的所有子集.
* @param[in] set 包含了所有元素的集合
* @return 所有子集构成的数组
*/
vector<vector<int>> subSets(vector<int>& set) {
	vector<vector<int>> subsets;
	int subset[1024];
	findSubsets(set, 0, subset, 0, subsets);
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