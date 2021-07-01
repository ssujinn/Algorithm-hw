#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MakeTable(char*, char*);
void Backtracking(int);

int **sequence;		// 2차원 table
int s, f, p, m, n;	// 문제에서 제시된 변수명 그대로 사용
char *xNew, *yNew;	// gap을 넣어 수정한 문자열 (역순저장)

int main() {
	FILE *fp = fopen("input.txt", "r");
	char f_name[100];
	int len[2];
	int i = 0;
	int score;
	char *x, *y;
	
	// 파일로부터 정보 저장
	fgets(f_name, sizeof(f_name), fp);
	while (1) {
		if (f_name[i] == '\n') {
			f_name[i] = '\0';
			break;
		}
		else if (f_name[i] == '\0')
			break;
		i++;
	}
	fscanf(fp, "%d %d %d", &s, &f, &p);
	fclose(fp);

	fp = fopen(f_name, "r");
	fread(len, 4, 2, fp);
	m = len[0];
	n = len[1];
	x = (char*)malloc(sizeof(char)*(m + 1));
	y = (char*)malloc(sizeof(char)*(n + 1));
	fread(x, 1, m, fp);
	fread(y, 1, n, fp);
	x[m] = '\0';
	y[n] = '\0';
	fclose(fp);

	// table 생성
	score = MakeTable(x, y);
	// gap 포함한 문자열 구하기
	Backtracking(score);

	// 동적 해제
	free(x);
	free(y);
	free(xNew);
	free(yNew);
	for (i = 0; i < m + 2; i++)
		free(sequence[i]);
	free(sequence);

	return 0;
}

int MakeTable(char *a, char *b) {
	int i, j;

	// (m+2)*(n+2) 크기의 2차원 table
	sequence = (int**)malloc(sizeof(int*)*(m + 2));
	for (i = 0; i < m + 2; i++)
		sequence[i] = (int*)malloc(sizeof(int)*(n + 2));

	sequence[0][0] = sequence[0][1] = sequence[1][0] = 0;
	sequence[1][1] = 0;

	// 첫 행과 첫 열에는 염기 정보 저장
	// 두번째 열과 두번째 행은 0부터 p만큼 감소하며 저장
	for (i = 2; i < m + 2; i++) {
		sequence[i][0] = a[i - 2];
		sequence[i][1] = sequence[i - 1][1] - p;
	}
	for (i = 2; i < n + 2; i++) {
		sequence[0][i] = b[i - 2];
		sequence[1][i] = sequence[1][i - 1] - p;
	}

	// 1. 비교하는 두 염기가 같을 경우 (좌측 상단) + s
	//    비교하는 두 염기가 다를 경우 (좌측 상단) - f
	// 2. (좌측) - p
	// 3. (상단) - p
	// 위 세가지 경우 중 가장 큰 경우를 저장한다
	for (i = 2; i < m + 2; i++) {
		for (j = 2; j < n + 2; j++) {
			if (sequence[i][0] == sequence[0][j])
				sequence[i][j] = sequence[i - 1][j - 1] + s;
			else
				sequence[i][j] = sequence[i - 1][j - 1] - f;

			if ((sequence[i][j - 1] - p) > sequence[i][j])
				sequence[i][j] = sequence[i][j - 1] - p;
			if ((sequence[i - 1][j] - p) > sequence[i][j])
				sequence[i][j] = sequence[i - 1][j] - p;
		}
	}

	return sequence[m + 1][n + 1];
}

void Backtracking(int score) {
	int len = 0;
	int num_gap = 0;
	int i = m + 1, j = n + 1;
	int xgap = 0, ygap = 0;
	int k = 1, l = 1;

	// 새로운 염기서열을 역순으로 저장할 문자열
	xNew = (char*)malloc(sizeof(char)*(m + n + 2));
	yNew = (char*)malloc(sizeof(char)*(m + n + 2));

	xNew[0] = 0;
	yNew[0] = 0;
	xNew[0] = sequence[i][0];
	yNew[0] = sequence[0][j];

	// 가장 우측 하단에 있는 원소부터 가장 좌측 상단의 원소까지 돌아간다
	while (i != 1 && j != 1) {
		if (sequence[i][j] == sequence[i][j - 1] - p) {
			j--;
			xgap++;
			xNew[k] = xNew[k - 1];
			xNew[k - 1] = '-';
			k++;
			if (j != 1) {
				yNew[l] = sequence[0][j];
				l++;
			}

		}
		else if (sequence[i][j] == sequence[i - 1][j] - p) {
			i--;
			ygap++;
			yNew[l] = yNew[l - 1];
			yNew[l - 1] = '-';
			l++;
			if (i != 1) {
				xNew[k] = sequence[i][0];
				k++;
			}
		}
		else if (sequence[i][0] == sequence[0][j] && sequence[i][j] == sequence[i - 1][j - 1] + s || sequence[i][0] != sequence[0][j] && sequence[i][j] == sequence[i - 1][j - 1] - f) {
			i--;
			j--;
			if (i != 1) {
				xNew[k] = sequence[i][0];
				k++;
			}
			if (j != 1) {
				yNew[l] = sequence[0][j];
				l++;
			}
		}
		else {
			printf("Error");
			break;
		}
		len++;
	}

	// 남은 것들 처리
	if (i == 1) {
		while (j > 2) {
			j--;
			xgap++;
			xNew[k] = xNew[k - 1];
			xNew[k - 1] = '-';
			k++;
			yNew[l] = sequence[0][j];
			l++;
		}
		if (k != l) {
			xgap++;
			xNew[k] = '-';
			k++;
			j--;
		}
	}
	if (j == 1) {
		while (i > 2) {
			i--;
			ygap++;
			yNew[l] = yNew[l - 1];
			yNew[l - 1] = '-';
			l++;
			xNew[k] = sequence[i][0];
			k++;
		}
		if (k != l) {
			i--;
			ygap++;
			yNew[l] = '-';
			l++;
		}
	}
	xNew[k] = '\0';
	yNew[l] = '\0';

	// 결과 출력
	FILE *fp = fopen("output.txt", "w");
	fprintf(fp, "%d\n%d\n", score, k);
	fprintf(fp, "%d\n", xgap);
	for (i = k -1; i >= 0; i--) {
		if (xNew[i] == '-')
			fprintf(fp, "%d\n", k - i);
	}
	fprintf(fp, "%d\n", ygap);
	for (i = k - 1; i >= 0; i--) {
		if (yNew[i] == '-')
			fprintf(fp, "%d\n", k - i);
	}
	fclose(fp);
}