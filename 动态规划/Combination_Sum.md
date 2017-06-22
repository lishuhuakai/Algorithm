这是一套非常有意思的套题,我想在这里总结一下个人的心得.

# 一. Combination Sum

给定一组没有重复的,候选的数字 **C** ,以及一个目标数字 **T** ,找到在 **C** 中所有的组合,使得该组合的和为 **T**.

在 **C** 中的每一个数字可以重复无数多次.



注意:

1. 所有的数字,包括 **T**, 都为正数.
2. 最终输出的方案中不应该包含重复的组合.

举个栗子,给定 **C** 为 `[2, 3, 6, 7]` , 以及 **T** `7`.可以得到这样一组解:

```c++
[
  [7],
  [2, 2, 3]
]
```

## 解析

虽然这道题目比较正宗的解法是 **BFS** ,但是这里我想从另外一个角度来看待这个问题.

这道题目给我的第一感觉就是,它是一道完全背包问题,每个数字可以取无数次,然后背包的容量为 **T** ,只是我们最终要求的是解法的数量,而不是价值最大.

我们用`dp[i][j]`表示数字 `j` 由 **C** 中的前 `i` 个数字组成的总数.因此

```shell
dp[i][j] = dp[i - 1][j] + dp[i][j - C[i]]
```

很明显, `dp[i][j]` 可由两部分构成,如果我们不取 **C[i]** 这个数字的话,那么有 `dp[i - 1][j]`, 如果我们取 **C[i]** 的话,有 `dp[i][j - C[i]]`.

然后利用完全背包的模版,我们最终可以得到 `dp[len(C)][T]` ,即无限制地使用C中的数字进行组合, 和为 **T** 的组合的个数. 得到了这个东西之后,我们就可以进行回溯了,如果在 `dp[i][j]` 不使用数字 **C[i]**, 可回退到子问题 `dp[i - 1][j]`, 使用数字 **C[i]**, 可以回退到 `dp[i][j - C[i]]`, 利用这一点,我们可以分分钟找出所有的组合.

```cpp
class Solution {
	static const int sz = 512;
	static int dp[sz][sz];
	void backTracing(vector<int>& nums, vector<vector<int>>& container, vector<int>& so, int pos, int target) {
		if (target == 0) {
			container.push_back(so);
			return;
		}
		if (dp[pos - 1][target]) 
			backTracing(nums, container, so, pos - 1, target);
		int remain = target - nums[pos - 1];
		if (remain >= 0 && dp[pos][remain]) {
			so.push_back(nums[pos - 1]); /* 位置pos对应的数字为nums[i -1] */
			backTracing(nums, container, so, pos, remain);
			so.pop_back();
		}
	}
public:
	vector<vector<int>> combinationSum(vector<int>& nums, int target) {
		int n = nums.size();
		vector<vector<int>> container;
		if (n == 0) return container;
		
		/* 不用nums中的数字,任意大于0的数字都无法得到 */
		for (int i = 1; i <= target; i++) dp[0][i] = 0;
		/* 0总是有一种方法可以获得 */
		for (int j = 0; j <= n; j++) dp[j][0] = 1;

		for (int i = 1; i <= n; i++) { /* 一共n个数字,第i个数字对应nums[i -1] */
			for (int j = 0; j <= target; j++) {
				dp[i][j] = j < nums[i - 1] ? dp[i - 1][j] : dp[i - 1][j] + dp[i][j - nums[i - 1]];
			}
		}
		/* 开始回溯 */
		vector<int> so;
		backTracing(nums, container, so, n, target);
		return container;
	}
};
int Solution::dp[sz][sz];
```

# 二. Combination Sum II
给定一组没有重复的,候选的数字 **C** ,以及一个目标数字 **T** ,找到在 **C** 中所有的组合,使得该组合的和为 **T**.

在 **C** 中的每一个数字仅可以使用一次.

注意:

1. 所有的数字,包括 **T**, 都为正数.
2. 最终输出的方案中不应该包含重复的组合.

举个栗子,给定 **C** 为`[10, 1, 2, 7, 6, 1, 5]` 以及 **T** `8`.一个可能的解是:

```shell
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
```

## 解析

我第一次看到这个题目的时候,立马认定了,这是一个01背包问题.

我们用`dp[i][j]`表示数字 `j` 由 **C** 中的前 `i` 个数字组成的总数.因此

```shell
dp[i][j] = dp[i - 1][j] + dp[i - 1][j - C[i]]
```

