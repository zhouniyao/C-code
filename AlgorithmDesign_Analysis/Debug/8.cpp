#include <stdio.h>
#include <stdlib.h>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

struct node {
	char a[3][3];
	struct node *parent,*next;
};
struct node START, END;

void init()
{
	START.a[0][0]=1;START.a[0][1]=2;START.a[0][2]=3;
	START.a[1][0]=8;START.a[1][1]=0;START.a[1][2]=4;
	START.a[2][0]=7;START.a[2][1]=6;START.a[2][2]=5;
	START.parent=NULL; START.next=NULL;

	END.a[0][0]=0;END.a[0][1]=1;END.a[0][2]=3;
	END.a[1][0]=8;END.a[1][1]=2;END.a[1][2]=4;
	END.a[2][0]=7;END.a[2][1]=6;END.a[2][2]=5;
}

bool compare(struct node *x, struct node *y)
{
	int i,j;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			if(x->a[i][j] != y->a[i][j]) return false;
	return true;
}
void copy(struct node *x, struct node *y) //x->y
{
	int i,j;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			y->a[i][j] = x->a[i][j];
}

void print(struct node *x)
{
	int i,j;

	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
			printf("%2d", x->a[i][j]);
		printf("\n");
	}
	printf("\n");
}
void output(struct node *p)
{
	while (p !=NULL )
	{
		print(p);
		p=p->parent;
	}
}

void space(struct node *p, int &spacei, int &spacej)
{
	for(spacei=0; spacei<3; spacei++)
		for(spacej=0; spacej<3; spacej++)
			if(p->a[spacei][spacej]==0) return;
}


bool exist(struct node *x)//x节点是否存在
{
	struct node *p=&START;
	while(p!=NULL)
	{
		if(compare(p,x)) return true;
		p=p->next;
	}
	return false;
}

struct node* exchange0(struct node *p,struct node *&q, int tag)//0（空格）的可移动位置
{
	int i,j;
	struct node *x=(struct node *)malloc(sizeof(struct node));
	if(x==NULL)
	{
		puts("out of memory");
		return NULL;
	}
    copy(p,x);

	space(x,i,j);//得到0的位置


	switch(tag)
	{
	case UP:
		if(i>0)
		{
			x->a[i][j] = x->a[i-1][j];
			x->a[i-1][j]=0;
		}
		break;
	case DOWN:
		if(i<2)
		{
			x->a[i][j] = x->a[i+1][j];
			x->a[i+1][j]=0;
		}
		break;

	case LEFT:
		if(j>0)
		{
			x->a[i][j] = x->a[i][j-1];
			x->a[i][j-1]=0;
		}
		break;
	case RIGHT:
		if(j<2)
		{
			x->a[i][j] = x->a[i][j+1];
			x->a[i][j+1]=0;
		}
		break;
	}
	if(exist(x)) free(x);//能不能不判断exist(x)
	else
	{
		q->next = x;
		x->parent = p;
		x->next = NULL;
		q = x;
	}
	return x;
}

struct node * gen()
{
	struct node *p,*q;
	int count=0;

	p = &START;
	q = p;
	while( p != NULL )
	{
		if( compare(p, &END) ) break;
		exchange0(p, q, UP);
		exchange0(p, q, DOWN);
		exchange0(p, q, LEFT);
		exchange0(p, q, RIGHT);
		printf("%d\t", ++count);
		printf("\n");
		p = p->next;
	}
	return p;
}
void main()
{
	struct node *p;
	init();

	if( (p=gen())==NULL) puts("无解");
	else output(p);
}



