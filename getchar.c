#include<stdio.h>
#include<string.h>

int main(void)
{
	char ch=0;
	char buff[500];
	char *temp;
	char *word[10];
	int  word_num = 1, buff_len = 0;
	
	while((ch=getchar()) !='\n')
	{
		buff[buff_len++] = ch;
	}
	buff[buff_len] = '\0';

	temp = buff;
	
	for(int i=0;i<buff_len;i++)
	{
		if(temp[i] == ' ' )
		{
			word_num++;
		}
	}
	
	word[0] = strtok(temp," ");

	for(int i=1; i<word_num; i++)
		{
			word[i] = strtok(NULL," ");
		}
	for(int i=0; i<word_num; i++)
		{
			printf("%s ",word[i]);
		}
	puts(" ");

}
