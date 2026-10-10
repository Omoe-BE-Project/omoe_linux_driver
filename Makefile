obj-m := omoe_driver.o

omoe_driver-y := omoe_driver_main.o omoe_driver_nf_receiver.o omoe_driver_sysfs_interface.o omoe_driver_protocol_parser.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
