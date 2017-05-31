/*
 * Heterogeneous Memory Attributes Table (HMAT) sysfs performance attributes
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

#include <linux/acpi.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include "hmat.h"

static ssize_t read_lat_nsec_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", hmat_local_attribute(dev, READ, LATENCY));
}
static DEVICE_ATTR_RO(read_lat_nsec);

static ssize_t write_lat_nsec_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", hmat_local_attribute(dev, WRITE, LATENCY));
}
static DEVICE_ATTR_RO(write_lat_nsec);

static ssize_t read_bw_MBps_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", hmat_local_attribute(dev, READ, BANDWIDTH));
}
static DEVICE_ATTR_RO(read_bw_MBps);

static ssize_t write_bw_MBps_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n",
			hmat_local_attribute(dev, WRITE, BANDWIDTH));
}
static DEVICE_ATTR_RO(write_bw_MBps);

struct attribute *performance_attributes[] = {
	&dev_attr_read_lat_nsec.attr,
	&dev_attr_write_lat_nsec.attr,
	&dev_attr_read_bw_MBps.attr,
	&dev_attr_write_bw_MBps.attr,
	NULL
};
