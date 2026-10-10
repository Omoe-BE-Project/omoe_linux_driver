#pragma once

#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/types.h>

struct omoe_object {
    u8 address;
    u8 hub_uart_num;
    u64 mac_address;
    struct kobject* omoe_folder;
    struct kobj_attribute voltage;
    struct kobj_attribute current_amps;
    struct kobj_attribute encoder_pos;
    struct kobj_attribute encoder_speed;
    struct kobj_attribute temperature;
    
    struct kobj_attribute target_pos;
    struct kobj_attribute target_vel;
};


int omoe_sysfs_init(void);
void omoe_sysfs_exit(void);

void create_omoe(u8 addr,
		 u8 hub_uart_num,
		 u64 mac_address);

void update_omoe(u8 addr,
		 u16 voltage,
		 u16 current_amps,
		 u16 encoder_pos,
		 u16 encoder_speed,
		 u16 temperature);
