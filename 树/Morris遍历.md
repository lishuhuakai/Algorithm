本文转载自[http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html](http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html)

本文主要解决一个问题，如何实现二叉树的前中后序遍历，有两个要求：

1.  **O(1)**空间复杂度，即只能使用常数空间；

2. 二叉树的形状不能被破坏（中间过程允许改变其形状）。

通常，实现二叉树的前序（preorder）、中序（inorder）、后序（postorder）遍历有两个常用的方法：一是递归(recursive)，二是使用栈实现的迭代版本(stack+iterative)。这两种方法都是**O(n)**的空间复杂度（递归本身占用stack空间或者用户自定义的stack），所以不满足要求。

**Morris Traversal** 方法可以做到这两点，与前两种方法的不同在于该方法只需要 **O(1)**空间，而且同样可以在 **O(n)**时间内完成。

要使用 **O(1)**空间进行遍历，最大的难点在于，遍历到子节点的时候怎样重新返回到父节点（假设节点中没有指向父节点的p指针），由于不能用栈作为辅助空间。为了解决这个问题， **Morris**方法用到了线索二叉树（threaded binary tree）的概念。在Morris方法中不需要为每个节点额外分配指针指向其前驱（predecessor）和后继节点（successor），只需要利用叶子节点中的左右空指针指向某种顺序遍历下的前驱节点或后继节点就可以了。

**Morris**只提供了中序遍历的方法，在中序遍历的基础上稍加修改可以实现前序，而后续就要再费点心思了。所以先从中序开始介绍。

首先定义在这篇文章中使用的二叉树节点结构，即由 **elem**， **left**和 **right**组成：

```c++
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
```

# 一.中序遍历

## 步骤：

1. 初始化当前节点 **cur**为 **root**节点.

2. 如果 **cur**没有左孩子，则输出当前节点并将其右孩子作为当前节点,即 ```cur = cur->right```。

3. 如果 **cur**有左孩子，在当前节点 **cur**的左子树中找到当前节点**cur**在中序遍历下的前驱节点。

   a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。

   b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。输出当前节点。当前节点更新为当前节点的右孩子。

4. 重复以上2、3直到当前节点为空。

下图为每一步迭代的结果（从左至右，从上到下），**cur**代表当前节点，深色节点表示该节点已输出。

![中序遍历](./pic/in_order_traversal.jpg)

```c++
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
```

## 复杂度分析：

空间复杂度： **O(1)**，因为只用了两个辅助指针。

时间复杂度： **O(n)**。证明时间复杂度为 **O(n)**，最大的疑惑在于寻找中序遍历下二叉树中所有节点的前驱节点的时间复杂度是多少，即以下两行代码：

```c++
while (prev->right != NULL && prev->right != cur)

    prev = prev->right;
```

直觉上，认为它的复杂度是 **O(nlgn)**，因为找单个节点的前驱节点与树的高度有关。但事实上，寻找所有节点的前驱节点只需要 **O(n)**时间。n个节点的二叉树中一共有n-1条边，整个过程中每条边最多只走2次，一次是为了定位到某个节点，另一次是为了寻找上面某个节点的前驱节点，如下图所示，其中红色是为了定位到某个节点，黑色线是为了找到前驱节点。所以复杂度为 **O(n)**。

![复杂度分析](http://images.cnitblog.com/blog/300640/201306/15150628-5285f29bab234750a62e2309394b6e14.jpg)

# 二.先序遍历

先序遍历与中序遍历相似，代码上只有一行不同，不同就在于输出的顺序。

## 步骤：

1. 初始化当前节点 **cur**为 **root**节点.

2. 如果 **cur**没有左孩子，则输出当前节点并将其右孩子作为当前节点,即 ```cur = cur->right```。

3. 如果 **cur**有左孩子，在当前节点 **cur**的左子树中找到当前节点 **cur**在 **中序遍历下的前驱节点**。

   a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。输出当前节点（在这里输出，这是与中序遍历唯一一点不同）。当前节点更新为当前节点的左孩子。

   b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空。当前节点更新为当前节点的右孩子。

4. 重复以上2、3直到 **cur**为空。

   ![先序遍历](./pic/pre_order_traversal.jpg)

   ```c++
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
   ```

   ## 复杂度分析

   时间复杂度与空间复杂度都与中序遍历时的情况相同。

   # 三.后序遍历

   后续遍历稍显复杂，需要建立一个临时节点 **dump**，令其左孩子是 **root**。并且还需要一个子过程，就是倒序输出某两个节点之间路径上的各个节点。

   ## 步骤：

   当前节点设置为临时节点 **dump**。

   1. 初始化当前节点 **cur**为 **root**节点.

   2. 如果 **cur**没有左孩子，则将其右孩子作为当前节点,即 ```cur = cur->right```。

   3. 如果 **cur**有左孩子，在当前节点 **cur**的左子树中找到当前节点 **cur**在中序遍历下的前驱节点。

      a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。

      b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空。 **倒序输出从当前节点的左孩子到该前驱节点这条路径上的所有节点**。当前节点更新为当前节点的右孩子。

   4. 重复以上2、3直到当前节点为空。

   ![后序遍历](./pic/post_order_traversal.jpg)

   ```c++
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
   ```

   ## 复杂度分析

   空间复杂度同样是 **O(1)**；时间复杂度也是 **O(n)**，倒序输出过程只不过是加大了常数系数。

   # 四. 代码

   ```c++
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
   ```

   ​