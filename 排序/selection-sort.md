## 算法原理 ##
选择排序（Selection Sort）是一种简单直观的排序算法。它的工作原理如下，首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

选择排序的主要优点与数据移动有关。如果某个元素位于正确的最终位置上，则它不会被移动。选择排序每次交换一对元素，它们当中至少有一个将被移到其最终位置上，因此对n个元素的序列进行排序总共进行至多n-1次交换。在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。

![图片来源于维基百科](./pic/selection_sort_animation.gif)

<!--more-->
## 实例分析 ##
以数组 arr = [8, 5, 2, 6, 9, 3, 1, 4, 0, 7] 为例，先直观看一下每一步的变化，后面再介绍细节

第一次从数组 [8, 5, 2, 6, 9, 3, 1, 4, 0, 7] 中找到最小的数 0，放到数组的最前面（与第一个元素进行交换）：

``` html
                                min
                                 ↓
 8   5   2   6   9   3   1   4   0   7
 ↑                               ↑
 └───────────────────────────────┘
```

交换后：

``` html
 0   5   2   6   9   3   1   4   8   7
```

在剩余的序列中 [5, 2, 6, 9, 3, 1, 4, 8, 7] 中找到最小的数 1，与该序列的第一个个元素进行位置交换：

``` html
                        min
                         ↓
 0   5   2   6   9   3   1   4   8   7
     ↑                   ↑
     └───────────────────┘
```

交换后：

``` html
 0   1   2   6   9   3   5   4   8   7
```

在剩余的序列中 [2, 6, 9, 3, 5, 4, 8, 7] 中找到最小的数 2，与该序列的第一个个元素进行位置交换（实际上不需要交换）：

``` html
        min
         ↓
 0   1   2   6   9   3   5   4   8   7
         ↑
```

重复上述过程，直到最后一个元素就完成了排序。

``` html
                    min
                     ↓
 0   1   2   6   9   3   5   4   8   7
             ↑       ↑
             └───────┘

                            min
                             ↓
 0   1   2   3   9   6   5   4   8   7
                 ↑           ↑
                 └───────────┘

                        min
                         ↓
 0   1   2   3   4   6   5   9   8   7
                     ↑   ↑
                     └───┘


                        min
                         ↓
 0   1   2   3   4   5   6   9   8   7
                         ↑   

                                    min
                                     ↓
 0   1   2   3   4   5   6   9   8   7
                             ↑       ↑
                             └───────┘  

                                min
                                 ↓
 0   1   2   3   4   5   6   7   8   9
                                 ↑      

                                    min
                                     ↓
 0   1   2   3   4   5   6   7   8   9
                                     ↑ 
```


![图片来源于维基百科](./pic/Selection-Sort-Animation.gif)

## CPP 语言实现 ##


``` cpp
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
 * @brief 插入排序
 * @param[in] array 欲排序的数组
 * @param[in] len 数组的长度
 * @return 无
 */
void
selection_sort(elem_t array[], int len)
{
	int min_idx;
	elem_t min_val;
	for (int i = 0; i < len; ++i) {
		min_idx = i;
		min_val = array[i];
		for (int j = i + 1; j < len; ++j) {
			if (array[j] < min_val) {
				min_val = array[j];
				min_idx = j;
			}
		}
		/* 扫描完之后交换位置 */
		swap(array, i, min_idx);
	}
}
```

## 参考文章 ##
- [en.wikipedia.org](http://en.wikipedia.org/wiki/Selection_sort)
- [wikibooks](http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Selection_sort)
- [维基百科](http://zh.wikipedia.org/wiki/%E9%80%89%E6%8B%A9%E6%8E%92%E5%BA%8F)
- [Selection sort in JavaScript](http://techblog.floorplanner.com/post/20528548241/selection-sort-in-javascript)
- [直接选择排序(Straight Selection Sort)](http://student.zjzk.cn/course_ware/data_structure/web/paixu/paixu8.4.1.htm)
- [经典排序算法 - 选择排序 Selection Sort](http://www.cnblogs.com/kkun/archive/2011/11/23/2260281.html)
- [选择排序算法](http://sjjg.js.zwu.edu.cn/SFXX/paixu/paixu6.4.1.html)