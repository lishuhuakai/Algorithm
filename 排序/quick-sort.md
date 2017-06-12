## 算法原理 ##

快速排序是图灵奖得主[ C. R. A. Hoare](http://zh.wikipedia.org/wiki/%E6%9D%B1%E5%B0%BC%C2%B7%E9%9C%8D%E7%88%BE) 于 1960 年提出的一种划分交换排序。它采用了一种分治的策略，通常称其为[分治法(Divide-and-ConquerMethod)](http://en.wikipedia.org/wiki/Quicksort)。

![C. R. A. Hoare](./pic/C.R.A.Hoare.jpg)

分治法的基本思想是：将原问题分解为若干个规模更小但结构与原问题相似的子问题。递归地解这些子问题，然后将这些子问题的解组合为原问题的解。

利用分治法可将快速排序的分为三步：

1. 在数据集之中，选择一个元素作为"基准"（pivot）。
2. 所有小于"基准"的元素，都移到"基准"的左边；所有大于"基准"的元素，都移到"基准"的右边。这个操作称为[分区 (partition) 操作](http://en.wikipedia.org/wiki/Quicksort)，分区操作结束后，基准元素所处的位置就是最终排序后它的位置。
3. 对"基准"左边和右边的两个子集，不断重复第一步和第二步，直到所有子集只剩下一个元素为止。
  ![图片来自维基百科](./pic/Sorting_quicksort_anim.gif)
  <!--more-->
  分区是快速排序的主要内容，用伪代码可以表示如下：

``` javaScript
function partition(a, left, right, pivotIndex)
     pivotValue := a[pivotIndex]
     swap(a[pivotIndex], a[right]) // 把 pivot 移到結尾
     storeIndex := left
     for i from left to right-1
         if a[i] < pivotValue
             swap(a[storeIndex], a[i])
             storeIndex := storeIndex + 1
     swap(a[right], a[storeIndex]) // 把 pivot 移到它最後的地方
     return storeIndex // 返回 pivot 的最终位置
```

首先，把基准元素移到結尾（如果直接选择最后一个元素为基准元素，那就不用移动），然后从左到右（除了最后的基准元素），循环移动小于等于基准元素的元素到数组的开头，每次移动 storeIndex 自增 1，表示下一个小于基准元素将要移动到的位置。循环结束后 storeIndex 所代表的的位置就是基准元素的所有摆放的位置。所以最后将基准元素所在位置（这里是 right）与 storeIndex 所代表的的位置的元素交换位置。要注意的是，一个元素在到达它的最后位置前，可能会被交换很多次。

一旦我们有了这个分区算法，要写快速排列本身就很容易：

``` javaScript
 procedure quicksort(a, left, right)
     if right > left
         select a pivot value a[pivotIndex]
         pivotNewIndex := partition(a, left, right, pivotIndex)
         quicksort(a, left, pivotNewIndex-1)
         quicksort(a, pivotNewIndex+1, right)
```

## 实例分析 ##

举例来说，现有数组 arr = [3,7,8,5,2,1,9,5,4]，分区可以分解成以下步骤：

1. 首先选定一个基准元素，这里我们元素 5 为基准元素（基准元素可以任意选择）：

``` html
            pivot
              ↓
  3   7   8   5   2   1   9   5   4
```

2. 将基准元素与数组中最后一个元素交换位置，如果选择最后一个元素为基准元素可以省略该步：

``` html
                                pivot
                                  ↓
  3   7   8   4   2   1   9   5   5
```

3. 从左到右（除了最后的基准元素），循环移动小于基准元素 5 的所有元素到数组开头，留下大于等于基准元素的元素接在后面。在这个过程它也为基准元素找寻最后摆放的位置。循环流程如下：

  循环 i == 0 时，storeIndex == 0，找到一个小于基准元素的元素 3，那么将其与 storeIndex 所在位置的元素交换位置，这里是 3 自身，交换后将 storeIndex 自增 1，storeIndex == 1：

  ``` html
                                pivot
                                  ↓
  3   7   8   4   2   1   9   5   5
  ↑
  storeIndex
  ```
```

  循环 i == 3 时，storeIndex == 1，找到一个小于基准元素的元素 4：

  ``` html
      ┌───────┐                 pivot
      ↓       ↓                   ↓
  3   7   8   4   2   1   9   5   5
      ↑       ↑
 storeIndex   i
```

  交换位置后，storeIndex 自增 1，storeIndex == 2：

  ``` html
                                pivot
                                  ↓
  3   4   8   7   2   1   9   5   5
          ↑           
     storeIndex
  ```

  循环 i == 4 时，storeIndex == 2，找到一个小于基准元素的元素 2：

  ``` html
          ┌───────┐             pivot
          ↓       ↓               ↓
  3   4   8   7   2   1   9   5   5
          ↑       ↑
     storeIndex   i
  ```

  交换位置后，storeIndex 自增 1，storeIndex == 3：

  ``` html
                                pivot
                                  ↓
  3   4   2   7   8   1   9   5   5
              ↑           
         storeIndex       
  ```


  循环 i == 5 时，storeIndex == 3，找到一个小于基准元素的元素 1：

  ``` html
              ┌───────┐         pivot
              ↓       ↓           ↓
  3   4   2   7   8   1   9   5   5
              ↑       ↑
         storeIndex   i
  ```

  交换后位置后，storeIndex 自增 1，storeIndex == 4：

  ``` html
                                pivot
                                  ↓
  3   4   2   1   8   7   9   5   5
                  ↑           
             storeIndex        
  ```

  循环 i == 7 时，storeIndex == 4，找到一个小于等于基准元素的元素 5：

  ``` html
                  ┌───────────┐ pivot
                  ↓           ↓   ↓
  3   4   2   1   8   7   9   5   5
                  ↑           ↑
             storeIndex       i      
  ```

  交换后位置后，storeIndex 自增 1，storeIndex == 5：

  ``` html
                                pivot
                                  ↓
  3   4   2   1   5   7   9   8   5
                      ↑           
                 storeIndex          
  ```


4. 循环结束后交换基准元素和 storeIndex 位置的元素的位置：

``` html
                    pivot
                      ↓
  3   4   2   1   5   5   9   8   7
                      ↑           
                 storeIndex          
```

  那么 storeIndex 的值就是基准元素的最终位置，这样整个分区过程就完成了。

  引用[维基百科](http://en.wikipedia.org/wiki/Quicksort)上的一张图片：

  ![图片来自维基百科](./pic/Partition_example.svg.png)


## cpp 语言实现 ##
按照[维基百科](http://en.wikipedia.org/wiki/Quicksort)中的原地(in-place)分区版本，实现快速排序方法如下：

```cpp
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
 ***/
void
quick_sort(elem_t array[], int len)
{
	sort(array, 0, len - 1);
}
```



## 参考文章 ##
- [wiki Quicksort](http://en.wikipedia.org/wiki/Quicksort)
- [维基百科 - 快速排序](http://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)
- [快速排序（Quicksort）的Javascript实现](http://www.ruanyifeng.com/blog/2011/04/quicksort_in_javascript.html)
- [Quicksort in JavaScript](http://www.cnblogs.com/ethanzheng/archive/2013/02/20/quicksort-in-javascript.html)
- [经典排序算法 - 快速排序Quick sort](http://www.cnblogs.com/kkun/archive/2011/11/23/2260270.html)
- [快速排序(QuickSort)](http://student.zjzk.cn/course_ware/data_structure/web/paixu/paixu8.3.2.1.htm)
- [ソートアルゴリズムを映像化してみた](http://jsdo.it/norahiko/oxIy/fullscreen)
- [Stable quicksort in Javascript](http://acatalept.com/blog/2008/10/28/stable-quicksort-in-javascript/)
- [Friday Algorithms: Quicksort – Difference Between PHP and JavaScript](http://www.stoimen.com/blog/2010/06/11/friday-algorithms-quicksort-difference-between-php-and-javascript/)