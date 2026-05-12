#include <kconsole.h>
#include <ACPI.h>

uint8_t checksum(uint8_t* start, int len);

int ACPI_init() {
	if (rsdp_request.response == NULL) {
		kprint("ACPI not available");
		return -1;
	}
	kprint("rsdp at ");
	kprint_hex64((uint64_t)rsdp_request.response->address);
	// parse rsdp, get rsdt or xsdt
	rsdp_t* rsdp_p = (rsdp_t*)rsdp_request.response->address;
	if (checksum((uint8_t*)rsdp_p, 20) != 0) {
		kprint("\nrsdp failed checksum???");
		return -1;
	}
	// TODO: use XSDT if rsdp.revision >= 2
	RSDT_t* rsdt_p = (RSDT_t*)PHYS_TO_VIRT(rsdp_p->rsdt_addr);
	if (checksum((uint8_t*)rsdt_p, rsdt_p->header.length) % 0x100 != 0) {
		kprint("\nrsdt failed checksum???");
		return -1;
	}
	kprint("\nrsdt at ");
	kprint_hex64((uint64_t)rsdt_p);
	kprint("\n");
	
	for (int ii = 0; ii < (rsdt_p->header.length - sizeof(SDT_header_t))/4; ii++) { // iterate over all entries
		SDT_header_t* p = (SDT_header_t*)PHYS_TO_VIRT(rsdt_p->entries[ii]);
		kprintn(p->signature, 4);
		kprint(" at ");
		kprint_hex64((uint64_t)p);
		kprint("\n");
		// we only really care about the APIC/MADT, so:
		if (memcmp(p->signature, "APIC", 4) == 0) {
			MADT_t* apic = (MADT_t*)p;
			if (checksum((uint8_t*)apic, apic->header.length) % 0x100 != 0) {
				kprint("APIC failed checksum???\n");
				return -1;
			}
			void* table_raw_p = (void*)apic;
			uint32_t offset = sizeof(SDT_header_t) + 8; // offset into the start of the entries
			// there's probably a better way to parse these, but this is just what jumps out to me.
			// I call this trick "stumbling around in the dark"
			while (offset < apic->header.length) {
				MADT_entry_t* entry = (MADT_entry_t*)(table_raw_p + (size_t)offset);
				switch (entry->entry_type) {
					case MADT_lapic_type: kprint("MADT_lapic_type\n");break;
					case MADT_io_apic_type: kprint("MADT_io_apic_type\n");break;
					case MADT_io_apic_source_override_type: kprint("MADT_io_apic_source_override_type\n");break;
					case MADT_io_apic_nmi_source_type: kprint("MADT_io_apic_nmi_source_type\n");break;
					case MADT_lapic_nmi_type: kprint("MADT_lapic_nmi_type\n");break;
					case MADT_lapic_address_override_type: kprint("MADT_lapic_address_override_type\n");break;
					case MADT_lx2apic_type: kprint("MADT_lx2apic_type\n");break;
					default: kprint("unknown MADT type???"); break;
				}
				offset += entry->record_length;
			}
		}
	}

	return 0;
}

uint8_t checksum(uint8_t* start, int len) {
	int sum = 0;
	for (int ii = 0; ii < len; ii++) sum += start[ii];
	return sum;
}
