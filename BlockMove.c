#include "BlockData.h"




// 좌로 이동
void LeftMove(int(*arr)[12]) {
	// 1) 저장받기
	int n = 0;
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (arr[i][j] == 1) { // 2차원 배열 상의 1에 대한 통제권만 가진다.
				arr[i][j] = 0;
				Block_pos[n].Pos.x = i;
				Block_pos[n].Pos.y = j;
				n++;
			}
		}
	}

	// 2) (좌로) 재배열하기
	for (int i = 0; i < 4; i++) {
		arr[Block_pos[i].Pos.x][Block_pos[i].Pos.y - 1] = 1;
	}
}


// 우로 이동
void RightMove(int(*arr)[12]) {
	// 1) 저장받기
	int n = 0;
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (arr[i][j] == 1) {
				arr[i][j] = 0;
				Block_pos[n].Pos.x = i;
				Block_pos[n].Pos.y = j;
				n++;
			}
		}
	}

	// 2) (우로) 재배열하기
	for (int i = 0; i < 4; i++) {
		arr[Block_pos[i].Pos.x][Block_pos[i].Pos.y + 1] = 1;
	}
}

// 바로 내리기
void DownMove(int(*arr)[12]) {
	// 1) 저장받기
	int n = 0;
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (arr[i][j] == 1) {
				arr[i][j] = 0;
				Block_pos[n].Pos.x = i;
				Block_pos[n].Pos.y = j;
				n++;
			}
		}
	}

	// 2) 아래로 바로 내려 재배열하기
	int m = 1;
	int v = 1;
	while (v) {
		for (int i = 0; i < 4; i++) {
			if (arr[Block_pos[i].Pos.x + m][Block_pos[i].Pos.y] == 2) {// 내려가게 될 공간이 
				v = 0;
				break;
			}
			else if (i == 3) {
				m++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		arr[Block_pos[i].Pos.x + m-1][Block_pos[i].Pos.y] = 2;
	}


	
}


// 회전
void Rotate(int(*arr)[12], int nType, BLOCK_POS* pos, int nRot) {
	int n = 0;
	switch (nType) {
	case 0:
		// 1) 저장받기
		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (arr[i][j] == 1) {
					arr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 회전시켜 재배열하기
		if (nRot % 2 != 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block0[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 1][j + Block_pos[1].Pos.y] = Block0[nRot][i][j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block0[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 1][j + Block_pos[1].Pos.y - 3] = Block0[nRot][i][j]; // 배열요소 마지막 정수들은 회전 시 모션을 조율해준다.
					}
				}
			}
		}
		break;
	case 1:
		// 1) 저장받기

		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (arr[i][j] == 1) {
					arr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 회전시켜 재배열하기
		if (nRot % 2 != 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block1[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 1][j + Block_pos[1].Pos.y] = Block1[nRot][i][j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block1[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 1][j + Block_pos[1].Pos.y - 2] = Block1[nRot][i][j]; // 배열요소 마지막 정수들은 회전 시 모션을 조율해준다.
					}
				}
			}
		}
		break;

	case 2:
		// 1) 저장받기

		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (arr[i][j] == 1) {
					arr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 회전시켜 재배열하기
		if (nRot % 2 != 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block2[nRot][i][j] == 1) {
						arr[i + Block_pos[2].Pos.x-2][j + Block_pos[2].Pos.y-1] = Block2[nRot][i][j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block2[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x-2][j + Block_pos[1].Pos.y - 1] = Block2[nRot][i][j]; // 배열요소 마지막 정수들은 회전 시 모션을 조율해준다.
					}
				}
			}
		}
		break;
	case 3:
		// 1) 저장받기

		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (arr[i][j] == 1) {
					arr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 회전시켜 재배열하기
		if (nRot % 2 != 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block3[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 2][j + Block_pos[1].Pos.y ] = Block3[nRot][i][j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block3[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 2][j + Block_pos[1].Pos.y - 1] = Block3[nRot][i][j]; // 배열요소 마지막 정수들은 회전 시 모션을 조율해준다.
					}
				}
			}
		}
		break;
	case 4:
		// 1) 저장받기

		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (arr[i][j] == 1) {
					arr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 회전시켜 재배열하기
		if (nRot % 2 != 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block4[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 2][j + Block_pos[1].Pos.y] = Block4[nRot][i][j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block4[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 2][j + Block_pos[1].Pos.y ] = Block4[nRot][i][j]; // 배열요소 마지막 정수들은 회전 시 모션을 조율해준다.
					}
				}
			}
		}
		break;
	case 5:
		break;
	case 6:
		// 1) 저장받기

		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (arr[i][j] == 1) {
					arr[i][j] = 0;
					Block_pos[n].Pos.x = i;
					Block_pos[n].Pos.y = j;
					n++;
				}
			}
		}

		// 2) 회전시켜 재배열하기
		if (nRot % 2 != 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block6[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 2][j + Block_pos[1].Pos.y] = Block6[nRot][i][j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block6[nRot][i][j] == 1) {
						arr[i + Block_pos[1].Pos.x - 2][j + Block_pos[1].Pos.y-2] = Block6[nRot][i][j]; // 배열요소 마지막 정수들은 회전 시 모션을 조율해준다.
					}
				}
			}
		}
		break;
	}
	

}