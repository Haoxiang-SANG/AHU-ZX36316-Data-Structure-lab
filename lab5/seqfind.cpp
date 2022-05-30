#include<bits/stdc++.h>
#define N 100050
#define ri register int
using namespace std;

typedef struct {
	int id; // 关键字
	char name[10];
	char sex[2];
	int age;
} record;

typedef struct {
	record stu[N];
	int num;
	void create() {
		num = 0;
		printf("Please input in id-ascending order (notice that id = 0 symbolize the end of the input)\n");
		printf("id\tname\tsex\tage\n");
		while (1) {
			int _id, _age;
			char _name[10], _sex[2];
			scanf("%d", &_id); if (!_id) break;
			scanf("%s %s %d", _name, _sex, &_age);
			strcpy(stu[num].name, _name); strcpy(stu[num].sex, _sex);
			//printf("%s", stu[num].name);
			stu[num].id = _id; stu[num].age = _age;
			num++;
		}
	}
	void print() {
		printf("The basic information of students are below:\n");
		for (ri i = 0; i < num; i++) {
			printf("%5d%5s%5s%5d\n", stu[i].id, stu[i].name, stu[i].sex, stu[i].age);
		}
	}
	int find(int number) {
		for (ri i = 0; i < num; i++) if (number == stu[i].id) return i;
		return -1;
	}
	int halffind(int number) {
		int lb = 0, rb = num - 1;
		while (lb <= rb) {
			int mid = (lb + rb) >> 1;
			if (stu[mid].id == number) return mid;
			if (stu[mid].id < number) lb = mid + 1; else rb = mid - 1;
		}
		return -1;
	}
} seqlist;

int main() {
	seqlist L;
	L.create();
	L.print();
	while (1) {
		printf("Please give the method you want to find: (0:seqfind / 1:halffind / 2:exit) ");
		int opt, x;
		scanf("%d", &opt);
		if (opt == 2) break;
		printf("Please give the number you are trying to find:");
		scanf("%d", &x);
		int loc = opt == 0 ? L.find(x) : L.halffind(x);
		if (loc == -1) {
			printf("Error: The number is unvalid!\n");
		}
		else {
			printf("The number you find is in the position %d\n", loc);
		}
	}
	return 0;
}
