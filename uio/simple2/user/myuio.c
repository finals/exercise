#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

#define UIO_DEV "/dev/uio0"
#define UIO_ADDR "/sys/class/uio/uio0/maps/map0/addr"
#define UIO_SIZE "/sys/class/uio/uio0/maps/map0/size"

static char uio_addr_buf[16], uio_size_buf[16];

int main(void)
{
    int uio_fd, addr_fd, size_fd;
    int uio_size;
    void *uio_addr, *access_address;

    uio_fd = open(UIO_DEV, O_RDWR);
    addr_fd = open(UIO_ADDR, O_RDONLY);
    size_fd = open(UIO_SIZE, O_RDONLY);
    if (addr_fd < 0 || size_fd < 0 || uio_fd < 0) {
        fprintf(stderr, "open: %s\n", strerror(errno));
        exit(-1);
    }

    read(addr_fd, uio_addr_buf, sizeof(uio_addr_buf));
    close(addr_fd);

    read(size_fd, uio_size_buf, sizeof(uio_size_buf));
    close(size_fd);

    uio_addr = (void *)strtoul(uio_addr_buf, NULL, 0);
    uio_size = (int)strtol(uio_size_buf, NULL, 0);

    access_address = mmap(NULL, uio_size, PROT_READ | PROT_WRITE, MAP_SHARED, uio_fd, 0);
    if ( access_address == (void*)-1) {
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        exit(-1);
    }

    printf("The device address %p (length %d)\n"
           "can be accessed over\n"
           "logical address %p\n", uio_addr, uio_size, access_address);

    printf("access_address = %lu\n", *((unsigned long*)access_address));

    unsigned long * addr = (unsigned long *)access_address;

    printf("1: read addr:%lu\n", *addr);
    printf("1: write 0 to access_address\n");

    //��д����
    *addr = 0;


    munmap(access_address, uio_size);
    close(uio_fd);

    return 0;
}

