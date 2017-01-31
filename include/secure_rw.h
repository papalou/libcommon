#ifndef __SECURE_RW_H__
#define __SECURE_RW_H__

int secure_read(int fd, void * buf, size_t count);
int secure_write(int fd, void * buf, size_t count);

#endif
