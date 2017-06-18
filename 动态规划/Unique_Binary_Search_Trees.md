# 题目描述

给定一个n,我们可以构建多少棵二叉搜索树呢?使用值1~n填充树的节点.

举个例子,如果n=3,那么一共会存在5棵这样的树:

```cpp
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

# 题目分析

这是一道非常经典的题目,很有意思.在此之前,我们有必要了解一下二叉搜索树的知识:

> 二叉查找树（Binary Search Tree），（又：[二叉搜索树](http://baike.baidu.com/item/%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91)，二叉排序树）它或者是一棵空树，或者是具有下列性质的[二叉树](http://baike.baidu.com/item/%E4%BA%8C%E5%8F%89%E6%A0%91)： 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值； 它的左、右子树也分别为[二叉排序树](http://baike.baidu.com/item/%E4%BA%8C%E5%8F%89%E6%8E%92%E5%BA%8F%E6%A0%91)。

需要注意的是, **如果以 i 节点为根,那么编号小于 i 的节点只可能出现在 i 的左子树中,编号大于 i 的节点只能出现在 i 的右子树中**.

对于给定的1~n节点,我们知道,每个节点都可以充当二叉搜索树的根.

如果以1号节点为根,求这种类型的二叉搜索树一共有多少棵?那么问题可以转化为,求2~n节点所能够成的二叉搜索树的棵数.

如果以2号节点为根,求这种类型的二叉搜索树一共有多少颗?问题转化成了两个子问题,第一个子问题是求以1节点所能构成的二叉搜索树的棵数,第二个子问题是求以3~n节点所能构成的二叉搜索树的棵数.然后将两者相乘,得到结果.

如果以3号节点为根,求这种类型的二叉搜索树一共有多少颗?问题转化成了两个子问题,第一个子问题是求以1,2节点所能构成的二叉搜索树的棵数,第二个子问题是求以3~n节点所能构成的二叉搜索树的棵数.然后将两者相乘,得到结果.

...

如果以n号节点为根,求这种类型的二叉搜索树一共有多少颗?那么问题可以转化为,求1~n-1节点所能够成的二叉搜索树的棵数.

然后将上面的结果加起来,就可以得到问题的解.

```cpp
#include <iostream>
using namespace std;

class Solution {
public:
	int numTrees(int n) {
		int dp[4000];
		dp[0] = 0; dp[1] = 1; dp[2] = 2; dp[3] = 5;
		for (int i = 4; i <= n; i++) {
			int sum = 0;
			for (int j = 1; j < i - 1; j++)
				sum += dp[j] * dp[i - 1 - j];
			dp[i] = sum + 2 * dp[i - 1];
		}
		return dp[n];
	}
};

int main()
{
	Solution so;
	cout << so.numTrees(4) << endl;
	getchar();
}
```



# 题目扩展

得到这些二叉搜搜索树

直接上代码吧:

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
	vector<TreeNode *> generateTrees(int begin, int end) {
		vector<TreeNode *> trees;
		if (begin > end) {
			trees.push_back(NULL); /* 空树 */
			return trees;
		}
		if (begin == end) {
			trees.push_back(new TreeNode(begin));
			return trees;
		}
		for (int root_idx = begin; root_idx <= end; root_idx++) {
			vector<TreeNode *> ltrees = generateTrees(begin, root_idx - 1); /* 左子搜索树 */
			vector<TreeNode *> rtrees = generateTrees(root_idx + 1, end); /* 右子搜索树 */
			for (auto ltree : ltrees) {
				for (auto rtree : rtrees) {
					TreeNode *tree = new TreeNode(root_idx);
					tree->left = ltree; tree->right = rtree;
					trees.push_back(tree); /* 合并成新树 */
				}
			}
		}
		return trees;
	}
public:
	vector<TreeNode*> generateTrees(int n) {
		if (n == 0) return vector<TreeNode *>();
		return generateTrees(1, n);
	}
};

int main()
{
	Solution so;
	cout << so.generateTrees(4).size() << endl;
	getchar();
}


```

