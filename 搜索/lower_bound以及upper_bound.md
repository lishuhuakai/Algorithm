# lower_bound以及upper_bound

STL中实现了这两个算法,但是代码看起来非常晦涩,如果要快速写出这两个算法的话,参照STL的实现,恐怕会非常费劲.这里,我提供一种非常简洁的实现.

代码仅供参考.

## lower_bound

给定一个有序数组 **vals**, 寻找 **vals** 中第一个为 **k** 的值的下标,没有找到的话,返回 -1.
举个栗子, `vals = [0, 1, 1, 1, 2, 3]`, 那么 lower_bound应该返回 1.

下面的算法的思想很简单,简单的二分法查找,二分查找算法的关键在于,每一次迭代,查找的范围都必须缩小,也就是每一次要么是 **begin** 向前,要么是 **end** 后退,如果范围不缩小的话,很有可能出现无限迭代的情况.

查找的时候还有一个特别要注意的地方,那就是如果 `vals[mid] == k` 的话, 如果是一般的二分查找算法的话,此刻返回即可,但是我们要找的是第一个 **k**, 此刻将`end` 要更新为 `mid - 1`, ` end`无非两种可能,要么指向一个小于 **k** 的数, 这样的话, `vals[mid] < k` 总是成立,再加上 **while** 终止的条件,  `begin` 最终会等于 `end + 1` . 

另外一种情况是 `end` 指向的数等于 `k`, 这样的话,  `end` 在接下来的迭代中再次被更新为 `mid - 1`, 一直到 `end` 指向一个不等于 **k** 的数.

```cpp
int lower_bound(vector<int>& vals, int k) {
		/* 寻找第一个k */
		int begin = 0, end = vals.size() - 1;
		while (begin <= end) {
			/* begin不断向end逼近 */
			int mid = (begin + end) / 2;
			if (vals[mid] < k) {
				begin = mid + 1;
			}
			else if (vals[mid] > k) {
				end = mid - 1;
			}
			else { /* vals[mid] == k */
				end = mid - 1;
			}
		}
		return vals[begin] == k ? begin : -1;
}
```

## upper_bound

`upper_bound` 函数用于寻找有序数组 **vals** 中最后一个等于 **k** 的值的下标(从左向右扫描), 找不到的话,返回 -1.

下面的代码和上面的稍微有一点不同,当 `vals[mid] == k` 的时候,  `begin` 会被更新为 `mid + 1`, 此时的 `begin` 指向的数无非两种可能, 一种不等于 `k`, 这样的话,接下来的迭代中 `vals[mid] > k` 总是成立的, 加上 **while** 的递归终止条件 `begin <= end`, `end` 最终会等于 `begin - 1`.

另外一种情况是 `begin` 指向的数等于 `k`, 同上面一样的道理,接下来的迭代中,  `begin` 会继续向前靠拢.

```cpp
int upper_bound(vector<int>& vals, int k) {
		/* 寻找最后一个k */
		int begin = 0, end = vals.size() - 1;
		while (begin <= end) {
			int mid = (begin + end) / 2;
			if (vals[mid] < k) {
				begin = mid + 1;
			}
			else if (vals[mid] > k) {
				end = mid - 1;
			}
			else { /* vals[mid] == k */
				begin = mid + 1;
			}
		}
		return vals[end] == k ? end : -1;
	}

```

