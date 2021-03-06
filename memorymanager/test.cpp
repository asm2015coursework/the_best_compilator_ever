#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include "manager.h"


void test1() {
	void* a = cmm_malloc(4);
	int* b = (int*) a;
	*b = -1;
	printf("%d\n", *b);
	printf("\n");
}

void test2() {
	void *a = cmm_malloc(100);
	printf("%lld\n", a);
	void *b = cmm_malloc(100);
	printf("%lld\n", b);
	void *c = cmm_malloc(100);
	printf("%lld\n", c);
	void *d = cmm_malloc(100);
	printf("%lld\n", d);
	void *a1 = cmm_malloc(100);
	printf("%lld\n", a1);
	void *b1 = cmm_malloc(100);
	printf("%lld\n", b1);
	void *c1 = cmm_malloc(100);
	printf("%lld\n", c1);
	void *d1 = cmm_malloc(100);
	printf("%lld\n", d1);
	cmm_free(a);
	cmm_free(d);
	cmm_free(a1);
	cmm_free(c);
	cmm_free(b);
	cmm_free(b1);
	cmm_free(c1);
	a = cmm_malloc(700);
	printf("%lld\n", a);
	printf("\n");
}

void test3() {
	void *a = cmm_malloc(1400);
	printf("%lld\n", a);
	void *b = cmm_malloc(100);
	printf("%lld\n", b);
	cmm_free(a);
	a = cmm_malloc(700);
	printf("%lld\n", a);
	a = cmm_malloc(600);
	printf("%lld\n", a);
	a = cmm_malloc(700);
	printf("%lld\n", a);
	printf("\n");
}

void test4() {
	void *a = cmm_malloc(1400);
	printf("%lld\n", a);
	void *b = cmm_malloc(100);
	printf("%lld\n", b);
	cmm_free(a);
	cmm_free(b);
	a = cmm_malloc(1400);
	printf("%lld\n", a);
	b = cmm_malloc(100);
	printf("%lld\n", b);
	cmm_free(a);
	cmm_free(b);
	printf("\n");
}


void test5() {
	void *a = cmm_malloc(100000);
	printf("%lld\n", a);
	void *b = cmm_malloc(100);
	printf("%lld\n", b);
	void *c = cmm_malloc(100000);
	printf("%lld\n", c);
	void *d = cmm_malloc(100);
	printf("%lld\n", d);
	cmm_free(a);
	cmm_free(c);
	cmm_free(b);
	a = cmm_malloc(200000);
	printf("%lld\n", a);
	b = cmm_malloc(100);
	printf("%lld\n", b);
	cmm_free(a);
	cmm_free(b);
	printf("\n");
}

void test6() {
	void *a = cmm_malloc(100000);
	printf("%lld\n", a);
	void *b = cmm_malloc(100);
	printf("%lld\n", b);
	void *c = cmm_malloc(100000);
	printf("%lld\n", c);
	void *d = cmm_malloc(100);
	printf("%lld\n", d);
	int *array = (int *) c;
	for (int i = 0; i < 25000; i++) {
		array[i] = i;
	}
	cmm_free(a);
	cmm_free(b);
	cmm_free(d);
	for (int i = 0; i < 25000; i++) {
		assert(array[i] == i);
	}
	printf("%s\n", "OK");
}


int main(int arg, char* args[]) {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	
	return 0;
}
