//游戏逻辑的实现
#include"game.h"
void menu() {
	printf("********************************\n"); 
	printf("*******1.play    0.exit*********\n");
	printf("********************************\n");
}
void game() {
	char ret = 0;
	char board[ROW][COL] = { 0 };
	//初始化棋盘
	initboard(board, ROW, COL);
	//打印棋盘
	display(board, ROW, COL);
	while (1) {
		//玩家输入
	playermove(board, ROW, COL);
	
		//判断输赢
	ret = win(board, ROW, COL);
	//打印棋盘
	display(board, ROW, COL);
	if (ret != 'c') {
		break;
	}
		//电脑输入
	computermove(board, ROW, COL);
	
		//判断输赢
	ret = win(board, ROW, COL);
	if (ret != 'c') {
		break;
	}
	//打印棋盘
	display(board, ROW, COL);
	}
	if (ret == '*') {
		printf("玩家赢");
	}
	else if (ret == '#') {
		printf("电脑赢");
	}
	else {
		printf("平局");
	}
	printf("\n");
	display(board, ROW, COL);
}
int main() {
	srand((unsigned int)time(NULL));
	int input = 0;
	do {
		menu();
		printf("请选择:__\b\b");
		scanf_s("%d", & input);
		switch (input) {
		case 1: printf("进入游戏\n");
			game(); 
			break;
		case 0:printf("退出游戏\n");
			break;
		default:printf("输入错误，请重新输入\n");
			break;
		}

	} while (input);

	return 0;
}
