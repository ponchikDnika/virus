#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int fdr, fdw;
    ssize_t ret;
    char buf;

    if(argc == 1) {
        printf("Empty args\n");
        return 1;
    }

    fdr = open(argv[0], O_RDONLY);
    if(fdr == -1) {
        perror("open");
        return 1;
    }

    fdw = open(argv[1], O_TRUNC | O_WRONLY);
    if(fdw == -1) {
        perror("open");
        return 1;
    }

    while(ret = read(fdr, &buf, sizeof(buf) * sizeof(char))) {
        if(ret == -1) {
            perror("read");
            return 1;
        }

        ret = write(fdw, &buf, ret);
        if(ret == -1) {
            perror("write");
            return 1;
        }
    }

    return 0;
}