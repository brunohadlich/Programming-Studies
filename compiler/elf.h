//This file was based on http://www.sco.com/developers/gabi/2000-07-17/ch4.eheader.html
#ifndef ELF_H
#define ELF_H

#include <sys/types.h>
#include <stdlib.h>

enum elf_hdr_ident_class
{
        ELFCLASSNONE = 0,
        ELFCLASS32 = 1,
        ELFCLASS64 = 2
};

enum elf_hdr_ident_data
{
        ELFDATANONE = 0,
        ELFDATA2LSB = 1,
        ELFDATA2MSB = 2
};

enum elf_hdr_version
{
        EV_NONE = 0,
        EV_CURRENT = 1
};

typedef struct
{
        u_int8_t EI_MAG0;       //0x7f
        u_int8_t EI_MAG1;       //'E' - 0x45
        u_int8_t EI_MAG2;       //'L' - 0x4C
        u_int8_t EI_MAG3;       //'F' - 0x46
        enum elf_hdr_ident_class EI_CLASS; //elf_hdr_ident_class
        enum elf_hdr_ident_data EI_DATA;   //elf_hdr_ident_data
        enum elf_hdr_version EI_VERSION;   //elf_hdr_ident_version
        u_int8_t EI_OSABI;      //0 - System V
        u_int8_t EI_ABIVERSION; //0 - not used in recent kernels
        u_int8_t EI_PAD[7];     //padding until struct has 16 bytes
} elf_hdr_ident;

enum elf_hdr_type
{
        ET_NONE = 0,        //No file type
        ET_REL = 1,         //Relocatable file
        ET_EXEC = 2,        //Executable file
        ET_DYN = 3,         //Shared object file
        ET_CORE = 4,        //Core file
        ET_LOOS = 0xfe00,   //Operating system-specific
        ET_HIOS = 0xfeff,   //Operating system-specific
        ET_LOPROC = 0xff00, //Processor-specific
        ET_HIPROC = 0xffff  //Processor-specific
};

enum elf_hdr_machine
{
        EM_NONE = 0, 	        //No machine
        EM_M32 = 1, 	        //AT&T WE 32100
        EM_SPARC = 2, 	        //SPARC
        EM_386 = 3, 	        //Intel 80386
        EM_68K = 4, 	        //Motorola 68000
        EM_88K = 5, 	        //Motorola 88000
        //RESERVED = 6 	Reserved for future use
        EM_860 = 7, 	        //Intel 80860
        EM_MIPS = 8, 	        //MIPS I Architecture
        EM_S370 = 9, 	        //IBM System/370 Processor
        EM_MIPS_RS3_LE = 10, 	//MIPS RS3000 Little-endian
        //RESERVED = 11-14 	Reserved for future use
        EM_PARISC = 15, 	//Hewlett-Packard PA-RISC
        //RESERVED = 16 	Reserved for future use
        EM_VPP500 = 17, 	//Fujitsu VPP500
        EM_SPARC32PLUS = 18, 	//Enhanced instruction set SPARC
        EM_960 = 19, 	        //Intel 80960
        EM_PPC = 20, 	        //PowerPC
        EM_PPC64 = 21, 	        //64-bit PowerPC
        //RESERVED = 22-35 	Reserved for future use
        EM_V800 = 36, 	        //NEC V800
        EM_FR20 = 37, 	        //Fujitsu FR20
        EM_RH32 = 38, 	        //TRW RH-32
        EM_RCE = 39, 	        //Motorola RCE
        EM_ARM = 40, 	        //Advanced RISC Machines ARM
        EM_ALPHA = 41, 	        //Digital Alpha
        EM_SH = 42, 	        //Hitachi SH
        EM_SPARCV9 = 43, 	//SPARC Version 9
        EM_TRICORE = 44, 	//Siemens Tricore embedded processor
        EM_ARC = 45, 	        //Argonaut RISC Core, Argonaut Technologies Inc.
        EM_H8_300 = 46, 	//Hitachi H8/300
        EM_H8_300H = 47, 	//Hitachi H8/300H
        EM_H8S = 48, 	        //Hitachi H8S
        EM_H8_500 = 49, 	//Hitachi H8/500
        EM_IA_64 = 50, 	        //Intel IA-64 processor architecture
        EM_MIPS_X = 51, 	//Stanford MIPS-X
        EM_COLDFIRE = 52, 	//Motorola ColdFire
        EM_68HC12 = 53, 	//Motorola M68HC12
        EM_MMA = 54, 	        //Fujitsu MMA Multimedia Accelerator
        EM_PCP = 55, 	        //Siemens PCP
        EM_NCPU = 56, 	        //Sony nCPU embedded RISC processor
        EM_NDR1 = 57, 	        //Denso NDR1 microprocessor
        EM_STARCORE = 58, 	//Motorola Star*Core processor
        EM_ME16 = 59, 	        //Toyota ME16 processor
        EM_ST100 = 60, 	        //STMicroelectronics ST100 processor
        EM_TINYJ = 61, 	        //Advanced Logic Corp. TinyJ embedded processor family
        EM_AMD_64 = 62,         //Advanced Micro Devices X86-64
        //Reserved = 63-65 	Reserved for future use
        EM_FX66 = 66, 	        //Siemens FX66 microcontroller
        EM_ST9PLUS = 67, 	//STMicroelectronics ST9+ 8/16 bit microcontroller
        EM_ST7 = 68, 	        //STMicroelectronics ST7 8-bit microcontroller
        EM_68HC16 = 69, 	//Motorola MC68HC16 Microcontroller
        EM_68HC11 = 70, 	//Motorola MC68HC11 Microcontroller
        EM_68HC08 = 71, 	//Motorola MC68HC08 Microcontroller
        EM_68HC05 = 72, 	//Motorola MC68HC05 Microcontroller
        EM_SVX = 73, 	        //Silicon Graphics SVx
        EM_ST19 = 74, 	        //STMicroelectronics ST19 8-bit microcontroller
        EM_VAX = 75, 	        //Digital VAX
        EM_CRIS = 76, 	        //Axis Communications 32-bit embedded processor
        EM_JAVELIN = 77, 	//Infineon Technologies 32-bit embedded processor
        EM_FIREPATH = 78, 	//Element 14 64-bit DSP Processor
        EM_ZSP = 79, 	        //LSI Logic 16-bit DSP Processor
        EM_MMIX = 80, 	        //Donald Knuth's educational 64-bit processor
        EM_HUANY = 81, 	        //Harvard University machine-independent object files
        EM_PRISM = 82 	        //SiTera Prism
};

