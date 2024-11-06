// sender.c
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAX_BUF 1024

int main()
{
    int fd1,fd2;
    char *myfifo1 = "myfifo1";
    char *myfifo2 = "myfifo2";
    char buff[MAX_BUF];
    char buffREAD[MAX_BUF];
    char line[MAX_BUF];
    int current_len = 0;

     // Create both FIFOs
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);


    printf("Enter multiple lines of text (type 'END' to finish):\n");

    // Loop to read multiple lines and store them in buff
    while (1)
    {
        fgets(line, MAX_BUF, stdin);

        // Check if the user entered "END" to stop input
        if (strncmp(line, "END", 3) == 0)
            break;

        // Check if adding this line would exceed the buffer size
        if (current_len + strlen(line) >= MAX_BUF - 1)
        {
            printf("Buffer is full, sending what has been read so far.\n");
            break;
        }

        // Append the line to buff
        strcpy(buff + current_len, line);
        current_len += strlen(line);
    }

    // Open FIFO1 for writing and send the entire buffer
    fd1 = open(myfifo1, O_WRONLY);
    write(fd1, buff, strlen(buff) + 1);
    close(fd1);

    printf("Message sent to receiver.\n");

	fd2 = open(myfifo2, O_RDONLY);
	read(fd2, buffREAD, MAX_BUF);
    close(fd2);
	printf("\n-----Contents of a.txt from receiver-----\n%s", buffREAD);
    // Remove FIFOs
    unlink(myfifo1);
    unlink(myfifo2);

	return 0;
}
