#include <stdio.h>
#include <cstdlib>
#include "manager.h"


void test1() {
	void *a = cmm_malloc(100);
	printf("%lld\n", a);
	void *b = cmm_malloc(100);
	printf("%lld\n", b);
	void *c = cmm_malloc(100);
	printf("%lld\n", c);
	void *d = cmm_malloc(100);
	printf("%lld\n", d);
	cmm_free(b);
	printf("HERE\n");
	cmm_free(c);
	printf("HERE\n");
	cmm_free(d);
	void *e = cmm_malloc(222);
	printf("%lld\n", e);
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
}

int main(int arg, char* args[]) {
	test5();
	
	return 0;
}
