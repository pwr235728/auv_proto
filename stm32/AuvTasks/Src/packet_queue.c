#include "packet_queue.h"

#define QUEUE_LENGTH	16
#define PACKET_COUNT 	32
#define QUEUE_COUNT 	16

#define TAG_CMP(T1, T2) (T1 == T2)

typedef struct
{
	packet_queue_t *head;
	int16_t count;
}packet_queue_list_t;


osMessageQDef(module_queue, QUEUE_LENGTH, rcon_packet*);
osPoolDef(rcon_pool, PACKET_COUNT, rcon_packet);
osPoolDef(queue_pool, QUEUE_COUNT, packet_queue_t);

osPoolId rcon_pool;
osPoolId queue_pool;
osMessageQId ans_queue;

packet_queue_list_t pq_list;

void pq_list_add(packet_queue_t *pq)
{
	packet_queue_t *tmp = pq_list.head;
    pq_list.head = pq;
    pq->next = tmp;
    pq_list.count++;
}


osStatus PacketQueue_Init(void)
{
	pq_list.count = 0;
	pq_list.head = NULL;

	ans_queue = osMessageCreate(osMessageQ(module_queue), NULL);
	rcon_pool = osPoolCreate(osPool(rcon_pool));
	queue_pool = osPoolCreate(osPool(queue_pool));

	if(rcon_pool == NULL || ans_queue == NULL || queue_pool == NULL)
	{
		/* ERROR */
		return osErrorResource;
	}

	return osOK;
}
packet_queue_t* PacketQueue_Create(pq_tag_t tag)
{

	packet_queue_t* queue = (packet_queue_t*)osPoolAlloc(queue_pool);
	if(!queue)
	{
		return NULL;
	}

	queue->next = NULL;
	queue->tag = tag;
	queue->queue = osMessageCreate(osMessageQ(module_queue), NULL);

	if(!queue->queue)
	{
		osPoolFree(queue_pool, (void*)queue);
		return NULL;
	}

	pq_list_add(queue);

	return queue;
}
packet_queue_t* PacketQueue_Find(pq_tag_t tag)
{
    int16_t i = pq_list.count;

    packet_queue_t* pq = pq_list.head;
    while( i-->0 && pq!=NULL )
    {
        if(TAG_CMP(tag, pq->tag))
            return pq;

        pq = pq->next;
    }
    return NULL;
}

rcon_packet* PacketQueue_Alloc(void)
{
	return (rcon_packet*)osPoolAlloc(rcon_pool);
}
osStatus PacketQueue_Free(rcon_packet *packet)
{
	return osPoolFree(rcon_pool, packet);
}


rcon_packet* PacketQueue_Recv(packet_queue_t *queue, uint32_t millisec)
{
	osEvent evt = osMessageGet(queue->queue, millisec);
	if (evt.status == osEventMessage)
		return (rcon_packet*)(evt.value.p);

	return NULL;
}
osStatus PacketQueue_Send(rcon_packet *packet, uint32_t millisec)
{
	return osMessagePut(ans_queue, (uint32_t)packet, millisec);
}

osStatus PacketQueue_Enqueue(rcon_packet *packet)
{
	packet_queue_t *pq = PacketQueue_Find(packet->module);

	if(!pq)
		return osErrorOS;

	return osMessagePut(pq->queue, (uint32_t)packet, 0);
}
rcon_packet* PacketQueue_Dequeue(void)
{
	osEvent evt = osMessageGet(ans_queue, 0);
	if (evt.status == osEventMessage)
		return (rcon_packet*)(evt.value.p);

	return NULL;
}
