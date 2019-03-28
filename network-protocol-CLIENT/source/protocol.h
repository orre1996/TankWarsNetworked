// protocol.h

#pragma once
// todo:
// - create make_<packet-name> functions

#include <stdint.h>

#define PROTOCOL_ID           (0x11223344)
#define PROTOCOL_VERSION      (0x01000001)
#define PROTOCOL_DEFAULT_PORT (32000)

uint64_t generate_challenge();
uint64_t generate_random_salt();

enum message_type
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

enum game_state
{
	RUNNING,
	WAITING,
	PAUSED,
};

enum Entity_Type
{
	TANK,
	BULLET,
};

enum Entity_State
{
	ALIVE,
	DEAD,
};



struct EntityMessage : message
{
	uint8_t entityType;
	uint8_t entityID;
	float posX;
	float posY;
	float rotation;
};

struct InputMessage : message
{
	uint8_t input;
	float rotation;
	uint16_t uniqueID;
	uint8_t deltaTime;

};

template<typename T>
bool serialize(InputMessage &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
	{
		return false;
	}

	if (!stream.serialize(packet.input))
	{
		return false;
	}
	if (!stream.serialize(packet.rotation))
	{
		return false;
	}

	if (!stream.serialize(packet.uniqueID))
	{
		return false;
	}

	if (!stream.serialize(packet.deltaTime))
	{
		return false;
	}

	return true;
};

struct game_state_message : message
{
	uint8_t gameState;
	uint8_t ID[4];
	uint8_t score[4];
	uint16_t roundTripTime[4];
	uint16_t time;
};

template<typename T>
bool serialize(game_state_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.gameState))
		return false;

	for (int i = 0; i < 4; i++)
	{
		if (!stream.serialize(packet.ID[i]))
			return false;

		if (!stream.serialize(packet.score[i]))
			return false;

		if (!stream.serialize(packet.roundTripTime[i]))
			return false;
	}

	if (!stream.serialize(packet.time))
		return false;

	return true;
}

struct local_entity_state : message
{
	float positionX;
	float positionY;
	uint16_t uniqueID;
	uint8_t entityID;
	uint8_t entityState;
};

struct remote_entity_state : message
{
	uint8_t entityType;
	uint8_t entityID;
	uint8_t entityState;
	float positionX;
	float positionY;
	float rotation;
};

template<typename T>
bool serialize(remote_entity_state &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.entityType))
		return false;

	if (!stream.serialize(packet.entityID))
		return false;

	if (!stream.serialize(packet.entityState))
		return false;

	if (!stream.serialize(packet.positionX))
		return false;

	if (!stream.serialize(packet.positionY))
		return false;

	if (!stream.serialize(packet.rotation))
		return false;

	return true;
}

struct connected_message : message
{
	uint8_t entityID;
};

template<typename T>
bool serialize(connected_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.entityID))
		return false;

	return true;
}

struct kill_message : message
{
	uint8_t killerID;
	uint8_t victimID;
};

template<typename T>
bool serialize(kill_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.killerID))
		return false;

	if (!stream.serialize(packet.victimID))
		return false;

	return true;
}


struct disconnect_message : message
{
	uint8_t entityID;
};

template<typename T>
bool serialize(disconnect_message &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;

	if (!stream.serialize(packet.entityID))
		return false;

	return true;
}

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
}


template<typename T>
bool serialize(EntityMessage &packet, T& stream)
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
}


template<typename T>
bool serialize(local_entity_state &packet, T &stream)
{
	if (!stream.serialize(packet.typeMessage))
		return false;
	if (!stream.serialize(packet.positionX))
		return false;
	if (!stream.serialize(packet.positionY))
		return false;
	if (!stream.serialize(packet.uniqueID))
		return false;
	if (!stream.serialize(packet.entityID))
		return false;
	if (!stream.serialize(packet.entityState))
		return false;

	return true;
}


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
}

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
}

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
}

struct payload_packet
{
   uint8_t type_;
   uint32_t sequence_;
   uint64_t combined_salt_;
   uint16_t payload_size_;
   uint8_t payload_[1024];
};

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
}

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
}


void make_connection_request_packet(connection_request_packet &packet, uint64_t salt);
void make_challenge_response_packet(challenge_response_packet &packet, uint64_t combined_salt);
void make_connection_denied_packet(connection_denied_packet &packet, denied_reason_type_id reason);
void make_connection_challenge_packet(connection_challenge_packet &packet, uint64_t client, uint64_t challenge);
void make_payload_packet(payload_packet &packet, uint32_t sequence, uint64_t combined_salt);
void make_disconnect_packet(disconnect_packet &packet, uint64_t combined_salt);
void make_input_message(InputMessage& message, uint8_t p_input, float p_rotation, uint16_t p_uniqueID, uint8_t p_deltaTime);
void make_roundTripTimer_message(roundtriptimer_message& message, uint64_t p_timestamp);