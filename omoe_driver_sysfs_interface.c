#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/atomic.h>

#include "omoe_driver_sysfs_interface.h"

static atomic_t value;

static ssize_t show_value(struct kobject* kobj,
			  struct kobj_attribute* attr,
			  char* buf)
{
    int val = atomic_read(&value);
    pr_info("Sending value %d\n", val);

    return sysfs_emit(buf, "%d\n", val);
}

static ssize_t store_value(struct kobject* kobj,
			   struct kobj_attribute* attr,
			   const char* buf,
			   size_t count)
{
    pr_info("received: %s\n", buf);

    return count;
}

static struct kobj_attribute value_attr = __ATTR(digger, 0664, show_value, store_value);

static struct kobject* omoe_obj;
static struct kobject* value_obj;

int __init omoe_sysfs_init(void)
{
    pr_info("Setting up OMOE sysfs interface");

    atomic_set(&value, 67);
    
    omoe_obj = kobject_create_and_add("omoe", NULL);
    if (!omoe_obj)
	return -ENOMEM;

    value_obj = kobject_create_and_add("omoe1", omoe_obj);
    if (!value_obj)
	return -ENOMEM;

    int retval = sysfs_create_file(value_obj, &value_attr.attr);

    if (retval)
    {
	pr_err("Failed to create file value");
	kobject_put(value_obj);
	kobject_put(omoe_obj);
	return retval;
    }

    return 0;
}

void __exit omoe_sysfs_exit(void)
{
    sysfs_remove_file(value_obj, &value_attr.attr);
    kobject_put(value_obj);
    kobject_put(omoe_obj);
}
