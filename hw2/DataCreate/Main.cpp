#include<cstdio>
#include<cstdlib>
#include<time.h>

#define N 1000

int main() {
	FILE* fa;
	fa = fopen("lab1.data", "wb");

	srand(time(NULL));
	int temp;
	temp = N;

	fwrite(&temp, sizeof(int), 1, fa);

	for (int i = temp - 1; i >= 0; i--) {
		//temp = (int)rand();

		/*
			아래 주석을 해체하면 0~ 2^15가 아닌 0 ~ 2^30 사이의 random 데이터가 나옵니다.

			테스트 하고자 하는 data의 크기가 2^15 이상이라면 아래 주석을 해체해서

			같은 데이터들을 최대한 적게 만들어 시간 측정을 함에 있어서 객관적으로 판단할 수 있게 됩니다.

			반드시 2^20 이상의 데이터에 대해서도 테스트 해주세요. 

			이론적인 시간과 일치하는지도 확인하면 좋습니다.

			예를 들면 제공드린 코드가 Bubble Sort 인데, 데이터의 수를 2^5 에서 2^10으로 늘리게 되면

			n이 2^5만큼 증가했기 때문에, 이론 상으론 n^2이여서 2^10, 1024배만큼의 시간이 증가해야 합니다.

			이런 것들을 확인해 보시고 보고서에 작성해주시면 되겠습니다.

			감사합니다.
		*/
		
		/*if (temp != 0) {
			temp = temp << 15;
			temp += (int)rand();
		}*/
		fwrite(&i, sizeof(int), 1, fa);
	}
	
	fclose(fa);

	return 0;
}

