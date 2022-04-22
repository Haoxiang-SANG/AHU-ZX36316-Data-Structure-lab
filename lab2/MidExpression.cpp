#include<bits/stdc++.h>
#define N 10005
#define ri int 
using namespace std;

char s[N];

int pri(char s) {								// 定义优先级，+- 为 1，*/ 为 2，而其他的无所谓。
	if (s == '+' || s == '-') return 1;
	if (s == '*' || s == '/') return 2;
	if (s == '(') return -1;
	if (s == '#') return -2;
	return 100;
}

struct stackopt{								// 操作符的栈
	char s[N];
	int tp;
	void init() {
		tp = 0;
	}
	bool empty() {
		return tp == 0;
	}
	void push(char x) {
		s[++tp] = x;
	}
	void pop() {
		tp--;
	}
	char top() {
		return s[tp];
	}
} ops;

struct stackint{								// 操作数的栈
	double s[N];
	int tp;
	void init() {
		tp = 0;
	}
	void push(double x) {
		s[++tp] = x;
	}
	void pop() {
		--tp;
	}
	double top() {
		return s[tp];
	}
} nus;

void work() {									// 进行一次运算
	double x2 = nus.top(); nus.pop(); 
	double x1 = nus.top(); nus.pop();
	char s = ops.top(); ops.pop();
	printf("%c ", s);							// 这里是输出运算符，因为要输出后缀表达式
	if (s == '+') nus.push(x1 + x2);
	else if (s == '-') nus.push(x1 - x2);
	else if (s == '/') nus.push(x1 / x2);
	else if (s == '*') nus.push(x1 * x2);
}

int main() {
	while (scanf("%s", s + 1) == 1) {
		ops.init(); nus.init();
		for (ri i = 1, l = strlen(s + 1), ret = -1; i <= l; i++) {
			if (s[i] >= '0' && s[i] <= '9') {	// 遇到数字读入，我这样写是为了支持 2 位及以上的数字
				if (ret == -1) ret = 0;
				ret = ret * 10 + s[i] - '0';
			}
			else {
				if (ret != -1) {				// 遇到数字，进栈，并且直接输出
					nus.push(ret);
					printf("%d ", ret);
					ret = -1;
				}
				if (s[i] == '#' && i != 1) {	// 遇到最后一个 #，弹栈直到第一个 #
					while (ops.top() != '#') work();
					ops.pop();
				}
				else if (s[i] == ')') {			// 遇到 )，弹栈到第一个左括号
					while (ops.top() != '(') work();
					ops.pop();
				}
				else if (s[i] == '(' || s[i] == '#' && i == 1) {	// 遇到第一个 # 或者 (，无条件进栈
					ops.push(s[i]);
				}
				else {
					while (!ops.empty() && pri(ops.top()) >= pri(s[i])) work();		// 遇到操作符，维护操作符栈的单调性。
					ops.push(s[i]);
				}
			}
		}
		puts("");
		printf("%.5lf\n", nus.top());			// 最后的结果就是数字栈的唯一一个元素
	}
}
