#include "cool_request_reading.h"
#define  MAX_READ_LENGTH 512

void cool_request_reading_departure(const unsigned int leaving_state, struct selector_key *key){
     cool_client *client_data = (cool_client *) key->data;

     process_cool_request_message((struct general_request_message * ) client_data->parsed_message, key);
     destroy_general_request_message((struct general_request_message * ) client_data->parsed_message);
     selector_set_interest_key(key, OP_NOOP);

}


unsigned cool_request_read_handler(struct selector_key *key){
    cool_client * client_data = (cool_client *) key->data;

    char temp_buffer[MAX_READ_LENGTH];

    int received_amount = recv(key->fd, temp_buffer, MAX_READ_LENGTH, MSG_DONTWAIT);

    bool finished = feed_general_request_parser(
        (struct general_request_message *) (client_data->parsed_message),
            temp_buffer,
            received_amount
    );

    return finished ?  COOL_RESPONSE_WRITING : COOL_REQUEST_READING;
}


void cool_request_reading_arrival(const unsigned int leaving_state, struct selector_key *key){
    cool_client *client_data = (cool_client *) key->data;
    client_data->current_parser.request_message = init_general_parser();
    selector_set_interest_key(key,OP_READ);
}
