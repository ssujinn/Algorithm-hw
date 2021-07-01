#include <stdio.h>
#include <stdlib.h>

int calculate(int*, int*, int*);

int **checkTable;	// 2���� Table

int main() {
	FILE *fp1 = fopen("input.txt", "r");
	FILE *fp2 = fopen("output.txt", "w");
	int Lcard, Rcard, Mcard;
	int i, j;
	int *left, *right, *mix;

	// ���Ϸκ��� ���� �Է�
	fscanf(fp1, "%d", &Lcard);
	left = (int*)malloc(sizeof(int)*(Lcard+1));
	left[0] = Lcard;
	for (j = 1; j <= Lcard; j++)
		fscanf(fp1, "%d", &left[j]);

	fscanf(fp1, "%d", &Rcard);
	right = (int*)malloc(sizeof(int)*(Rcard+1));
	right[0] = Rcard;
	for (j = 1; j <= Rcard; j++)
		fscanf(fp1, "%d", &right[j]);

	// ���̺� ����
	checkTable = (int**)malloc(sizeof(int)*(Lcard + 3));
	for (i = 0; i < Lcard + 3; i++)
		checkTable[i] = (int*)malloc(sizeof(int)*(Rcard + 3));

	// testcase �Է�
	for (i = 0; i < 2; i++) {
		fscanf(fp1, "%d", &Mcard);
		mix = (int*)malloc(sizeof(int)*(Mcard + 1));
		mix[0] = Mcard;
		for (j = 1; j <= Mcard; j++)
			fscanf(fp1, "%d", &mix[j]);
		fprintf(fp2, "%d", calculate(left, right, mix));
		free(mix);
	}

	// ���� �Ҵ� ����
	free(left);
	free(right);
	for (i = 0; i < Lcard + 3; i++)
		free(checkTable[i]);
	free(checkTable);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

int calculate(int* left, int* right, int* mix) {
	int result = 0;
	int i, j, k = 1, cnt = 0;
	int m = left[0], n = right[0], t = mix[0];
	int flag = 0, tmp1, tmp2;

	// Table �ʱ�ȭ
	for (i = 0; i < m + 3; i++) {
		for (j = 0; j < n + 3; j++) {
			checkTable[i][j] = 0;
		}
	}
	for (i = 1; i <= m; i++)
		checkTable[i + 1][0] = left[i];
	for (i = 1; i <= n; i++)
		checkTable[0][i + 1] = right[i];
	checkTable[1][1] = 1;

	// Table ä��� (�ʱⰪ : 0, �湮�ߴ� �� : 1, ������ �� : -1)
	i = 1; j = 1;
	while (i < m + 2 && j < n + 2 && k <= t) {
		// ����������
		if (checkTable[0][j + 1] == mix[k] && checkTable[i][j + 1] != -1) {
			j++; k++;
			checkTable[i][j] = checkTable[i][j - 1];
			flag = 0;
		}
		// ����
		else if (checkTable[i + 1][0] == mix[k] && checkTable[i + 1][j] != -1) {
			i++; k++;
			checkTable[i][j] = checkTable[i - 1][j];
			flag = 0;
		}
		// ���� ����
		else if (i == 1 && j == 1)
			break;
		// �Դ� ��� ���ư���
		else {
			checkTable[i][j] = -1 * checkTable[i][j];
			k--;
			if (flag == 1) {
				checkTable[tmp1][tmp2] = 0;
				if (j == tmp2)
					checkTable[tmp1 - 1][tmp2 + 1] = 0;
				if (i == tmp1)
					checkTable[tmp1 + 1][tmp2 - 1] = 0;
			}
			flag = 1; tmp1 = i;  tmp2 = j;
			if (checkTable[i][j - 1] == 1)
				j--;
			else if (checkTable[i - 1][j] == 1)
				i--;
		}
	}

	// ������ �����ϸ� 1 �ƴϸ� 0
	if (checkTable[m + 1][n + 1] == 1)
		result = 1;

	return result;
}