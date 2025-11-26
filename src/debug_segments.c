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
        mini_printf("Could not open file\n");
        return -1;
    }

    Elf64_Ehdr hdr;
    long bytes_read = sys_read(fd, &hdr, sizeof(hdr));
    if (bytes_read < 0) {
        mini_printf("Unsuccessful elf header read\n");
        return -1;
    }

    int offset = sys_lseek(fd, hdr.e_phoff, SEEK_SET);
    if (offset < 0) {
        mini_printf("Unsuccessful lseek\n");
        return -1;
    }

    size_t size = hdr.e_phnum * sizeof(Elf64_Phdr);

    Elf64_Phdr phdr_table;
    bytes_read = sys_read(fd, &phdr_table, size);
    if (bytes_read < 0) {
        mini_printf("Unsuccessful program header read\n");
        return -1;
    }

    for (int i = 0; i < hdr.e_phnum; i ++) {
        if (phdr_table[i].p_type == PT_LOAD) {
            // Requested virtual address range
            
            // Page-aligned address range
            
            // Size in bytes and pages

            // File offset and size

            // BSS/Zero-filled regions (if memsz > filesz)

            // Permissions

    return 0;
}
