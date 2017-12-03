#include<stdio.h>
#include<iostream>
#include<stdlib.h>
int main()
{
	FILE * fp;
	char ch,filename[10];
	scanf("%s",filename);
	if((fp = fopen(filename,"w")) == NULL)
	{printf("cannot open file\n");}
	while((ch = getchar()) != '#')
	{
		fputc(ch,fp);
		putchar(ch);
	}
	fclose(fp);
	return 0;
}