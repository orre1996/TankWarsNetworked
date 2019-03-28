// server.h

#pragma once

#include "types.h"
#include "protocol.h"
#include <queue>
#include "TestPlayerObject.h"
#include "Game_Server.h"
#include <tuple>

// server config
const int SERVER_CHALLENGE_LIMIT                      = 16;
const int SERVER_CONNECTION_LIMIT                     = 4;
const int SERVER_CONNECTION_TIMEOUT_LIMIT             = 5000;
const int SERVER_CONNECTION_CHALLENGE_RESEND_TICKS    = 500;
const int SERVER_PAYLOAD_SEND_RATE                    = 33;
const int SERVER_STAT_REPORT_RATE                     = 10000;


struct challenge
{
   ip_address ip_;
   uint64_t client_salt_;
   uint64_t challenge_salt_;
   int64_t last_send_tick_;
   int64_t last_recv_tick_;
};

enum connection_state_type_id
{
   CONNECTION_STATE_DISCONNECTED,
   CONNECTION_STATE_CONNECTED,
};

struct connection
{
   connection_state_type_id state_;
   ip_address ip_;
   uint64_t client_salt_;
   uint64_t challenge_salt_;
   uint64_t combined_salt_;
   int64_t connect_tick_;
   int64_t last_send_tick_;
   int64_t last_recv_tick_;
   uint32_t sequence_;
   std::vector<message*> msgQueue;
   uint8_t index = 0;
   uint8_t score = 0;
   uint64_t lastReceivedRTT = 0;
   uint16_t lastReceivedUniqueID = 0;
   uint32_t latestSequence = 0;
   uint64_t canShoot = 0;
};



struct server_stats
{
   int64_t last_stat_tick_;
   uint64_t payload_count_;
   uint64_t payload_bytes_;
   uint64_t total_connections_;
};

struct server
{
   udp_socket sock_;
   uint64_t server_salt_;
   int64_t start_tick_;
   server_stats stats_;
   int challenge_count_;
   challenge challenges_[SERVER_CHALLENGE_LIMIT];
   int connection_count_;
   connection connections_[SERVER_CONNECTION_LIMIT];
   Game_Server* gameServer;
   Local_Entity_State positionMessage;
   EntityMessage entityMessage;
   uint8_t connections_index = 0;
   int sendConnectionsMessageTries = 0;
   int sendDisonnectionsMessageTries = 0;
   uint64_t time = 120 * 1000;
   uint64_t lastTick = 0;
   uint64_t deltaTime = 0;
   

   uint8_t iDArray[4] = { 99,99,99,99};
   uint8_t scoreArray[4] = { 99,99,99,99 };
   uint16_t roundtripTimer[4] = { 99,99,99,99 };

   server() : gameServer(new Game_Server())
   {
	  
   };
   ~server()
   {
	   delete gameServer;
	   gameServer = nullptr;
   }

  
};


bool server_init(server &srv, int adapter_index);
void server_run(server &srv);
float bytesToFloat(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);
void SerializeMessage(connection* p_conn, server& p_srv, const int64_t current_tick);
void MakeLocalEntityMessage(connection& p_conn, server& p_srv);
void MakeRemoteEntityMessage(connection& p_conn, server& p_srv);
void MakeGameStateMessage(connection& p_conn, server& p_srv);
void MakeKillMessage(connection& p_conn, server& p_srv);
void MakeRoundTripMessage(connection& p_conn, server& p_srv);
void MakeConnectMessage(connection& p_conn, server& p_srv);
void MakeDisconnectMessage(connection& p_conn, server& p_srv);


