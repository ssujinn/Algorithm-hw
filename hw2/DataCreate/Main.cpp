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
			�Ʒ� �ּ��� ��ü�ϸ� 0~ 2^15�� �ƴ� 0 ~ 2^30 ������ random �����Ͱ� ���ɴϴ�.

			�׽�Ʈ �ϰ��� �ϴ� data�� ũ�Ⱑ 2^15 �̻��̶�� �Ʒ� �ּ��� ��ü�ؼ�

			���� �����͵��� �ִ��� ���� ����� �ð� ������ �Կ� �־ ���������� �Ǵ��� �� �ְ� �˴ϴ�.

			�ݵ�� 2^20 �̻��� �����Ϳ� ���ؼ��� �׽�Ʈ ���ּ���. 

			�̷����� �ð��� ��ġ�ϴ����� Ȯ���ϸ� �����ϴ�.

			���� ��� �����帰 �ڵ尡 Bubble Sort �ε�, �������� ���� 2^5 ���� 2^10���� �ø��� �Ǹ�

			n�� 2^5��ŭ �����߱� ������, �̷� ������ n^2�̿��� 2^10, 1024�踸ŭ�� �ð��� �����ؾ� �մϴ�.

			�̷� �͵��� Ȯ���� ���ð� �������� �ۼ����ֽø� �ǰڽ��ϴ�.

			�����մϴ�.
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
