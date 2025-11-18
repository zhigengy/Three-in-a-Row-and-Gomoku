//游戏代码的实现
#include "game.h"

void initboard(char board[ROW][COL], int row, int col) {
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            board[i][j] = ' ';
        }
    }
}

void display(char board[ROW][COL], int row, int col) {
    int i = 0;
    int j = 0;
    printf("\n   |");
    for (j = 1; j <= col; j++) {
        printf("%2d ", j);
        if (j < col)
            printf("|");
    }
    printf("\n");
    printf("---|");
    for (j = 0; j < col; j++) {
        printf("---");
        if (j < col - 1)
            printf("|");
    }
    printf("\n");

    for (i = 0; i < row; i++) {
        printf("%2d |", i + 1);
        for (j = 0; j < col; j++) {
            printf(" %c ", board[i][j]);
            if (j < col - 1)
                printf("|");
        }
        printf("\n");
        if (i < row - 1) {
            printf("---|");
            for (j = 0; j < col; j++) {
                printf("---");
                if (j < col - 1)
                    printf("|");
            }
            printf("\n");
        }
    }
    printf("\n");
}

void playermove(char board[ROW][COL], int row, int col) {
    int x = 0;
    int y = 0;
    printf("\n玩家下棋>\n");
    while (1) {
        printf("请输入坐标(行 列，范围1-3)：");
        scanf_s("%d %d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col) {
            if (board[x - 1][y - 1] == ' ') {
                board[x - 1][y - 1] = '*';
                printf("玩家在(%d,%d)落子\n", x, y);
                break;
            }
            else {
                printf("该位置已被占用，请重新输入\n");
            }
        }
        else {
            printf("坐标非法，请输入1-3之间的数字\n");
        }
    }
}

// 评估当前棋盘状态
int evaluate(char board[ROW][COL]) {
    int i, j;

    // 检查行
    for (i = 0; i < ROW; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == '#') return +10;
            else if (board[i][0] == '*') return -10;
        }
    }

    // 检查列
    for (j = 0; j < COL; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == '#') return +10;
            else if (board[0][j] == '*') return -10;
        }
    }

    // 检查对角线
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == '#') return +10;
        else if (board[0][0] == '*') return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == '#') return +10;
        else if (board[0][2] == '*') return -10;
    }

    return 0; // 无人获胜
}

// Minimax算法实现
int minimax(char board[ROW][COL], int depth, int isMax) {
    int score = evaluate(board);

    // 如果电脑赢了
    if (score == 10) return score - depth;
    // 如果玩家赢了
    if (score == -10) return score + depth;
    // 如果平局
    if (IsFull(board, ROW, COL)) return 0;

    int best;
    if (isMax) {
        best = -1000;
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = '#';
                    best = (best > minimax(board, depth + 1, !isMax)) ? best : minimax(board, depth + 1, !isMax);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else {
        best = 1000;
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = '*';
                    best = (best < minimax(board, depth + 1, !isMax)) ? best : minimax(board, depth + 1, !isMax);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// 改进的电脑下棋算法 - 使用Minimax算法
void computermove(char board[ROW][COL], int row, int col) {
    printf("\n电脑思考中");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        // 简单的延时效果
        for (int j = 0; j < 100000000; j++);
    }
    printf("\n");

    int bestVal = -1000;
    int bestX = -1, bestY = -1;

    // 如果是第一步，选择中心或角落
    int moveCount = 0;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (board[i][j] != ' ') moveCount++;
        }
    }

    if (moveCount == 0) {
        // 第一步选择中心
        bestX = 1; bestY = 1;
    }
    else if (moveCount == 1 && board[1][1] == ' ') {
        // 如果玩家走了角落，电脑走中心
        bestX = 1; bestY = 1;
    }
    else {
        // 使用Minimax算法找到最佳移动
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = '#';
                    int moveVal = minimax(board, 0, 0);
                    board[i][j] = ' ';

                    if (moveVal > bestVal) {
                        bestX = i;
                        bestY = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
    }

    board[bestX][bestY] = '#';
    printf("电脑在(%d,%d)落子\n", bestX + 1, bestY + 1);
}

int IsFull(char board[ROW][COL], int row, int col) {
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

// 判断游戏状态
char win(char board[ROW][COL], int row, int col) {
    int i = 0;
    // 检查行
    for (i = 0; i < row; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ') {
            return board[i][1];
        }
    }

    // 检查列
    int j = 0;
    for (j = 0; j < col; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ') {
            return board[1][j];
        }
    }

    // 检查对角线
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ') {
        return board[1][1];
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
        return board[1][1];
    }

    // 没有人赢，检查是否平局
    if (IsFull(board, row, col)) {
        return 'q'; // 平局
    }

    return 'c'; // 游戏继续
}