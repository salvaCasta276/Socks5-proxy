#ifndef COOL_STATE_MACHINE_H
#define COOL_STATE_MACHINE_H

#define HELLO_ANSWER_LENGTH 2
#define AUTHENTICATION_ANSWER_LENGTH 2
#define REQUEST_CONNECT_ANSWER 20
#define READ_AMOUNT 512
#include <errno.h>
#include "stm.h"
#include <string.h>
#include "../parsing/sock_hello_parser.h"
#include "../selector.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "../bufferService.h"
#include "../client_request_processor.h"
#include "../sock_client.h"
#include "../parsing/sock_authentication_parser.h"
#include "../parsing/sock_request_parser.h"
#include "../general_handlers.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

enum cool_client_state{
    COOL_AUTHENTICATE_READING,
    COOL_AUTHENTICATE_WRITING,
    COOL_REQUEST_READING,
    ADD_USER_READING,
    REMOVE_USER_READING,
    ENBALE_PASSWORD_SPOOFING_READING,
    DISABLE_PASSWORD_SPOOFING_READING,
    COOL_RESPONSE_WRITING,
};


struct state_machine *init_cool_state_machine();
void destroy_cool_state(struct state_machine *cool_machine);

#endif