#include "communication.h"

int get_msgid()
{
    return msgget(message_queue_key, 0666 | IPC_CREAT);
}

