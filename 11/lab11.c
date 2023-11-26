#include <stdio.h>


typedef enum _States
{
	CHECK_START = 0,
	CHECK_OTHER,
	CHECK_ERROR
} States;

int isSpace(int ch);

int main(void)
{
	int ch, cnt = 0;
	States state = CHECK_START;

	while (ch = getchar())
	{
		switch (state)
		{
			case CHECK_START:
			{
				if ((ch >= 65 && ch <= 90) || ch == '_' || (ch >= 97 && ch <= 122)) state = CHECK_OTHER;
				else state = CHECK_ERROR;
			}
			break;
			
			case CHECK_OTHER:
			{
				if (ch == EOF){
					cnt++;
					goto exit;
				}
				else if (isSpace(ch)){
					cnt++;
					state = CHECK_START;
				}
				else if (!((ch >= 65 && ch <= 90) || ch == '_' || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57))){
					state = CHECK_ERROR;
				}
			}
			break;
			
			case CHECK_ERROR:
			{
				if (ch == EOF) goto exit;
				if (isSpace(ch)) state = CHECK_START;
			}
			break;
		}
	}
	exit:
		printf("Количество идентификаторов языка Си: %d\n", cnt);
	
		return 0;
}


int isSpace(int ch)
{
	return (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t');
}
