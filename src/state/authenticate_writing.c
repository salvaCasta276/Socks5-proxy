#include "authenticate_writing.h"

void authenticate_writing_arrival(const unsigned int leaving_state, struct selector_key *key){
    selector_set_interest_key(key,OP_WRITE);
}


unsigned authenticate_write_handler(struct selector_key *key){
    sock_client *client_data = (sock_client *) key->data;

    if (!buffer_can_read(client_data->write_buffer))
        return SOCK_AUTHENTICATE_WRITING;

    size_t write_amount;
    uint8_t *reading_since = buffer_read_ptr(client_data->write_buffer, &write_amount);
    ssize_t written_bytes = send(client_data->client_fd, reading_since, write_amount, MSG_DONTWAIT);
    buffer_read_adv(client_data->write_buffer, written_bytes);
    buffer_compact(client_data->write_buffer);

    if(written_bytes < write_amount)
        return SOCK_AUTHENTICATE_WRITING;
    else
        return SOCK_REQUEST_READING;
}

void authenticate_writing_departure(const unsigned int leaving_state, struct selector_key *key){
    selector_set_interest_key(key,OP_NOOP);
}