很明显, `dp[i][j]` 可由两部分构成,如果我们不取 **C[i]** 这个数字的话,那么有 `dp[i - 1][j]`, 如果我们取 **C[i]** 的话,有 `dp[i][j - C[i]]`.

利用01背包的模版,一下子可以写出解,至于求组合,一样可以用上面的回溯.

稍微有点难度的点在于去重,其实也没有多难,碰到重复的丢掉即可,我直接用 `set` 开干了.

```cpp
class Solution {
	static const int sz = 512;
	static int dp[sz][sz];
	void backTracing(vector<int>& nums, set<vector<int>>& container, vector<int>& so, int pos, int target) {
		if (target == 0) { /* target==0并不代表i==0 */
			// sort(so.begin(), so.end()); 不用再次排序,因为刚开始的时候已经排过一次了.
			container.insert(so); /* 可以起到去重的效果 */
			return;
		}
		
		if (dp[pos - 1][target])
			backTracing(nums, container, so, pos - 1, target);
		int remain = target - nums[pos - 1];
		if (remain >= 0 && dp[pos - 1][remain]) {
			so.push_back(nums[pos - 1]);
			backTracing(nums, container, so, pos - 1, remain);
			so.pop_back();
		}
	}
public:
	vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
		int n = nums.size();
		vector<vector<int>> container;
		if (n == 0) return container;
		sort(nums.begin(), nums.end());
		for (int i = 1; i <= target; i++) dp[0][i] = 0;
		for (int j = 0; j <= n; j++) dp[j][0] = 1;
	
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= target; j++) {
				dp[i][j] = j < nums[i - 1] ? dp[i - 1][j] : dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
			}
		}
		/* 开始回溯 */
		vector<int> so;
		set<vector<int>> s_container;
		if (dp[n][target])
			backTracing(nums, s_container, so, n, target);
		for (auto &elem : s_container) {
			container.push_back(elem);
		}
		return container;
	}
};
int Solution::dp[sz][sz];
```

# 三. Combination Sum III

意义不大,是问题而的特殊化,这里不再赘述.

# 四. Combination Sum VI

给定一个全为正数的整数数组,没有重复,找到所有可能的组合,使得组合的和达到 **T**.

输出组合的总数.

举个栗子:

```shell
nums = [1, 2, 3]
target = 4

所有可能的组合方式有:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

需要注意的是,相同数字的不同组合也是认可的.
输出结果为 7.
```

 ## 解析

好吧,我承认,最近脑袋一团浆糊,本来是一道非常简单的题目,但是被我弄得复杂万分,最终导致做不下去,所以这里算是一个总结吧.

[https://leetcode.com/problems/combination-sum-iv/#/solutions](https://leetcode.com/problems/combination-sum-iv/#/solutions)有关于这道题如何思考的非常好的解答,我在这里稍微翻译一下,同时也勉励一下自己.

如果我们直接用暴力法来解这道题,我们应该怎么做呢?下面是一种方式:

```cpp
int combinationSum4(vector<int>& nums, int target) {
	if (target == 0) return 1;
	int res = 0;
	for (int i = 0; i < nums.size(); i++) { /* 每一层都可以取nums数组中的每一个数字 */
		if (target >= nums[i])
			res += combinationSum4(nums, target - nums[i]);
	}
}
```

使用暴力法的话,显然会超时,但是我们可以注意到,上面的递归函数中,其实存在着非常多重复的计算.因此,我们只需要将递归中的一些中间结果记录下来,下次要用到时直接拿出来即可,不用再次计算.

```cpp
class Solution {
	static const int sz = 10240;
	static int dp[sz];
private:
	int helper(vector<int>& nums, int target) {
		if (dp[target] != -1) { /* 这个子问题已经有解了 */
			return dp[target]; 
		}
		int res = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (target >= nums[i]) res += helper(nums, target - nums[i]);
		}
	}
public:
	int combinationSum4(vector<int>& nums, int target) {
		for (int i = 0; i < sz; i++) dp[i] = -1;
		dp[0] = 1;
		return helper(nums, target);
	}
};

int Solution::dp[sz];
```

最后,将上面的结果转换一下,就变成了动态规划:

```cpp
class Solution {
	static const int sz = 10240;
	static int dp[sz];
public:
	int combinationSum4(vector<int>& nums, int target) {
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for (int i = 1; i <= target; i++) {
			for (int j = 0; j < nums.size(); j++) {
				if (i - nums[j] >= 0)
					dp[i] += dp[i - nums[j]];
			}
		}
		return dp[target];
	}
};

int Solution::dp[sz];
```



