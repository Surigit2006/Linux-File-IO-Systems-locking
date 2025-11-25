# Linux-File-IO-Systems-locking
Ex07-Linux File-IO Systems-locking
# AIM:
To Write a C program that illustrates files copying and locking

# DESIGN STEPS:

### Step 1:

Navigate to any Linux environment installed on the system or installed inside a virtual environment like virtual box/vmware or online linux JSLinux (https://bellard.org/jslinux/vm.html?url=alpine-x86.cfg&mem=192) or docker.

### Step 2:

Write the C Program using Linux IO Systems locking

### Step 3:

Execute the C Program for the desired output. 

# PROGRAM:

## 1.To Write a C program that illustrates files copying 

```
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *src, *dest;
    char ch;

    src = fopen("source.txt", "r");
    if (src == NULL) {
        printf("Error: Cannot open source file.\n");
        exit(1);
    }

    dest = fopen("destination.txt", "w");
    if (dest == NULL) {
        printf("Error: Cannot open destination file.\n");
        fclose(src);
        exit(1);
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    printf("File copied successfully.\n");

    fclose(src);
    fclose(dest);
    return 0;
}
```








## 2.To Write a C program that illustrates files locking

```
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

```




## OUTPUT

<img width="1920" height="1057" alt="image" src="https://github.com/user-attachments/assets/3286cf11-584e-4c72-b429-2aa862dcc65d" />






# RESULT:
The programs are executed successfully.
