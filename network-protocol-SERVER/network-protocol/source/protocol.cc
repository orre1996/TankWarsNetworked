// protocol.cc

#include "protocol.h"
#include "util.h"
#include <stdlib.h>

static int 
random()
{
   return rand();
}

/*
	bool test_message::serialize(struct byte_stream_writer *stream) 
	{
		return serialize<byte_stream_writer>(*this, *stream);
	}
	
	bool test_message::deserialize(struct byte_stream_reader *stream)
	{
		return serialize<byte_stream_reader>(*this, *stream);
	}




	bool input_message::serialize(struct byte_stream_writer *stream)
	{
		return serialize<byte_stream_writer>(*this, *stream);
	}

	bool input_message::deserialize(struct byte_stream_reader *stream)
	{
		return serialize<byte_stream_reader>(*this, *stream);
	}




	bool position_message::serialize(struct byte_stream_writer *stream)
	{
		return serialize<byte_stream_writer>(*this, *stream);
	}

	bool position_message::deserialize(struct byte_stream_reader *stream)
	{
		return serialize<byte_stream_reader>(*this, *stream);
	}
	*/

	/*
	bool entity_message::serialize(struct byte_stream_writer *stream)
	{
		return serialize<byte_stream_writer>(*this, *stream);
	}

	bool entity_message::deserialize(struct byte_stream_reader *stream)
	{
		return serialize<byte_stream_reader>(*this, *stream);
	}*/



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




bool serializeInput(InputMessage& p_message, byte_stream_writer& p_writer)
{
	if (serialize<byte_stream_writer>(p_message, p_writer))
		return true;

	return false;
}
bool serializeInput(InputMessage& p_message, byte_stream_reader& p_reader)
{
	if (serialize<byte_stream_reader>(p_message, p_reader))
		return true;

	return false;
}

/*
uint8_t InputMessage::GetTypeMessage()
{
	return typeMessage;
}

uint8_t Local_Entity_State::GetTypeMessage()
{
	return typeMessage;
}*/

void make_local_entity_message(Local_Entity_State &p_input, uint8_t message_type, float p_PosX, float p_PosY, uint16_t p_UniqueID, uint8_t p_entityID, uint8_t p_entityState)
{		
	/*p_input.typeMessage = LOCAL_ENTITY_MESSAGE;
	p_input.positionX = p_PosX;
	p_input.positionY = p_PosY;
	p_input.UniqueID = p_UniqueID;
	p_input.EntityID = p_entityID;
	p_input.EntityState = p_entityState;*/
}

void make_local_entity_message(Local_Entity_State& p_input, float p_PosX, float p_PosY, uint16_t p_UniqueID,uint8_t p_entityID, uint8_t p_entityState)
{
	p_input.typeMessage = LOCAL_ENTITY_MESSAGE;
	p_input.positionX = p_PosX;
	p_input.positionY = p_PosY;
	p_input.UniqueID = p_UniqueID;
	p_input.EntityID = p_entityID;
	p_input.EntityState = p_entityState;
}

void make_remote_entity_message(Remote_Entity_State& p_input,uint8_t p_entityType, uint8_t p_entityID,uint8_t p_entityState, float p_PosX, float p_PosY, float p_rotation)
{
	p_input.typeMessage = REMOTE_ENTITY_MESSAGE;
	p_input.EntityType = p_entityType;
	p_input.EntityID = p_entityID;
	p_input.EntityState = p_entityState;
	p_input.positionX = p_PosX;
	p_input.positionY = p_PosY;
	p_input.rotation = p_rotation;

}


void make_connected_message(Connected_Message& p_message,  uint8_t entityID)
{
	p_message.typeMessage = CONNECTED_MESSAGE;
	p_message.EntityID = entityID;
}

void make_disconnected_message(Disconnected_Message& p_message, uint8_t entityID)
{
	p_message.typeMessage = DISCONNECTED_MESSAGE;
	p_message.EntityID = entityID;
}



void make_game_state_message(game_state_message &p_message, uint8_t gameState, uint8_t id[4], uint8_t score[4], uint16_t roundtripTimer[4], uint16_t time)
{
	p_message.typeMessage = GAMESTATE_MESSAGE;
	p_message.Game_State = gameState;
	for (int i = 0; i < 4; i++)
	{
		p_message.ID[i] = id[i];
		p_message.Score[i] = score[i];
		p_message.RoundtripTime[i] = roundtripTimer[i];
	}
	p_message.time = time;
}

void make_kill_message(kill_message& p_message, uint8_t killID, uint8_t victimID)
{
	p_message.typeMessage = KILL_MESSAGE;
	p_message.killerID = killID;
	p_message.victimID = victimID;
}

void make_roundTripTimer_message(roundtriptimer_message& message, uint64_t p_timestamp)
{
	message.typeMessage = ROUNDTRIPTIMER_MESSAGE;
	message.TimeStamp = p_timestamp;
}






