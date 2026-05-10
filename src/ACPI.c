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
	
	return 0;
}

uint8_t checksum(uint8_t* start, int len) {
	int sum = 0;
	for (int ii = 0; ii < len; ii++) sum += start[ii];
	return sum;
}
