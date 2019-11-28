/*
 * rcon_addr_broadcasting.c
 *
 *  Created on: Nov 28, 2019
 *      Author: proxima
 */

#include "cmsis_os.h"
#include "lwip.h"
#include "lwip/api.h"

#include "string.h"

#include "rcon_addr_broadcasting.h"


void AddrBroadcastTask(void *argument)
{
	static const char signature[] = "AUV";
	struct netconn* conn;
	struct netbuf *buf;
	err_t err;
	osDelay(7000);
	conn = netconn_new(NETCONN_UDP);


	err = netconn_bind(conn, IP4_ADDR_ANY, RCON_ADDR_BROADCAST_PORT);
	err += netconn_connect(conn, IP_ADDR_BROADCAST, RCON_ADDR_BROADCAST_PORT);

	osDelay(1000);
	if (err == ERR_OK) {
		while (1) {
			buf = netbuf_new();
			char* data = netbuf_alloc(buf, sizeof(signature));
			memcpy(data, signature, sizeof(signature));
			if ((err = netconn_send(conn, buf)) != ERR_OK) {
				break;
			}
			netbuf_delete(buf);
			osDelay(5000);
		}
	}
	// some bananas happend
	netconn_delete(conn);

	for (;;) {

		osDelay(10000); // suspend thread
	}
}
