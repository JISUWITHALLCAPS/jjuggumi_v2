#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4
void draw();
void print_status();

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col) {
    COORD pos = { col,row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col) {
    gotoxy(row, col);
    printf("%c", ch);
}

void map_init(int n_row, int n_col) {
    // 두 버퍼를를 완전히 비우기
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = front_buf[i][j] = ' ';
        }
    }
    N_ROW = n_row;
    N_COL = n_col;
    for (int i = 0; i < N_ROW; i++) {
        // 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
        back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

        for (int j = 1; j < N_COL - 1; j++) {
            back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
        }
    }
}

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col) {
    if (row < 0 || row >= N_ROW || col < 0 || col >= N_COL || back_buf[row][col] != ' ') {
        return false;
    }
    return true;
}

// 상단에 맵을, 하단에는 현재 상태를 출력
void display() {
    draw();
    gotoxy(N_ROW + 6, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
    print_status();
}

void draw() {
    for (int row = 0; row < N_ROW; row++) {
        for (int col = 0; col < N_COL; col++) {
            if (front_buf[row][col] != back_buf[row][col]) {
                front_buf[row][col] = back_buf[row][col];
                printxy(front_buf[row][col], row, col);
            }
        }
    }
}

void print_status() {
    printf("no. of players left: %d\n", n_alive);
    printf("                    intl     str      stm\n");
    for (int i = 0; i < n_player; i++) {
        PLAYER* p = &player[i];
        printf("player %2d: %5s", i, p->is_alive ? "alive" : "DEAD");

        printf("   %2d(%s%d)   %2d(%s%d)   %3d%%\n", p->intel, p->item.intel_buf >= 0 ? ("+") : (""), p->item.intel_buf, p->str, p->item.str_buf >= 0 ? ("+") : (""), p->item.str_buf, p->stamina);
    }
}
void dialog(char message[]) {
    int remainTime = DIALOG_DURATION_SEC;
    while (remainTime > 0)
    {
        gotoxy(5, 5); //커서 중앙으로 이동
        printf("Remaining time : %d seconds\n", remainTime);
        gotoxy(6, 5);
        printf("**********************\n");
        gotoxy(7, 5);
        printf("%s\n", message);
        gotoxy(8, 5);
        printf("**********************\n");
        remainTime--;
        Sleep(1000);
        gotoxy(5, 5);
        printf("                            ");
        gotoxy(6, 5);
        printf("                            ");
        gotoxy(7, 5);
        printf("                            ");
        gotoxy(8, 5);
        printf("                            ");
    }
    display();
}