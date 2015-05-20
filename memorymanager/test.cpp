#include <stdio.h>
#include "manager.h"

int main(int arg, char* args[]) {
	void* t = malloc(10);
	free(t);
	//printf("OK\n");
	return 0;
}
