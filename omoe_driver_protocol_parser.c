
#include "omoe_driver_sysfs_interface.h"
#include <linux/types.h>

#include "omoe_driver_sysfs_interface.h"
#include "omoe_driver_protocol_parser.h"

int parse_incoming_packet(u8* payload,
			  u16 payload_len)
{

    u16* payload_body = (u16*) (payload + 1);

    u8 address = payload[0];
    
    u16 voltage = payload_body[0];
    u16 current_amps = payload_body[1];
    u16 encoder_pos = payload_body[2];
    u16 encoder_speed = payload_body[3];
    u16 temperature = payload_body[4];

    /* update_omoe(address, */
    /* 		voltage, */
    /* 		current_amps, */
    /* 		encoder_pos, */
    /* 		encoder_speed, */
    /* 		temperature); */
    
    return 0;
}

void create_outgoing_packet(u16 encoder_pos)
{
    
}


