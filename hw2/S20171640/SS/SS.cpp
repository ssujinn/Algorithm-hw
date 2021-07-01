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
#define FILE_NAME "descend_array_2_10.bin"

//지우지
__int64 start, freq, end;
float resultTime;
int swap_temp;
//마세요!

int Validation(int* data, int left, int right);
int Selection_Sort(int* data, int left, int right);

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
	
	
	if (Selection_Sort(Arr, 0, N) == 0) {
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

int Selection_Sort(int* data, int left, int right) {
	CHECK_TIME_START;
	int i, j, cur;

	for (i = left; i < right - 1; i++) {
		cur = i;
		for (j = i + 1; j < right; j++) {
			if (data[j] < data[cur])
				cur = j;
		}
		SWAP(data[i], data[cur]);
	}
	CHECK_TIME_END(resultTime);
	return Validation(data, left, right);
}

int Validation(int* data, int left, int right) {
	for (int i = left; i < right - 1; i++) {
		if (data[i] > data[i + 1]) return -1;
	}
	return 0;
}