

#ifndef K_ACPI_H
#define K_ACPI_H

#include <limine.h>
#include <stdint.h>

extern volatile struct limine_rsdp_request rsdp_request;

typedef struct rsdp {
	uint8_t signature[8]; // should equal "RSD PTR "
	uint8_t checksum;
	uint8_t OEM_ID[6];
	uint8_t revision;
	uint32_t rsdt_addr;
// revision 2 or greater, for xsdt
	uint32_t length; // length of rsdt, including header
	uint64_t xsdt_addr;
	uint8_t ex_checksum;
	uint8_t reserved[3];
} __attribute__((packed)) rsdp_t;

typedef struct SDT_header {
	char signature[4]; // should equal "RSDT"
	uint32_t length; // length of table, including header
	uint8_t revision;
	uint8_t checksum; // all bytes of the table, including the header, equal to 0 mod 0x100
	char OEMID[6];
	char OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t creator_id;
	uint32_t creator_revision;
} __attribute__ ((packed)) SDT_header_t;

typedef struct RSDT {
	SDT_header_t header;
	uint32_t entries[]; // [(header.length - sizeof(header)) / 4];
} RSDT_t;

int ACPI_init();

#endif // K_ACPI_H
