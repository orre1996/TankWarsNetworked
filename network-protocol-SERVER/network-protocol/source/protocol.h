// protocol.h

#pragma once

#include <stdint.h>
#include "types.h"
#include <iostream>


#define PROTOCOL_ID           (0x11223344)
#define PROTOCOL_VERSION      (0x01000001)
#define PROTOCOL_DEFAULT_PORT (32000)

uint64_t generate_challenge();
uint64_t generate_random_salt();

enum packet_type_id
{
   PACKET_CONNECTION_REQUEST,
   PACKET_CONNECTION_DENIED,
   PACKET_CONNECTION_CHALLENGE,
   PACKET_CHALLENGE_RESPONSE,
   PACKET_CONNECTION_PAYLOAD,
   PACKET_DISCONNECT,
};

enum denied_reason_type_id
{
   DENIED_REASON_SERVER_FULL,
   DENIED_REASON_WRONG_VERSION,
};

struct connection_request_packet
{
   uint8_t type_;
   uint32_t protocol_;
   uint32_t version_;
   uint64_t client_salt_;
   uint8_t padding_[256];
};


enum Entity_State
{
	ALIVE,
	DEAD
};

enum Entity_Type
{
	TANK,
	BULLET,
	WALL,
};

enum Game_State
{
	RUNNING,
	WAITING,
	PAUSED
};


template <typename T>
bool serialize(connection_request_packet &packet, T &stream)
{
   if (!stream.serialize(packet.type_))
      return false;

   if (!stream.serialize(packet.protocol_))
      return false;

   if (!stream.serialize(packet.version_))
      return false;

   if (!stream.serialize(packet.client_salt_))
      return false;

   if (!stream.serialize(sizeof(packet.padding_), packet.padding_))
      return false;

   return true;
};

struct connection_denied_packet
{
   uint8_t type_;
   uint8_t reason_;
};

template <typename T>
bool serialize(connection_denied_packet &packet, T &stream)
{
   if (!stream.serialize(packet.type_))
      return false;

   if (!stream.serialize(packet.reason_))
      return false;

   return true;
};

struct connection_challenge_packet
{
   uint8_t type_;
   uint64_t client_salt_;
   uint64_t challenge_salt_;
};

template <typename T>
bool serialize(connection_challenge_packet &packet, T &stream)
{
   if (!stream.serialize(packet.type_))
      return false;

   if (!stream.serialize(packet.client_salt_))
      return false;

   if (!stream.serialize(packet.challenge_salt_))
      return false;

   return true;
};

struct challenge_response_packet
{
   uint8_t type_;
   uint64_t combined_salt_;
   uint8_t padding_[256];
};

template <typename T>
bool serialize(challenge_response_packet &packet, T &stream)
{
   if (!stream.serialize(packet.type_))
      return false;
   
   if (!stream.serialize(packet.combined_salt_))
      return false;
   
   if (!stream.serialize(256, packet.padding_))
      return false;

   return true;
};

struct payload_packet
{
   uint8_t type_;
   uint32_t sequence_;
   uint64_t combined_salt_;
   uint16_t payload_size_;
   uint8_t payload_[512];
};
enum message_types
{
	CONNECTED_MESSAGE,
	DISCONNECTED_MESSAGE,
	LOCAL_ENTITY_MESSAGE,
	REMOTE_ENTITY_MESSAGE,
	GAMESTATE_MESSAGE,
	KILL_MESSAGE,
	INPUT_MESSAGE,
	ROUNDTRIPTIMER_MESSAGE,
};



struct message
{
	uint8_t typeMessage;
};



struct EntityMessage : message
{
	uint8_t entityType;
	uint8_t entityID;
	float posX;
	float posY;
	float rotation;
};

template<typename T>
static bool serialize(EntityMessage &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.entityType))
		return false;

	if (!stream.serialize(packet.posX))
		return false;

	if (!stream.serialize(packet.posY))
		return false;

	if (!stream.serialize(packet.rotation))
		return false;

	if (!stream.serialize(packet.entityID))
		return false;

	return true;
};



struct InputMessage : message
{
	uint8_t inputMessage;
	float rotation;
	uint16_t UniqueID;
	uint8_t deltaTime;
};

template<typename T>
static bool serialize(InputMessage &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
	{
		return false;
	}

	if (!stream.serialize(packet.inputMessage))
	{
		return false;
	}
	if (!stream.serialize(packet.rotation))
	{
		return false;
	}

	if (!stream.serialize(packet.UniqueID))
	{
		return false;
	}

	if (!stream.serialize(packet.deltaTime))
	{
		return false;
	}
	
	return true;
};


//bool serializeInput(InputMessage& p_message, struct byte_stream_writer &stream);
//bool serializeInput(InputMessage& p_message, struct byte_stream_reader &stream);


