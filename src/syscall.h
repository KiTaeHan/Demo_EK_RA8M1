#ifndef SYSCALL_H_
#define SYSCALL_H_

#include <sys/stat.h>

int _open(char *path, int flags, ...);
int _close(int file);
int _read(int file, char *ptr, int len);
int _write(int file, char *ptr, int len);
int _lseek(int file, int ptr, int dir);
int _fstat(int file, struct stat *st);
int _isatty(int file);

#endif /* SYSCALL_H_ */
