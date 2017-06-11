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

int main()
{
	trie_tree_t *tree = trie_tree_create();
	trie_tree_insert(tree, "Hello");
	trie_tree_insert(tree, "world");
	trie_tree_insert(tree, "Trie");
	trie_tree_insert(tree, "Tree");
	trie_tree_insert(tree, "Nice");

	cout << trie_tree_query(tree, "Hello") << endl;
	cout << trie_tree_query(tree, "Yihulee") << endl;
	cout << trie_tree_query(tree, "world") << endl;
	cout << trie_tree_query(tree, "Nice") << endl;
	trie_tree_destroy(tree);
	getchar();
}