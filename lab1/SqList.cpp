#include<bits/stdc++.h>								// 万能头文件
#define ri int 										// 个人习惯，把 register int 缩写成 int
using namespace std;								// 命名空间 std

typedef struct {									// 顺序表类
	int *elem;										// 起始位置
	int length, maxlength;							// 长度和最大长度

	void init() {									// 初始化
		elem = (int*)malloc(sizeof(int) * 100);   	// 先申请 100 个内存空间
		length = 0;								 	// 现在已经插入了 0 个元素
		maxlength = 100;							// 最长不超过 100 个元素
	}

	void insert(int x) {							// 在尾部插入元素
		*(elem + length++) = x;						// 给最后一个位置赋值，同时 length++
	}

	void print() {									// 输出每个元素
		for (ri i = 0; i < length; i++) printf("%d ", *(elem + i)); // 第 i 个元素的位置是 elem + i，间接访问
		puts("");									// 换行
	}

	bool empty() {									// 判断是否为空
		return length == 0;							// length == 0 说明为空
	}

	int visit(int x) {								// 访问第 x 个元素
		return *(elem + x - 1);						// 如果 x 从一开始，第 x 个元素的位置是 elem + x - 1
	}

	int find(int x) {								// 找值为 x 的元素在哪里，返回值是从 0 开始
		for (ri i = 0; i < length; i++) if (*(elem + i) == x) return i; // 找到了就返回 i
		return -1;									// 找不到返回 -1
	}

	void inserttheleftof(int p, int x) {			// 在 p 的左边插入 x
		for (ri i = length - 1; i >= p; i--) *(elem + i + 1) = *(elem + i);	// 把在新元素右边的所有元素统一向右边挪一个位置
		length++;									// 插入完成之后，多了一个元素
		*(elem + p) = x;							// 新元素的位置空出来，直接赋值
	}

	void erasetheindex(int p) {						// 删除这个位置的元素
		for (ri i = p + 1; i <= length - 1; i++) *(elem + i - 1) = *(elem + i); // 这个位置之后的元素统一向前挪一位
		length--;									// 删除这个位置的元素后，顺序表的长度 -1
	}

	int len() {										// 输出顺序表长度
		return length;								// 由定义，length 就是顺序表的长度
	}
} SqList;											// 这个类型的名称叫 SqList


SqList L;											// 创建对象 L

int main() {										// 主函数，按照题意操作即可。
	L.init();
	L.insert(-1); L.insert(21); L.insert(13); L.insert(24); L.insert(8);
	L.print();
	printf("L.len() = %d\n", L.len());
	if (L.empty()) puts("L is empty"); else puts("L isn't empty");
	printf("The 3-rd element: %d\n", L.visit(3));
	printf("The position of 24 : %d (from 0 to l - 1)\n", L.find(24));
	L.inserttheleftof(4 - 1, 0);					// 题目中的第 x 个元素我默认从 1 开始，先把它转换为从 0 开始
	L.print();
	L.erasetheindex(5 - 1);
	L.print();
	return 0;
}
