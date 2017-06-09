#include <iostream>
#include <algorithm>
using namespace std;

/**
* @brief 预处理，计算模式串中每个字符最靠右的位置距离模式串末尾的长度.
*
* @param[in] pattern 模式串
* @param[in] m 模式串的长度
* @param[out] bmBc 用于记录每个字符在模式串中最靠右的位置距离模式串末尾的长度.
*/
void preBmBc(const char *pattern, int m, int bmBc[])
{
	int i;

	for (i = 0; i < 256; i++) {
		bmBc[i] = m;
	}

	for (i = 0; i < m - 1; i++) {
		bmBc[pattern[i]] = m - 1 - i; /* pattern[i]是模式字符串的第i个字符 */
	}
}
/**
* @brief 预处理，计算从模式串位置i开始的子串，从后往前，和后缀相匹配的最大长度.
*
* @param[in] pattern 模式字符串
* @param[in] m 模式串的长度
* @param[out] suff 用于记录结果的数组
*/
void suffixes(const char *pattern, int m, int *suff)
{
	suff[m - 1] = m;
	for (int i = m - 2; i >= 0; --i) {
		int q = i;
		/* pattern[q]属于子串部分，pattern[m-1-i+q]属于后缀部分 */
		while (q >= 0 && pattern[q] == pattern[m - 1 - i + q])
			--q;
		suff[i] = i - q;
	}
}

/**
* @brief 预处理,构建好后缀规则表.
*
* @param[in] pattern 模式串
* @param[in] m 模式串的长度
* @param[out] bmGs bmGs[i]表示如果在模式串的i位置遭遇不匹配,那么采用好后缀规则,模式串应当相对于文本串向后移动的位数.
*/
void preBmGs(const char *pattern, int m, int bmGs[])
{
	int i, j;
	int *suff = (int *)malloc(sizeof(int) * (m + 1));
	suffixes(pattern, m, suff);
	for (i = 0; i < m; ++i) /* 既无子串匹配好后缀，也没有最大前缀 */
		bmGs[i] = m;
	j = 0;
	for (i = m - 1; i >= 0; --i)
		if (suff[i] == i + 1)
			for (; j < m - 1 - i; ++j)
				if (bmGs[j] == m) /* 保证只会修改一次 */
					bmGs[j] = m - 1 - i;
	for (i = 0; i <= m - 2; ++i) /* 存在子串匹配好后缀 */
		bmGs[m - 1 - suff[i]] = m - 1 - i;
	free(suff);
}

int BM(const char *pattern, const char *text)
{
	int i = 0, j = 0;
	int bmBc[256];
	int n = strlen(text), m = strlen(pattern);
	int *bmGs = (int *)malloc(sizeof(int) * (m + 1));
	/* Preprocessing */
	preBmGs(pattern, m, bmGs);
	preBmBc(pattern, m, bmBc);

	/* Searching */
	while (i <= n - m) {
		for (j = m - 1; j >= 0 && pattern[j] == text[i + j]; --j);
		if (j < 0) {
			j += bmGs[0];
			free(bmGs);
			return i;
		}
		else
			i += max(bmGs[j], bmBc[text[i + j]] - m + 1 + j);
	}
	free(bmGs);
	return -1;
}


int main()
{
	char haystack[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char needle[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	cout << BM(needle, haystack) << endl;
	getchar();
}