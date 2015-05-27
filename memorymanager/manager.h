#ifndef MANAGER_H
#define MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

void* my_malloc(int sizemem);
void my_free(void* ptrmem);
void init_my_heap();

#ifdef __cplusplus
}
#endif

#endif