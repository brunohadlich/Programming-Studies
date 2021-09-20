#include <stdio.h>
#include <stdlib.h>
#include "elf.h"

elf_header *get_exec_elf_header() {
	int i;
	elf_header *header = (elf_header *)malloc(sizeof(elf_header));
	header->e_ident.EI_MAG0 = 0x7f;
	header->e_ident.EI_MAG1 = 0x45;//'E'
	header->e_ident.EI_MAG2 = 0x4c;//'L'
	header->e_ident.EI_MAG3 = 0x46;//'F'
	header->e_ident.EI_CLASS = ELFCLASS64;//ELF64
	header->e_ident.EI_DATA = ELFDATA2LSB;//2's complement, little endian
	header->e_ident.EI_VERSION = EV_CURRENT;// 1 (current)
	header->e_ident.EI_OSABI = 0x01;//UNIX - System V
	header->e_ident.EI_ABIVERSION = 0;
	for (i = 0; i < sizeof(header->e_ident.EI_PAD); i++) {
		header->e_ident.EI_PAD[i] = 0;
	}
	header->e_type = ET_EXEC;
	header->e_machine = EM_AMD_64;
	header->e_version = EV_CURRENT;
	header->e_entry = 0x00;//Virtual address to which the system first transfers control, thus starting the process
	header->e_phoff = 0x00;//program header table's file offset in bytes. If the file has no program header table, this member holds zero.
	header->e_shoff = 0x00;//section header table's file offset in bytes. If the file has no section header table, this member holds zero.
	header->e_flags = 0x00;//processor-specific flags associated with the file
	header->e_ehsize = 0x00;//ELF header's size in bytes, this case will be 64 bytes
	header->e_phentsize = 0x00;//Size of the program header table entries in bytes
	header->e_phnum = 0x00;//Number of elements at program header table
	header->e_shentsize = 0x00;//Size of the section header table entries in bytes
	header->e_shnum = 0x00;//Number of elements at section header table
	header->e_shtrndx = 0x00;//Offset of the section header table index of the entry associated with the section name string table
}

#include "regex.h"

int main(int argc, char *argv[]) {
	char *regex = "ab*d";
	struct regex *p_regex = build_regex(regex);
	int length = match_regex(p_regex, "abbbbbbbbd");
	printf("%d", length);
	exit(EXIT_SUCCESS);
}