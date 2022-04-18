#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAXSIZE 3
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct
{
	int *top;
	int *base;
	int stacksize;
}sqstack;

//初始化 
Status InitStack(sqstack &S)
{
	S.base=(int*)malloc(MAXSIZE*sizeof(int));
	if(!S.base) return ERROR;
	S.top=S.base;
	S.stacksize=MAXSIZE;
	return OK;
} 

//入栈 1
Status Push1(sqstack &S,char &e)
{
	if(S.top-S.base==MAXSIZE) return ERROR;
	*S.top++==e;
	return OK;
}

//入栈 2
Status Push2(sqstack &S,float &e)
{
	if(S.top-S.base==MAXSIZE) return ERROR;
	*S.top++==e;
	return OK;
}

//出栈
Status Pop(sqstack &S,char &e)
{
	if(S.top==S.base) return ERROR;
	e=*--S.top;
	return OK;
}

//取栈顶元素 
char GetTop(sqstack S,char &e)
{
	if(S.top==S.base) return ERROR;
	e=*--S.top;
	S.top++;
	return e;
}


//判断运算符的优先级 
char precede(char a,char b){  


	if(a=='#'){
		if(b=='#'){
			return '=';
		}else{
			return '<'; //除了读入字符是#的情况，其余情况都是栈顶元素优先级较低，返回 < 
		}
	}
	//当栈顶元素为 + 或者 - 时，情况一样 
	if(a=='+'||a=='-'){
		if(b=='+'||b=='-'||b==')'||b=='#'){  //这种情况是栈顶优先级较高，返回 > 
			return '>'; 
		}else{
			return '<';
		}
	}
	//当栈顶元素为 * 或者 / 时，情况一样 
	if(a=='*'||a=='/'){
		if(b=='('){
			return '<'; 
		}else{
			return '>';
		}
	}
	//当栈顶元素为 ( 时，情况如下 
	if(a=='('){
		if(b==')'){
			return '=';
		}else{
			return '<';
		}
	}
	//当栈顶元素为 ) 时，情况如下 
	if(a==')'){
		return '>';
	}
} 

int in(char ch)
{
	 switch(ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '#':return 1;//是运算符返回1 
        default:return 0;//不是运算符返回0 
    }
}

float Operate(char X,char ch,char Y)
{
	float z;
	int x,y;
	x=X-'0';y=Y-'0';
	switch(ch)
	{
		case '+':z=x+y;break;
		case '-':z=x-y;break;
		case '*':z=x*y;break;
		case '/':z=x/y;break;
	}
	return z;
}

//将中缀表达式转换为后缀表达式 
char* transform (char exp[10]) 
{
	int i,j=0;
	char ch,x1,x2,x3,e,postfix[10];
	sqstack OPTR;
	sqstack OPND;
	InitStack(OPTR);
	InitStack(OPND);
	e='#';
	Push1(OPTR,e);
	for(i=0;exp[i]!='#'||GetTop(OPTR,e)!='#';i++)
	{
		ch=exp[i];
		if(in(ch)==0)
		{
			postfix[j]=ch;
			j++;
		}
		else 
		{
			GetTop(OPTR,x1);
			x2=ch;
			x3=precede(x1,x2);
			switch(x3)
			{
				case'<':Push1(OPTR,ch);break;
				case'>':Pop(OPTR,e);postfix[j]=e;j++;break;
				case'=':Pop(OPTR,e);break;
			}	
		}
	}

	return postfix;
}


char EvaluateExpression(char exp[10])
{
	int i=1;
	char ch,e,X,Y;
	float z;
	sqstack OPTR;
	sqstack OPND;
	InitStack(OPTR);
	InitStack(OPND);
	ch=exp[0];
	while(ch!='#')
	{
		if(in(ch)==0)
		{
			Push1(OPND,ch);
		}
		else  
		{
			Pop(OPND,Y);
			Pop(OPND,X);
			z=Operate(X,ch,Y);
			Push2(OPND,z);
		}
		ch=exp[i];
		i++;
	}
	GetTop(OPND,e);
	return e;
}

int main()
{
	int i; 
	char exp[3][10],*exp1;
	float result[3];
	
	printf("请输入三组中缀表达式：");
	for(i=0;i<=0;i++)
	{
		scanf("%s",exp[i]);
	}
	for(i=0;i<=0;i++)
	{
		printf("1\n");
		//exp1=transform(exp[i]);
		transform(exp[i]);
		printf("2");
		//result[i]=EvaluateExpression(exp[i]);
		//printf("第%d个中缀表达式转换为后缀表达式是：%s\n",i+1,exp1);
		//printf("第%d个后缀表达式运算的结果是：%d\n",result[i]);
		//printf("2");
	}
	return 0;
}
