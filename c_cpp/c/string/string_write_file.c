//
// Created by 张宜鹏 on 2023/2/20.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


#define XCC_ERRNO_UNKNOWN  1001
#define XCC_ERRNO_INVAL    1002
#define XCC_ERRNO_NOMEM    1003
#define XCC_ERRNO_NOSPACE  1004
#define XCC_ERRNO_RANGE    1005
#define XCC_ERRNO_NOTFND   1006
#define XCC_ERRNO_MISSING  1007
#define XCC_ERRNO_MEM      1008
#define XCC_ERRNO_DEV      1009
#define XCC_ERRNO_PERM     1010
#define XCC_ERRNO_FORMAT   1011
#define XCC_ERRNO_ILLEGAL  1012
#define XCC_ERRNO_NOTSPT   1013
#define XCC_ERRNO_STATE    1014
#define XCC_ERRNO_JNI      1015
#define XCC_ERRNO_FD       1016

#define XCC_ERRNO_SYS     ((0 != errno) ? errno : XCC_ERRNO_UNKNOWN)



int xcc_util_write(int fd, const char *buf, size_t len)
{
    size_t      nleft;
    ssize_t     nwritten;
    const char *ptr;

    if(fd < 0) return XCC_ERRNO_INVAL;

    ptr   = buf;
    nleft = len;

    while(nleft > 0)
    {
        errno = 0;
        if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0; /* call write() again */
            else
                return XCC_ERRNO_SYS;    /* error */
        }

        nleft -= (size_t)nwritten;
        ptr   += nwritten;
    }

    return 0;
}


int xcc_util_write_str(int fd, const char *str)
{
    const char *tmp = str;
    size_t      len = 0;

    if(fd < 0) return XCC_ERRNO_INVAL;

    while(*tmp) tmp++;
    len = (size_t)(tmp - str);
    //printf("str: %s, len: %d\n", str, len);
    if(0 == len) return 0;

    return xcc_util_write(fd, str, len);
}



int main() {
    const char haystack[20] = "RUNOOB";
    const char needle[10] = "NOOB";
    char *ret;
    ret = strstr(haystack, needle);
    printf("子字符串是： %s\n", ret);

    char str[5] = {'a','b','c','d','\0'};
    printf("%s\n",str);//乱码

    int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        printf("Open Error!\n");
        return 0;
    }

    //syscall(6, fd);
    //close(fd);
    printf("fd: %d\n", fd);
    xcc_util_write_str(fd, "123\n");

    char  cmd[128] = "adb logcat -b main -d -v threadtime -t 10";
    char  buf[1025];
    char  pid_filter[64] = "";
    char  pid_label[32] = "";
    int   r = 0;
    printf("sizeof(cmd): %d\n", sizeof(cmd));
    printf("strlen(cmd): %d\n", strlen(cmd));


    FILE *fp;
    if(NULL != (fp = popen(cmd, "r")))
    {
        buf[sizeof(buf) - 1] = '\0';
        while(NULL != fgets(buf, sizeof(buf) - 1, fp))
            if(NULL != strstr(buf, pid_label)) {
                if (0 != (r = xcc_util_write_str(fd, buf))) break;
            }
        pclose(fp);
    }

    //system("ls -al /etc/passwd /etc/shadow");

    //execl("ls", "-al", "./");


    return 0;
}
