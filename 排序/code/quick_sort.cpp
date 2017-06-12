#include <iostream>
using namespace std;

typedef int elem_t;


/**
* @breif 交换数组中两个元素的位置
* @param[in] array 数组的首地址
* @param[in] left 下标
* @param[in] right 下标
* @return 无
*/
inline void
swap(elem_t array[], int i, int j)
{
	elem_t tmp = array[j];
	array[j] = array[i];
	array[i] = tmp;
}

/**
 * @brief 在array数组的left到right的部分选择一个数作为切分数,并且排列该部分,使得切分数
 * 左侧的数全都小于等于切分数,切分点右侧的数全都大于等于切分数.
 * @param[in] array 欲切分的数组
 * @param[in] left, right 数组下标,需保证left < right
 * @return 排列后切分数的下标
 **/
int
partition(elem_t array[], int left, int right)
{
	int pivot_idx = (left + right) / 2;
	int pivot = array[pivot_idx];	/* 选择中心点元素作为pivot */
	int lidx = left, ridx = right - 1;


	swap(array, pivot_idx, right);
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

/**
* @brief partition的另外一个实现版本.
* @param[in] array 欲切分的数组
* @param[in] left, right 数组下标,需保证left < right
* @return 排列后切分数的下标
**/
int
partition_ex(elem_t array[], int left, int right)
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


/**
 * @brief 对array数组的left到right部分进行排序
 * @param[in] array 欲排序的数组
 * @param[in] left, right 数组的下标
 * @return 无
 **/
void
sort(elem_t array[], int left, int right)
{
	if (left > right) return;
	int pivot_idx = partition_ex(array, left, right);
	sort(array, left, pivot_idx - 1);
	sort(array, pivot_idx + 1, right);
}

/**
 * @brief 快速排序
 * @param[in] array 欲排序的数组
 * @param[in] len 数组的大小
 * @return 无
 */
void
quick_sort(elem_t array[], int len)
{
	sort(array, 0, len - 1);
}

int main()
{
	elem_t array[] = { 1, 2, 4, 99, 100, 120, 34, 48, 47, 36, 3, 1000, 45, 2, 3 };
	int size = sizeof(array) / sizeof(elem_t);
	quick_sort(array, size);
	for (int i = 0; i < size; ++i) {
		cout << array[i] << endl;
	}
	getchar();
}