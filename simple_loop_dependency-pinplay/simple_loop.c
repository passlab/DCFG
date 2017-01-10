#include <stdio.h>
#include <stdlib.h>
int n = 0; int a[100]; int N=100;
int main(int argc, char *argv[]) {
	for (int i = 0; i < N; i++) {
		n = n + a[i];
	}
	printf("n = %d\n", n);
	exit(0);
}
