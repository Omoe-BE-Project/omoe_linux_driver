#pragma once

int parse_incoming_packet(u8* payload, u16 size);

void create_outgoing_packet(u16);
