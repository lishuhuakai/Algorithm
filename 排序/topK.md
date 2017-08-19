# 最小的K个数

输入n个整数,输出其中最小的k个.举个栗子,如果输入 1, 2, 3, 4, 5, 6, 7, 8,那么最小的4个数字为 1, 2, 3, 4.

## 思路

这里介绍两种方法来解决这个问题.

### 堆排序

堆排序这种方法特别适用于海量的数据,而且还有一点好处,那就是不用一次性将所有数据全部读入内存.

首先,我们读入k个数,构建一个大小为k的最大堆,然后依次读入剩余的数据,如果当前数据比大根堆的堆顶要小,则用这个数来替换当前堆顶,并且调整堆,使其满足最大堆的性质,如果当前数据比大根堆的堆顶要大,那么可以抛弃掉这个数据.

这种方法的时间复杂度是 O(nlogk).

实现代码如下:

```cpp
typedef int elem_t;
const int MAX_SIZE = 1024;

/**
 * @brief 交换数组中两个下标的值
 * @param[in] array 数组的地址
 * @param[in] idx1 第一个下标
 * @param[in] idx2 第二个下标
 */
void
swap(elem_t array[], int idx1, int idx2)
{
	elem_t temp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = temp;
}

/**
* @brief 从数组idx下标开始的地方,维持好最大堆的性质
* @param[in] array 数组的地址
* @param[in] idx 下标
* @param[in] size 堆的大小
*/
void
max_heaplify(elem_t array[], int idx, int size)
{
	int greater_val_idx = idx; /* greater_val_idx记录父子节点中较大值的下标 */
	int lchild_idx = 2 * idx + 1, rchild_idx = 2 * idx + 2; /* 左孩子和右孩子的下标 */

	if (lchild_idx < size && array[idx] < array[lchild_idx]) {
		greater_val_idx = lchild_idx;
	}

	if (rchild_idx < size && array[greater_val_idx] < array[rchild_idx]) {
		greater_val_idx = rchild_idx;
	}

	if (greater_val_idx != idx) {
		swap(array, greater_val_idx, idx);
		max_heaplify(array, greater_val_idx, size);
	}
}


/**
 * @brief 构建最大堆
 * @param[in] array 数组
 * @param[in] size 数组的大小
 */
void
build_max_heap(elem_t array[], int size) {
	int parent_idx = (int)floor((size - 1) / 2);
	for (int i = parent_idx; i >= 0; i--) {
		max_heaplify(array, i, size);
	}
}


int solver(elem_t array[], int size, int k) {
	assert(k < MAX_SIZE);
	elem_t array_copy[MAX_SIZE];
	memcpy(array_copy, array, sizeof(elem_t) * k); /* 拷贝k个元素 */
	build_max_heap(array_copy, k);
	for (int i = k; i < size; i++) {
		if (array[i] >= array_copy[0]) continue;
		else {
			array_copy[0] = array[i];
			max_heaplify(array_copy, 0, k);
		}
	}
	return 0;
}
```

如果问题变成了找最大的k个数,解法很类似,只需要将最大堆变为最小堆即可.

### 快速排序
上面的问题其实也可以用快速排序来解决.

我们假设最小的k个数中最大的数为A,在快速排序算法中,我们先在数组中随机选择一个数字,然后调整数组中数字的顺序,使得比选中数字小的数字都排列在它的左边,比选中数字大的数字都排列在它的右边(一次快排).如果这个选中的数字的下标刚好是k - 1(下标从0开始),那么这个数字加上左侧的k-1个数字就是最小的k个数.

如果它的下标大于k-1,那么A位于它的左边,我们可以接着在它的左边部分的数组中查找,如果它的下标小于k - 1, 那么A应该位于它的右边,我们可以接着在它的右边部分的数组中查找.

代码实现如下:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

typedef int elem_t;

/**
 * @brief 交换数组中两个下标的值
 * @param[in] array 数组的地址
 * @param[in] idx1 第一个下标
 * @param[in] idx2 第二个下标
 */
void
swap(elem_t array[], int idx1, int idx2)
{
	elem_t temp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = temp;
}

/**
* @brief partition的另外一个实现版本.
* @param[in] array 欲切分的数组
* @param[in] left, right 数组下标,需保证left < right
* @return 排列后切分数的下标
**/
int
partition(elem_t array[], int left, int right)
{
	int pivot_idx = right;
	int pivot = array[right]; /* 直接选择最后一个元素作为pivot */
	int lidx = left, ridx = right - 1;

	for (; ;) {
		while (array[lidx] < pivot && lidx < right) lidx++;
		while (array[ridx] > pivot && ridx > lidx) ridx--;
		if (lidx < ridx)
			swap(array, lidx, ridx);
		else break;
	}
	swap(array, right, lidx);
	return lidx;
}


int solver(elem_t array[], int size, int k) {
	int left = 0, right = size - 1;
	int index = partition(array, left, right);

	while (index != k - 1) {
		if (index > k - 1) {
			right = index - 1;
			index = partition(array, left, right);
		}
		else {
			left = index + 1;
			index = partition(array, left, right);
		}
	}
	// array的前k个数即为所求
	return 0;
}
```

上面方法的时间复杂度为O(N).



