#include<bits/stdc++.h>
#define N 10005
#define ri int 
using namespace std;

char s[N];

int pri(char s) {
	if (s == '+' || s == '-') return 1;
	if (s == '*' || s == '/') return 2;
	if (s == '(') return -1;
	if (s == '#') return -2;
	return 100;
}

struct stackopt{
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

struct stackint{
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

void work() {
	double x2 = nus.top(); nus.pop(); 
	double x1 = nus.top(); nus.pop();
	char s = ops.top(); ops.pop();
	printf("%c ", s);
	if (s == '+') nus.push(x1 + x2);
	else if (s == '-') nus.push(x1 - x2);
	else if (s == '/') nus.push(x1 / x2);
	else if (s == '*') nus.push(x1 * x2);
}

int main() {
	while (scanf("%s", s + 1) == 1) {
		ops.init(); nus.init();
		for (ri i = 1, l = strlen(s + 1), ret = -1; i <= l; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				if (ret == -1) ret = 0;
				ret = ret * 10 + s[i] - '0';
			}
			else {
				if (ret != -1) {
					nus.push(ret);
					printf("%d ", ret);
					ret = -1;
				}
				if (s[i] == '#' && i != 1) {
					while (ops.top() != '#') work();
					ops.pop();
				}
				else if (s[i] == ')') {
					while (ops.top() != '(') work();
					ops.pop();
				}
				else if (s[i] == '(' || s[i] == '#' && i == 1) {
					ops.push(s[i]);
				}
				else {
					while (!ops.empty() && pri(ops.top()) >= pri(s[i])) work();
					ops.push(s[i]);
				}
			}
		}
		puts("");
		printf("%.5lf\n", nus.top());
	}
}
