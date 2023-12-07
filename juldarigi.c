#include <stdio.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <string.h>

double str;
int tick = 0,w = 2;
void print_stat_jul(void);
void wins(int n) {
	int i = n;
	if (player[i].is_alive == false) {
		player[i].is_alive = true;
	}
}
void lose(int n) {
	int i = n;
	if (player[i].is_alive == true) {
		player[i].hasitem = false;
		memset(&player[p].item, 0, sizeof(ITEM));
		player[i].str /= 2;
		player[i].intel /= 2;
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
			if (player_copy[i]) {
				str -= player[i].str;
			}
		}
		else {
			if (player_copy[i]) {
				str += player[i].str;
			}
		}
	}
	return str;
}

void wakeup_str(int t) {
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == t) {
			if (player_copy[i]) {
				player[i].str /= 2;
			}
		}
	}
}

void cal_str_lie_down(int t) {
	for (int i = 0; i < n_player; i++)
		if (i % 2 == t) {
			if (player_copy[i]) {
				player[i].str *= 2;
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
			for (int i = 0; i < n_player; i++) {
				if (player_copy[i] == true) {
					wins(i);
				}
			}
			return true;
		}

		for (; back_buf[1][i] != ' '; i--) {
			back_buf[1][i] = back_buf[1][i - 1];
		}
	}
	else {
		for (int i = 0; i < 27; i++) {
			arr[i] = back_buf[1][i + 1];
		}

		for (int i = 0; i < 26; i++) {
			back_buf[1][i + 2] = arr[i];
		}
	}
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
			for (int i = 0; i < n_player; i++) {
				if (player_copy[i] == true) {
					wins(i);
				}
			}
			return true;
		}
		for (; back_buf[1][i] != ' '; i++) {
			back_buf[1][i] = back_buf[1][i + 1];
		}
	}
	else {
		for (int i = 0; i < 27; i++) {
			arr[i] = back_buf[1][i + 1];
		}

		for (int i = 1; i < 27; i++) {
			back_buf[1][i] = arr[i];
		}
	}
	return false;
}

void when_liedown_r() {
	gotoxy(4, 0);
	printf("lie down RIGHT");
	rLieDownOn = true;
	cal_str_lie_down(1);
	str = cal_str();
	print_stat_jul();
	if (str < 0) {
		g = pull_left();
		g = pull_left();
	}
	else {
		g = pull_right();
		g = pull_right();
	}

	for (int i = 0; i < n_player; i++)
		if (i % 2 == 1) {
			if (player[i].stamina > 30)
				player[i].stamina -= 30;
			else
				player[i].stamina = 0;
		}
	wakeup_str(1);
}
void when_liedown_l() {
	gotoxy(4, 0);
	printf("lie down LEFT");
	lLieDownOn = true;
	cal_str_lie_down(0);
	str = cal_str();
	print_stat_jul();
	if (str < 0) {
		g = pull_left();
		g = pull_left();
	}
	else {
		g = pull_right();
		g = pull_right();
	}
	for (int i = 0; i < n_player; i++)
		if (i % 2 == 0) {
			if (player[i].stamina > 30) {
				player[i].stamina -= 30;
			}
			else {
				player[i].stamina = 0;
			}
		}
	wakeup_str(0);
}


void print_stat_jul() {
	gotoxy(4, 0);
	printf("str:                        \n");
	gotoxy(4, 0);
	printf("str:\t\t%.1f\n", str);
	gotoxy(5, 0);
	printf("no. of players left: %d\n", n_alive);
	for (int i = 0; i < n_player; i++) {
		printf("player %2d: alive", i);
		if (player[i].is_alive == false) {
			printf("*");
		}
		printf("\n");
	}
}

void juldarigi() {
	draw_jul();
	draw();
	print_stat_jul();
	str = cal_str();
	key_t key;
	while (g == false) {
		tick += 10;
		if (back_buf[1][13] != ' ' && back_buf[1][115] != ' ') {
			key = get_key();
			if (key == K_QUIT) {
				break;
			}
			switch (key) {
			case K_PULL_L:str--; break;
			case K_PULL_R:str++; break;
			case K_LIEDOWN_L:when_liedown_l(); break;
			case K_LIEDOWN_R:when_liedown_r(); break;
			default: break;
			}
		}
		if (tick % 1000 == 0) {
			if (lLieDownOn || rLieDownOn) {
				draw();
				print_stat_jul();
				Sleep(10);
				lLieDownOn = rLieDownOn = false;
				continue;
			}

			if (str < 0) {
				g = pull_left();
			}
			else {
				g = pull_right();
			}
			str = cal_str();
		}
		;
		draw();
		print_stat_jul();
		Sleep(10);
	}
}
