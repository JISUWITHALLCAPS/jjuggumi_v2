#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define PLAYER_MAX		10
#define ITEM_MAX	10

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

typedef struct {
    char name[100];
    int intel_buf, str_buf, stamina_buf;
}ITEM;

typedef struct {
    int id;
    char name[100];

    int intel, str, stamina;

    bool is_alive;
    bool hasitem;

    ITEM item;

}PLAYER;  // ±‚∫ª∞™ true, ≈ª∂Ù«œ∏È false

PLAYER player[PLAYER_MAX];

ITEM item[ITEM_MAX];

bool win[PLAYER_MAX], player_copy[PLAYER_MAX], lLieDownOn, rLieDownOn, g;
int n_player, n_alive, n_item;
int tick;  // Ω√∞Ë

// πÃ¥œ∞‘¿”

//void sample(void);
//void mugunghwa(void);
void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
void jebi(void);

int randint(int low, int high);


#endif

