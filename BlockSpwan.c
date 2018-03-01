#include<time.h>
#include<stdlib.h>
#include"BlockData.h"

// 블록 모양 결정
int BlockSpwan(void) {
	srand(time(NULL));
	return rand() % 7; // 0~6까지...

}

// 결정된 블록 맨 위에서 출력하기
void BlockSpwan2(int(*arr)[12], int* nType) {
	*nType = BlockSpwan();

	switch (*nType) {
	case  0:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i][j] = Block0[0][i][j];
			}
		}
		break;
	case 1:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i + 1][j + 1] = Block1[0][i][j];
			}
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i + 1][j + 1] = Block2[0][i][j];
			}
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i + 1][j + 1] = Block3[0][i][j];
			}
		}
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i + 1][j + 1] = Block4[0][i][j];
			}
		}
		break;
	case 5:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i + 1][j + 1] = Block5[0][i][j];
			}
		}
		break;
	case 6:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i + 1][j + 1] = Block6[0][i][j];
			}
		}
		break;
	}
}