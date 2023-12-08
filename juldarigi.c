#define _CRT_SECURE_NO_WARNINGS
#include "keyin.h"
#include "jjuggumi.h"
#include "canvas.h"
#include <stdio.h>
#include <string.h>

int tick = 0, w = 2;
double str;
bool jul_player[PLAYER_MAX],jul_player2[PLAYER_MAX];
void print_stat_jul(void);

void wins(int n) {
	if (player[n].is_alive == false) {
		player[n].is_alive = true;
	}
}
void lose(int n) {
	if (player[n].is_alive == true) {
		player[n].hasitem = false;
		memset(&player[n].item, 0, sizeof(ITEM));
		player[n].str /= 2;
		player[n].intel /= 2;
		return;
	}
	n_alive--;
}

void draw_jul() {
	system("cls");
	map_init(3, 29);
	back_buf[0][29/2] = back_buf[2][29/2] = ' ';
	back_buf[1][29/2-1] = back_buf[1][29/2] = back_buf[1][29/2+1] = '-';
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == 0) {
			back_buf[1][29 / 2 - w] = '0' + i;
		}
		else {
			back_buf[1][29/2 + w] = '0' + i;
			w += 1;
		}
		player_copy[i] = true;
	}
}

double cal_str() {
	double str = 0;
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == 0) {
			if (player_copy[i] == true) {
				str -= player[i].str;
			}
		}
		else {
			if (player_copy[i] == true) {
				str += player[i].str;
			}
		}
	}
	return str;
}

void wakeup_str(int t) {
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == t) {
			if (player_copy[i] == true) {
				player[i].str /= 2;
			}
		}
	}
}

void cal_str_lie_down(int t) {
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == t) {
			if (player_copy[i] == true) {
				player[i].str *= 2;
			}
		}
	}
}

bool pull_right() {
	char arr[27];
	if (back_buf[1][29 / 2 - 1] != '-') {
		int i = 29 / 2 - 1;

		if (back_buf[1][i] != ' ') {
			player_copy[back_buf[1][i] - '0'] = false;
			lose(back_buf[1][i] - '0');

		}
		else {
			for (int j = 0; j < n_player; j++) {
				if (player_copy[j] == true) {
					wins(j);
				}
			}
			return true;
		}

		for (; back_buf[1][i] != ' '; i--) {
			back_buf[1][i] = back_buf[1][i - 1];
		}
	}
	else {
		for (int j = 0; j < 27; j++) {
			arr[j] = back_buf[1][j + 1];
		}

		for (int j = 0; j < 26; j++) {
			back_buf[1][j + 2] = arr[j];
		}
	}
	memcpy(jul_player2, player_copy, sizeof(player_copy));
	return false;
}

bool pull_left() {
	char arr[27];
	if (back_buf[1][29/2+1] != '-') {
		int i = 29/2+1;
		if (back_buf[1][i] != ' ') {
			player_copy[back_buf[1][i] - '0'] = false;
			lose(back_buf[1][i] - '0');
		}
		else {
			for (int j = 0; j < n_player; j++) {
				if (player_copy[j] == true) {
					wins(j);
				}
			}
			return true;
		}
		for (; back_buf[1][i] != ' '; i++) {
			back_buf[1][i] = back_buf[1][i + 1];
		}
	}
	else {
		for (int j = 0; j < 27; j++) {
			arr[j] = back_buf[1][j + 1];
		}

		for (int j = 1; j < 27; j++) {
			back_buf[1][j] = arr[j];
		}
	}
	memcpy(jul_player2, player_copy, sizeof(player_copy));
	return false;
}
void juldarigi_init(int t) {
	draw_jul();
	print_stat_jul();
	str = cal_str();
	gotoxy(6, 0);
	printf("no. of players left: %d\n", t);
	for (int i = 0; i < n_player; i++) {
		printf("player %2d: alive", i);
		if (player[i].is_alive == false) {
			printf("*");
		}
		printf("\n");
	}
}
void lieDownPull(str) {
	if (str > 0) {
		g = pull_right();
		g = pull_right();
	}
	else {
		g = pull_left();
		g = pull_left();
	}
}
void cal_stam(int n) {
	for (int i = 0; i < n_player; i++)
		if (i % 2 == n) {
			if (player[i].stamina > 30)
				player[i].stamina -= 30;
			else
				player[i].stamina = 0;
		}
	wakeup_str(1);
}
void when_liedown_r() {
	rLieDownOn = true;
	gotoxy(3, 15);
	printf("lie down RIGHT");
	cal_str_lie_down(1);
	str = cal_str();
	print_stat_jul();
	cal_stam(1);
	wakeup_str(1);
}
void when_liedown_l() {
	lLieDownOn = true;
	gotoxy(3, 0);
	printf("lie down LEFT");
	cal_str_lie_down(0);
	str = cal_str();
	print_stat_jul();
	lieDownPull(str);
	cal_stam(0);
	wakeup_str(0);
}

void oneSecPull(str) {
	if (str > 0) {
		g = pull_right();
	}
	else {
		g = pull_left();
	}
	str = cal_str();
}


void print_stat_jul() {
	draw();
	gotoxy(4, 0);
	printf("str:    %.1f\n", str);
}
void erase_liedown() {
	gotoxy(3, 0);
	printf("                              ");
}
void juldarigi() {
	int temp = n_alive;
	juldarigi_init(temp);
	memcpy(jul_player, player_copy, sizeof(player_copy));
	memcpy(jul_player2, player_copy, sizeof(player_copy));
	while (g == false) {
		tick += 10;
		if (back_buf[1][13] != ' ' && back_buf[1][15] != ' ') {
			key_t key = get_key();
			if (key == K_QUIT) {
				break;
			}
			else if (key == K_LIEDOWN_L) {
				when_liedown_l();
			}
			else if (key == K_LIEDOWN_R) {
				when_liedown_r();
			}
			else {
				switch (key) {
				case K_PULL_L: str--; break;
				case K_PULL_R: str++; break;
				default: break;
				}
			}
		}
		if (tick % 1000 == 0 && tick % 2000 != 0) {
			if (lLieDownOn || rLieDownOn) {
				print_stat_jul();
				lLieDownOn = rLieDownOn = false;
				Sleep(10);
				erase_liedown();
				continue;
			}
			oneSecPull(str);
		}
		else if (tick % 2000 == 0) {
			gotoxy(5, 0);
			printf("                           ");
			gotoxy(5, 0);
			int cnt = 0;
			for (int i = 0; i < n_player; i++) {
				if (jul_player[i] != jul_player2[i]) {
					printf("%d, ", i);
					cnt++;
				}
			}
			if (cnt > 0) {
				printf("player fall");
				memcpy(jul_player, jul_player2, sizeof(jul_player2));
			}
			cnt = 0;
		}
		print_stat_jul();
		Sleep(10);
	}
}
