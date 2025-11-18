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

    // 打印列号
    printf("   |");
    for (j = 1; j <= col; j++) {
        printf("%2d ", j);
        if (j < col)
            printf("|");
    }
    printf("\n");

    // 打印分隔线
    printf("---|");
    for (j = 0; j < col; j++) {
        printf("---");
        if (j < col - 1)
            printf("|");
    }
    printf("\n");

    for (i = 0; i < row; i++) {
        // 打印行号
        printf("%2d |", i + 1);

        // 打印棋盘内容
        for (j = 0; j < col; j++) {
            printf(" %c ", board[i][j]);
            if (j < col - 1)
                printf("|");
        }
        printf("\n");

        // 打印行间分隔线（除了最后一行）
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
    printf("玩家: *   电脑: #\n\n");
}
void playermove(char board[ROW][COL], int row, int col) {
    int x = 0;
    int y = 0;
    printf("\n玩家下棋>\n");
    while (1) {
        printf("请输入坐标(行 列，范围1-%d)：", row);
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
            printf("坐标非法，请输入1-%d之间的数字\n", row);
        }
    }
}

// 评估位置得分
int evaluate_position(char board[ROW][COL], int row, int col, int player) {
    char symbol = (player == 1) ? '#' : '*';
    char opponent = (player == 1) ? '*' : '#';
    int score = 0;

    // 检查四个方向：水平、垂直、两个对角线
    int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int d = 0; d < 4; d++) {
                int dx = directions[d][0];
                int dy = directions[d][1];

                // 检查连续棋子
                int count = 0;
                int block = 0;
                int empty = 0;

                for (int k = 0; k < WIN_COUNT; k++) {
                    int ni = i + dx * k;
                    int nj = j + dy * k;

                    if (ni < 0 || ni >= row || nj < 0 || nj >= col) {
                        block++;
                        break;
                    }

                    if (board[ni][nj] == symbol) {
                        count++;
                    }
                    else if (board[ni][nj] == ' ') {
                        empty++;
                    }
                    else {
                        block++;
                        break;
                    }
                }

                // 根据连续棋子数量评分
                if (count == WIN_COUNT) {
                    score += 100000; // 获胜
                }
                else if (count == WIN_COUNT - 1 && empty == 1) {
                    score += 10000; // 四连珠
                }
                else if (count == WIN_COUNT - 2 && empty == 2) {
                    score += 1000; // 三连珠
                }
                else if (count == WIN_COUNT - 3 && empty == 3) {
                    score += 100; // 二连珠
                }

                // 检查对手的棋子并防守
                count = 0;
                block = 0;
                empty = 0;

                for (int k = 0; k < WIN_COUNT; k++) {
                    int ni = i + dx * k;
                    int nj = j + dy * k;

                    if (ni < 0 || ni >= row || nj < 0 || nj >= col) {
                        block++;
                        break;
                    }

                    if (board[ni][nj] == opponent) {
                        count++;
                    }
                    else if (board[ni][nj] == ' ') {
                        empty++;
                    }
                    else {
                        block++;
                        break;
                    }
                }

                // 防守评分
                if (count == WIN_COUNT - 1 && empty == 1) {
                    score += 5000; // 阻止对手四连珠
                }
                else if (count == WIN_COUNT - 2 && empty == 2) {
                    score += 500; // 阻止对手三连珠
                }
            }
        }
    }

    // 中心位置加分
    int center_i = row / 2;
    int center_j = col / 2;
    for (int i = center_i - 2; i <= center_i + 2; i++) {
        for (int j = center_j - 2; j <= center_j + 2; j++) {
            if (i >= 0 && i < row && j >= 0 && j < col && board[i][j] == ' ') {
                int dist = abs(i - center_i) + abs(j - center_j);
                score += (5 - dist) * 10;
            }
        }
    }

    return score;
}

void computermove(char board[ROW][COL], int row, int col) {
    printf("\n电脑思考中");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        for (int j = 0; j < 100000000; j++);
    }
    printf("\n");

    int bestX = -1, bestY = -1;
    int bestScore = -1000000;

    // 检查是否有立即获胜的机会
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = '#';
                if (win(board, row, col) == '#') {
                    bestX = i;
                    bestY = j;
                    board[i][j] = ' ';
                    goto found_move;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 检查是否需要防守（阻止玩家获胜）
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = '*';
                if (win(board, row, col) == '*') {
                    bestX = i;
                    bestY = j;
                    board[i][j] = ' ';
                    goto found_move;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 使用评估函数选择最佳位置
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == ' ') {
                int score = evaluate_position(board, row, col, 1); // 1代表电脑

                // 给已经有棋子的位置周围加分
                for (int di = -2; di <= 2; di++) {
                    for (int dj = -2; dj <= 2; dj++) {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col &&
                            board[ni][nj] != ' ') {
                            score += 50;
                        }
                    }
                }

                if (score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

found_move:
    if (bestX != -1 && bestY != -1) {
        board[bestX][bestY] = '#';
        printf("电脑在(%d,%d)落子\n", bestX + 1, bestY + 1);
    }
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

// 检查指定方向是否有连续棋子
int check_direction(char board[ROW][COL], int row, int col, int x, int y, int dx, int dy, char symbol) {
    int count = 0;
    for (int i = 0; i < WIN_COUNT; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx >= 0 && nx < row && ny >= 0 && ny < col && board[nx][ny] == symbol) {
            count++;
        }
        else {
            break;
        }
    }
    return count;
}

// 判断游戏状态
char win(char board[ROW][COL], int row, int col) {
    int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} }; // 水平、垂直、对角线

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] != ' ') {
                char current = board[i][j];
                for (int d = 0; d < 4; d++) {
                    int count = 1; // 当前位置已经有一个棋子
                    int dx = directions[d][0];
                    int dy = directions[d][1];

                    // 正向检查
                    for (int k = 1; k < WIN_COUNT; k++) {
                        int ni = i + dx * k;
                        int nj = j + dy * k;
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col && board[ni][nj] == current) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }

                    // 反向检查
                    for (int k = 1; k < WIN_COUNT; k++) {
                        int ni = i - dx * k;
                        int nj = j - dy * k;
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col && board[ni][nj] == current) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }

                    if (count >= WIN_COUNT) {
                        return current;
                    }
                }
            }
        }
    }

    // 没有人赢，检查是否平局
    if (IsFull(board, row, col)) {
        return 'q'; // 平局
    }

    return 'c'; // 游戏继续
}