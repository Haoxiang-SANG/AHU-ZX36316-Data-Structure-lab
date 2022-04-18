#include<stdio.h>
#include<stdlib.h>
typedef struct qnode
{
	int data;
	struct qnode *next;
 }qnode,*queueptr;
 typedef struct
 {
 	queueptr front;
 	queueptr rear;
 }linkqueue;
 
 
 void initqueue(linkqueue *q)//初始化 
 {
 	q->front=q->rear=(queueptr)malloc(sizeof(qnode));
 	q->front->next=NULL;
 	printf("init ok\n");
 }
 
 
 void isempty(linkqueue q)//判断是否为空队
 {
 	if(q.front==q.rear)
 	printf("empty\n");
 	else printf("inempty\n");
  } 
  
  
 void  input(linkqueue *q)//输入待输入的队和元素个数
  {
  	queueptr p;
  	p=(queueptr)malloc(sizeof(qnode));
  	scanf("%d",&p->data);
  	p->next=NULL;
  	q->rear->next=p;
  	q->rear=p;
   } 
   
   
   int dequeue(linkqueue q)
   {
   	if(q.front==q.rear)
	{
	   printf("error");
	   return 0;
	}
	qnode *p;
	p=q.front->next;
	int e;
	e=p->data;
	q.front->next=p->next;
	if(q.rear==p)q.rear=q.front;
	delete p;
	return e;
   }
   
   
   
   void length(linkqueue q)//求队长度 
   {
   	int i=0;
   	while(q.front!=q.rear)
   	{
   		q.front=q.front->next;
   		i++;
	   }
   	printf("the length is %d",i);
   }
   
   void getqueue(linkqueue q)
   {
   	while(q.front!=q.rear)
   	{
	   printf("%d\t",q.front->next->data);
	   q.front=q.front->next;
}
   }
   
   
   int main()
   {
   	int n,i,x;
   	linkqueue q;
   	initqueue(&q);
   	isempty(q);
   	printf("input the number of elemnts to be inputed:");
   	scanf("%d",&n);
   	for(i=1;i<=n;i++)
   	{
   	 input(&q);
	}
	x=dequeue(q);
	printf("the elemnt to be outputted is%d",x);
   length(q);
   printf("input the number of elemnts to be inputed:");
   	scanf("%d",&n);
   	for(i=1;i<=n;i++)
   	{
   	 input(&q);
	}
	 length(q);
	 getqueue(q);
	 }
