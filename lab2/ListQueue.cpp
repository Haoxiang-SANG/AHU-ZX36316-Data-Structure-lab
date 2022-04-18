#include<bits/stdc++.h>
using namespace std;

struct node {
	node *next;
	int data;
};

struct LianDuiLie {
	node *head, *tail;
	int cnt;
	void init() {
		head = tail = (node*)malloc(sizeof(node));
		head->data = 0;
		cnt = 0;
	}
	bool isempty() {
		return head == tail;
	}
	void RuDui(int x) {
		node *p = (node*)malloc(sizeof(node));
		p->data = x;
		tail->next = p;
		tail = p;
		cnt++;
	}
	void ChuDui() {
		node *sb = head;
		head = head->next;
		delete(sb);
		--cnt;
	}
	int gethead() {
		if (isempty()) return -1;
		return head->next->data;
	}
	int length() {
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
