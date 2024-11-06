// receiver.c
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BUF 1024

int main()
{
    int words = 0, lines = 0, chars = 0;
    FILE *fp;
    char buf[MAX_BUF];
    int fd1, fd2, i = 0;

    char *myfifo1 = "myfifo1";
    char *myfifo2 = "myfifo2";

    // Open FIFO1 for reading the message
    fd1 = open(myfifo1, O_RDONLY);
    read(fd1, buf, MAX_BUF);
    close(fd1);

    printf("\n-----Message received-----\n%s", buf);

    // Count lines, words, and characters
    while (buf[i] != '\0')
    {
        if (buf[i] == '\n')
            lines++;
        if (buf[i] == ' ' || buf[i] == '\n')
        {
            words++;
        }
        else
            chars++;

        i++;
    }

    printf("\nNo. of lines: %d", lines);
    printf("\nNo. of words: %d", words);
    printf("\nNo. of chars: %d", chars);
    // Save counts to a.txt
    fp = fopen("a.txt", "w");
    fprintf(fp, "No. of lines: %d\n", lines);
    fprintf(fp, "No. of words: %d\n", words);
    fprintf(fp, "No. of chars: %d\n", chars);
    fclose(fp);

    // Send contents of a.txt to FIFO2
    fd2 = open(myfifo2, O_WRONLY);
    system("cat a.txt>myfifo2");
    close(fd2);

    return 0;
}
