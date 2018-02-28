#pragma once


// 내려가는 블록의 정보를 저장
int Block0[4][4][4];
int Block1[4][4][4];
int Block2[4][4][4];
int Block3[4][4][4];
int Block4[4][4][4];
int Block5[4][4][4];
int Block6[4][4][4];


typedef struct _POS {
	int x;
	int y;
}POS;

typedef struct _BLOCK_POS { // 내려가고 있는 대상의 블록의 좌표를 저장
	POS Pos;
}BLOCK_POS;

BLOCK_POS Block_pos[4];