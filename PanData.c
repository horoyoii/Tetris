
// 22x12 배열 설명
// 배열요소 2 : 경계
// 배열요소 1 : 블록
// 배열요소 0 : 공백


void PanMap(int(*arr)[12]) {
	for (int i = 0; i < 12; i++) {
		arr[0][i] = 2;
		arr[21][i] = 2;
	}

	for (int i = 0; i < 22; i++) {
		arr[i][0] = 2;
		arr[i][11] = 2;
	}
}