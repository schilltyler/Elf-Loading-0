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
    
    // Table Headers
    mini_printf("Program Headers:\n");
    mini_printf("\tType\t\tOffset\t\tVirtAddr\t\tPhysAddr\n");
    mini_printf("\t\t\t\tFileSiz\t\tMemSiz\t\t Flags  Align\n");

    for (int i = 0; i < hdr.e_phnum; i ++) {
        // Type
        if (phdr_table[i].p_type == PT_NULL) {
            mini_printf("NULL");
        }
        else if (phdr_table[i].p_type == PT_LOAD) {
            mini_printf("LOAD");
        }
        else if (phdr_table[i].p_type == PT_DYNAMIC) {
            mini_printf("DYNAMIC");
        }
        else if (phdr_table[i].p_type == PT_INTERP) {
            mini_printf("INTERP");
        }
        else if (phdr_table[i].p_type == PT_NOTE) {
            mini_printf("NOTE");
        }
        else if (phdr_table[i].p_type == PT_SHLIB) {
            mini_printf("SHLIB");
        }
        else if (phdr_table[i].p_type == PT_PHDR) {
            mini_printf("PHDR");
        }
        else if (phdr_table[i].p_type >= PT_LOPROC && phdr_table[i].p_type <= PT_HIPROC) {
            mini_printf("LOPROC/HIPROC");
        }
        else (phdr_table[i].p_type == PT_LOAD) {
            mini_printf("GNU_STACK");
        }

        
        // File Offset
        
        
        // Virtual Address


        // Physical Address


        // File Size


        // Memory Size


        // Flags (R/W/X)


        // Alignment

    return 0;
}
