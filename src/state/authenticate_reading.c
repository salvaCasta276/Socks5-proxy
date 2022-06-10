#include "authenticate_reading.h"
#define SOCK_AUTHENTICATION_MAX_LENGTH 2
#define  MAX_READ_LENGTH 512

 void authenticate_reading_departure(const unsigned int leaving_state, struct selector_key *key){
     sock_client *client_data = (sock_client *) key->data;
     process_authentication_message((struct sock_authentication_message * ) client_data->parsed_message, key);
     close_sock_authentication_parser(client_data->using_parser);
     close_sock_authentication_message((struct sock_authentication_message * ) client_data->parsed_message);
     selector_set_interest_key(key, OP_NOOP);

}


unsigned authenticate_read_handler(struct selector_key *key){
    sock_client * client_data = (sock_client *) key->data;

    char temp_buffer[MAX_READ_LENGTH];

    int received_amount = recv(key->fd, temp_buffer, MAX_READ_LENGTH, MSG_DONTWAIT);

    bool finished = feed_sock_authentication_parser(
            client_data->using_parser,
        (struct sock_authentication_message *) (client_data->parsed_message),
            temp_buffer,
            received_amount
    );

    return finished ?  SOCK_AUTHENTICATE_WRITING : SOCK_AUTHENTICATE_READING;
}


void authenticate_reading_arrival(const unsigned int leaving_state, struct selector_key *key){
    sock_client *client_data = (sock_client *) key->data;
    client_data->using_parser = init_sock_authentication_parser();
    client_data->parsed_message= init_sock_authentication_message();
    selector_set_interest_key(key,OP_READ);
}
