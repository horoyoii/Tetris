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
#include "BlockSpwan.h"

#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 

int nScore = 0; // 전역변수 for 누적점수  
int nBlockType; // 0~6까지의 블록 모형 
int nRot; // 회전 차순의 지표 0,1,2,3,0,1,2,3,0,1,2,3.... 무한반복
int nSpawning; // 1이면 내려가는 중, 0이면 스폰준비완료
int nSpeed; // 내려가는 속도 조절



void init() {
	// 맵 배열 구성 20x10
	PanMap(nArr); // 22x12배열에서 모서리들을 ▩ 블록으로 우선 채운다.
	
	// 블록n 생성
	/*
	nBlockType = 0;
	int n = BlockSpwan();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			nArr[i + 1][j + 1] = Block1[0][i][j];
		}
	}
	*/
	nRot = 1;
	nSpawning = 0;
	nSpeed = 500; 
}


clock_t Oldtime = 0;
void Update() {
	clock_t Curtime = clock();

	// 블록 생성하기 
	// 현재 1,1 좌표에서 생성되어 내려온다.
	if (nSpawning == 0) {
		BlockSpwan2(nArr, &nBlockType);
		nSpawning = 1;
	}






	// 블록 내리기
	//===================================
	int n = 0;
	if (Curtime - Oldtime > nSpeed) { // 내려가는 속도 조절
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

		// 충돌처리
		for (int i = 0; i < 4; i++) {
			if (nArr[Block_pos[i].Pos.x + 1][Block_pos[i].Pos.y] == 2) {// 내려가게 될 공간이 2라면 충돌...
				for (int j = 0; j < 4; j++) {
					nArr[Block_pos[j].Pos.x][Block_pos[j].Pos.y] = 2;
				}
				nSpawning = 0;
				nRot = 1;
				break;
			}
			// 2) 한칸내려 재배열하기 ( 위에서 충돌하지 않았다면)
			else if (i == 3) {
				for (int i = 0; i < 4; i++) {
					nArr[Block_pos[i].Pos.x + 1][Block_pos[i].Pos.y] = 1;
				}
			}
		}



	}
	//===================================
	
	// 완성된 행 검사 후 빼기
	int m = 0;
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (nArr[i][j] == 2) {
				m++;
			}
		}
		if (m == 10) { // 행 완성 시
			nScore++; // 500점 추가
			for (int m = i; m >1; m--) {
				for (int n = 1; n < 11; n++) {
					nArr[m][n] = nArr[m-1][n];
				}
			}
		}
		m = 0;
	}

	// 게임 패배 조건 - nArr의 0행에 새로운 2가 저장된다면 gg


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
	Map();


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
				int k = 1;
				if (nKey == 224) {
					nKey = _getch();
					switch (nKey) {
					case LEFT:
						Beep(200, 200);
						// 경계와 충돌처리
						for (int i = 0; i < 4; i++) {
							if (nArr[Block_pos[i].Pos.x][Block_pos[i].Pos.y-1] == 2) { // 못 간다.
								Beep(400, 200); 
								k = 0;
							}
						}
						// 경계와 충돌안되면 갈 수 있다.
						if (k) {
							LeftMove(nArr); // 좌로 이동
						}
						break;
					case RIGHT:
						Beep(200, 200);
						// 경계와 충돌처리
						for (int i = 0; i < 4; i++) {
							if (nArr[Block_pos[i].Pos.x][Block_pos[i].Pos.y + 1] == 2) { // 못 간다.
								Beep(400, 200);
								k = 0;
							}
						}
						// 경계와 충돌안되면 갈 수 있다.
						if (k) {
							RightMove(nArr); // 우로 이동
						}
						break;
					case UP : // 회전
						Beep(200, 200);
						Rotate(nArr,nBlockType, Block_pos, nRot);
						if (nRot == 3) {
							nRot = -1;
						}
						nRot++;
						break;
					case DOWN: // 바로 내려보리기
						DownMove(nArr);
						nSpawning = 0;
						nRot = 1;
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