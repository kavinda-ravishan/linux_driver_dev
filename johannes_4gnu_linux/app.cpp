#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>

int main() {

    const int sls_dev = open("/dev/sls_dev", O_RDWR);

    if(sls_dev == -1) {
        printf("Fail to open the device!\n");
        return -1;
    }

    printf("Opening was successfull!\n");

    const char input_buff[] = "hello world\n";
    if(-1 == write(sls_dev, input_buff, sizeof(input_buff))) {
        printf("Fail to write data to device!\n");
        return -1;
    }

    char output_buff[255];
    if(-1 == read(sls_dev, output_buff, sizeof(output_buff))) {
        printf("Fail to read data from device!\n");
        return -1;
    }

    printf("msg : %s", output_buff);

    close(sls_dev);

    return 0;
}