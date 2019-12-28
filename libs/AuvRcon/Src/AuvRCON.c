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


void rcon_parser_reset(rcon_parser* parser)
{
	parser->index = 0;
	parser->state = _RCON_DATA_RESET;

	rcon_packet *packet = parser->packet;
	packet->id = 0;
	packet->module = 0;
	packet->cmd = 0;
	packet->size = 0;
}

// Sprawdzenie czy pakiet jest poprawny.
// Czy jest znak początku i w odpowienim miejscu jest znak końca.
// Czy minimalny rozmiar to 0, i czy jest znak "\0" na końcu BODY
rcon_state rcon_packet_check(rcon_packet* packet) {

	if (packet->size > 0 &&
			packet->data[packet->size - 1] == '\0' &&
			packet->data[packet->size] == rcon_end_char) {
		return RCON_PACKET_COMPLETE;
	} else {
		return RCON_PACKET_INVALID;
	}
}

rcon_state rcon_parser_parse(rcon_parser* parser, uint8_t data)
{
	rcon_packet *packet = parser->packet;

	switch (parser->state) {

	case _RCON_DATA_INVALID:
	{	}
	/* no break */

	case _RCON_DATA_RESET:
	{
		rcon_parser_reset(parser);
		parser->state = _RCON_DATA_HEADER_RX;
	}
	/* no break */

	case _RCON_DATA_HEADER_RX:
	{
		parser->state = (data == rcon_begin_char)
				? _RCON_DATA_HEADER_GOT_BEGIN
				: _RCON_DATA_RESET;
	}
		break;

	case _RCON_DATA_HEADER_GOT_BEGIN:
	{
		if(parser->index == 0)
			packet->id = data;
		if(parser->index == 1)
			packet->id |= ((u16_t)data) << 8;
		if(parser->index == 2)
			packet->module = data;
		if(parser->index == 3)
			packet->cmd = data;
		if(parser->index == 4)
			packet->size = data;

		parser->index++;
		if((parser->index) == 5)
		{
			parser->state = _RCON_DATA_GOT_HEADER;
		}
	}
		break;

	case _RCON_DATA_GOT_HEADER:
	{
		parser->index = 0;
		parser->state = _RCON_DATA_PAYLOAD_RX;
	}
	/* no break */
	case _RCON_DATA_PAYLOAD_RX:
	{
		if (parser->index < packet->size + 1) {
			packet->data[parser->index++] = data;
		}
		if (parser->index == packet->size+1) {
			parser->state = _RCON_DATA_GOT_PAYLOAD;
		}
	}
		break;

	default: {
		/* some bananas happend */
		rcon_parser_reset(parser);
		// :(
	}
		break;
	}

	if (parser->state == _RCON_DATA_GOT_PAYLOAD) {
		if (rcon_packet_check(packet) == RCON_PACKET_COMPLETE)
		{
			parser->state = _RCON_DATA_RESET;
			return RCON_PACKET_COMPLETE;
		}
		else
		{
			parser->state = _RCON_DATA_INVALID;
			return RCON_PACKET_INVALID;
		}
	}

	return RCON_PACKET_INCOMPLETE;
}


