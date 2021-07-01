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
#define FILE_NAME "input_array_2_10.bin"

//������
__int64 start, freq, end;
float resultTime;
int swap_temp;
//������!

int Validation(int* data, int left, int right);
int Bubble_Sort(int* data, int left, int right);

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

	
	if (Bubble_Sort(Arr, 0, N) == 1) {
		printf("Well Done\n");
	}
	else { // Validation ����� �ùٸ��� ������ �����޽����� ����մϴ�.
		printf("Try Again\n");
	}

	//�ð����
	printf("Total Time is [ %f (ms)]\n", resultTime*1000.0f);

	
	//for data check
	// �ּ� ��ü �Ͻð� �����͸� Ȯ���غ��ø� �˴ϴ�.

	/*for (int i = 0; i < N; i++) {
		printf("\t[%d]'s data is %d\n", i, Arr[i]);
	}*/

	fclose(fa);
	return 0;
}

int Bubble_Sort(int* data, int left, int right) {	
	// �������� ������� Bubble Sort �ڵ带 �����߽��ϴ�.
	// �����Ͻð� �����ؾ� �ϴ� �ڵ�� �����Ͻø� �ǰڽ��ϴ�.
	CHECK_TIME_START;
	for (int i = left; i < right; i++) {
		for (int j = 0; j < right - 1 - i; j++) {
			if (data[j] > data[j + 1]) {
				SWAP(data[j], data[j+1]);
			}
		}
	}
	CHECK_TIME_END(resultTime);
	return Validation(data, left, right);
}

int Validation(int* data, int left, int right) {
	for (int i = left; i < right-1; i++) {
		if( data[i] > data[i+1]) return -1;
	}
	return 1;
}