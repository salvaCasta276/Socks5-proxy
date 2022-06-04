#ifndef PROXY_STATE_MACHINE_H
#define PROXY_STATE_MACHINE_H

#include "stm.h"
#include <string.h>
#include "sock_hello_parser.h"
#include "selector.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "bufferService.h"
#include "sock_client.h"
#include "client_request_processor.h"

enum sock_state {
    TCP_CONNECTED,
    HELLO_SOCK_RECEIVED,
    AUTHENTICATED,
    CONNECT_SOCK_RECEIVED,
    CONNECTED
};

#define HELLO_REQUEST_LENGTH 2
#define READ_AMOUNT 512

struct state_machine *init_proxy_state_machine();

void destroy_sock_state(struct state_machine *sock_machine);

#endif