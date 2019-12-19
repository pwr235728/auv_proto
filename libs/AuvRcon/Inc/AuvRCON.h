/*
 * AuvRCON.h
 *
 *  Created on: 02.11.2019
 *      Author: Kurat
 */

#ifndef AUVRCON_H_
#define AUVRCON_H_

#include "stdint.h"
#include "lwip/api.h"
#include "cmsis_os.h"


/* Rcon packet format:
 * [ '>' | ID: u16 | TYPE: u8 | LEN: u8 | BODY: 0-255 bytes | '<' ]
 * BODY is null terminated string. "\0" if empty;
 * Minimal packet length is: 7 bytes -> ('>', id, type, len, "\0" in body, '<')
 * Maximum packet length is: 261 bytes
 */


#define RCON_PACKET_HEADER_SIZE 5		// BEGIN_CHAR 1 byte, ID 2 bytes, Type 1 byte, Size 1 bytes
#define RCON_PACKET_PAYLOAD_SIZE 256	// BODY 255 bytes, END '<' 1 byte
#define RCON_PACKET_SIZE (RCON_PACKET_HEADER_SIZE+RCON_PACKET_PAYLOAD_SIZE)

typedef enum
{
	RCON_PACKET_INVALID,
	RCON_PACKET_COMPLETE,
	RCON_PACKET_INCOMPLETE
}rcon_state;

typedef enum
{
	_RCON_DATA_INVALID,
	_RCON_DATA_RESET,
	_RCON_DATA_HEADER_RX,
	_RCON_DATA_HEADER_GOT_BEGIN,
	_RCON_DATA_GOT_HEADER,
	_RCON_DATA_PAYLOAD_RX,
	_RCON_DATA_GOT_PAYLOAD
}_rcon_data_state;

typedef struct
{
	uint8_t data[RCON_PACKET_PAYLOAD_SIZE];
	uint32_t index;
	_rcon_data_state state;
}_rcon_data;

typedef struct
{
	uint16_t id;
	uint8_t type;
	uint8_t size;
	uint8_t* body;

	_rcon_data _rcon_data;
}rcon_packet;

void rcon_packet_reset(rcon_packet* packet);
rcon_state rcon_check_packet(rcon_packet* packet);
rcon_state rcon_parse_byte(rcon_packet* packet, uint8_t data);


#endif /* AUVRCON_H_ */
