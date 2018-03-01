// Map.h
//========================
// 맵의 UI를 구성하는 부분
//========================
#define _CRT_SECURE_NO_WARNINGS
#include "MapUI.h"
#include "Screen.h"
#include <stdio.h>

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

void MapNext(void) {
	//
}


// 준비맵
void MapReady1(void) {
	ScreenPrint(6, 5, "T E T R I S");
}

// 준비맵
void MapReady2(void) {

	ScreenPrint(4, 10, "Press Enter" );
	ScreenPrint(12, 11, "to Start");
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