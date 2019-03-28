// protocol.cc
#include "stdafx.h"
#include "protocol.h"
#include "util.h"
#include <stdlib.h>
#include <vector>

static int 
random()
{
   return rand();
}

inline uint64_t 
random_salt()
{
   uint64_t result = 0;

   result |= ((uint64_t)random() << 48) & 0xFFFF000000000000;
   result |= ((uint64_t)random() << 32) & 0x0000FFFF00000000;
   result |= ((uint64_t)random() << 16) & 0x00000000FFFF0000;
   result |= ((uint64_t)random() <<  0) & 0x000000000000FFFF;

   return result;
}

uint64_t generate_challenge()
{
   return random_salt();
}

uint64_t generate_random_salt()
{
   return random_salt();
}


//void make_input_message(InputMessage & message, uint8_t p_input, float p_rotation, uint8_t p_uniqueID, uint8_t p_deltaTime)
//{
//	message.typeMessage = INPUT_MESSAGE;
//	message.input = p_input;
//	message.rotation = p_rotation;
//	message.uniqueID = p_uniqueID;
//	message.deltaTime = p_deltaTime;
//}


void make_local_entity_message(local_entity_state& message, float p_posX, float p_posY, uint8_t p_entityID)
{
	message.typeMessage = LOCAL_ENTITY_MESSAGE;
	message.positionX = p_posX;
	message.positionY = p_posY;
	message.entityID = p_entityID;
}

void make_roundTripTimer_message(roundtriptimer_message& message,  uint64_t p_timestamp)
{
	message.typeMessage = ROUNDTRIPTIMER_MESSAGE;
	message.TimeStamp = p_timestamp;
}



void make_connection_request_packet(connection_request_packet &packet, uint64_t salt)
{
   packet.type_ = PACKET_CONNECTION_REQUEST;
   packet.protocol_ = PROTOCOL_ID;
   packet.version_ = PROTOCOL_VERSION;
   packet.client_salt_ = salt;
   zero_memory(packet.padding_, sizeof(packet.padding_));
}

void make_challenge_response_packet(challenge_response_packet &packet, uint64_t combined_salt)
{
   packet.type_ = PACKET_CHALLENGE_RESPONSE;
   packet.combined_salt_ = combined_salt;
   zero_memory(packet.padding_, sizeof(packet.padding_));
}

void make_connection_denied_packet(connection_denied_packet &packet, denied_reason_type_id reason)
{
   packet.type_ = PACKET_CONNECTION_DENIED;
   packet.reason_ = reason;
}

void make_connection_challenge_packet(connection_challenge_packet &packet, uint64_t client, uint64_t challenge)
{
   packet.type_ = PACKET_CONNECTION_CHALLENGE;
   packet.client_salt_ = client;
   packet.challenge_salt_ = challenge;
}

void make_payload_packet(payload_packet &packet, uint32_t sequence, uint64_t combined_salt)
{
   packet.type_ = PACKET_CONNECTION_PAYLOAD;
   packet.sequence_ = sequence;
   packet.combined_salt_ = combined_salt;
   packet.payload_size_ = 0;
   zero_memory(packet.payload_, sizeof(packet.payload_));
}

void make_disconnect_packet(disconnect_packet &packet, uint64_t combined_salt)
{
   packet.type_ = PACKET_DISCONNECT;
   packet.combined_salt_ = combined_salt;
}

void make_input_message(InputMessage& message, uint8_t p_input, float p_rotation, uint16_t p_uniqueID,	uint8_t p_deltaTime)
{
	message.typeMessage = INPUT_MESSAGE;
	message.input = p_input;
	message.rotation = p_rotation;
	message.uniqueID = p_uniqueID;
	message.deltaTime = p_deltaTime;
}

