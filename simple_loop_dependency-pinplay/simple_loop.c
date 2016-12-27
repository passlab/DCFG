#include <stdio.h>
#include <stdlib.h>
int n = 0;
int main(int argc, char *argv[]) {
	for (int i = 0; i < 3; i++) {
		n = n + 1;
	}
	printf("n = %d\n", n);
	exit(0);
}
