#ifndef MANAGER_H
#define MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

void* cmm_malloc(int sizemem);
void cmm_free(void* ptrmem);

#ifdef __cplusplus
}
#endif

#endif