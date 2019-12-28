#ifndef MODULE_H_
#define MODULE_H_

#include "cmsis_os.h"

#include "AuvRCON.h"

typedef uint8_t module_tag_t;


typedef struct module
{
    struct module* next;
    module_tag_t tag;
    osMessageQId que;
}module_t;

typedef struct {
    module_t* head;
    int16_t count;
}module_list_t;

module_t module_create(module_tag_t tag, osMessageQId que);
module_t* module_find(module_tag_t tag);
void module_register(module_t* module);

// Packet manager


osStatus pm_init(void);
rcon_packet* pm_alloc(void);
osStatus pm_free(rcon_packet* packet);
osStatus pm_enqueue(rcon_packet* packet);


#endif /* MODULE_H_ */
