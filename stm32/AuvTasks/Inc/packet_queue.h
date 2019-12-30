#ifndef PACKET_QUEUE_H_
#define PACKET_QUEUE_H_

#include "cmsis_os.h"

#include "AuvRCON.h"

typedef uint8_t pq_tag_t;

typedef struct packet_queue
{
	struct packet_queue *next;
	pq_tag_t tag;
	osMessageQId queue;
}packet_queue_t;

// Initialize internal state
osStatus PacketQueue_Init(void);

// Create queue for given tag
packet_queue_t* PacketQueue_Create(pq_tag_t tag);

// Find queue with given tag
packet_queue_t* PacketQueue_Find(pq_tag_t tag);

rcon_packet* PacketQueue_Alloc(void);
osStatus PacketQueue_Free(rcon_packet *packet);

/* Task side only */
// Get -> recv
// Put -> send
rcon_packet* PacketQueue_Recv(packet_queue_t *queue, uint32_t millisec);
osStatus PacketQueue_Send(rcon_packet *packet, uint32_t millisec);
// PacketQueue_Put(..);


/* Server side only */
osStatus PacketQueue_Enqueue(rcon_packet *packet);
rcon_packet* PacketQueue_Dequeue(void);


#endif /* PACKET_QUEUE_H_ */
