#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @file priority_queue.c
 * @brief 一个利用小顶堆实现的优先队列
 * @author soulmachine@gmail.com
 */

typedef int heap_elem_t;

/**
 * @struct
 * @brief 堆结构的定义
 */
typedef struct heap_t {
	int size;	/* 实际元素的个数 */
	int capacity;	/* 容量 */
	heap_elem_t *elems;  /* 堆的数组 */
	int(*cmp)(const heap_elem_t*, const heap_elem_t*); /* 元素的比较函数 */
}heap_t;

int
cmp_int(const int *x, const int *y)
{
	const int sub = *x - *y;
	if (sub > 0) return 1;
	else if (sub < 0) return -1;
	else return 0;
}

/**
 * @brief 创建堆
 * @param[in] capacity 初始容量
 * @param[in] cmp 比较函数,小于返回-1.等于返回0,大于返回1
 * @return 成功返回堆对象的指针,失败返回NULL
 */
heap_t *
heap_create(const int capacity, int(*cmp)(const heap_elem_t*, const heap_elem_t*))
{
	heap_t* h = (heap_t *)malloc(sizeof(heap_t));
	h->size = 0;
	h->capacity = capacity;
	h->elems = (heap_elem_t *)malloc(capacity * sizeof(heap_elem_t));
	h->cmp = cmp;
	return h;
}

/**
 * @brief 销毁堆
 * @param[inout] h 堆对象的指针
 * @return 无
 */
void
heap_destroy(heap_t *h)
{
	free(h->elems);
	free(h);
}

/**
 * @brief 判断堆是否为空
 * @param[in] h 堆对象的指针
 * @return 如果为空,返回1,否则返回0
 */
int
heap_empty(heap_t *h)
{
	return h->size == 0;
}

/**
 * @brief 获取元素的个数
 * @param[in] h 堆对象的指针
 * @return 元素的个数
 */
int
heap_size(const heap_t *h)
{
	return h->size;
}

/**
 * @brief 由于堆中start位置元素的变化,有可能导致原先堆的性质不再,所以要将start位置处的元素
 * 调整到合适的位置,继续维护好堆的性质,这里实际上在自上而下调整父子节点.
 * @param[in] h 堆对象的指针
 * @param[in] start 开始节点的位置
 * @return 无
 */
void
heap_sift_down(const heap_t *h, const int start)
{
	int i = start;
	int j;
	const heap_elem_t tmp = h->elems[start];
	/* i节点的子节点为 2*i+1 以及 2*i+2 */
	for (j = 2 * i + 1; j < h->size; j = 2 * j + 1) {
		if (j < (h->size - 1) &&
			h->cmp(&(h->elems[j]), &(h->elems[j + 1])) > 0) {
			j++; /* j指向两子女中的小者 */
		}
		
		if (h->cmp(&tmp, &(h->elems[j])) <= 0) { /* 父节点的值小于子节点的较小值 */
			break; /* 不需要调整 */
		}
		else {
			h->elems[i] = h->elems[j]; /* 让较小的子节点浮上去 */
			i = j;
		}
	}
	h->elems[i] = tmp;
}

/**
 * @brief 由于堆中start位置处的元素发生了变化,有可能导致堆的性质不再,所以要将start位置处
 * 的元素调整到合适的位置上去,这里实际上在自下而上调整父子节点.
 * @param[in] h 堆对象的指针
 * @param[in] start 开始节点
 * @return 无
 */
void
heap_sift_up(const heap_t *h, const int start)
{
	int j = start;	/* j记录子节点的下标 */
	int i = (j - 1) / 2; /* i记录父节点的下标 */
	const heap_elem_t tmp = h->elems[start];

	while (j > 0) {
		if (h->cmp(&(h->elems[i]), &tmp) <= 0) { /* 父节点的值小于子节点,不需要调整 */
			break;
		}
		else {
			h->elems[j] = h->elems[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	h->elems[j] = tmp;
}

/**
 * @brief 往堆中添加一个元素
 * @param[in] h 堆对象的指针
 * @param[in] x 要添加的元素
 * @return 无
 */
void
heap_push(heap_t *h, const heap_elem_t x)
{
	if (h->size == h->capacity) {
		heap_elem_t * tmp = (heap_elem_t *)
			realloc(h->elems, h->capacity * 2 * sizeof(heap_elem_t));
		h->elems = tmp;
		h->capacity *= 2;
	}
	h->elems[h->size] = x; /* 将新加入的元素放在末尾 */
	h->size++;
	heap_sift_up(h, h->size - 1); /* 自下而上维持堆的性质 */
}

/**
 * @brief 弹出堆顶的元素
 * @param[in] h 堆对象的指针
 * @return 无
 */
void
heap_pop(heap_t *h)
{
	h->elems[0] = h->elems[h->size - 1]; /* 将h->elems[0]移除 */
	h->size--;
	heap_sift_down(h, 0); /* 自上而下维持堆的性质 */
}

/**
 * @brief 获取堆顶的元素
 * @param[in] h 堆对象的指针
 * @return 堆顶元素
 */
heap_elem_t
heap_top(const heap_t *h)
{
	return h->elems[0];
}

int main()
{
	heap_t *h = heap_create(100, cmp_int);
	heap_push(h, 100);
	heap_push(h, 55);
	heap_push(h, 150);
	printf("%d\n", heap_top(h));
	heap_pop(h);
	printf("%d\n", heap_top(h));
	heap_pop(h);
	printf("%d\n", heap_top(h));
	heap_pop(h);
	heap_destroy(h);
	getchar();
}