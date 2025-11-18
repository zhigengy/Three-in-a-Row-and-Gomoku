#pragma once
//游戏代码的声明
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3
#define COL 3

void initboard(char board[ROW][COL], int row, int col);
void display(char board[ROW][COL], int row, int col);
void playermove(char board[ROW][COL], int row, int col);
void computermove(char board[ROW][COL], int row, int col);
char win(char board[ROW][COL], int row, int col);
int IsFull(char board[ROW][COL], int row, int col);
int evaluate(char board[ROW][COL]);
int minimax(char board[ROW][COL], int depth, int isMax);