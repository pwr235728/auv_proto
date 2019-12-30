
#include "cmsis_os.h"
#include "lwip.h"
#include "lwip/api.h"
#include "string.h"

#include "AuvRCON.h"
#include "rcon_server.h"
#include "packet_queue.h"

static const pq_tag_t tag = 1;


packet_queue_t queue;
rcon_packet *packet;

void ControlTask(void *argument) {

	osDelay(15000);
	PacketQueue_Create(&queue, tag); // todo: error checking


	while (1) {
		if((packet = PacketQueue_Recv(&queue, osWaitForever)))
		{
			if(packet->cmd == 1)
				HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
			if(packet->cmd == 2)
				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			if(packet->cmd == 3)
				HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

			PacketQueue_Free(packet);
		}else
		{
			osDelay(100);
		}
	}
}
