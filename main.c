//
//  main.c
//  squash_game
//
//  Created by Andy on 2016/1/23.
//  Copyright © 2016年 Andy. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ttime(int count, int i);//時間計數
void det_site(char site[5]);//判斷位置
int win(int a, int b);//判斷輸贏

int main()
{
	int a = 0, b = 0, input = 0;//input改為button
	int i = 0;// 判斷依據
	char site[5];

	printf("熱身\n");
	ttime(2, 150);

	i = 1;
	while (1)
	{
		printf("目前比數 %d  :  %d\t", a, b);
		do {
			scanf("%d", &input);
			getchar();//擋住site收到\n
			switch (input)
			{
			case 1:
				a = a + 1;
				if (i == 2)
				{
					det_site(site);
				}
				else
				{
					printf("輸入位置：");
					scanf("%s", site);
				}
				i = 2;//判斷連續得分
				break;

			case 0:
				b = b + 1;
				if (i == 3)
				{
					det_site(site);
				}
				else
				{
					printf("輸入位置：");
					scanf("%s", site);
				}

				i = 3;//判斷連續得分
				break;

			default:
				printf("輸入錯誤！\n");
				i = 1;
				break;
			}
			if (win(a, b))
			{
				a = 0;
				b = 0;
				i = 1;
				printf("休息90秒\n");
				ttime(1, 90);
				break;
			}
		} while (i == 1);
	}
	//    system("pause");
	return 0;
}

void det_site(char site[5])//判斷位置
{
	if (!strcmp(site, "R"))
	{
		strcpy(site, "L");
		printf("左邊發球\n");
	}
	else if (!strcmp(site, "L"))
	{
		strcpy(site, "R");
		printf("右邊發球\n");
	}
}

int win(int a, int b)//判斷輸贏
{
	if (a>10 && b<10) {
		printf("A WIN!!\n");
		printf(" %d : %d\n", a, b);
		return 1;
	}

	else if (b>10 && a<10) {
		printf("B WIN!!\n");
		printf(" %d : %d\n", a, b);
		return 1;
	}

	else if (a >= 10 && b >= 10) {
		if ((a - b) == 2) {
			printf("A WIN!!\n");
			printf(" %d : %d\n", a, b);
			return 1;
		}

		else if ((b - a) == 2) {
			printf("B WIN!!\n");
			printf(" %d : %d\n", a, b);
			return 1;
		}
	}
	return 0;
}

void ttime(int count, int i)//時間計數
{
	int temp = 0;
	time_t t1 = 0, t2 = 0;
	for (temp = 0; temp < count; temp++)
	{
		t1 = time(NULL);
		t2 = time(NULL);
		for (; (int)difftime(t2, t1) < i; )
			t2 = time(NULL);
		if (temp == 0 && count == 2)
			printf("換邊\n");

		else
			printf("開始比賽\n");
	}
}