typedef struct
{
        elf_hdr_ident e_ident;
        enum elf_hdr_type e_type;     //elf_hdr_type
        enum elf_hdr_machine e_machine;  //elf_hdr_machine
        enum elf_hdr_version e_version;  //elf_hdr_version
        u_int64_t e_entry;    //This member gives the virtual address to which the system first transfers control, thus starting the process. If the file has no associated entry point, this member holds zero.
        u_int64_t e_phoff;    //This member holds the program header table's file offset in bytes. If the file has no program header table, this member holds zero.
        u_int64_t e_shoff;    //This member holds the section header table's file offset in bytes. If the file has no section header table, this member holds zero.
        u_int32_t e_flags;    //This member holds processor-specific flags associated with the file. Flag names take the form EF_machine_flag.
        u_int16_t e_ehsize;   //This member holds the ELF header's size in bytes.
        u_int16_t e_phentsize;//This member holds the size in bytes of one entry in the file's program header table; all entries are the same size.
        u_int16_t e_phnum;    //This member holds the number of entries in the program header table. Thus the product of e_phentsize and e_phnum gives the table's size in bytes. If a file has no program header table, e_phnum holds the value zero.
        u_int16_t e_shentsize;//This member holds a section header's size in bytes. A section header is one entry in the section header table; all entries are the same size.
        u_int16_t e_shnum;    //This member holds the number of entries in the section header table. Thus the product of e_shentsize and e_shnum gives the section header table's size in bytes. If a file has no section header table, e_shnum holds the value zero. If the number of sections is greater than or equal to SHN_LORESERVE (0xff00), this member has the value zero and the actual number of section header table entries is contained in the sh_size field of the section header at index 0. (Otherwise, the sh_size member of the initial entry contains 0.)
        u_int16_t e_shtrndx;  //This member holds the section header table index of the entry associated with the section name string table. If the file has no section name string table, this member holds the value SHN_UNDEF. See ``Sections'' and ``String Table'' below for more information. If the section name string table section index is greater than or equal to SHN_LORESERVE (0xff00), this member has the value SHN_XINDEX (0xffff) and the actual index of the section name string table section is contained in the sh_link field of the section header at index 0. (Otherwise, the sh_link member of the initial entry contains 0.)
} elf_header;

#endif