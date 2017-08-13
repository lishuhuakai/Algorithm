#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;


/*
 * @struct
 * @brief 二叉树节点
 */
struct treeNode {
	treeNode *left;
	treeNode *right;
	int val;  /* 卫星数据 */
	treeNode(int x): val(x), left(nullptr), right(nullptr){}
};

/**
 * @brief 先序遍历,非递归版本
 */
void preOrder(const treeNode *root, void(*visit)(const treeNode*)) {
	const treeNode *p = root;
	stack<const treeNode*> nodes;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	递归版本的先序遍历
	void preOrder(const treeNode *root, void (*visit)(const treeNode *)) {
		if (root == nullptr) return;
		visit(root);
		if (root->left != nullptr) preOrder(root->left);
		if (root->right != nullptr) preOrder(root->right);
	}
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if (p != nullptr) nodes.push(p);
	/* 非递归版本的先序遍历是递归版本的忠实模拟 */
	while (!nodes.empty()) {
		p = nodes.top(); nodes.pop();
		visit(p);
		if (p->right != nullptr) nodes.push(p->right);
		if (p->left != nullptr) nodes.push(p->left);
	}
}

/**
 * @brief 中序遍历,非递归版本
 */
void inOrder(const treeNode *root, void(*visit)(const treeNode*)) {
	const treeNode *p = root;
	stack<const treeNode*> nodes;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 递归版本的中序遍历
	  void inOrder(treeNode *root, void (*visit)(const treeNode *)) {
		if (root == nullptr) return;
		if (root->left != nullptr) inOrder(root->left);
		visit(root);
		if (root->right != nullptr) inOrder(root->right);
	  }
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while (!nodes.empty() || p != nullptr) {
		if (p != nullptr) { /* 先将左边部分入栈 */
			nodes.push(p);
			p = p->left;
		}
		else {
			p = nodes.top(); nodes.pop();
			visit(p);
			p = p->right; /* 访问右子树 */
		}
	}
}

void inOrder2(const treeNode *root, void(*visit)(const treeNode*)) {
	const treeNode *p = root;
	stack<const treeNode*> nodes;
	
	do {
		while (p != nullptr) { /* 将左子树全部入栈 */
			nodes.push(p);
			p = p->left;
		}

		while (!nodes.empty()) {
			p = nodes.top(); nodes.pop();
			visit(p);
			if (p->right != nullptr) { /* 左子树已经访问过了,右子树不为空 */
				p = p->right;
				break;
			}
			/* p不存在右子树,那么要退栈 */
		}
	} while (!nodes.empty());
}


/**
 * @brief 后序遍历,非递归版本
 */
void postOrder(const treeNode* root, void *(*visit)(const treeNode*)) {
	const treeNode *p = root, *q;
	stack<const treeNode*> nodes;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	递归版本的后续遍历
	void postOrder(treeNode *root, void (*visit)(const treeNode *)) {
		if (root == nullptr) return;
		postOrder(root->left);
		postOrder(root->right);
		visit(root);
	}
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	do {
		while (p != nullptr) { /* 往左下走 */
			nodes.push(p);
			p = p->left;
		}
		q = nullptr;
		while (!nodes.empty()) {
			p = nodes.top(); nodes.pop();
			/* 右孩子不存在或者已经被访问过了,访问该节点 */
			if (p->right == q) {
				visit(p);
				q = p;  /* 保存刚访问过的节点 */
			}
			else {
				/* 当前节点不能访问,需要第二次进栈 */
				nodes.push(p);
				/* 左子树已经遍历过了,根据后序遍历规则,先处理右子树 */
				p = p->right;
				break;
			}
		}
	} while (!nodes.empty());
}

void print(const treeNode* root) {
	cout << root->val << endl;
}

int main() {
	treeNode n1(1), n2(2), n3(3), n4(4), n5(5);
	n1.left = &n2; n2.left = &n3; n3.left = &n4; n3.right = &n5;
	inOrder2(&n1, print);
	getchar();
}