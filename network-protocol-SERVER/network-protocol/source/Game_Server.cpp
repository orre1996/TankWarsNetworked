#include "Game_Server.h"
#include "server.h"
#include "TestPlayerObject.h"
#include "LevelCreator.h"
#include "CollisionManager.h"
#include "Wall.h"
#include "Bullet.h"
#include "IEntity.h"
#include "ObjectPool.h"
#include "ServiceLocator.h"

Game_Server::Game_Server()
{
	levelCreator = new LevelCreator("Assets/Level/Level.txt");
	collisionManager = new CollisionManager();
	walls = levelCreator->GetWalls();
	objectPool = new ObjectPool();
	ServiceLocator<ObjectPool>::SetService(objectPool);

	for (auto i = 0; i < 4; i++)
	{
		auto tank = new TestPlayerObject();
		tank->setEntityID(i);
		tank->setPositionSpawnPoint(i);
		Tanks.push_back(tank);
		entities.push_back(tank);
		tanksAndBullets.push_back(tank);
		objectPool->AddToPool(tank);
	}

	for (auto i = 4; i < 24; i++)
	{
		auto* bullet = new Bullet(0,0,0);
		bullet->setEntityID(i);
		bullets.push_back(bullet);
		entities.push_back(bullet);
		tanksAndBullets.push_back(bullet);
		objectPool->AddToPool(bullet);
	}

	for (auto& wall : walls)
	{
		entities.push_back(wall);
	}

}

Game_Server::~Game_Server() = default;

void Game_Server::on_payload(uint8_t index, payload_packet* packet, connection& conn, uint8_t p_deltaTime)
{	
	

	byte_stream stream_(sizeof(packet->payload_), packet->payload_);
	byte_stream_reader streamReader_(stream_);

	
		while (packet->payload_size_ > streamReader_.cursor_ - stream_.base_)
		{
			const auto message_type = static_cast<message_types>(streamReader_.cursor_[0]);
			
			if(message_type == INPUT_MESSAGE)
			{
			
				
				auto msg = new InputMessage();
				if (!serialize(*msg, streamReader_))
				{
					__debugbreak();
				}

				const float rotation = msg->rotation;
				msg->rotation = rotation;
				deltaTime = static_cast<float>(msg->deltaTime) * 0.001f;
				conn.lastReceivedUniqueID = msg->UniqueID;

				msgQueue.push_back(msg);
				Tanks[conn.index]->SetRotation(rotation);


			}

			if(message_type == ROUNDTRIPTIMER_MESSAGE)
			{
				const auto msg = new roundtriptimer_message();
				if (!serialize(*msg, streamReader_))
				{
					break;
				}

				conn.lastReceivedRTT = network::get_ticks() - msg->TimeStamp;
			}
			
		}

		stream_.reset();

	Update(deltaTime, conn);
}

void Game_Server::Update(float p_delta, connection& conn)
{
	HandleInput(conn, p_delta);
	CheckCollision(conn);
	ClearMessages();
}

void Game_Server::HandleInput(connection& p_conn, float p_delta)
{
	for (auto& i : msgQueue)
	{
		if (currentGameState == RUNNING)
		{
			
			Tanks[p_conn.index]->SendInput(i->inputMessage, p_delta);

			const uint8_t FifthBit = i->inputMessage & (1 << 4);

			if (FifthBit > 0)
			{
				if (network::get_ticks() > p_conn.canShoot && Tanks[p_conn.index]->getEntityState() == ALIVE)
				{
					auto bullet = dynamic_cast<Bullet*>(objectPool->create("Bullet"));
					bullet->setCreator(Tanks[p_conn.index]);
					bullet->SetRotation(bullet->GetCreator()->GetRotation());
					bullet->updateForward();
					bullet->setPosition(bullet->GetCreator()->getMiddleX() + bullet->getForward().x * 1.5f, bullet->GetCreator()->getMiddleY() + bullet->getForward().y * 1.5f);
					bullet->GetCreator()->setCanShoot(false);
					p_conn.canShoot = network::get_ticks() + 1000;
				}
			}
		}
	}
}


