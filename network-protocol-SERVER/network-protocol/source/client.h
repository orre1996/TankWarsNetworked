// client.h

#pragma once

#include "types.h"
#include "protocol.h"

// client config
const int CLIENT_CONNECTION_TIMEOUT_LIMIT             = 5000;
const int CLIENT_CONNECTION_CHALLENGE_RESEND_TICKS    = 500;
const int CLIENT_PAYLOAD_SEND_RATE                    = 1000;

enum client_state_type_id
{
   CLIENT_STATE_DISCONNECTED,
   CLIENT_STATE_SENDING_CONNECTION_REQUEST,
   CLIENT_STATE_SENDING_CHALLENGE_RESPONSE,
   CLIENT_STATE_CONNECTED,
};

struct client
{
   bool quit_;
   client_state_type_id state_;
   udp_socket sock_;
   ip_address server_ip_;
   uint64_t client_salt_;
   uint64_t challenge_salt_;
   int64_t connect_tick_;
   int64_t last_send_tick_;
   int64_t last_recv_tick_;
   uint32_t sequence_;
};

#if 0
// example: server_address.host_ = make_ip(192, 168, 1, 208);
uint32_t make_ip(uint32_t a, uint32_t b, 
                 uint32_t c, uint32_t d)
{
   uint32_t result = 0;
   result |= (a & 0xFF) << 24;
   result |= (b & 0xFF) << 16;
   result |= (c & 0xFF) <<  8;
   result |= (d & 0xFF) <<  0;
   return result;
}
#endif

bool client_init(client &cl);
void client_run(client  &cl);
