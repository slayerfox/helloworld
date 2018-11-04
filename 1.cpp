#include <fcntl.h>

int creat(const char *pathname, mode_t mode);  // 相当于 open (pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);


#define BUFFSIZE 4096

int
main(void)
{
    // 从输入拷贝内容到输出
    int    n;
    char   buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");

    if (n < 0)
        err_sys("read error");

    exit(0);
}
