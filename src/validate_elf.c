#include "elf_debug.h"
#include "syscalls.h"
#include "utils.h"

// NOTE: you might want to save this for future assignments :)

// Helper function to parse hex string to address
static uintptr_t parse_hex_address(const char *str) {
  uintptr_t addr = 0;
  const char *p = str;

  // Skip "0x" or "0X" prefix if present
  if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
    p += 2;
  }

  // Parse hex digits
  while (*p) {
    char c = *p;
    int digit;

    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    } else {
      // Invalid character
      return 0;
    }

    addr = (addr << 4) | digit;
    p++;
  }

  return addr;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    mini_printf("Usage: %s <virtual_address>\n", argv[0]);
    mini_printf("Example: %s 0x400000\n", argv[0]);
    return 1;
  }

    // Your solution here!
    uintptr_t address = parse_hex_address(argv[1]);

    if (address == 0) {
        return -1;
    }

    Elf64_Ehdr *hdr = (Elf64_Ehdr *)address;

    // Validate magic bytes
    if (hdr->e_ident[EI_MAG0] == 0x7f &&
        hdr->e_ident[EI_MAG1] == 'E' &&
        hdr->e_ident[EI_MAG2] == 'L' &&
        hdr->e_ident[EI_MAG3] == 'F') {
        mini_printf("Valid ELF magic bytes\n");
    }
    else {
        mini_printf("Invalid ELF magic bytes\n");
        return -1;
    }

    // Validate class
    if (hdr->e_ident[EI_CLASS] == ELFCLASS64) {
        mini_printf("Valid ELF class\n");
    }
    else {
        mini_printf("Invalid ELF class\n");
        return -1;
    }

    // Validate little-endian encoding
    if (hdr->e_ident[EI_DATA] == ELFDATA2LSB) {
        mini_printf("Little endian\n");
    }
    else {
        mini_printf("Not little endian\n");
        return -1;
    }

    // Validate AARCH64
    if (hdr->e_ident[EI_OSABI] == ELFOSABI_ARM) {
        mini_printf("AArch64\n");
    }
    else {
        mini_printf("Not AArch64\n");
        return -1;
    }

  return 0;
}
