#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct node
{
	char a[3][3];
	struct node *next, *parent;
};

struct node START, END;

void init()
{
	START.a[0][0]=1; START.a[0][1]=2; START.a[0][2]=3;
	START.a[1][0]=8; START.a[1][1]=0; START.a[1][2]=4;
	START.a[2][0]=7; START.a[2][1]=6; START.a[2][2]=5;
	START.parent = NULL; START.next = NULL;

	END.a[0][0]=0; END.a[0][1]=1; END.a[0][2]=3;
	END.a[1][0]=8; END.a[1][1]=2; END.a[1][2]=4;
	END.a[2][0]=7; END.a[2][1]=6; END.a[2][2]=5;
}
int compare(struct node *x, struct node *y)
{
	int i,j;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			if( x->a[i][j] != y->a[i][j] ) return 0;
	return 1;
}
void space(struct node *p,int &spacei, int &spacej)
{
	for(spacei=0; spacei<3; spacei++)
			for(spacej=0; spacej<3; spacej++)
				if( p->a[spacei][spacej] ==0 ) return;
}
void copy( struct node *x, struct node *y) // x->y
{
	int i,j;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			y->a[i][j] = x->a[i][j];
}
int exist(struct node *x)
{
	struct node *p=&START;
	while( p != NULL)
	{
		if( compare(p,x) ) return 1;
		p = p->next;
	}
	return 0;
}
void print(struct node *p)
{
	for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
				printf("%2d",p->a[i][j]);
			printf("\n");
		}
	printf("\n");
}
void output(struct node *p)
{
	while( p != NULL )
	{
		print(p);
	
		p = p->parent;
	}
}
struct node * gen()
{
	struct node *p= &START, *x, *q;
	int spacei, spacej;

	q = p;
	while( p != NULL )
	{
		if( compare(p, &END) )  break;

		//print(p); getch();
		space(p, spacei, spacej );

		if(spacei>0) //UP
		{
			if( (x=(struct node *)malloc( sizeof(struct node) ))==NULL )
			{
				puts("内存不够!");
				return NULL;
			}
			copy( p, x);
			x->a[spacei][spacej] = x->a[spacei-1][spacej];
			x->a[spacei-1][spacej] = 0;
			if( exist(x) ) free(x);
			else
			{
				x->next=NULL; x->parent =p;
			    q->next = x;  q = x;
				//puts("UP");
			}
			
		}
		if(spacei<2) //DOWN
		{
			if( (x=(struct node *)malloc( sizeof(struct node) ))==NULL )
			{
				puts("内存不够!");
				return NULL;
			}
			copy( p, x);
			x->a[spacei][spacej] = x->a[spacei+1][spacej];
			x->a[spacei+1][spacej] = 0; 
			if( exist(x) ) free(x);
			else
			{
				x->next=NULL; x->parent =p;
			    q->next = x;  q = x;
				//puts("DOWN");
			}
			
		}
		if(spacej>0) //LEFT
		{
			if( (x=(struct node *)malloc( sizeof(struct node) ))==NULL )
			{
				puts("内存不够!");
				return NULL;
			}
			copy( p, x);
			x->a[spacei][spacej] = x->a[spacei][spacej-1];
			x->a[spacei][spacej-1] = 0; 
			if( exist(x) ) free(x);
			else
			{
				x->next=NULL; x->parent =p;
			    q->next = x;  q = x;
				//puts("LEFT");
			}
			
		}
		if(spacej<2) //RIGHT
		{
			if( (x=(struct node *)malloc( sizeof(struct node) ))==NULL )
			{
				puts("内存不够!");
				return NULL;
			}
			copy( p, x);
			x->a[spacei][spacej] = x->a[spacei][spacej+1];
			x->a[spacei][spacej+1] = 0; 
			if( exist(x) ) free(x);
			else
			{
				x->next=NULL; x->parent =p;
			    q->next = x;  q = x;
				//puts("RIGHT");
			}
			
		}
		p = p->next;
	}
	return p;
}


void main()
{

	init();
	struct node *p;
	if( (p=gen())!=NULL )	output(p);
	else puts("无解!");
}




