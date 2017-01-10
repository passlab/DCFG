#include <stdio.h>
#include <stdlib.h>
int n = 0; int N=10; int a[10];
int main(int argc, char *argv[]) {
	for (int i = 0; i < N; i++) {
		n = n + a[i];
	}
	printf("n = %d\n", n);
	exit(0);
}
