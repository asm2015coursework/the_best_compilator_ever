#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

int main(int arg, char* args[]) {
	/*init_cmm_heap();
	void *t = cmm_malloc(102);
	printf("%lld\n", t);
	t = cmm_malloc(10);
	printf("%lld\n", t);
	t = cmm_malloc(10);
	printf("%lld\n", t);
	cmm_free(t);
	int* c = (int*) t;
	c[0] = 1;
	printf("%d\n", c[0]);

	t = cmm_malloc(400002);
	printf("%lld\n", t);
	t = cmm_malloc(1002);
	printf("%lld\n", t);
	*/
	void* a = malloc(100000);
	printf("%lld\n", a);
	void* d = malloc(10);
	printf("%lld\n", d);
	free(a);
	void* e = malloc(101001);
	printf("%lld\n", e);
	return 0;
}
