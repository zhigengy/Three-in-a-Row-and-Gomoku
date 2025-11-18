//游戏逻辑的实现
#include"game.h"

void menu() {
    printf("********************************\n");
    printf("*******1.play    0.exit*********\n");
    printf("********************************\n");
}

void game() {
    char ret = 'c';
    char board[ROW][COL] = { 0 };

    //初始化棋盘
    initboard(board, ROW, COL);
    printf("游戏开始！\n");
    display(board, ROW, COL);

    while (1) {
        //玩家输入
        playermove(board, ROW, COL);
        ret = win(board, ROW, COL);
        display(board, ROW, COL);
        if (ret != 'c') break;

        //电脑输入
        computermove(board, ROW, COL);
        ret = win(board, ROW, COL);
        display(board, ROW, COL);
        if (ret != 'c') break;
    }

    printf("\n========== 游戏结束 ==========\n");
    if (ret == '*') {
        printf(" 恭喜！玩家获胜！\n");
    }
    else if (ret == '#') {
        printf(" 电脑获胜！再接再厉！\n");
    }
    else if (ret == 'q') {
        printf("  平局！棋逢对手！\n");
    }
    printf("==============================\n\n");
}

int main() {
    srand((unsigned int)time(NULL));
    int input = 0;
    do {
        menu();
        printf("请选择: ");
        scanf_s("%d", &input);
        switch (input) {
        case 1:
            printf("进入游戏...\n");
            game();
            break;
        case 0:
            printf("退出游戏，再见！\n");
            break;
        default:
            printf("输入错误，请重新输入\n");
            break;
        }
        printf("\n");
    } while (input);

    return 0;
}