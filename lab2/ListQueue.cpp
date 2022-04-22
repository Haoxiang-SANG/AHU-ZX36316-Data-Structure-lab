#include<bits/stdc++.h>
using namespace std;

struct node {												// 单链表的一个节点
	node *next;
	int data;
};

struct LianDuiLie {											// 用单链表实现的队列，把它封装成一个类
	node *head, *tail;
	int cnt;
	void init() {											// 初始化，找到头节点，规定队列中的节点是 (head, tail]
		head = tail = (node*)malloc(sizeof(node));			
		head->data = 0;
		cnt = 0;
	}
	bool isempty() {										// head == tail，说明链表为空
		return head == tail;
	}
	void RuDui(int x) {										// 入队
		node *p = (node*)malloc(sizeof(node));
		p->data = x;
		tail->next = p;
		tail = p;
		cnt++;
	}
	void ChuDui() {											// 出队
		node *sb = head;
		head = head->next;
		delete(sb);
		--cnt;
	}
	int gethead() {											// 访问队头，注意队头实际上是 head 的下一个元素
		if (isempty()) return -1;
		return head->next->data;
	}
	int length() {											// 队列的长度，我直接用一个变量记录下来，并在插入删除的时候维护
		return cnt;	
	}
} q;

int main() {
	q.init();
	printf("q is empty? %c!\n", q.isempty() ? 'Y' : 'N');
	q.RuDui(-1); q.RuDui(12); q.RuDui(10);
	printf("Now the head of q is %d\n", q.gethead()); q.ChuDui();
	printf("The length of q is %d\n", q.length());
	q.RuDui(-3); q.RuDui(2); q.RuDui(-10);
	printf("The length of q is %d\n", q.length());
	while (!q.isempty()) {
		printf("%d ", q.gethead());
		q.ChuDui();
	}
	return 0;
}