void Game_Server::CheckCollision(connection& p_conn)
{
	for (auto& entities : entities)
	{
		for (auto& Tank : Tanks)
		{
			if (CollisionManager::CheckCollision(Tank, entities))
			{
				if (Tank->getEntityState() == ALIVE && entities->getEntityState() == ALIVE)
				{
					auto* tank = dynamic_cast<TestPlayerObject*>(entities);
					if (tank != nullptr)
					{
						continue;
					}
					Vec vec;
					const vec2 WallNormal = CollisionManager::GetNormalOfRect(Tank->m_collider, entities->m_collider);

					const vec2 OverlapVec = CollisionManager::CalculateCollisionOverlap(Tank->m_collider, entities->m_collider);
					const vec2 collisionVector = { WallNormal.x * OverlapVec.x, WallNormal.y * OverlapVec.y };

					const float xPos = Tank->GetTankX() + collisionVector.x;
					const float yPos = Tank->GetTankY() + collisionVector.y;
					Tank->SetTankPos(xPos, yPos);
				}
			}
		}
	}

	for (auto& i : bullets)
	{
		for (auto& entities : entities)
		{
			if (CollisionManager::CheckCollision(i, entities))
			{
				const auto bullet = dynamic_cast<Bullet*>(entities);
				if (bullet != nullptr)
				{
					continue;
				}

				if (i->getEntityState() == ALIVE && entities->getEntityType() == TANK && entities->getEntityState() == ALIVE)
				{
					entities->setEntityState(DEAD);
					entities->setDeadCD();
					i->setEntityState(DEAD);
					p_conn.score++;
					killerID = i->GetCreator()->getEntityID();
					victimID = entities->getEntityID();
					killMessageTries = 0;
				}

				else if (i->getEntityState() == ALIVE && entities->getEntityState() == ALIVE)
				{
					i->setEntityState(DEAD);
				}
			}
		}
	}
}

void Game_Server::ClearMessages()
{
	if (!msgQueue.empty()) {
		for (auto& it : msgQueue)
		{
			delete it;
			it = nullptr;
		}
		msgQueue.clear();
	}
}

payload_packet Game_Server::GetPayload() const
{
	return payloadPacket;
}

void Game_Server::on_Connect(int connection_index)
{
	latestConnect = connection_index;
	Tanks[connection_index]->setCurrentState(ALIVE);
	Tanks[connection_index]->setConnected(true);
	Tanks[connection_index]->setPositionSpawnPoint(connection_index);

}

void Game_Server::on_Disonnect(const int connection_index)
{
	latestDC = connection_index;
	Tanks[connection_index]->setConnected(false);
	Tanks[connection_index]->setCurrentState(DEAD);
}



int Game_Server::getLatestDc() const
{
	return latestDC;
	
}

int Game_Server::getLatestConnect() const
{
	return latestConnect;
}

TestPlayerObject* Game_Server::GetTank() const
{
	return Tank;
}

std::vector<Bullet*> Game_Server::getBullets() const
{
	return bullets;
}

std::vector<TestPlayerObject*> Game_Server::GetTanks() const
{
	return Tanks;
}

std::vector<IEntity*> Game_Server::GetEntities() const
{
	return entities;
}

std::vector<IEntity*> Game_Server::GetTanksAndBullets() const
{
	return tanksAndBullets;
}

int Game_Server::GetKillID() const
{
	return killerID;
}

int Game_Server::GetVictimID() const
{
	return victimID;
}

int Game_Server::GetKillMessageTries() const
{
	return killMessageTries;
}

void Game_Server::IncreaseKillMessageTries()
{
	killMessageTries++;
}

Game_State Game_Server::GetCurrentGameState() const
{
	return currentGameState;
}

void Game_Server::SetCurrentGameState(Game_State p_state)
{
	currentGameState = p_state;
}

void Game_Server::setRoundTimer(int p_value)
{
	roundTime = p_value;
}

int Game_Server::getRoundTimer() const
{
	return static_cast<int>(roundTime);
}

