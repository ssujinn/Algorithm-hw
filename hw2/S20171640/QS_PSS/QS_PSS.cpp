#include<cstdio>
#include<cstdlib>
#include<Windows.h>

/*
	Algorithm Asignment2 ���� �ڵ��Դϴ�.
	���� ���࿡ �־� Release��带 �ݵ�� Ȯ���� �ּ���. Debug�� �ӵ��� ��û ���̳��ϴ�.
	a��� ���������� ������� �����ּ���. CHECK_TIME_END �ÿ� ���װ� �߻��մϴ�.

	�Ʒ��� ���� �ڵ带 �⺻���� �ڵ��� ���ֽø� �˴ϴ�.
*/

//�ð� ���� �ڵ��Դϴ�. 
#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);
// a��� ���������� ���� ������� ������. �ð����� ������ �߻��մϴ�.

//SWAP�� �����ϴ� ��ũ�� �Դϴ�.
#define SWAP(a, b) {\
	swap_temp = a; a = b; b = swap_temp;\
}

//���� �̸��� ���� ��ũ�� �Դϴ�.
#define FILE_NAME "descend_array_2_10.bin"

//������
__int64 start, freq, end;
float resultTime;
int swap_temp;
//������!

int Validation(int* data, int left, int right);
void Quick_Sort_PSS(int* data, int left, int right);
int partition(int* data, int left, int right);


#define M 15

int main() {

	int N;
	int temp;
	int* Arr;
	FILE* fa = fopen(FILE_NAME, "rb");
	fread(&N, sizeof(int), 1, fa);

	Arr = (int*)malloc(sizeof(int) * N);
	printf("[ %d ] Numbers Of Input Data\n", N);
	for (int i = 0; i < N; i++) {
		fread(&temp, sizeof(int), 1, fa);
		Arr[i] = temp;
	}
	CHECK_TIME_START;
	Quick_Sort_PSS(Arr, 0, N - 1);
	CHECK_TIME_END(resultTime);

	if (Validation(Arr, 0, N) == 0) {
		printf("Well Done\n");
	}
	else { // Validation ����� �ùٸ��� ������ �����޽����� ����մϴ�.
		printf("Try Again\n");
	}

	//�ð����
	printf("Total Time is [ %f (ms)]\n", resultTime*1000.0f);

	
	//for data check
	for (int i = 0; i < N; i++) {
		printf("\t[%d]'s data is %d\n", i, Arr[i]);
	}
	
	fclose(fa);
	return 0;
}

void Quick_Sort_PSS(int* data, int left, int right) {
	int pivot, i, j, cur;

	if ((right - left) > 0) {
		// QS_P �κ�
		if ((right - left + 1) >= M) {
			pivot = partition(data, left, right);

			Quick_Sort_PSS(data, left, pivot - 1);
			Quick_Sort_PSS(data, pivot + 1, right);
		}
		// SS �κ�
		else {
			for (i = left; i < right; i++) {
				cur = i;
				for (j = i + 1; j <= right; j++) {
					if (data[j] < data[cur])
						cur = j;
				}
				SWAP(data[i], data[cur]);
			}
		}
	}
}

int partition(int* data, int left, int right) {
	int i, pivot;

	pivot = left;
	for (i = left; i < right; i++) {
		if (data[i] < data[right]) {
			SWAP(data[i], data[pivot]);
			pivot++;
		}
	}
	SWAP(data[right], data[pivot]);
	return(pivot);
}

int Validation(int* data, int left, int right) {
	for (int i = left; i < right - 1; i++) {
		if (data[i] > data[i + 1]) return -1;
	}
	return 0;
}