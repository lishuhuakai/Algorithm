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
 * @brief 希尔排序
 * @param[in] array 欲排序的数组的首地址
 * @param[in] len 数组的长度
 * @return 无
 **/
void 
shell_sort(elem_t array[], int len)
{
	int gap = len / 2;
	while (gap > 0) {
		for (int i = gap; i < len; i++) {
			for (int j = i; 0 < j; j -= gap) {
				if (array[j - gap] > array[j])
					swap(array, j - gap, j);
				else
					break;
			}
		}
		gap = gap / 2;
	}
}

int main()
{
	elem_t array[] = { 1, 2, 4, 5, 100, 120, 34, 48, 47, 36, 3 };
	int size = sizeof(array) / sizeof(elem_t);
	shell_sort(array, size);
	for (int i = 0; i < size; ++i) {
		cout << array[i] << endl;
	}
	getchar();
}