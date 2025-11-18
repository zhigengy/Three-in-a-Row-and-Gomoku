#pragma once
//游戏代码的声明
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 25
#define COL 25
#define WIN_COUNT 5

void initboard(char board[ROW][COL], int row, int col);
void display(char board[ROW][COL], int row, int col);
void playermove(char board[ROW][COL], int row, int col);
void computermove(char board[ROW][COL], int row, int col);
char win(char board[ROW][COL], int row, int col);
int IsFull(char board[ROW][COL], int row, int col);
int evaluate_position(char board[ROW][COL], int row, int col, int player);