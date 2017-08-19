## 算法原理 ##

设有一组关键字｛K<sub>1</sub>， K<sub>2</sub>，…， K<sub>n</sub>｝；排序开始就认为 K<sub>1</sub> 是一个有序序列；让 K<sub>2</sub> 插入上述表长为 1 的有序序列，使之成为一个表长为 2 的有序序列；然后让 K<sub>3</sub> 插入上述表长为 2 的有序序列，使之成为一个表长为 3 的有序序列；依次类推，最后让 K<sub>n</sub> 插入上述表长为 n-1 的有序序列，得一个表长为 n 的有序序列。

具体算法描述如下：
1. 从第一个元素开始，该元素可以认为已经被排序
2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
4. 重复步骤 3，直到找到已排序的元素小于或者等于新元素的位置
5. 将新元素插入到该位置后
6. 重复步骤 2~5

如果比较操作的代价比交换操作大的话，可以采用[二分查找法](http://zh.wikipedia.org/wiki/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE%E6%B3%95)来减少比较操作的数目。该算法可以认为是插入排序的一个变种，称为**二分查找排序**。

二分查找法，是一种在有序数组中查找某一特定元素的搜索算法。搜素过程从数组的中间元素开始，如果中间元素正好是要查找的元素，则搜素过程结束；如果某一特定元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，而且跟开始一样从中间元素开始比较。如果在某一步骤数组为空，则代表找不到。这种搜索算法每一次比较都使搜索范围缩小一半。

![图片来自维基百科](./pic/Insertion_sort_animation.gif)

<!--more-->

## 实例分析 ##

现有一组数组 arr = [5, 6, 3, 1, 8, 7, 2, 4]，共有八个记录，排序过程如下：

``` html

    [5]   6   3   1   8   7   2   4
      ↑   │
      └───┘

    [5, 6]   3   1   8   7   2   4
    ↑        │
    └────────┘

    [3, 5, 6]  1   8   7   2   4
    ↑          │
    └──────────┘

    [1, 3, 5, 6]  8   7   2   4
               ↑  │
               └──┘

    [1, 3, 5, 6, 8]  7   2   4
                ↑    │
                └────┘

    [1, 3, 5, 6, 7, 8]  2   4
       ↑                │
       └────────────────┘

    [1, 2, 3, 5, 6, 7, 8]  4
             ↑             │
             └─────────────┘
 
    [1, 2, 3, 4, 5, 6, 7, 8]

```

其中有一点比较有意思的是，在每次比较操作发现新元素小于等于已排序的元素时，可以将已排序的元素移到下一位置，然后再将新元素插入该位置，接着再与前面的已排序的元素进行比较，这样做交换操作代价比较大。还有一个做法是，将新元素取出，从左到右依次与已排序的元素比较，如果已排序的元素大于新元素，那么将该元素移动到下一个位置，接着再与前面的已排序的元素比较，直到找到已排序的元素小于等于新元素的位置，这时再将新元素插入进去，就像下面这样：

![图片来自维基百科](./pic/Insertion-sort-example-300px.gif)

## CPP 语言实现 ##

直接插入排序 **CPP** 实现代码：

``` c++
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
```

下面这种方式可以减少交换次数：

``` cpp
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
```

利用二分查找法实现的插入排序，**二分查找排序**：

``` cpp
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
```

## 稳定性分析 ##

插入排序是一个 **稳定** 的排序算法．

仔细想一下插入排序的操作吧,插入排序是一个通过不断增加有序序列长度最终使得整个序列变得有序的排序算法，一般我们通过将紧接在有序序列后的元素 `a`  插入有序序列来增加其长度,算法的主体思想是, 从后向前扫描有序序列,将 `a` 插入到算法所碰到的第一个等于小于 `a` 的数的后面, 可以看得到,如果两个元素相等,它们的相对位置是不会发生变化的．


## 参考文章 ##

- [Wikipedia](http://en.wikipedia.org/wiki/Insertion_sort)
- [维基百科 - 插入排序](http://zh.wikipedia.org/wiki/%E6%8F%92%E5%85%A5%E6%8E%92%E5%BA%8F)
- [维基百科 - 二分查找法](http://zh.wikipedia.org/wiki/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE%E6%B3%95)
- [排序算法--折半插入排序（二分查找排序）](http://hualang.iteye.com/blog/1187110)
- [直接插入排序](http://sjjg.js.zwu.edu.cn/SFXX/paixu/paixu6.2.1.html)
- [直接插入排序基本思想](http://student.zjzk.cn/course_ware/data_structure/web/paixu/paixu8.2.1.1.htm)





