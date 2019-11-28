/*
 * rcon_server.c
 *
 *  Created on: Nov 28, 2019
 *      Author: proxima
 */

#include "cmsis_os.h"
#include "lwip.h"
#include "lwip/api.h"
#include "string.h"

#include "AuvRCON.h"
#include "rcon_server.h"

rcon_server server;

err_t RconServer(rcon_server* server)
{
	u16_t buflen;
	char* buf;

	osDelay(10000);
	if ((server->conn = netconn_new(NETCONN_UDP)) == NULL) {
		return ERR_MEM; /* out of memory */
	}

	if ((server->err = netconn_bind(server->conn, NULL, RCON_SERVER_PORT)) != ERR_OK) {
		return server->err;
	}

	server->err = netconn_err(server->conn);

	rcon_sender sender;
	rcon_packet packet;

	while (1) {

		if ((server->err = netconn_recv(server->conn, &(server->buf)))
				!= ERR_OK) {
			return server->err;
		}

		sender.ip = *netbuf_fromaddr(server->buf);
		sender.port = netbuf_fromport(server->buf);

		do {
			netbuf_data(server->buf, (void**) &buf, &buflen);

			char* buf_iter = buf;
			while(buflen--)
			{
				rcon_state parser_state = rcon_parse_byte(&packet, *buf_iter++);

				if(parser_state == RCON_PACKET_COMPLETE){
					// push packet to in_queue
				}else if(parser_state == RCON_PACKET_INVALID){
					// some bananas happend
				}else{ //parser_state == RCON_PACKET_INCOMPLETE
					// do nothing
				}
			}
		} while (netbuf_next(server->buf) >= 0);

		if(buflen > 0)
		{
			// some bannanas happend, packet incomplete
		}

		netbuf_delete(server->buf);
	}
}

void RconServerTask(void *argument) {

	// Error handling
	if (RconServer(&server) != ERR_OK) {
		/* banana happend */
	}

	while (1) {
		osDelay(100);
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	}
}
