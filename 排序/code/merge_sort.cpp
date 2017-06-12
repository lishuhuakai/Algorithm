#include <iostream>
using namespace std;


typedef int elem_t;


/**
 * @brief 对array数组的left到right部分进行排序
 * @param[in] array 欲排序的数组
 * @param[in] left, right 数组的下标
 * @return 无
 */
void
sort(elem_t array[], int left, int right)
{
	if (right <= left) return; /* 递归终止条件 */
	int mid = (left + right) / 2;

	sort(array, left, mid); /* 分治法 */
	sort(array, mid + 1, right);

	/* array[left, mid]以及array[mid+1, right]都已经有序 */
	int l = left, h = mid + 1;
	while (l < h && h <= right) {
		/* l指向array[left, mid]这一边, h指向array[mid+1, right]这一边,
		 * 开始合并两个数组.这里的主题思想是,让array[left, mid]中较大的部分
		 * 迁移到右侧.
		 */
		if (array[l] >= array[h]) {
			elem_t tmp = array[h];
			for (int i = h - 1; i >= l; i--) {
				array[i + 1] = array[i]; 
			}
			array[l] = tmp;
			h++;
		}
		/* 不管交换与否,l总要向前移动 */
		l++;
	}
}


/**
 * @brief 归并排序
 * @param[in] array 欲排序的数组
 * @param[in] len 数组的大小
 * @return 无
 */
void
merge_sort(elem_t array[], int len)
{
	sort(array, 0, len - 1);
}

int main()
{
	elem_t array[] = { 1, 2, 4, 99, 100, 120, 34, 48, 47, 36, 3, 1000, 45, 2, 3 };
	int size = sizeof(array) / sizeof(elem_t);
	merge_sort(array, size);
	for (int i = 0; i < size; ++i) {
		cout << array[i] << endl;
	}
	getchar();
}
