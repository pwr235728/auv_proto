
#include "cmsis_os.h"
#include "lwip.h"
#include "lwip/api.h"
#include "string.h"

#include "AuvRCON.h"
#include "rcon_server.h"
#include "module.h"

static const module_tag_t tag = 1;
module_t module;

osMessageQDef(ctrl_msg, 16, rcon_packet*);
osMessageQId ctrl_msg;


void ControlTask(void *argument) {

	// Create queue
	ctrl_msg = osMessageCreate(osMessageQ(ctrl_msg), NULL);

	if(ctrl_msg == NULL){
		/* ERROR */
		while(1){ osDelay(1000); }
	}

	//Register module
	module = module_create(tag, ctrl_msg);
	module_register(&module);

	while (1) {



		osDelay(100);
	}
}
