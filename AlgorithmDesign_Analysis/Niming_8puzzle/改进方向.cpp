//=========================
//盲目搜索
//=========================
#include <stdio.h>
#include <stdlib.h>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

typedef struct node{
	char a[3][3];
//	char flag;
	struct node *parent,*next;
}puzzle_8;      //每种状态表现形式
puzzle_8 START,END;
void Init()     //初始化
{
	START.a[0][0]=1;START.a[0][1]=2;START.a[0][2]=3;
	START.a[1][0]=8;START.a[1][1]=0;START.a[1][2]=4;
	START.a[2][0]=7;START.a[2][1]=6;START.a[2][2]=5;
	/*
	END.a[0][0]=1;END.a[0][1]=2;END.a[0][2]=3;
	END.a[1][0]=7;END.a[1][1]=0;END.a[1][2]=4;
	END.a[2][0]=8;END.a[2][1]=6;END.a[2][2]=5;
	*/

	END.a[0][0]=0;END.a[0][1]=2;END.a[0][2]=3;
	END.a[1][0]=1;END.a[1][1]=8;END.a[1][2]=4;
	END.a[2][0]=7;END.a[2][1]=6;END.a[2][2]=5;

	START.parent=START.next=END.parent=END.next=NULL;
}

void print(puzzle_8 *p)//打印节点状态
{
	for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
					printf("%8d",p->a[i][j]);
				printf("\n");
			}
	printf("\n");
}

void searchSpace(puzzle_8 *x,int &a,int &b)//查找空格的位置（查找0的位置）
{
	char flag=1;
		for(a=0;a<3&&flag;a++)
		{
			for(b=0;b<3;b++)
			{
				if(x->a[a][b]==0)
				{flag=0;return;}
			}
			
		}
			
			
}
void outPut(puzzle_8 *p)//从p节点打印其所有父节点、祖父节点，直达START根节点。
{
	while(p)
	{
		print(p);
		p=p->parent;
	}
}
bool compare(puzzle_8 *p,puzzle_8 *q)//比较节点是否相同
{
	for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(p->a[i][j]!=q->a[i][j])return false;
			}
			
		}
	return true;

}
bool exist(puzzle_8 *x)//判断新派生的节点是否已经存在
{
	puzzle_8 * p=&START;
	while(p)
	{
		if(compare(x,p))return true;
		p=p->next;
	}
	return false;
}

void copy(puzzle_8 * p,puzzle_8 *x)//节点p==>x(仅复制值)
{
	for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				x->a[i][j]=p->a[i][j];
			}
			
		}
}
puzzle_8 * moveUp(puzzle_8 * p)
{
	puzzle_8 *x=NULL;
		x=(puzzle_8 *)malloc(sizeof(puzzle_8));
	if(!x){printf("out of memory");return NULL;}
	x->parent=x->next=NULL;
	copy(p,x);
	int i,j;
	searchSpace(x,i,j);
	//确定移动位置
	x->a[i][j]=x->a[i-1][j];x->a[i-1][j]=0;
}
puzzle_8 * moveDown(puzzle_8 * p)
{
	puzzle_8 *x=NULL;
		x=(puzzle_8 *)malloc(sizeof(puzzle_8));
	if(!x){printf("out of memory");return NULL;}
	x->parent=x->next=NULL;
	copy(p,x);
	int i,j;
	searchSpace(x,i,j);
	//确定移动位置
	x->a[i][j]=x->a[i+1][j];x->a[i+1][j]=0;
}
puzzle_8 * moveLeft(puzzle_8 * p)
{
	puzzle_8 *x=NULL;
		x=(puzzle_8 *)malloc(sizeof(puzzle_8));
	if(!x){printf("out of memory");return NULL;}
	x->parent=x->next=NULL;
	copy(p,x);
	int i,j;
	searchSpace(x,i,j);
	//确定移动位置
	x->a[i][j]=x->a[i][j-1];x->a[i][j-1]=0;
}
puzzle_8 * moveLeft(puzzle_8 * p)
{
	puzzle_8 *x=NULL;
		x=(puzzle_8 *)malloc(sizeof(puzzle_8));
	if(!x){printf("out of memory");return NULL;}
	x->parent=x->next=NULL;
	copy(p,x);
	int i,j;
	searchSpace(x,i,j);
	//确定移动位置
	x->a[i][j]=x->a[i][j+1];x->a[i][j+1]=0;
}
void gen()
{
	int count=0;
	Init();
	puzzle_8* p=&START;
	puzzle_8* tail=p;  //tail始终指向最后一个节点
	while(p)
	{
		puzzle_8 *x=NULL;
		searchSpace(p,i,j);	
		if(i>0){x=moveUp(p);tail=x;}
		if(i<2){x=moveDown;tail=x;}
		if(j)
	}

}
/*
puzzle_8 * exchange0(puzzle_8 * p,puzzle_8 * &pre ,int tag)//更改0的位置
{
	puzzle_8 *x=NULL;
		x=(puzzle_8 *)malloc(sizeof(puzzle_8));
	if(!x){printf("out of memory");return NULL;}
	x->parent=x->next=NULL;
	copy(p,x);
	int i,j;
	searchSpace(x,i,j);
	switch(tag)
	{
	case UP:
		if(i>0)
		{x->a[i][j]=x->a[i-1][j];x->a[i-1][j]=0;}
		break;
	case DOWN:
		if(i<2)
		{x->a[i][j]=x->a[i+1][j];x->a[i+1][j]=0;}
		break;
	case LEFT:
		if(j>0)
		{x->a[i][j]=x->a[i][j-1];x->a[i][j-1]=0;}
		break;
	case RIGHT:
		if(j<2)
		{x->a[i][j]=x->a[i][j+1];x->a[i][j+1]=0;}
		break;

	}
	if(exist(x))
	{
		free (x);
	//	return NULL;
	}
	else
	{
	//	x->next=NULL;
		pre->next=x;
		x->parent=p;
		pre=x;
		//p=x;
	}
		return x;
	
}
*/

/*
void gen()//查找中
{
	int count=0;
	Init();
	puzzle_8* p=&START;
	puzzle_8* pre=p;  //pre始终指向最后一个节点
	
	if(compare(pre,&END))
	{printf("未排序！");return;}
*/
	/*
	while(p)
	{

		exchange0(p,pre,UP);
		if(compare(pre,&END))
		{outPut(pre);break;}

		exchange0(p,pre,DOWN);
		if(compare(pre,&END))
		{outPut(pre);break;}

		exchange0(p,pre,LEFT);
		if(compare(pre,&END))
		{outPut(pre);break;}

		exchange0(p,pre,RIGHT);
		if(compare(pre,&END))
		{outPut(pre);break;}

		printf("%4d\t",++count);
		printf("\n");
		p=p->next;
	}
	*/
/*
	while(p)
	{
		if(compare(p,&END))
			{outPut(p);break;}
		exchange0(p,pre,UP);
		exchange0(p,pre,DOWN);
		exchange0(p,pre,LEFT);
		exchange0(p,pre,RIGHT);
		printf("%4d\t",++count);
		if(count%10==0)
			printf("\n");
		p=p->next;
	
	}

	if(!p){printf("没找到！");}
}
*/
void main()
{
	//Init();
	gen();	
	
	
}