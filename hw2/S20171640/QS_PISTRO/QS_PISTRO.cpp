#include<cstdio>
#include<cstdlib>
#include<Windows.h>

/*
	Algorithm Asignment2 예제 코드입니다.
	과제 진행에 있어 Release모드를 반드시 확인해 주세요. Debug랑 속도가 엄청 차이납니다.
	a라는 전역변수는 사용하지 말아주세요. CHECK_TIME_END 시에 버그가 발생합니다.

	아래와 같은 코드를 기본으로 코딩을 해주시면 됩니다.
*/

//시간 측정 코드입니다. 
#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);
// a라는 전역변수를 절대 사용하지 마세요. 시간측정 오류가 발생합니다.

//SWAP을 진행하는 매크로 입니다.
#define SWAP(a, b) {\
	swap_temp = a; a = b; b = swap_temp;\
}

//파일 이름에 대한 매크로 입니다.
#define FILE_NAME "input_array_2_10.bin"

//지우지
__int64 start, freq, end;
float resultTime;
int swap_temp;
//마세요!


int Validation(int* data, int left, int right);
void Quick_Sort_PISTRO(int* data, int left, int right);
int partition(int* data, int left, int right);
int Insertion_Sort(int*, int, int);

#define M 15
int N;
int main() {


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
	Quick_Sort_PISTRO(Arr, 0, N - 1);
	CHECK_TIME_END(resultTime);

	if (Validation(Arr, 0, N) == 0) {
		printf("Well Done\n");
	}
	else { // Validation 결과가 올바르지 않으면 에러메시지를 출력합니다.
		printf("Try Again\n");
	}

	//시간출력
	printf("Total Time is [ %f (ms)]\n", resultTime*1000.0f);


	//for data check
	for (int i = 0; i < N; i++) {
		printf("\t[%d]'s data is %d\n", i, Arr[i]);
	}
	

	fclose(fa);
	return 0;
}
int Insertion_Sort(int* data, int left, int right) {
	CHECK_TIME_START;
	int i, j, tmp;

	for (i = left + 1; i < right; i++) {
		tmp = data[i];
		for (j = i; j > 0 && data[j - 1] > tmp; j--) {
			data[j] = data[j - 1];
		}
		data[j] = tmp;
	}
	CHECK_TIME_END(resultTime);
	return Validation(data, left, right);
}
void Quick_Sort_PISTRO(int* data, int left, int right) {
	int pivot, i, j, tmp;

	while (left < right) {
			SWAP(data[(left + right) / 2], data[right - 1]);

			if (data[left] < data[right - 1])
				SWAP(data[left], data[right - 1]);
			if (data[left] < data[right])
				SWAP(data[left], data[right]);
			if (data[right - 1] < data[right])
				SWAP(data[right - 1], data[right]);

			pivot = partition(data, left + 1, right - 1);

		if (pivot < (left + right) / 2) {
			Quick_Sort_PISTRO(data, left, pivot - 1);
		}
		else {
			Quick_Sort_PISTRO(data, pivot + 1, right);
		}
		if (left1 == 0 && right1 == N - 1) {
			Insertion_Sort(data, 0, N);
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