   #include<stdio.h>
#include<stdlib.h>
#define maxsize 100
typedef struct
{
	char *base;
	char *top;
	int stacksize;
}sqstack;

void initstack(sqstack s)//栈的初始化 
{
	s.base=(char*)malloc(maxsize*sizeof(char));
	if(!s.base)printf("分配失败");
	s.top=s.base;
	s.stacksize=maxsize;
}
void push(sqstack s,char e)//入栈 
{
	if(s.top-s.base==s.stacksize)printf("error");
	*s.top++=e;
}
void pop(sqstack s,char &e)//出栈 
{
	if(s.top==s.base)printf("error");
	e=*--s.top;
	s.top=NULL;
}
char gettop(sqstack s)//取栈顶元素 
{
	char e;
	e=*s.top;
	return e;
}
int in(char ch)//判断是否为运算符 
{
	 switch(ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '#':return 1;
        default:return 0;
    }
}
char precede(char ch,char c)//ch是栈顶字符,c 是表达式字符
{
    switch(ch)
    {
    case '+':
        if(c=='+')return '>';
        if(c=='-')return '>';
        if(c=='*')return '<';
        if(c=='/')return '<';
        if(c=='(')return '<';
        if(c==')')return '>';
        if(c=='#')return '>';
    case '-':
        if(c=='+')return '>';
        if(c=='-')return '>';
        if(c=='*')return '<';
        if(c=='/')return '<';
        if(c=='(')return '<';
        if(c==')')return '>';
        if(c=='#')return '>';
    case '*':
        if(c=='+')return '>';
        if(c=='-')return '>';
        if(c=='*')return '>';
        if(c=='/')return '>';
        if(c=='(')return '<';
        if(c==')')return '>';
        if(c=='#')return '>';
    case '/':
        if(c=='+')return '>';
        if(c=='-')return '>';
        if(c=='*')return '>';
        if(c=='/')return '>';
        if(c=='(')return '<';
        if(c==')')return '>';
        if(c=='#')return '>';
    case '(':
        if(c=='+')return '<';
        if(c=='-')return '<';
        if(c=='*')return '<';
        if(c=='/')return '<';
        if(c=='(')return '<';
        if(c==')')return '=';
        if(c=='#')return ' ';
    case ')':
        if(c=='+')return '>';
        if(c=='-')return '>';
        if(c=='*')return '>';
        if(c=='/')return '>';
        if(c=='(')return ' ';
        if(c==')')return '>';
        if(c=='#')return '>';
    case '#':
        if(c=='+')return '<';
        if(c=='-')return '<';
        if(c=='*')return '<';
        if(c=='/')return '<';
        if(c=='(')return '<';
        if(c==')')return ' ';
        if(c=='#')return '=';
    default:
        return '$';
    }
}



int operate(char a,char theta,char b)
{
	switch(theta)
	{
		case '+':return (a+b);
		case '-':return(a-b);
	    case '*':return(a*b);
        case '/':return(a/b);
		
	}
}

void output(sqstack s)
{
	while(s.top!=s.base)
	{
		printf("%c",*s.base++);
	}
 } 




int main()
{
	char a[maxsize];
	sqstack opnd,optr,queue;
	initstack(opnd);
	initstack(optr);
	initstack(queue);
	printf("输入字符串a: ");
    scanf("%s",a); 
    int i=0;
    char theta,b,c,x;
    push(optr,'#');
    while(a[i]!='#'||gettop(optr)!='#')
    {
    	if(!in(a[i]))
		{
    		push(opnd,a[i]);
    		push(queue,a[i]);
    		i++;
		}
		else
		switch(precede(gettop(optr),a[i]))
		{
			case'<':
				push(optr,a[i]);i++;
				break;
			case'>':
				pop(optr,theta);push(queue,theta);
				pop(opnd,b);pop(opnd,c);
				push(opnd,operate(c,theta,b));
				break;
			case'=':
				pop(optr,x);
				i++;
				break;
		}
	}
	i=gettop(opnd);
	output(queue);
	printf("\n%d",i);
	
}
