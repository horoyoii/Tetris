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

// 소리 출력 PlaySound함수
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")


#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 

int nScore = 0; // 전역변수 for 누적점수  
int nBlockType; // 0~6까지의 블록 모형 
int nBlockType2; // 다음에 출력할 블록 모형
int nRot; // 회전 차순의 지표 0,1,2,3,0,1,2,3,0,1,2,3.... 무한반복
int nSpawning; // 1이면 내려가는 중, 0이면 스폰준비완료
int nSpeed; // 내려가는 속도 조절


typedef enum _STAGE {
	READY, RUNNING, RESULT //  시작화면 / 실행화면 / 결과화면
}STAGE;
STAGE Stage;


void init() {
	// 맵 배열 구성 20x10
	PanMap(nArr); // 25x12배열에서 모서리들을 ▩ 블록으로 우선 채운다.
	
	Stage = READY;
	nRot = 1;
	nSpawning = 0;
	nSpeed = 500; 
}


clock_t Oldtime = 0;
void Update() {
	clock_t Curtime = clock();
	switch (Stage) {
	case READY :
		break;
	case RUNNING:
		//브금 재생
		// 블록 생성하기 
		// 현재 1,1 좌표에서 생성되어 내려온다.
		if (nSpawning == 0) {
			nBlockType = BlockSpwan();
			nBlockType2 = BlockSpwan();
			BlockSpwan2(nArr, &nBlockType);

			nSpawning=1;
		}
		if (nSpawning == 3) {
			nBlockType = nBlockType2;
			nBlockType2 = BlockSpwan();
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

			// 1-1) 충돌처리
			for (int i = 0; i < 4; i++) {
				if (nArr[Block_pos[i].Pos.x + 1][Block_pos[i].Pos.y] == 2) {// 내려가게 될 공간이 2라면 충돌...
					for (int j = 0; j < 4; j++) {
						nArr[Block_pos[j].Pos.x][Block_pos[j].Pos.y] = 2;
					}
					nSpawning = 3;
					nRot = 1;
					break;
				}
				// 1-2) 한칸내려 재배열하기 ( 위에서 충돌하지 않았다면)
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
						nArr[m][n] = nArr[m - 1][n];
					}
				}
			}
			m = 0;
		}

		// 게임 패배 조건 - nArr의 3행에 2가 저장된다면 gg
		for (int i = 1; i < 11; i++) {
			if (nArr[3][i] == 2) {
				Stage = RESULT;
			}
		}
		break;
	case RESULT:

		break;
	}
	

}



void Render() {
	clock_t Curtime = clock();
	ScreenClear();
	//출력코드
	

	switch (Stage) {
	case READY :
		MapReady1();
		if (Curtime % 1000 > 500) { // 깜빡임
			MapReady2();
		}
		break;
	case RUNNING :
		//=============================
		// 배열을 출력
		//=============================
		for (int i = 4; i < 22; i++) {
			for (int j = 0; j < 12; j++) {
				if (nArr[i][j] == 2) {
					ScreenPrint(j * 2, i - 3, "▩");
				}
				else if (nArr[i][j] == 1) {
					ScreenPrint(j * 2, i - 3, "■");
				}
				else {
					ScreenPrint(j * 2, i - 3, "  ");
				}
			}
		}
		// 다음 블록을 우측에서 미리 출력
		MapNext(&nBlockType2);
		MapScore(&nScore);
		//==============================
		break;
	case RESULT:
		MapResult(&nScore);
		break;
	}
	Map();
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
				if (nKey == 13) {
					PlaySound(TEXT("tetris.wav"), NULL, SND_ASYNC | SND_LOOP);
					Stage = RUNNING;
				}
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
						nSpawning = 3;
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