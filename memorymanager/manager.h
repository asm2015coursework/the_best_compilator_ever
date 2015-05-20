#ifndef MANAGER_H
#define MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

void* malloc(int sizemem);
void free(void* ptrmem);

#ifdef __cplusplus
}
#endif

#endif