/*
 * auv_tasks.c
 *
 *  Created on: 18.11.2019
 *      Author: proxima
 */

#include "cmsis_os.h"
#include "lwip.h"
#include "lwip/api.h"

#include "string.h"

typedef struct {
	struct netconn *conn;
	err_t err;
	struct netbuf *buf;
	ip_addr_t *addr;
	ip_addr_t destip;
	unsigned short port;

} rconServer;

err_t RconServer(rconServer* server) {
	u16_t buflen;
	char* buf;

	osDelay(10000);
	if ((server->conn = netconn_new(NETCONN_UDP)) == NULL) {
		return ERR_MEM; /* out of memory */
	}

	if ((server->err = netconn_bind(server->conn, NULL, 5005)) != ERR_OK) {
		return server->err;
	}

	server->err = netconn_err(server->conn);



	while (1) {


		if ((server->err = netconn_recv(server->conn, &(server->buf)))
				!= ERR_OK) {
			return server->err;
		}

		do
		{
			netbuf_data(server->buf, (void**) &buf, &buflen);

			if (buf[2] == 1)
				HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

			if (buf[2] == 2)
				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

			if (buf[2] == 3)
				HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

			server->addr = netbuf_fromaddr(server->buf);
			server->destip = *server->addr;
			server->port = netbuf_fromport(server->buf);
		} while (netbuf_next(server->buf) >= 0);

		netbuf_delete(server->buf);
	}
}

rconServer server;

void RconServerTask(void *argument) {

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

void AddrBroadcastTask(void *argument) {
	static const char signature[] = "AUV";
	struct netconn* conn;
	struct netbuf *buf;
	err_t err;
	osDelay(7000);
	conn = netconn_new(NETCONN_UDP);


	err = netconn_bind(conn, IP4_ADDR_ANY, 1234);
	err += netconn_connect(conn, IP_ADDR_BROADCAST, 1234);
	//err += netbuf_ref(buf, signature, strlen(signature));

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

