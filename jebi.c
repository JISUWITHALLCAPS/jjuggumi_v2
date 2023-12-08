#define _CRT_SECURE_NO_WARNINGS
#include "keyin.h"
#include "jjuggumi.h"
#include "canvas.h"
#include <stdio.h>
#include <string.h>

int jebi_loca[PLAYER_MAX] = { 0 };
int loca = 2, t = 0, l = 0, cnt;
int round = 1;
int playerNum = 0;
char jebiMark[PLAYER_MAX];

void player_pick(key_t, int);
void set_jebi();
void draw_jebi();
void pick(int, int);
void print_turn(int);
void startNewJebi(int nt);
int winneris();
void jebi();

void draw_jebi() {
	gotoxy(2, 2);
	for (int i = 0; i < n_alive; i++) {
		printf("%c ", jebiMark[i]);
	}
}
void set_jebi() {
	jebiMark[0] = '@';
	for (int i = 1; i < n_alive; i++) {
		jebiMark[i] = '?';
	}
	system("cls");
	int f = randint(0, n_alive - 1);
	jebi_loca[f] = 1;
	map_init(10, n_alive * 2 + 3);
	draw();
	draw_jebi();
	gotoxy(10, 0);
	printf("ROUND %d", round);
	display();
}
void player_pick(key_t key, int p) {
	int dir, c = 0;
	switch (key) {
	case K_LEFT:  dir = -1; break;
	case K_RIGHT: dir = 1; break;
	case K_SPACE: dir = 0; break;
	default: return;
	}
	if (dir == 0) {
		pick(t, p);
		return;
	}
	else if (l + dir < 0 || l + dir > n_alive - 1) {
		return;
	}
	if (jebiMark[l + dir] == ' ') {
		while (1) {
			if (dir > 0) {
				for (int i = l; i < n_player; i++) {
					if (jebiMark[i] == '?') {
						jebiMark[i] = '@';
						jebiMark[l] = '?';
						draw_jebi();
						l = i;
						return;
					}
				}
				c += 1;
			}
			else if (dir < 0) {
				for (int i = l; i >= 0; i--) {
					if (jebiMark[i] == '?') {
						jebiMark[i] = '@';
						jebiMark[l] = '?';
						draw_jebi();
						l = i;
						return;
					}
				}
				c += 1;
			}
			if (c == 2) {
				c = 0;
				return;
			}
		}
	}
	jebiMark[l + dir] = '@';
	jebiMark[l] = '?';
	l += dir;
	if (jebiMark[l - dir] == ' ') {
		draw_jebi();
		return;
	}
	draw_jebi();
}
void pick(int t, int p) {
	char str2[50];
	playerNum += 1;
	if (jebi_loca[l] == 1) {
		player[p].is_alive = false;
		n_alive -= 1;
		sprintf(str2, "%d player %d fail!", n_alive, p);
		dialog(str2);
		map_init(10, n_alive * 2 + 3);
		display();
	}
	else {
		jebiMark[l] = ' ';
		for (int i = 0; i < n_player; i++) {
			if (jebiMark[i] == '?') {
				jebiMark[i] = '@';
				l = i;
				break;
			}
		}
		draw_jebi();
		sprintf(str2, "%d player %d pass!", n_alive, p);
		dialog(str2);
		map_init(10, n_alive * 2 + 3);
		display();
	}
	if (player[playerNum].is_alive == false && playerNum < n_player) {
		playerNum += 1;
	}
	if (playerNum >= n_player) {
		for (int i = 0; i < n_player; i++) {
			if (player[i].is_alive == true) {
				playerNum = i;
				break;
			}
		}
	}
}
void print_turn(int pn) {
	gotoxy(10, 7);
	printf(", turn: player %d", playerNum);
}
void startNewJebi(int nt) {
	if (nt != n_alive) {
		round += 1;
		playerNum = 0;
		if (player[0].is_alive == false) {
			for (int i = 0; i < n_player; i++) {
				if (player[i].is_alive == true) {
					playerNum = i;
					break;
				}
			}
		}
		l = 0;
		set_jebi();
	}
}
int winneris() {
	if (n_alive == 1) {
		for (int i = 0; i < n_player; i++) {
			if (player[i].is_alive == true) {
				win[i] = true;
				break;
			}
		}
		return 1;
	}
	return 0;
}
void jebi() {
	for (int i = 0; i < n_player; i++) {
		win[i] = false;
	}
	set_jebi();
	while (1) {
		int nt = n_alive;
		if (player[0].is_alive == true && playerNum == 0) {
			print_turn(playerNum);
			key_t key = get_key();
			if (key == K_QUIT) {
				break;
			}
			else if (key != K_UNDEFINED && player[0].is_alive == true) {
				player_pick(key, 0);
			}
		}
		else {
			for (int i = 1; i < n_player; i++) {
				print_turn(playerNum);
				if (player[i].is_alive == true) {
					while (1) {
						int com_pick = randint(1, 3);
						switch (com_pick) {
						case 1: Sleep(1000); player_pick(K_LEFT, i);  break;
						case 2: Sleep(1000); player_pick(K_RIGHT, i); break;
						case 3: Sleep(1000); player_pick(K_SPACE, i); break;
						default: break;
						}
						Sleep(1000);
						if (com_pick == 3) {
							break;
						}
					}
					if (player[i].is_alive != true) {
						break;
					}
				}
			}
		}
		int w = winneris();
		if (w == 1) {
			break;
		}
		startNewJebi(nt);
	}
}
