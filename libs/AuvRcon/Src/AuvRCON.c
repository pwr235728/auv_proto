/*
 * AuvRCON.c
 *
 *  Created on: 02.11.2019
 *      Author: Kurat
 */


#include "AuvRCON.h"

#include "cmsis_os.h"
#include "lwip/api.h"


#define RCON_HEADER_ID 1
#define RCON_HEADER_TYPE (RCON_HEADER_ID   + 2)
#define RCON_HEADER_SIZE (RCON_HEADER_TYPE + 1)
#define RCON_HEADER_BODY (RCON_HEADER_SIZE + 1)

static const char rcon_begin_char = '>';
static const char rcon_end_char = '<';


void rcon_packet_reset(rcon_packet* packet)
{
	packet->_rcon_data.index = 0;
	packet->_rcon_data.state = _RCON_DATA_RESET;

	packet->id = 0;		//(int16_t*)&(packet->_rcon_data.data[RCON_HEADER_ID]);
	packet->type = 0;	//(int8_t*)&(packet->_rcon_data.data[RCON_HEADER_TYPE]);
	packet->size = 0;	//&(packet->_rcon_data.data[RCON_HEADER_SIZE]);
	packet->body = (packet->_rcon_data.data);
}

// Sprawdzenie czy pakiet jest poprawny.
// Czy jest znak początku i w odpowienim miejscu jest znak końca.
// Czy minimalny rozmiar to 0, i czy jest znak "\0" na końcu BODY
rcon_state rcon_check_packet(rcon_packet* packet) {
	if (packet->size > 0 &&
			packet->body[packet->size - 1] == '\0' &&
			packet->body[packet->size] == rcon_end_char) {
		return RCON_PACKET_COMPLETE;
	} else {
		return RCON_PACKET_INVALID;
	}
}

rcon_state rcon_parse_byte(rcon_packet* packet, uint8_t data)
{
	_rcon_data* rd = &(packet->_rcon_data);

	switch (rd->state) {

	case _RCON_DATA_INVALID:
	{	}
	/* no break */

	case _RCON_DATA_RESET:
	{
		rcon_packet_reset(packet);
		rd->state = _RCON_DATA_HEADER_RX;
	}
	/* no break */

	case _RCON_DATA_HEADER_RX:
	{
		rd->state = (data == rcon_begin_char)
				? _RCON_DATA_HEADER_GOT_BEGIN
				: _RCON_DATA_RESET;
	}
		break;

	case _RCON_DATA_HEADER_GOT_BEGIN:
	{
		if(rd->index == 0)
			packet->id = data;
		if(rd->index == 1)
			packet->id |= ((u16_t)data) << 8;
		if(rd->index == 2)
			packet->type = data;
		if(rd->index == 3)
			packet->size = data;

		rd->index++;
		if((rd->index) == 4)
		{
			rd->state = _RCON_DATA_GOT_HEADER;
		}
	}
		break;

	case _RCON_DATA_GOT_HEADER:
	{
		rd->index = 0;
		rd->state = _RCON_DATA_PAYLOAD_RX;
	}
	/* no break */
	case _RCON_DATA_PAYLOAD_RX:
	{
		if (rd->index < packet->size + 1) {
			rd->data[rd->index++] = data;
		}
		if (rd->index == packet->size+1) {
			rd->state = _RCON_DATA_GOT_PAYLOAD;
		}
	}
		break;

	default: {
		/* some bananas happend */
		rcon_packet_reset(packet);
		// :(
	}
		break;
	}

	if (rd->state == _RCON_DATA_GOT_PAYLOAD) {
		if (rcon_check_packet(packet) == RCON_PACKET_COMPLETE)
		{
			rd->state = _RCON_DATA_RESET;
			return RCON_PACKET_COMPLETE;
		}
		else
		{
			rd->state = _RCON_DATA_INVALID;
			return RCON_PACKET_INVALID;
		}
	}

	return RCON_PACKET_INCOMPLETE;
}
