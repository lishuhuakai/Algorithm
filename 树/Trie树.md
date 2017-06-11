# Trie树

**Trie** 树，即 **字典树** ，又称单词查找树或键树，是一种树形结构，是一种哈希树的变种。典型应用是用于统计和排序大量的字符串（但不仅限于字符串），所以经常被搜索引擎系统用于文本词频统计。它的优点是：**最大限度地减少无谓的字符串比较** ，查询效率比哈希表高。

## Trie树结构

**Trie** 的核心思想是空间换时间：利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。

举例：将 `tea，ten，to，in，inn，int` 几个单词构建成一个 **Trie** 树，看一下具体的**Trie** 树的结构,图中绿色的节点表示根节点,蓝色的节点表示单词的结尾.

![Trie树结构](./pic/trietree.jpg)


从图中可以看出 **Trie** 树的某些特性：

1. **根节点不包含字符** ，除根节点外每一个节点都只包含 <font color='red'>一个字符</font>。

2. 从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。

3. 每个节点的所有子节点包含的字符都不相同。


## Trie树实现

**Trie** 树的插入、删除、查找的操作都是一样的，只需要简单的对树进行一遍遍历即可，时间复杂度：**O(n)** 。

对于 **Tried** 树的实现可以使用数组和链表两种方式：

   - 数组：由于我们知道一个 **Tried** 树节点的子节点的数量是固定26个（针对不同情况会不同，比如兼容数字，则是36等），所以可以使用固定长度的数组来保存节点的子节点
     - 优点：在对子节点进行查找时速度快
     - 缺点：浪费空间，不管子节点有多少个，总是需要分配26个空间
   - 链表：使用链表的话我们需要在每个子节点中保存其兄弟节点的链接，当我们在一个节点的子节点中查找是否存在一个字符时，需要先找到其子节点，然后顺着子节点的链表从左往右进行遍历
     - 优点：节省空间，有多少个子节点就占用多少空间，不会造成空间浪费

     - 缺点：对子节点进行查找相对较慢，需要进行链表遍历，同时实现也较数组麻烦

下面给一个非常简单的实现:
```c++
#include <iostream>
using namespace std;

#define MAXN 10000 /** 输入的单词的最大个数 */
#define CHAR_COUNT 128  /** ASCII编码范围 */
#define MAX_CODE_LEN 10  /** 单词的最大长度 */
#define MAX_NODE_COUNT (MAXN * MAX_CODE_LEN + 1)

typedef struct trie_node_t {
	struct trie_node_t* next[CHAR_COUNT];
	bool is_tail;	/** 单词结尾标记 */
} trie_node_t;

typedef struct trie_tree_t {
	trie_node_t *root; /** 树的根节点 */
	int size;	/** 树中实际出现的节点数 */
	trie_node_t nodes[MAX_NODE_COUNT];
} trie_tree_t;

/**
 * @brief 构建一棵Trie树
 * @return 创建的树的指针
 */
trie_tree_t *
trie_tree_create(void)
{
	trie_tree_t *tree = (trie_tree_t *)malloc(sizeof(struct trie_tree_t));
	tree->root = &(tree->nodes[0]);
	memset(tree->nodes, 0, sizeof(tree->nodes));
	tree->size = 1;
	return tree;
}

/**
 * @brief 销毁Trie树
 * @param[in] tree 欲销毁的Trie树的指针
 * @return 无
 */
void
trie_tree_destroy(trie_tree_t *tree)
{
	free(tree);
	tree = NULL;
}

/**
 * @brief 清空Trie树的节点信息
 * @param[in] tree 欲清空的Trie树的指针
 * @return 无
 */
void
trie_tree_clear(trie_tree_t *tree)
{
	memset(tree->nodes, 0, sizeof(tree->nodes));
	tree->size = 1;
}

/**
 * @brief 在Trie树中插入单词
 * @param[in] tree Trie树的指针
 * @param[in] word 欲插入的单词的指针
 * @return 插入成功,返回true,否则返回false
 */
bool
trie_tree_insert(trie_tree_t *tree, char *word)
{
	trie_node_t *p = tree->root; /* 从根节点开始 */
	while (*word) {
		if (p->next[*word] == NULL) {
			p->next[*word] = &(tree->nodes[tree->size++]);
		}
		p = p->next[*word];
		word++; /* 指针下移 */
	}
	p->is_tail = true;
	return true;
}

/**
 * @brief 查询单词是否存在于Trie树中
 * @param[in] tree Trie树的指针
 * @param[in] word 欲查询的单词的指针
 * @return 存在,返回true,否则返回false
 **/
bool
trie_tree_query(trie_tree_t *tree, char *word)
{
	trie_node_t *p = tree->root;
	while (*word) {
		if (p->next[*word] == NULL) return false;
		p = p->next[*word];
		word++;
	}
	return p->is_tail;
}
```
从上面的数组实现可以发现,内存浪费的现象还是挺严重的,所以,你可以自己用动态数组的形式实现一下,应该会好很多.