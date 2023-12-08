// 2023-2 ∞Ì±ﬁ«¡∑Œ±◊∑°π÷ ∞˙¡¶: ¬ﬁ≤ŸπÃ ∞‘¿”

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jjuggumi.h"
#include <windows.h>

#define	DATA_FILE	"jjuggumi.dat"


int jjuggumi_init(void);



// low ¿ÃªÛ high ¿Ã«œ ≥≠ºˆ∏¶ πﬂª˝Ω√≈∞¥¬ «‘ºˆ
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}



int jjuggumi_init(void) {

	srand((unsigned int)time(NULL));
	/*printf("플레이어 수: ");

	scanf_s("%d", &n_player);

	n_alive = n_player;*/

	FILE* fp; 
	fopen_s(&fp, DATA_FILE, "r");

	if (fp == NULL) {
		printf("file open error");
		return -1;
	}

	fscanf_s(fp, "%d", &n_player);
	n_alive = n_player;

	for (int i = 0; i < n_player; i++) {

		PLAYER* p = &player[i];

		fscanf_s(fp, "%s%d%d", p->name, (unsigned int)sizeof(p->name), &(p->intel), &(p->str));

		p->stamina = 100;
		p->is_alive = true;
		p->hasitem = false;
	}


	fscanf_s(fp, "%d", &n_item);

	for (int i = 0; i < n_item; i++) {

		fscanf_s(fp, "%s%d%d%d", item[i].name, (unsigned int)sizeof(item[i].name), &(item[i].intel_buf), &(item[i].str_buf), &(item[i].stamina_buf));

	}



	fclose(fp);

	return 0;


}

void intro(void) // intro()
{
	int x = 10;
	int y = 1;

	for (int i = x; i >= 1; i--)
	{
		for (int j = 1; j <= x - i; j++)
		{
			printf(" ");
		}
		for (int j = 1; j <= 2 * i - 1; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	printf("게임을 시작합니다.\n");

	for (int h = 0; h < 5; h++)
	{
		Sleep(1000);
		if (h == 1)
		{
			Sleep(1000);
			break;
		}
	}
}


void ending(void) // 확실한지?
{
	int winner = 0;
	for (int i = 0; i < n_player; i++)
	{
		if (player[i].is_alive == true && win[i] == true)
		{
			winner = i;
		}
	}
	if (n_alive == 1)
	{
		system("cls");
		gotoxy(7, 5);
		printf("우승자는 player %d번 입니다.\n", winner);
	}
}

int main(void) {

	jjuggumi_init();
	intro();
	//sample();

	//무궁화
	system("cls");
	system("pause");
	char message_mugunghwa[] = "mugunghwa game";
	dialog(message_mugunghwa);
	mugunghwa();
	//야간운동
	/*system("cls");
	system("pause");
	char message_night[] = "night game";
	dialog(message_mugunghwa);
	nightgame();*/

	//줄다리기
	system("cls");
	system("pause");
	char message_jul[] = "juldarigi game";
	dialog(message_jul);
	juldarigi();

	//제비뽑기
	system("cls");
	system("pause");
	char message_jebi[] = "jebi game";
	dialog(message_jebi);
	jebi();
	
	ending();

	return 0;

}

