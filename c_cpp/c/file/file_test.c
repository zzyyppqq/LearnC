#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>

void read_file();

void stdin_input_text();

int setRawMode();

int main() {
    printf("start...\n");

    //stdin_input_text();
    //read_file();

    setRawMode();

    return 0;
}

int setRawMode() {
    static struct termios orig_termios; // Save original terminal status here.
    struct termios raw;

    int fd = fileno(stdin);

    printf("Standard Input File Descriptor: %d\n", fd);

    if (!isatty(fd))goto fatal;
    // 用于获取与终端相关的属性配置
    if (tcgetattr(fd, &orig_termios) == -1) goto fatal;

    raw = orig_termios;
    // 设置为原始模式
    cfmakeraw(&raw);

    // 用于设置终端的属性配置
    if (tcsetattr(fd, TCSAFLUSH, &raw) < 0) goto fatal;


    return 0;

fatal:
    errno = ENOTTY;
    return -1;
}

void stdin_input_text() {
    while (1) {
        int fd = fileno(stdin);
        printf("Standard Input File Descriptor: %d\n", fd);

        printf("input\n");
        // 使用文件描述符进行底层 I/O 操作
        char buffer[100];
        read(fd, buffer, sizeof(buffer));
        printf("print: %s\n", buffer);
    }
}

void read_file() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error");
        printf("errno = %d\n", errno);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}
