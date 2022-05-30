#include<bits/stdc++.h>
#define N 1050
#define ri register int
using namespace std;

struct record {
	int id;
	char name[10];
	char sex[2];
	int age;
	record *ch[2];
};

typedef struct {
	record *root;
	record stu[N];
	int num;

	void init() {
		root = (record*)malloc(sizeof(record));
		root->id = -2e9; root->ch[0] = root->ch[1] = NULL;
		root->ch[1] = (record*)malloc(sizeof(record));
		root->ch[1]->id = 2e9;
		root->ch[1]->ch[0] = root->ch[1]->ch[1] = NULL;
	}

	void insert(record *&cur, record *k) {
		if (!cur) {
			cur = k;
			cur->ch[0] = cur->ch[1] = NULL;
			printf("Successfully insert!\n");
			return;
		}
		if (k->id < cur->id) {
			insert(cur->ch[0], k);
		}
		else if (k->id > cur->id) {
			insert(cur->ch[1], k);
		}
		else if (k->id == cur->id) {
			puts("Invalid input!");
			return;
		}
	}
	
	void insert1() {
		printf("id\tname\tsex\tage\n");
		record *t = (record*)malloc(sizeof(record));
		int _id, _age; char _name[10], _sex[2];
		scanf("%d %s %s %d", &_id, _name, _sex, &_age);
		t->id = _id; t->age = _age;
		t->ch[0] = t->ch[1] = NULL;
		strcpy(t->name, _name); strcpy(t->sex, _sex);
		insert(root, t);
	}

	void find1(record *cur, int x) {
		if (!cur) {
			printf("Invalid input!\n");
			return;
		}
		if (x == cur->id) {
			printf("Find! %5d%5s%5s%5d\n", cur->id, cur->name, cur->sex, cur->age);
			return;
		}
		else if (cur->id > x) find1(cur->ch[0], x); else find1(cur->ch[1], x);
	}
	void find() {
		int x;
		printf("Please input the number you want to find\n");
		scanf("%d", &x);
		find1(root, x);
	}
	void create() {
		//puts("72");
		init();
		num = 1;
		printf("Please input in id-ascending order (notice that id = 0 symbolize the end of the input)\n");
		printf("id\tname\tsex\tage\n");
		while (1) {
			int _id, _age;
			char _name[10], _sex[2];
			scanf("%d", &_id); if (!_id) break;
			scanf("%s %s %d", _name, _sex, &_age);
			strcpy(stu[num].name, _name); strcpy(stu[num].sex, _sex);
			stu[num].ch[0] = stu[num].ch[1] = NULL;
			stu[num].id = _id; stu[num].age = _age;
			num++;
		}
		create1(root->ch[1]->ch[0], 1, num - 1);
	}
	void create1(record *&cur, int lb, int rb) {
		if (rb < lb) {
			cur = NULL;
			return;
		}
		int mid = (lb + rb) >> 1;
		cur = &stu[mid];
		create1(cur->ch[0], lb, mid - 1);
		create1(cur->ch[1], mid + 1, rb);
	}

	void print1(record *cur) {
		if (!cur) return;
		print1(cur->ch[0]);
		if (strlen(cur->name)) {
			printf("%5d%5s%5s%5d\n", cur->id, cur->name, cur->sex, cur->age);
		}
		print1(cur->ch[1]);
	}

	void print() {
		printf("The basic information of students are below:\n");
		print1(root);
	}
} bst;

int main() {
	bst T;
	T.create();
	T.print();
	while (1) {
		printf("Please give the instructions you want to do: (0:insert / 1:find / 2:exit) ");
		int opt;
		scanf("%d", &opt);
		if (opt == 2) break;
		if (opt == 0) {
			T.insert1();
			T.print();
		}
		if (opt == 1) {
			T.find();
		}
	}
	return 0;
}
