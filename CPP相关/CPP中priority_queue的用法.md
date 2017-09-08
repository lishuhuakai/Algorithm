# CPP中priority_queue的用法

转载自[http://blog.chinaunix.net/uid-533684-id-2100009.html](http://blog.chinaunix.net/uid-533684-id-2100009.html)

**priority_queue** 调用 **STL** 里面的 make_heap(), pop_heap(), push_heap() 算法实现，也算是堆的另外一种形式。先写一个用 **STL** 里面堆算法实现的与真正的 **STL** 里面的 **priority_queue** 用法相似的 **priority_queue** ， 以加深对 **priority_queue** 的理解.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class priority_queue
{
private:
	vector<int> data;

public:
	void push(int t) {
		data.push_back(t);
		push_heap(data.begin(), data.end()); /* 将最后一个元素压入堆,然后进行堆调整 */
	}

	void pop() {
		pop_heap(data.begin(), data.end()); /* 将堆的第一个元素移动到最后,然后调整好前面的元素 */
		data.pop_back();
	}

	int top() { return data.front(); }
	int size() { return data.size(); }
	bool empty() { return data.empty(); }
};


int main()
{
	priority_queue test;
	test.push(3);
	test.push(5);
	test.push(2);
	test.push(4);

	while (!test.empty()) {
		cout << test.top() << endl;
		test.pop();
	}

	return 0;
}
```

几个函数的说明:

```cpp
// make_heap将[first, last)内的元素进行堆排序,compare可以省略,默认构造大顶堆,即最大的元素在第一个位置
template <class RandomAccessIterator, class Compare>
void make_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

// pop_heap将第一个元素移动到last之前的位置(最后一个位置),然后对剩余的元素进行堆调整 
template <class RandomAccessIterator, class Compare>
void pop_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

// push_heap将last之前的元素压入堆,然后进行堆调整
template <class RandomAccessIterator, class Compare>
void push_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```



**STL** 里面的 **priority_queue** 写法与此相似，只是增加了模板及相关的迭代器什么的。 

**priority_queue** 对于基本类型的使用方法相对简单。他的模板声明带有三个参数:

```cpp
priority_queue<Type, Container, Functional>
```

其中 **Type** 为数据类型，**Container** 为保存数据的容器，**Functional** 为元素比较方式。
**Container** 必须是用数组实现的容器，比如 **vector** , **deque** 但不能用 **list**.
**STL** 里面默认用的是 **vector**. 比较方式默认用 **operator<** , 所以如果你把后面俩个参数缺省的话，
优先队列就是大顶堆，队头元素最大。

如果要用到小顶堆，则一般要把模板的三个参数都带进去。
**STL** 里面定义了一个仿函数 `greater<>`，对于基本类型可以用这个仿函数声明小顶堆.

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>> q;
    
    for(int i= 0; i < 10; ++i) q.push(rand());
    while(!q.empty()){
        cout << q.top() << endl;
        q.pop();
    }
    
    getchar();
    return 0;
}
```

对于自定义类型，则必须自己重载 **operator<** 或者自己写仿函数.

```cpp
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int x, y;
    Node(int a, int b):x(a), y(b) {}
};

bool operator<(Node a, Node b)
{
    if (a.x == b.x) return a.y > b.y;
    return a.x> b.x; 
}

int main()
{
    priority_queue<Node> q;
    
    for(int i = 0; i < 10; ++i)
    q.push(Node(rand(), rand()));
    
    while(!q.empty()) {
        cout << q.top().x << ' ' << q.top().y << endl;
        q.pop();
    }
    
    getchar();
    return 0;
}
```

自定义类型重载 **operator<** 后，声明对象时就可以只带一个模板参数。
但此时不能像基本类型这样声明:
```cpp
priority_queue<Node, vector<Node>, greater<Node>>;
```
原因是  **greater<Node>** 没有定义，如果想用这种方法定义则可以按如下方式:
```cpp
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int x, y;
    Node( int a= 0, int b= 0 ): x(a), y(b) {}
};

struct cmp
{
    bool operator() ( Node a, Node b )
    {
        if(a.x == b.x) return a.y > b.y;
        
        return a.x> b.x; 
    }
};

int main()
{
    priority_queue<Node, vector<Node>, cmp> q;
    
    for( int i= 0; i< 10; ++i )
    q.push(Node(rand(), rand()));
    
    while(!q.empty())
    {
        cout << q.top().x << ' ' << q.top().y << endl;
        q.pop();
    }
    
    getchar();
    return 0;
} 
//以上代码实现的是一个小顶堆
```

