#include "system_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

// 시스템 정보를 출력하는 함수
void print_system_info() {
    printf("System information:\n");
    system("uname -a");
}

// 프로세스 정보를 출력하는 함수
void print_process_info() {
    printf("Process information:\n");
    system("ps -e");
}

// 자식 프로세스를 생성하여 작업을 수행하는 함수
void create_process_example(const char *cmd) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스
        execlp(cmd, cmd, NULL);
        perror("execlp");
        exit(1);
    } else {
        // 부모 프로세스
        wait(NULL);
        printf("%s command executed\n", cmd);
    }
}

// 시그널 핸들러 함수
void signal_handler(int sig) {
    printf("Received signal %d\n", sig);
}

// 메모리 매핑을 사용하는 함수
void memory_mapping_example() {
    int fd;
    char *data;

    fd = open("example.txt", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // 파일 크기를 확인하고, 그 크기를 기반으로 매핑해야 합니다.
    struct stat file_stat;
    if (fstat(fd, &file_stat) < 0) {
        perror("fstat");
        close(fd);
        exit(1);
    }

    if (file_stat.st_size == 0) {
        fprintf(stderr, "File is empty\n");
        close(fd);
        return;
    }

    data = mmap(NULL, file_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    printf("Mapped file content: %s\n", data);

    munmap(data, file_stat.st_size);
    close(fd);
}

