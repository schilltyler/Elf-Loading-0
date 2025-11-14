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

    char buf[sizeof(Elf64_Ehdr)];    

    long bytes_read = sys_read(fd, buf, sizeof(Elf64_Ehdr));
    if (bytes_read < 0) {
        return -1;
    }

    if (buf[0] == 0x7f &&
        buf[1] == 'E' &&
        buf[2] == 'L' &&
        buf[3] == 'F') {

        // Magic Bytes
        sys_write(1, "Magic Bytes\n", sizeof("Magic Bytes\n"));

        for (int i = 0; i < 4; i ++) {
            sys_write(1, &buf[i], sizeof(buf[i]));
        }

        sys_write(1, "\n", sizeof("\n"));

        // Class (ELF32/ELF64)
        sys_write(1, "Class\n", sizeof("Class\n"));
        sys_write(1, &buf[4], sizeof(buf[4]));
        sys_write(1, "\n", sizeof("\n"));

        // Endianness
        sys_write(1, "Endianness\n", sizeof("Endianness\n"));   
        sys_write(1, &buf[5], sizeof(buf[5]));
        sys_write(1, "\n", sizeof("\n"));
        
        // OS/ABI
        sys_write(1, "OS/ABI\n", sizeof("OS/ABI\n"));
        sys_write(1, &buf[7], sizeof(buf[7]));
        sys_write(1, "\n", sizeof("\n"));

        // Type (EXEC, DYN, etc.)
        sys_write(1, "Type\n", sizeof("Type\n"));
        // e_ident[] is 16 bytes long
        sys_write(1, &buf[16], sizeof(buf[16]));
        sys_write(1, "\n", sizeof("\n"));

        // Machine Architecture
        sys_write(1, "Machine Architecture\n", sizeof("Machine Architecture\n"));
        // 18 because e_type is 2 bytes
        sys_write(1, &buf[18], sizeof(buf[18]));
        sys_write(1, "\n", sizeof("\n"));

        // Entry Point Address
        sys_write(1, "Entry Point Address\n", sizeof("Entry Point Addres\n"));
        sys_write(1, &buf[24], sizeof(buf[24]));
        sys_write(1, "\n", sizeof("\n"));

        // Program and Section Header Info
        sys_write(1, "Program/Section Header Info\n", sizeof("Program/Section Header Info\n"));
        sys_write(1, &buf[32], sizeof(buf[32]));
        sys_write(1, &buf[40], sizeof(buf[40]));
        sys_write(1, "\n", sizeof("\n"));
    }
    else {
        sys_write(1, "Not a valid Elf", sizeof("Not a valid Elf"));
        return -1;
    }

    return 0;
}
