#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// 디렉터리 내용을 출력하는 함수
void list_directory(const char *dir_path) {
    struct dirent *entry;
    DIR *dp = opendir(dir_path);
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}

// 파일 입/출력을 사용하는 함수
void file_io_example() {
    int fd;
    char buffer[100];

    // 파일 생성 및 쓰기
    fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    strcpy(buffer, "This is an example file content.\n");
    write(fd, buffer, strlen(buffer));

    close(fd);
}

// 파일 정보를 출력하는 함수
void print_file_info(const char *filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) < 0) {
        perror("stat");
        exit(1);
    }

    printf("File: %s\n", filename);
    printf("Size: %lld bytes\n", (long long)file_stat.st_size);
    printf("Permissions: %o\n", file_stat.st_mode);
    printf("Last modified: %ld\n", file_stat.st_mtime);
}

