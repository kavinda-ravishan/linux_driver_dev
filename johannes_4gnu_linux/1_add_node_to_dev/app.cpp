#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>

int main() {

    const int sls_dev = open("/dev/sls_dev", O_RDONLY);

    if(sls_dev == -1) {
        printf("Fail to open the device\n");
        return -1;
    }

    printf("Opening was successfull!\n");

    close(sls_dev);
    return 0;
}