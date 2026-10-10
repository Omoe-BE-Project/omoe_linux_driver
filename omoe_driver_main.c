#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "omoe_driver_nf_receiver.h"
#include "omoe_driver_sysfs_interface.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liquidcat");
MODULE_DESCRIPTION("kernel driver which exposes OMOE devices on the network as sysfs");
MODULE_VERSION("0.1");


static int __init omoe_driver_init(void)
{
    pr_info("Initializing OMOE kernel module\n");

    int retval = omoe_nf_init();
    if (retval != 0)
	return retval;

    retval = omoe_sysfs_init();
    if (retval != 0)
	return retval;

    return 0;
}

static void __exit omoe_driver_exit(void)
{
    omoe_nf_exit();
    omoe_sysfs_exit();

    pr_info("Exiting Module\n");
}

module_init(omoe_driver_init);
module_exit(omoe_driver_exit);
