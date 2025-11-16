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
        return -1;
    }

    if (hdr.e_ident[EI_MAG0] == 0x7f &&
        hdr.e_ident[EI_MAG1] == 'E' &&
        hdr.e_ident[EI_MAG2] == 'L' &&
        hdr.e_ident[EI_MAG3] == 'F') {
        
        // Magic Bytes
        mini_printf("Magic Bytes: %x %x %x %x\n", hdr.e_ident[EI_MAG0], hdr.e_ident[EI_MAG1], hdr.e_ident[EI_MAG2], hdr.e_ident[EI_MAG3]);
       
        // Class (ELF32/ELF64)
        if (hdr.e_ident[EI_CLASS] == ELFCLASSNONE) {
            mini_printf("Class: ELFNONE\n");
        }
        else if (hdr.e_ident[EI_CLASS] == ELFCLASS32) {
            mini_printf("Class: ELF32\n");
        }
        else {
            mini_printf("Class: ELF64\n");
        }
        
        // Endianness
        if (hdr.e_ident[EI_DATA] == ELFDATANONE) {
            mini_printf("Data: Unkown data format\n");
        }
        else if (hdr.e_ident[EI_DATA] == ELFDATA2LSB) {
            mini_printf("Data: 2's compliment, little endian\n");
        }
        else {
            mini_printf("Data: 2's compliment, big endian\n");
        }

        // OS/ABI
        if (hdr.e_ident[EI_OSABI] == ELFOSABI_NONE) {
            mini_printf("OS/ABI: Unix - System V\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_SYSV) {
            mini_printf("OS/ABI: Unix - System V\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_HPUX) {
            mini_printf("OS/ABI: HP-UX\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_NETBSD) {
            mini_printf("OS/ABI: NetBSD\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_LINUX) {
            mini_printf("OS/ABI: Linux\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_SOLARIS) {
            mini_printf("OS/ABI: Solaris\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_IRIX) {
            mini_printf("OS/ABI: IRIX\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_FREEBSD) {
            mini_printf("OS/ABI: FreeBSD\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_TRU64) {
            mini_printf("OS/ABI: Unix - TRU64\n");
        }
        else if (hdr.e_ident[EI_OSABI] == ELFOSABI_ARM) {
            mini_printf("OS/ABI: Arm\n");
        }
        else {
            mini_printf("OS/ABI: Stand-alone (embedded)\n");
        }

        // Type
        if (hdr.e_type == ET_NONE) {
            mini_printf("Type: Unkown\n");
        }
        else if (hdr.e_type == ET_REL) {
            mini_printf("Type: REL (Relocatable file)\n");
        }
        else if (hdr.e_type == ET_EXEC) {
            mini_printf("Type: EXEC (Executable file)\n");
        }
        else if (hdr.e_type == ET_DYN) {
            mini_printf("Type: DYN (Shared object)\n");
        }
        else {
            mini_printf("Type: CORE (Core file)\n");
        }

        // Machine Architecture
        switch (hdr.e_machine) {
            case EM_NONE:
                mini_printf("Machine: Unknown\n");
                break;
            case EM_M32:
                mini_printf("Machine: AT&T WE 32100\n");
                break;
            case EM_SPARC:
                mini_printf("Machine: Sun Microsystems SPARC\n");
                break;
            case EM_386:
                mini_printf("Machine: Intel 80386\n");
                break;
            case EM_68K:
                mini_printf("Machine: Motorola 68000\n");
                break;
            case EM_88K:
                mini_printf("Machine: Motorola 88000\n");
                break;
            case EM_860:
                mini_printf("Machine: Intel 80860\n");
                break;
            case EM_MIPS:
                mini_printf("Machine: MIPS RS3000\n");
                break;
            case EM_PARISC:
                mini_printf("Machine: HP/PA\n");
                break;
            case EM_SPARC32PLUS:
                mini_printf("Machine: SPARC with enhanced instruction set\n");
                break;
            case EM_PPC:
                mini_printf("Machine: PowerPC\n");
                break;
            case EM_PPC64:
                mini_printf("Machine: PowerPC 64-bit\n");
                break;
            case EM_S390:
                mini_printf("Machine: IBM S/390\n");
                break;
            case EM_ARM:
                mini_printf("Machine: Advanced RISC Machines\n");
                break;
            case EM_SH:
                mini_printf("Machine: Renesas SuperH\n");
                break;
            case EM_SPARCV9:
                mini_printf("Machine: SPARC v9 64-bit\n");
                break;
            case EM_IA_64:
                mini_printf("Machine: Intel Itanium\n");
                break;
            case EM_X86_64:
                mini_printf("Machine: AMD x86-64\n");
                break;
            case EM_VAX:
                mini_printf("Machine: DEC Vax\n");
                break;
            default:
                mini_printf("Machine: Not matching any cases\n");
                break;
        }

        // Entry Point Address
        mini_printf("Entry point address: 0x%x\n", hdr.e_entry);

        // Program/Section Header Info
        mini_printf("Start of program headers: %d (bytes into file)\n", hdr.e_phoff);
        mini_printf("Start of section headers: %d (bytes into file)\n", hdr.e_shoff);
        mini_printf("Size of program headers: %d (bytes)\n", hdr.e_phentsize);
        mini_printf("Number of program headers: %d\n", hdr.e_phnum);
        mini_printf("Size of section headers: %d (bytes)\n", hdr.e_shnum);
 
    }
    else {
        sys_write(1, "Not a valid ELF\n", sizeof("Not a valid ELF\n"));
        return -1;
    }

    return 0;
}
