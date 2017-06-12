#include <iostream>
using namespace std;

typedef int elem_t;
/**
* @breif 交换数组中两个元素的位置
* @param[in] array 数组的首地址
* @param[in] start 下标
* @param[in] end 下标
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
* @breif 插入排序
* @param[in] array 欲排序的数组
* @param[in] n 数组的大小
* @return 无
*/
void
insertion_sort(elem_t array[], int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (array[j - 1] > array[j]) swap(array, j - 1, j);
			else break;
		}
	}
}

/**
* @breif 插入排序
* @param[in] array 欲排序的数组
* @param[in] n 数组的大小
* @return 无
*/
void
insertion_sort_ex(elem_t array[], int n)
{
	for (int i = 1; i < n; i++) {
		elem_t tmp = array[i];
		for (int j = i; j >= 0; j--) {
			if (array[j - 1] > tmp) {
				array[j] = array[j - 1];
			}
			else {
				array[j] = tmp;
				break;
			}
		}
	}
}


/**
 * @brief 寻找target在有序数组array的插入位置.
 * @param[in] array 数组的首地址
 * @param[in] start, end 数组下标
 * @param[in] target 欲插入的元素
 * @return 插入的位置
 */
int search_insert_pos(elem_t array[], int head, int tail, elem_t target)
{
	int mid;
	/*
	这里有一个点，需要提一下，那就是head 不可能大于tail，顶多会等于tail。可以这样来分析：
	mid = (head + tail) / 2,除非head == tail，否则mid不可能等于tail，然而head == tail
	是不可能通过while语句的，换个角度，mid是可以等于head，所以tail的最小值是head - 1
	*/
	while (head < tail) {
		mid = (head + tail) / 2;
		if (array[mid] == target) return mid;
		if (target < array[mid]) tail = mid - 1;
		else head = mid + 1;
	}
	// head == tail
	// tail < head
	if (target > array[head]) return head + 1;
	else return head;
}

/**
* @breif 插入排序
* @param[in] array 欲排序的数组
* @param[in] n 数组的大小
* @return 无
*/
void
insertion_sort_3(elem_t array[], int n)
{
	int k;
	for (int i = 1; i < n; ++i) {
		elem_t tmp = array[i];
		if (array[i - 1] <= tmp) k = i;
		else {
			k = search_insert_pos(array, 0, i - 1, tmp);
			for (int j = i; j > k; j--) {
				array[j] = array[j - 1];
			}
		}
		array[k] = tmp;
	}
}

void test()
{
	elem_t array[] = { 1, 2, 4, 9, 12, 12, 12 };
	int size = sizeof(array) / sizeof(elem_t);
	cout << search_insert_pos(array, 0, 5, 10) << endl;
	cout << search_insert_pos(array, 0, 5, 1) << endl;
	cout << search_insert_pos(array, 0, 5, 3) << endl;
	cout << search_insert_pos(array, 0, size - 1, 12) << endl;
}

int main()
{
	elem_t array[] = { 1, 5, 134, 123, 12, 11, 12 };
	int size = sizeof(array) / sizeof(elem_t);
	insertion_sort(array, size);
	for (int i = 0; i < size; ++i) {
		cout << array[i] << endl;
	}
	getchar();
}