struct Local_Entity_State : message
{
	float positionX;
	float positionY;
	uint16_t UniqueID;
	uint8_t EntityID;
	uint8_t EntityState;
};

template<typename T>
bool serialize(Local_Entity_State &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.positionX))
		return false;

	if (!stream.serialize(packet.positionY))
		return false;

	if (!stream.serialize(packet.UniqueID))
		return false;

	if (!stream.serialize(packet.EntityID))
		return false;

	if (!stream.serialize(packet.EntityState))
		return false;

	return true;
};

struct Remote_Entity_State : message
{
	uint8_t EntityType;
	uint8_t EntityID;
	uint8_t EntityState;
	float positionX;
	float positionY;
	float rotation;

};

template<typename T>
bool serialize(Remote_Entity_State &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.EntityType))
		return false;

	if (!stream.serialize(packet.EntityID))
		return false;

	if (!stream.serialize(packet.EntityState))
		return false;

	if (!stream.serialize(packet.positionX))
		return false;

	if (!stream.serialize(packet.positionY))
		return false;

	if (!stream.serialize(packet.rotation))
		return false;

	return true;
};

struct Connected_Message : message
{
	uint8_t EntityID;
};

template <typename T>
bool serialize(Connected_Message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.EntityID))
		return false;

		return true;
};

struct Disconnected_Message : message
{
	uint8_t EntityID;
};

template <typename T>
bool serialize(Disconnected_Message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.EntityID))
		return false;

	return true;
};

struct game_state_message : message
{
	uint8_t Game_State;
	uint8_t ID[4];
	uint8_t Score[4];
	uint16_t RoundtripTime[4];
	uint16_t time;
};

template< typename T>
bool serialize(game_state_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.Game_State))
		return false;

	for (int i = 0; i < 4; i++)
	{

		if (!stream.serialize(packet.ID[i]))
			return false;

		if (!stream.serialize(packet.Score[i]))
			return false;

		if (!stream.serialize(packet.RoundtripTime[i]))
			return false;
	}

	if (!stream.serialize(packet.time))
		return false;
	

	return true;
}



template <typename T>
bool serialize(payload_packet &packet, T &stream)
{
   if (!stream.serialize(packet.type_))
      return false;

   if (!stream.serialize(packet.sequence_))
      return false;

   if (!stream.serialize(packet.combined_salt_))
      return false;

   if (!stream.serialize(packet.payload_size_))
      return false;

   if (!stream.serialize(packet.payload_size_, packet.payload_))
      return false;

   return true;
};

template <typename T>
bool serialize(message &packet, T &stream)
{	
	return true;
}

struct disconnect_packet
{
   uint8_t type_;
   uint64_t combined_salt_;
};

template <typename T>
bool serialize(disconnect_packet &packet, T &stream)
{
   if (!stream.serialize(packet.type_))
      return false;

   if (!stream.serialize(packet.combined_salt_))
      return false;

   return true;
};

struct kill_message : message
{
	uint8_t killerID;
	uint8_t victimID;
};

template <typename T>
bool serialize(kill_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.killerID))
		return false;

	if (!stream.serialize(packet.victimID))
		return false;

	return true;
};

struct roundtriptimer_message : message
{
	uint64_t TimeStamp;
};

template <typename T>
bool serialize(roundtriptimer_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.TimeStamp))
		return false;

	return true;
};


void make_connection_request_packet(connection_request_packet &packet, uint64_t salt);
void make_challenge_response_packet(challenge_response_packet &packet, uint64_t combined_salt);
void make_connection_denied_packet(connection_denied_packet &packet, denied_reason_type_id reason);
void make_connection_challenge_packet(connection_challenge_packet &packet, uint64_t client, uint64_t challenge);
void make_payload_packet(payload_packet &packet, uint32_t sequence, uint64_t combined_salt);
void make_disconnect_packet(disconnect_packet &packet, uint64_t combined_salt);
void make_local_entity_message(Local_Entity_State &p_input, float p_PosX, float p_PosY, uint16_t p_UniqueID, uint8_t p_entityID, uint8_t p_entityState);
void make_remote_entity_message(Remote_Entity_State &p_input,uint8_t p_entityType, uint8_t p_entityID, uint8_t p_entityState, float p_PosX, float p_PosY, float p_rotation);
void make_connected_message(Connected_Message &p_message, uint8_t entityID);
void make_disconnected_message(Disconnected_Message &p_message, uint8_t entityID);
void make_game_state_message(game_state_message &p_message,uint8_t gameState, uint8_t id[4], uint8_t score[4], uint16_t roundtripTimer[4], uint16_t time);
void make_kill_message(kill_message& p_message, uint8_t killID, uint8_t victimID);
void make_roundTripTimer_message(roundtriptimer_message& message, uint64_t p_timestamp);