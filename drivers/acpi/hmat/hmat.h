/*
 * Heterogeneous Memory Attributes Table (HMAT) representation in sysfs
 *
 * Copyright (c) 2017, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef _ACPI_HMAT_H_
#define _ACPI_HMAT_H_

enum hmat_attr_type {
	LATENCY,
	BANDWIDTH,
};

struct memory_initiator {
	struct list_head list;
	struct device dev;

	/* only one of the following three will be set */
	struct acpi_srat_cpu_affinity *cpu;
	struct acpi_srat_x2apic_cpu_affinity *x2apic;
	struct acpi_srat_gicc_affinity *gicc;

	int pxm;
	bool is_registered;
};
#define to_memory_initiator(d) container_of((d), struct memory_initiator, dev)

struct memory_target {
	struct list_head list;
	struct device dev;
	struct acpi_srat_mem_affinity *ma;
	struct acpi_hmat_address_range *spa;
	struct memory_initiator *local_init;

	bool is_cached;
	bool is_registered;
	bool has_perf_attributes;
};
#define to_memory_target(d) container_of((d), struct memory_target, dev)

struct memory_locality {
	struct list_head list;
	struct acpi_hmat_locality *hmat_loc;
};

extern const struct attribute_group *memory_initiator_attribute_groups[];
extern const struct attribute_group *memory_target_attribute_groups[];
extern struct attribute *performance_attributes[];

extern struct list_head locality_list;

int hmat_local_attribute(struct device *tgt_dev, int direction,
		enum hmat_attr_type type);
#endif /* _ACPI_HMAT_H_ */
