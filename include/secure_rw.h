#ifndef __SECURE_RW_H__
#define __SECURE_RW_H__

//Needed to use this header file with C++ source code
#ifdef __cplusplus
extern "C" {
#endif

int secure_read(int fd, void * buf, size_t count);
int secure_write(int fd, void * buf, size_t count);

#ifdef __cplusplus
}
#endif
