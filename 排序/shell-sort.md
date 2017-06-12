
## 算法原理 ##
希尔排序算法是按其设计者希尔（Donald Shell）的名字命名，该算法由1959年公布，是插入排序的一种更高效的改进版本。它的作法不是每次一个元素挨一个元素的比较。而是初期选用大跨步（增量较大）间隔比较，使记录跳跃式接近它的排序位置；然后增量缩小；最后增量为 1 ，这样记录移动次数大大减少，提高了排序效率。希尔排序对增量序列的选择没有严格规定。

希尔排序是基于插入排序的以下两点性质而提出改进方法的：
- 插入排序在对几乎已经排好序的数据操作时， 效率高， 即可以达到线性排序的效率
- 但插入排序一般来说是低效的， 因为插入排序每次只能将数据移动一位

算法思路：
1. 先取一个正整数 d<sub>1</sub>(d<sub>1</sub> < n)，把全部记录分成 d<sub>1</sub> 个组，所有距离为 d<sub>1</sub> 的倍数的记录看成一组，然后在各组内进行插入排序
2. 然后取 d<sub>2</sub>(d<sub>2</sub> < d<sub>1</sub>)
3. 重复上述分组和排序操作；直到取 d<sub>i</sub> = 1(i >= 1) 位置，即所有记录成为一个组，最后对这个组进行插入排序。一般选 d<sub>1</sub> 约为 n/2，d<sub>2</sub> 为 d<sub>1</sub> /2， d<sub>3</sub> 为 d<sub>2</sub>/2 ，…， d<sub>i</sub> = 1。

![图片来自维基百科](./pic/shell-sort-animation.gif)

<!--more-->

## 实例分析 ##

假设有数组 array = [80, 93, 60, 12, 42, 30, 68, 85, 10]，首先取 d<sub>1</sub> = 4，将数组分为 4 组，如下图中相同颜色代表一组：

![](./pic/shell-sort-step1.1.png)

然后分别对 4 个小组进行插入排序，排序后的结果为：

![](./pic/shell-sort-step1.2.png)

然后，取 d<sub>2</sub> = 2，将原数组分为 2 小组，如下图：

![](./pic/shell-sort-step2.1.png)

然后分别对 2 个小组进行插入排序，排序后的结果为：

![](./pic/shell-sort-step2.2.png)

最后，取 d<sub>3</sub> = 1，进行插入排序后得到最终结果：

![](./pic/shell-sort-step3.png)

## CPP 语言实现 ##
按照惯例，下面给出了 cpp 的算法实现：

``` cpp
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
```

## 参考文章 ##
- [维基百科，自由的百科全书](http://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F)
- [希尔排序基本思想](http://student.zjzk.cn/course_ware/data_structure/web/paixu/paixu8.2.2.1.htm)
- [[演算法] 希爾排序法(Shell Sort)](http://notepad.yehyeh.net/Content/Algorithm/Sort/Shell/Shell.php)
- [算法系列15天速成——第三天 七大经典排序【下】](http://www.cnblogs.com/huangxincheng/archive/2011/11/20/2255695.html)
- [Algorithm Implementation/Sorting/Shell sort](http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Shell_sort)