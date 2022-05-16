#include<bits/stdc++.h>
using namespace std;

bool del[1000], vis[1000];
int dis[1000], pre[1000];
char na[100], in[10000];
map<string, int> ot;
typedef struct {
	char name[100];
	char info[10000];
} VertexType;

typedef struct {
	VertexType vexs[1000];
	int arcs[100][100];
	int vexnum, arcnum;
	void printinfo() {
		for (int i = 1; i <= vexnum; i++) if (!del[i]) {
			printf("\t%3d. %s\n", i, vexs[i].name);
		}
	}
} MGraph;

MGraph G;

void f(char *s) {
	printf("---%*s%*s---\n", 10 + strlen(s) / 2, s, 10 - strlen(s) / 2, "");
}

void welcome() {
	f("欢迎来到安徽大学！");
	printf("\t1.查询景点信息\n\t2.问路查询\n\t3.增加一个顶点及相关信息\n\t4.修改一个顶点的相关信息\n\t5.增加一条新的路径\n\t6.退出\n\t7.删除一个顶点\n\t8.删除一条路径\n");
	f("安大校园导游系统");
	printf("请选择需要的服务：(1 ~ 8)\n");
}

void thanks() {
	printf("感谢你的使用，我们下次再见！\n");
}

void info() {
	printf("本校景点有：\n");
	G.printinfo();
	printf("请选择您需要查询的景点：(1 ~ %d)\n", G.vexnum);
}

void initwenlu() {
	printf("本校景点有：\n");
	G.printinfo();
	printf("请选择您的起点和终点，用一个空格隔开：(1 ~ %d) (1 ~ %d)\n", G.vexnum, G.vexnum);
}

void pp(int x, int y) {
	if (x != y) pp(pre[x], y);
	if (x == y) printf("%s", G.vexs[x].name); else printf(" -> %s", G.vexs[x].name);
}

void printpath(int a, int b) {
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= G.vexnum; i++) if (!del[i] && G.arcs[a][i] < dis[i]) {
		dis[i] = G.arcs[a][i];
		pre[i] = a;
	}
	vis[a] = 1;
	for (int i = 1; i < G.vexnum; i++) {
		int tot = 1e9, u = -1;
		for (int j = 1; j <= G.vexnum; j++) if (!del[j] && !vis[j] && dis[j] < tot) {
			tot = dis[j];
			u = j;
		}
		if (u == -1) {
			printf("%s -> %s 不通！\n", G.vexs[a].name, G.vexs[b].name);
			return;
		}
		else if (u == b) {
			printf("%s -> %s 一共需要 %d 步！\n", G.vexs[a].name, G.vexs[b].name, dis[u]);
			pp(b, a); printf("\n");
			return;
		}
        vis[u] = 1;
		for (int j = 1; j <= G.vexnum; j++) if (!del[j] && dis[u] + G.arcs[u][j] < dis[j]) {
			pre[j] = u;
			dis[j] = dis[u] + G.arcs[u][j];
		}
	}
}

void AddVertex() {
	printf("请分两行输入你想加入景点的名字和信息，名称和信息中不要有空白字符：\n");
	++G.vexnum;
	if (G.vexnum == 1000) {
		printf("错误：已超过最大顶点限度！");
		return;
	}
	//gets(G.vexs[G.vexnum].name);
	//gets(G.vexs[G.vexnum].info);
    scanf("%s%s", G.vexs[G.vexnum].name, G.vexs[G.vexnum].info);
}

void ChangeInfo() {
	printf("本校景点有：\n");
	G.printinfo();
	printf("请选择您想修改信息的景点编号：(1 ~ %d)\n", G.vexnum);
	int x;
	cin >> x;
	if (del[x]) {
		printf("错误：该顶点已被删除！");
		return;
	}
	printf("请问该景点的新信息是：\n");
	//gets(G.vexs[x].info);
    scanf("%s", G.vexs[x].info);
}

void Addegde() {
	printf("请输入你要加边的两个端点和长度，用空格隔开：\n");
	int x, y, z;
	cin >> x >> y >> z;
	G.arcs[x][y] = G.arcs[y][x] = min(z, G.arcs[x][y]);
	printf("加边成功：\n");
}

void EraseEdge() {
	printf("请输入你要删除的边的两个端点，用空格隔开：\n");
	int x, y;
	cin >> x >> y;
	G.arcs[x][y] = G.arcs[y][x] = 1.2e9;
	printf("删边成功！\n");
}

void EraseVertex() {
	printf("请输入你要删除的顶点：\n");
	int x;
	cin >> x;
	del[x] = 1;
	printf("删点成功！\n");
}

void init() {
	FILE *fp = fopen("graph.txt", "r");
	int n, m, d;
	fscanf(fp, "%d%d\n", &n, &m);
    memset(G.arcs, 0x3f, sizeof(G.arcs));
	G.vexnum = n;
	for (int i = 1; i <= n; i++) {
		fscanf(fp, "%s%s", na, in);
		strcpy(G.vexs[i].name, na); strcpy(G.vexs[i].info, in);
        ot[na] = i;
	}
	for (int i = 1; i <= m; i++) {
		fscanf(fp, "%s%s%d", na, in, &d);
		int u = ot[na], v = ot[in];
		G.arcs[u][v] = G.arcs[v][u] = d;
	}
	fclose(fp);
}

int main() {
	int x, a, b;
	init();
	while (1) {
		welcome();
		cin >> x;
		if (x == 6) {
			thanks();
			return 0;
		}
		else if (x == 1) {
			info();
			cin >> x;
			printf("%s\n", G.vexs[x].info);
		}
		else if (x == 2) {
			initwenlu();
			cin >> a >> b;
			if (del[a] || del[b]) {
				printf("错误：该顶点已被删除");
				continue;
			}
			printpath(a, b);
		}
		else if (x == 3) {
			AddVertex();
		}
		else if (x == 4) {
			ChangeInfo();
		}
		else if (x == 5) {
			Addegde();
		}
		else if (x == 7) {
			EraseVertex();
		}
		else if (x == 8) {
			EraseEdge();
		}
	}
	return 0;
}
