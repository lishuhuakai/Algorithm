#include <iostream>
using namespace std;

typedef int elem_t;


/**
 * @breif 交换数组中两个元素的位置
 * @param[in] array 数组的首地址
 * @param[in] i 下标
 * @param[in] j 下标
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
 * @breif 冒泡排序
 * @param[in] array 欲排序的数组
 * @param[in] n 数组的大小
 * @return 无
 */
void 
bubble_sort(elem_t array[], int n)
{
	for (int i = n - 1; i > 0; --i) {
		for (int j = 0; j < i; j++) {
			if (array[j] > array[j + 1]) {
				swap(array, j, j + 1);
			}
		}
	}
}

int main()
{
	elem_t array[] = { 1, 5, 4, 3, 9, 144, 45, 99, 124 };
	int size = sizeof(array) / sizeof(elem_t);
	bubble_sort(array, size);
	for (int i = 0; i < size; ++i) {
		cout << array[i] << endl;
	}
	getchar();
}