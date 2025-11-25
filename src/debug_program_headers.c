#include "elf_debug.h"
#include "syscalls.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        mini_printf("Usage: %s <elf_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    // Your solution here!
    int fd = sys_openat(AT_FDCWD, filename, O_RDONLY);
    if (fd < 0) {
        return -1;
    }

    Elf64_Ehdr hdr;
    long bytes_read = sys_read(fd, &hdr, sizeof(hdr));
    if (bytes_read < 0) {
        mini_printf("Unsuccessful read\n");
        return -1;
    }

    int offset = sys_lseek(fd, hdr.e_phoff, SEEK_SET);
    if (offset == -1) {
        mini_printf("Unsuccessful lseek\n");
        return -1;
    }

    uint16_t size = hdr.e_phnum * sizeof(Elf64_Phdr);

    Elf64_Phdr phdr;
    bytes_read = sys_read(fd, &phdr

    return 0;
}
