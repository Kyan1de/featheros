

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
	char signature[4]; 
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
} __attribute__ ((packed)) RSDT_t;

typedef struct MADT_entry {
	uint8_t entry_type;
	uint8_t record_length;
	uint8_t dat[]; // dat[record_length], cast to whatever device descriptor is specified.
} __attribute__ ((packed)) MADT_entry_t;

#define MADT_lapic_type 0
#define MADT_io_apic_type 1
#define MADT_io_apic_source_override_type 2
#define MADT_io_apic_nmi_source_type 3
#define MADT_lapic_nmi_type 4
#define MADT_lapic_address_override_type 5
#define MADT_lx2apic_type 9

typedef struct MADT_ENTRY_cpu_lapic {
	uint8_t processor_id;
	uint8_t apic_id;
	uint32_t flags;
} __attribute__ ((packed)) MADT_ENTRY_cpu_lapic_t;

typedef struct MADT_ENTRY_io_apic {
	uint8_t id;
	uint8_t reserved;
	uint32_t address;
	uint32_t global_sysint_base;
} __attribute__ ((packed)) MADT_ENTRY_io_apic_t;

typedef struct MADT_ENTRY_apic_int_source_override {
	uint8_t bus_source;
	uint8_t irq_source;
	uint32_t global_sysint;
	uint16_t flags;
} __attribute__ ((packed)) MADT_ENTRY_apic_int_source_override_t;

typedef struct MADT_ENTRY_io_apic_nmi_source {
	uint8_t source;
	uint8_t reserved;
	uint16_t flags;
	uint32_t global__sysint;
} __attribute__ ((packed)) MADT_ENTRY_io_apic_nmi_source_t;

typedef struct MADT_ENTRY_lapic_nmi_source {
	uint8_t processor_id;
	uint16_t flags;
	uint8_t lint_num; // 0 or 1
} __attribute__ ((packed)) MADT_ENTRY_lapic_nmi_source_t;

typedef struct MADT_ENTRY_lapic_address_override {
	uint16_t reserved;
	uint64_t address;
} __attribute__ ((packed)) MADT_ENTRY_lapic_address_override_t;

typedef struct MADT_ENTRY_lx2apic {
	uint16_t reserved;
	uint32_t lx2apic_id;
	uint32_t flags;
	uint32_t acpi_id;
} __attribute__ ((packed)) MADT_ENTRY_lx2apic_t;

// flags, OR together.
#define MADT_flag_active_high 0b0001
#define MADT_flag_active_low 0b0011
#define MADT_flag_edge_trigger 0b0100
#define MADT_flag_level_trigger 0b1100

typedef struct MADT {
	SDT_header_t header;
	uint32_t lapic_addr;
	uint32_t flags;
	uint8_t entries[]; // cast as needed, size is not fixed for either the array or its elements
} __attribute__ ((packed)) MADT_t;

int ACPI_init();

#endif // K_ACPI_H
