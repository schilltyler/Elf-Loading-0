#include "mini_loader.h"
#include "elf_format.h"
#include "syscalls.h"
#include "utils.h"

#define PAGE_SIZE 0x1000
#define PAGE_ALIGN_DOWN(x) ((x) & ~(PAGE_SIZE - 1))
#define PAGE_ALIGN_UP(x) (((x) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

void *read_file_into_memory(const char *path, size_t *size) {
    // Your solution here!
    int fd = sys_openat(AT_FDCWD, path, O_RDONLY);
    if (fd < 0) {
        mini_printf("Could not open file\n");
        return -1;
    }

    size_t size = sys_lseek(fd, 0, SEEK_END);
    if (size < 0) {
        mini_printf("Error during lseek\n");
        return -1;
    }
}

uintptr_t map_elf(void *elf_data, size_t size) {
    // Your solution here!
}

void load_elf_from_path(const char *path) {
    // Your solution here!
}

int main(int argc, char **argv) {
    if (argc != 2) {
        mini_printf("Usage: %s <elf_file>\n", argv[0]);
        return 1;
    }

    load_elf_from_path(argv[1]);

    // Should never reach here
    return 0;
}
