#include<bits/stdc++.h>
#define ri register int
using namespace std;

struct HNode {									// 链表的节点类型
	int data;
	struct HNode *next;
};

struct Linklist {								// 链表类型，只需要一个头节点。
	HNode *head;
	void init() {								// 初始化，我们需要申请头结点的空间，并且把头结点的 next 域置为 NULL
		head = (HNode*)malloc(sizeof(HNode));
		head->next = NULL;
	}

	void insert(int x) {						// 插入元素时，注意题目要求的是头插法，新的元素在链表头
		HNode *t = (HNode*)malloc(sizeof(HNode));
		t->data = x;
		t->next = head->next;
		head->next = t;
	}

	void print() {								// 输出链表：依次遍历
		for (HNode *i = head->next; i != NULL; i = i->next) {
			printf("%d ", i->data);
		}
		puts("");
	}

	int len(int ret = 0) {						// 链表的长度：在遍历的过程中顺便计数
		for (HNode *i = head->next; i; i = i->next) {
			ret++;
		}
		return ret;
	}

	int empty() {								// 判断链表是否为空，就是判断链表的长度是否为 0
		return len() == 0;
	}

	int visit(int p, int ret = 0) {				// 访问链表的第 p 个元素，我们需要一个计数器记录现在访问的是第几个元素
		for (HNode *i = head->next; i; i = i->next) {
			if (ret == p) return i->data;
			ret++;
		}
		return -1;								// 没有找到第 p 个元素，返回 -1 代表出错，提高程序的鲁棒性
	}

	int find(int x, int ret = 0) {				// 查找 data 域为 x 的节点的序号，我们也需要遍历
		for (HNode *i = head->next; i; i = i->next) {
			if (i->data == x) return ret;		// 找到了，就返回
			ret++;
		}
		return -1;								// 找不到，报错
	}

	void inserttheLeftof(int p, int x, int ret = -1) {	// 在第 p 个元素的左端插入（p 从 0 开始）
		for (HNode *i = head; i; i = i->next) {			// 这里从 head 开始算，把 head 记为第 -1 个元素
			if (ret == p - 1) {							// 因为在第 p 个元素的左端插入需要找到第 p - 1 个元素
				HNode *t = (HNode*)malloc(sizeof(HNode));
				t->next = i->next;
				t->data = x;
				i->next = t;
				return;
			}
			ret++;
		}
		if (ret == p - 1) insert(x);					// 在最后的元素后面插入，需要特判，调用 insert
	}

	void erasetheindex(int p, int ret = -1) {			// 将第 p 个元素删去，也需要找第 p - 1 个元素
		for (HNode *i = head; i; i = i->next) {
			if (ret == p - 1) {
				HNode *p = i->next;
				i->next = i->next->next;
				delete(p);
				return;
			}
			ret++;
		}
	}

} H;

int main() {
	H.init();
	H.insert(-1);  H.insert(21); H.insert(13); H.insert(24); H.insert(8);
	H.print();
	printf("H.Hen() = %d\n", H.len());
	if (H.empty()) puts("H is empty"); else puts("H isn't empty");
	printf("The 3-rd element: %d\n", H.visit(3 - 1));
	printf("The position of 24 : %d (from 0 to l - 1)\n", H.find(24));
	H.inserttheLeftof(4 - 1, 0);	// 题目中的“第 i 个元素”，我认为是从 1 开始的
	H.print();						// 而我在处理中，我认为从 0 开始，所以需要把 x - 1
	H.erasetheindex(5 - 1);			// 我的返回值也是从 0 开始。
	H.print();
	return 0;
}
