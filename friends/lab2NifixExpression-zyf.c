#include<stdio.h>
#include<stdlib.h>
typedef struct StackNode1
{
    char data;
    struct StackNode1 *next;
}StackNode1,*LinkStack1;
typedef struct StackNode2
{
    double data;
    struct StackNode2 *next;
}StackNode2,*LinkStack2;

void InitStack1(LinkStack1 S)
{
    S=NULL;
}

void InitStack2(LinkStack2 S)
{
    S=NULL;
}

void Push1(LinkStack1 S,char e)
{
    LinkStack1 p;
    p=malloc(sizeof(struct StackNode1));
    p->data=e;
    p->next=S;
    S=p;
}

void Push2(LinkStack2 S,double e)
{
    LinkStack2 p;
    p=malloc(sizeof(struct StackNode2));
    p->data=e;
    p->next=S;
    S=p;
}

char Pop1(LinkStack1 S)
{
    char e;
    LinkStack1 p;
    if(S==NULL)
        printf("error!");
    e=S->data;
    p=S;
    S=S->next;
    free(p);
    return e;
}

double Pop2(LinkStack2 S)
{
    double e;
    LinkStack2 p;
    if(S==NULL)
        printf("error!");
    e=S->data;
    p=S;
    S=S->next;
    free(p);
    return e;
}

char GetTop1(LinkStack1 S)
{
    if(S!=NULL)
        return S->data;
}

double GetTop2(LinkStack2 S)
{
    if(S!=NULL)
        return S->data;
}

int In(char ch)
{
    if(ch=='+') return 1;
    else if(ch=='-') return 1;
    else if(ch=='*') return 1;
    else if(ch=='/') return 1;
    else if(ch=='(') return 1;
    else if(ch==')') return 1;
    else if(ch=='#') return 1;
    else return 0;
}

char Precede(char a,char b)
{
    if(b=='+')
    {
        if(a=='('||a=='#')
            return '<';
        else
            return '>';
    }
    else if(b=='-')
    {
        if(a=='('||a=='#')
            return '<';
        else
            return '>';
    }
    else if(b=='*')
    {
        if(a=='*'||a=='/'||a==')')
            return '>';
        else
            return '<';
    }
    else if(b=='/')
    {
        if(a=='*'||a=='/'||a==')')
            return '>';
        else
            return '<';
    }
    else if(b=='(')
            return '<';
    else if(b==')')
    {
        if(a=='(')
            return '=';
        else
            return '>';
    }
    else if(b=='#')
    {
        if(a=='#')
            return '=';
        else
            return '>';
    }
}

double Operate(double a,char theta,double b)
{
    if(theta=='+') return a+b;
    if(theta=='-') return a-b;
    if(theta=='*') return a*b;
    if(theta=='/') return a/b;
}

double EvaluateExpression()
{
    LinkStack1 OPTR;
    InitStack1(OPTR);
    LinkStack2 OPND;
    InitStack2(OPND);
    char ch,theta;
    double a,b;
    int i;
    Push1(OPTR,'#');
    ch=getchar();
    while(ch!='#'||GetTop1(OPTR)!='#')
    {
        if(!In(ch))
        {
            Push2(OPND,ch);
            ch=getchar();
        }
        else
            switch (Precede(GetTop1(OPTR),ch))
            {
                case'<':
                    Push1(OPTR,ch);
                    ch=getchar();
                    break;
                case'>':
                    theta=Pop1(OPTR);
                    b=Pop2(OPND);
                    a=Pop2(OPND);
                    Push2(OPND,Operate(a,theta,b));
                    break;
                case'=':
                    Pop1(OPTR);
                    ch=getchar();
                    break;
            }
    }
    return GetTop2(OPND);
}

int main ( )
{
    double i;
    printf("Please input the expression:\n");
    i=EvaluateExpression();
    printf("%-5.2lf",i);
    return 0;
}
