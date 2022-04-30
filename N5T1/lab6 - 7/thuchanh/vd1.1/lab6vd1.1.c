#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char result[100]; // biến lưu dữ liệu tiến trình cha ghi dữ liệu vào pipe
    int fp[2];
    int pid;
    if (argc < 2) // đối số bị sai sẽ dừng chương trình
    {
        printf("Doi so thieu.\n");
        return -1;
    }

    // điều kiện đúng thì vào
    if (pipe(fp) == 0)
    {
        pid = fork();
        if (pid < 0)
        {
            printf("Fork failed\n");
            return -1;
        }
        else if (pid == 0)
        {
            printf("Data from child : %s\n", argv[1]);
            close(fp[0]);
            // tiến trình con đọc, hiển thị dữ liệu, ghi dữ liệu
            write(fp[1], argv[1], strlen(argv[1]));
        }
        else
        {
            close(fp[1]);
            read(fp[0], result, strlen(argv[1])); // tiến trình cha đọc dữ liệu, hiển thị ra màn hình
            printf("Read from child : %s\n", result);
        }
    }
    else
    {
        // kết quả trả về -2
        printf("Pipe failed\n");
        return -2;
    }
}