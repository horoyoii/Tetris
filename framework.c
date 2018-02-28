// 테트리스 // 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#include"Screen.h""
#include"PanData.h"
#include "MapUI.h"
#include "BlockData.h"
#include "BlockMove.h"

#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 

int nScore = 0; // 전역변수 for 누적점수  
int nBlockType;
int nRot; // 회전 차순의 지표 0,1,2,3,0,1,2,3,0,1,2,3.... 무한반복





void init() {
	// 맵 배열 구성 20x10
	PanMap(nArr); // 22x12배열에서 모서리들을 ▩ 블록으로 우선 채운다.
	
	// 블록0 생성
	nBlockType = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			nArr[i + 1][j + 1] = Block0[0][i][j];
		}
	}

	nRot = 1;
}


clock_t Oldtime = 0;
void Update() {
	clock_t Curtime = clock();

	//블록 좌우 움직이기






	// 블록 내리기
	//===================================
	int n = 0;
	if (Curtime - Oldtime > 1000) {
		Oldtime = Curtime;
		// 1) 저장받기
		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (nArr[i][j] == 1) {
					nArr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 재배열하기
		for (int i = 0; i < 4; i++) {
			nArr[Block_pos[i].Pos.x + 1][Block_pos[i].Pos.y] = 1;
		}
	}
	//===================================
	
	



}

void Render() {
	ScreenClear();
	//출력코드
	MapScore(&nScore);


	//=============================
	// 배열을 출력
	//=============================
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 12; j++) {
			if (nArr[i][j] == 2) {
				ScreenPrint( j*2, i, "▩");
			}
			else if (nArr[i][j] == 1) {
				ScreenPrint(j * 2, i, "■");
			}
			else {
				ScreenPrint( j*2, i, "  ");
			}
		}
	}



	//==============================
	ScreenFlipping();
}

void Release() {

}

int main(void) {
	
	ScreenInit();
	init(); // 초기화
	
	while (1) {
		int nKey;
		while (1) {
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 224) {
					nKey = _getch();
					switch (nKey) {
					case LEFT:
						Beep(200, 200);
						LeftMove(nArr); // 좌로 이동
						break;
					case RIGHT:
						Beep(200, 200);
						RightMove(nArr); // 우로 이동
						break;
					case UP : // 회전
						Beep(200, 200);
						Rotate(nArr,nBlockType, Block_pos, nRot);
						if (nRot == 3) {
							nRot = -1;
						}
						nRot++;
						break;
					}
				}
				
			}
			Update();  // 데이터 갱신
			Render();  // 화면출력
		}
	

		
	}
	Release(); // 해제
	ScreenRelease();
	return 0;
}