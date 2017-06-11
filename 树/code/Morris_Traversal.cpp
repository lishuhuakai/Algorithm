#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

/**
 * @struct
 * @brief 二叉树节点.
 */
typedef struct bt_node_t {
	elem_t elem;
	struct bt_node_t *left;
	struct bt_node_t *right;
};

/**
 * @brief 使用Morrris算法进行中序遍历.
 * @param[in] root 根节点
 * @param[in] visit 访问函数
 */
void 
in_order_mirrors(bt_node_t *root, int(*visit)(bt_node_t *))
{
	bt_node_t *cur;
	cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			visit(cur);
			cur = cur->right;	/* 将右孩子作为当前节点 */
		}
		else {
			/* 查找cur节点的前驱节点 */
			bt_node_t *node = cur->left;
			while (node->right != NULL && node->right != cur)
				node = node->right;

			if (node->right == NULL) { /* 还没有线索化，则建立线索 */
				node->right = cur;
				cur = cur->left;
			}
			else { /* 如果已经线索化了，则访问节点，并删除线索 */
				visit(cur);
				node->right = NULL;
				cur = cur->right;
			}
		}
	}
}

/**
 * @brief 使用Morrris算法先序遍历
 * @param[in] root 根节点
 * @param[in] visit 访问函数
 */
void
pre_order_morris(bt_node_t *root, int(*visit)(bt_node_t *))
{
	bt_node_t *cur;

	cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			visit(cur);
			cur = cur->right;
		}
		else {
			/* 查找前驱 */
			bt_node_t *node = cur->left;
			while (node->right != NULL && node->right != cur)
				node = node->right;

			if (node->right == NULL) {
				visit(cur);
				node->right = cur;
				cur = cur->left;
			}
			else { /* 已经线索化了，则删除线索 */
				node->right = NULL;
				cur = cur->right;
			}
		}
	}
}

/**
 * @brief 将指针反转
 * @param[in] from 反转路径的起点.
 * @param[in] to 反转路径的终点。
 */
static void 
reverse(bt_node_t *from, bt_node_t *to) 
{
	bt_node_t *x = from, *y = from->right, *z;
	if (from == to) return;
	/* 需要注意的是,这里并不是完全的路径反转,但是用在这里足够了.所以这里只是一个局部函数. */
	while (x != to) {
		z = y->right;
		y->right = x;
		x = y;
		y = z;
	}
}

/**
 * @brief 访问逆转后的路径上的所有节点.
 * @param[in] from 需要访问路径的起点,也就是应该最后一个访问的节点.
 * @param[in] to 需要访问路径的终点,也是第一个应该被访问的节点.
 */
static void
visit_reverse(bt_node_t* from, bt_node_t *to, int (*visit)(bt_node_t *))
{
	bt_node_t *p = to;
	reverse(from, to);
	while (1) {
		visit(p);
		if (p == from)
			break;
		p = p->right;
	}
	reverse(to, from);
}

/**
 * @brief 使用Morrris算法进行后序遍历.
 * @param[in] root 根节点
 * @param[in] visit 访问函数
 */
void
post_order_morris(bt_node_t *root, int(*visit)(bt_node_t *))
{
	bt_node_t dummy = { 0, NULL, NULL };
	bt_node_t *cur, *prev = NULL;

	dummy.left = root;
	cur = &dummy;
	while (cur != NULL) {
		if (cur->left == NULL) {
			prev = cur;
			cur = cur->right;
		}
		else {
			bt_node_t *node = cur->left;
			while (node->right != NULL && node->right != cur)
				node = node->right;

			if (node->right == NULL) { /* 尚未线索化,立即线索化 */
				node->right = cur;
				prev = cur;
				cur = cur->left;
			}
			else {
				/* visit_reverse其实有一个小问题,那就是prev->right在访问的时候会别修改 */
				visit_reverse(cur->left, prev, visit); 
				prev->right = NULL;
				prev = cur;
				cur = cur->right;
			}
		}
	}
}

/**
 * @breif 分配一个新节点.
 * @param[in] e 新节点的数据
 */
bt_node_t* new_node(int e)
{
	bt_node_t* node = (bt_node_t *)malloc(sizeof(bt_node_t));
	node->elem = e;
	node->left = NULL;
	node->right = NULL;
	return node;
}

static int
print(bt_node_t *node)
{
	printf(" %d", node->elem);
	return 0;
}

void 
test_01()
{
	bt_node_t n1, n2, n3, n4;
	n1.elem = 1, n1.left = NULL, n1.right = &n2;
	n2.elem = 2, n2.left = NULL, n2.right = &n3;
	n3.elem = 3, n3.left = NULL, n3.right = &n4;
	n4.elem = 4, n4.left = NULL, n4.right = NULL;
	reverse(&n1, &n4);
	reverse(&n4, &n1);
}

int main()
{
	bt_node_t *n1 = new_node(1);
	bt_node_t *n2 = new_node(2);
	bt_node_t *n3 = new_node(3);
	bt_node_t *n4 = new_node(4);
	bt_node_t *n5 = new_node(5);
	bt_node_t *n6 = new_node(6);
	bt_node_t *n7 = new_node(7);
	bt_node_t *n8 = new_node(8);
	bt_node_t *n9 = new_node(9);

	n6->left = n2; n6->right = n7;
	n2->left = n1; n2->right = n4;
	n1->left = NULL; n1->right = NULL;
	n4->left = n3; n4->right = n5;
	n3->left = n3->right = NULL;
	n5->left = n5->right = NULL;
	n7->left = NULL; n7->right = n9;
	n9->left = n8; n9->right = NULL;
	n8->left = n8->right = NULL;
	
	pre_order_morris(n6, print);
	printf("\n");
	
	in_order_mirrors(n6, print);
	printf("\n");
	
	post_order_morris(n6, print);
	printf("\n");
	getchar();
}