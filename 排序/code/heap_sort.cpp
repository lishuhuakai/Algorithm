#include <iostream>
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
* @brief max_heaplify函数的非递归版本
* @param[in] array 数组的地址
* @param[in] idx 下标
* @param[in] size 堆的大小
*/
void max_heaplify_non_recursive(elem_t array[], int idx, int size)
{
	int greater_val_idx, lchild_idx, rchild_idx;
	while (true) {
		greater_val_idx = idx;
		lchild_idx = 2 * idx + 1;	/* 左孩子的下标 */
		rchild_idx = 2 * idx + 2;	/* 右孩子的下标 */

		if (lchild_idx < size && array[idx] < array[lchild_idx]) {
			greater_val_idx = lchild_idx;
		}

		if (rchild_idx < size && array[greater_val_idx] < array[rchild_idx]) {
			greater_val_idx = rchild_idx;
		}

		if (greater_val_idx != idx) {
			swap(array, greater_val_idx, idx);
			idx = greater_val_idx;
		}
		else break;
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

/**
 * @brief 堆排序
 * @param[in] array 待排序的数组
 * @param[in] size 数组的大小
 */
void
heap_sort(elem_t array[8], int size)
{
	build_max_heap(array, size); /* 构建最大堆 */
	for (int i = size - 1; i > 0; i--) {
		swap(array, 0, i);
		max_heaplify(array, 0, i);
	}
}

int main()
{
	elem_t array[] = { 1, 5, 6, 10, 8, 7, 99, 35 };
	int size = sizeof(array) / sizeof(elem_t);
	heap_sort(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << endl;
	}
	getchar();
}

