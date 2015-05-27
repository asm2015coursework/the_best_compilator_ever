#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

int main(int arg, char* args[]) {
	init_my_heap();
	void *t = my_malloc(102);
	printf("%lld\n", t);
	t = my_malloc(10);
	printf("%lld\n", t);
	t = my_malloc(10);
	printf("%lld\n", t);
	/*t = my_malloc(10);
	printf("%lld\n", t);
	t = my_malloc(10);
	printf("%lld\n", t);
	t = my_malloc(10);
	printf("%lld\n", t);*/
	
	my_free(t);

	t = my_malloc(1002);
	printf("%lld\n", t);
	t = my_malloc(1002);
	printf("%lld\n", t);
	
	return 0;
}
