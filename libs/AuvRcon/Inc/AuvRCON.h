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
 * [ '>' | ID: u16 | Module: u8 | Cmd: u8 | LEN: u8 | BODY: 0-255 bytes | '<' ]
 * BODY - binary
 * Minimal packet length is: 7 bytes -> ('>', id, module, cmd, len, "" in body, '<')
 * Maximum packet length is: 262 bytes
 */

/*
 * id - packet id
 * module - module id (control, torpedoes, magnetic gripper, ...)
 * cmd - command for the module
 * len - length of payload
 * body/payload - data for the module
 */

/* Control commands
 * setDepth
 * getDept
 * enable depth control
 *
 */

#define RCON_PACKET_HEADER_SIZE 6		// BEGIN_CHAR 1 byte, ID 2 bytes, module 1 byte, cmd 1 byte, Size 1 bytes
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
	uint16_t id;
	uint8_t module;
	uint8_t cmd;
	uint8_t size;
	uint8_t data[RCON_PACKET_PAYLOAD_SIZE];
}rcon_packet;

typedef struct
{
	rcon_packet *packet;

	uint32_t index;
	_rcon_data_state state;
}rcon_parser;

void rcon_parser_reset(rcon_parser* parser);
rcon_state rcon_packet_check(rcon_packet* packet);
rcon_state rcon_parser_parse(rcon_parser* parser, uint8_t data);

// rcon_packet manager
osStatus rcon_init(void);
rcon_packet* rcon_packet_alloc(void);
osStatus rcon_packet_free(rcon_packet* packet);


#endif /* AUVRCON_H_ */
