#include <string.h>
#include "module.h"
#include "AuvRCON.h"

#define TAG_CMP(T1, T2) (T1 == T2)


module_list_t* module_list;


module_t module_create(module_tag_t tag, osMessageQId que)
{
    module_t m;
    m.next = NULL;
    m.tag = tag;
    m.que = que;

    return m;
}

module_t* module_find(module_tag_t tag)
{
    int16_t i = module_list->count;

    module_t* m = module_list->head;
    while( i-->0 && m!=NULL )
    {
        if(TAG_CMP(tag, m->tag))
            return m;
    }
    return NULL;
}


void module_register(module_t* module)
{
    module_t* tmp = module_list->head;
    module_list->head = module;
    module->next = tmp;
    module_list->count++;
}

// Packet manager

osPoolDef(rcon_pool, 32, rcon_packet);
osPoolId rcon_pool;

osStatus pm_init(void)
{
	rcon_pool = osPoolCreate(osPool(rcon_pool));
	if(rcon_pool == NULL)
	{
		/* ERROR */
		return osErrorResource;
	}
	return osOK;
}


rcon_packet* pm_alloc(void)
{
	return (rcon_packet*)osPoolAlloc(rcon_pool);
}

osStatus pm_free(rcon_packet* packet)
{
	return osPoolFree(rcon_pool, packet);
}

osStatus pm_enqueue(rcon_packet* packet)
{
	module_t *module = module_find(packet->module);

	if(!module)
		return osErrorOS;

	return osMessagePut(module->que, (uint32_t)packet, 0);
}

