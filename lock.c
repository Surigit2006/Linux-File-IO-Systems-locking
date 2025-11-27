//C program that illustrates files locking goes here
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    struct flock lock;
    int fd;

    fd = open("lockfile.txt", O_WRONLY | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;     // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;            // Lock entire file

    printf("Trying to acquire lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Lock acquired. Press Enter to release lock...\n");
    getchar();                 // Hold the lock

    lock.l_type = F_UNLCK;     // Unlock
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
        close(fd);
        return 1;
    }

    printf("Lock released.\n");
    close(fd);
    return 0;
}
