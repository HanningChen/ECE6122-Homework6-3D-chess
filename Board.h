/*
	Author:Hanning Chen
	Class:ECE6122
	Last Date Modified:2019.11.21
	Description:This is the .h file for ECE6122 which includes init the Board function
	and the pawn moving function and knight moving function
*/
#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
//initBoard iniate the board including the position of pieces
void initBoard(int**board);
//pawnMoving calculate the position of the pawn after pressing 'p' or 'P'
//Input parameter is the postion of piece and board matrix
void pawnMoving(double* whiteX, double* whiteY, double* blackX, double* blackY,int** board);
//knightMoving calculate the position of the pawn after pressing 'p' or 'P'
//Input parameter is the postion of piece and board matrix
void knightMoving(double* whiteX, double* whiteY, double* blackX, double* blackY, int** board);