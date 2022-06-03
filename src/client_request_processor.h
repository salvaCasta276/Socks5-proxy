#ifndef CLIENT_REQUEST_PROCESSOR_H
#define CLIENT_REQUEST_PROCESSOR_H
#include "selector.h"
#include "sock_hello_parser.c"
#include "client_request_processor.h"
#include "sock_client.h"
#include "buffer.h"
#DEFINE USERNAME_AUTHENTICATION 2
#DEFINE VERSION 5
#DEFINE NON_METHODS_ACCEPTED 255

void process_hello_message(struct sock_hello_message data, struct selector_key * key);
void process_authentication_message(struct sock_authentication_message data, struct selector_key * key);
void process_request_message(struct sock_request_message data, struct selector_key * key);
#endif