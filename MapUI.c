// Map.h
//========================
// 맵의 UI를 구성하는 부분
//========================
#define _CRT_SECURE_NO_WARNINGS
#include "MapUI.h"
#include "Screen.h"
#include <stdio.h>
#include "BlockData.h"

// 전체 틀
void Map(void) {
	ScreenPrint(0, 0, "■■■■■■■■■■■■");
	for (int i = 1; i < 18; i++) {
		ScreenPrint(0, i, "■");
		ScreenPrint(22, i, "■");
	}
	ScreenPrint(0, 18, "■■■■■■■■■■■■");
}

// 점수 틀
void MapScore(int* nScore) {
	char chScore[15];
	sprintf(chScore, "Score : %d", (*nScore)*500);
	ScreenPrint(25, 10, chScore);
}

void MapNext(int* nBlockType) {
	ScreenPrint(25, 0, "□□□□□□□□");
	ScreenPrint(25, 6, "□□□□□□□□");
	for (int i = 0; i < 6; i++) {
		ScreenPrint(25, i+1, "□");
		ScreenPrint(39, i +1, "□");
	}

	switch (*nBlockType) {
	case 0:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block0[0][i][j] == 1) {
					ScreenPrint( j*2+29, i+1,"■");
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block1[0][i][j] == 1) {
					ScreenPrint(j * 2 + 29, i + 1, "■");
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block2[0][i][j] == 1) {
					ScreenPrint(j * 2 + 29, i + 1, "■");
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block3[0][i][j] == 1) {
					ScreenPrint(j * 2 + 29, i + 1, "■");
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block4[0][i][j] == 1) {
					ScreenPrint(j * 2 + 29, i + 1, "■");
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block5[0][i][j] == 1) {
					ScreenPrint(j * 2 + 29, i + 1, "■");
				}
			}
		}
		break;
	case 6:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Block6[0][i][j] == 1) {
					ScreenPrint(j * 2 + 29, i + 1, "■");
				}
			}
		}
		break;
	}



}


// 준비맵
void MapReady1(void) {
	ScreenPrint(6, 2, "T E T R I S");
	ScreenPrint(4, 7, "Left   : ←");
	ScreenPrint(4, 8, "Right  : →");
	ScreenPrint(4, 9, "Rotate : ↑");
	ScreenPrint(4, 10, "Down   : ↓");
}

// 준비맵
void MapReady2(void) {

	ScreenPrint(4, 14, "Press Enter" );
	ScreenPrint(12, 15, "to Start");
}

//결과맵
void MapResult(int* nScore) {

	ScreenPrint(5, 5, "Game Over~");
	char chScore[15];
	sprintf(chScore, "Score : %d", (*nScore) * 500);
	ScreenPrint(5, 10, chScore);
	for (int i = 1; i < 11; i++) {
		ScreenPrint(i*2, 17, "  ");
	}

}