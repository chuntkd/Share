#include<stdio.h>

void input(char *buff, int *buff_len)
{
	char ch = 0;
	while((ch == getchar()) != '\n')
	{
		buff[(*buff_len)++] = ch;
	}
	buff[(*buff_len)] = "\0";
	
}
