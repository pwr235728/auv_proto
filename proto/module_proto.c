

typedef const char* module_tag_t;

#define TAG_CMP(T1, T2) {}

typedef struct module
{
    struct module* next;
    const char* module_tag;
    queue que;
}module_t;

typedef struct module
{
    struct module* next;
    module_tag_t tag;
    queue que;

}module_t;

typedef struct {
    module_t* head;
    int16_t count;
}module_list_t;

module_list_t* module_list;


module_t module_create(module_tag_t tag, queue *que)
{
    module_t m;
    m.next = NULL;
    m.tag = tag;
    m.que = que;

    return m;
}

module_t module_find(module_tag_t tag)
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

// EXAMPLE:
// file: AvuControll.c

module_tag_t AC_module_tag = "AuvControll";
module_t AC_module;
queue AC_queue;
void AC_Init()
{
    AC_module = module_create(tag, &AC_queue);
    module_register(&AC_module);
}

void AC_Task(void* args) // FreeRTOS task
{
    AC_Init();

    .
    .
    .
}



//

AuvRcon

połączenie mempoola z queue



MemPool (1)-------[posrednik]----(*)queue

