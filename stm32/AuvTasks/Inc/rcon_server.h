/*
 * AuvRCON.h
 *
 *  Created on: 02.11.2019
 *      Author: Kurat
 */

#ifndef RCON_SERVER_H_
#define RCON_SERVER_H_

#define RCON_SERVER_PORT 5005

typedef struct {
	ip_addr_t ip;
	unsigned short port;
} rcon_sender;

typedef struct {
	struct netconn *conn;
	struct netbuf *buf;
	err_t err;
} rcon_server;

typedef struct{
	rcon_sender sender;
	rcon_packet packet;
}rcon_in_packet;

void RconServerTask(void *argument);

#endif /* RCON_SERVER_H_ */
