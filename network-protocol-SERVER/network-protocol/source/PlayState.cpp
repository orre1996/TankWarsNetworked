#include "PlayState.h"
#include "Game_Server.h"
#include "server.h"
#include <iostream>
#include "TestPlayerObject.h"
#include "LevelCreator.h"
#include "CollisionManager.h"
#include "Wall.h"
#include "PlayState.h"
#include "Bullet.h"



PlayState::PlayState() /*: Tank(new TestPlayerObject())*/
{
	levelCreator = new LevelCreator("Assets/Level/Level.txt");
	collisionManager = new CollisionManager();
	walls = levelCreator->GetWalls();

}


PlayState::~PlayState()
{
}

void PlayState::Update(float p_delta)
{
	for (int i = 0; i < msgQueue.size(); i++)
	{

		Tank->SendInput(msgQueue[i]->inputMessage, p_delta);

		uint8_t FifthBit = msgQueue[i]->inputMessage & (1 << 4);

		if (FifthBit > 0)
		{
			Bullet* bullet = new Bullet(Tank->GetTankX(), Tank->GetTankY(), Tank->GetRotation());
			bullets.push_back(bullet);
		}
	}

	/*for (int i = 0; i < walls.size(); i++)
	{
		if (CollisionManager::CheckCollision(Tank, walls[i]))
		{
			Vec vec;

			vec2 WallNormal = CollisionManager::GetNormalOfRect(Tank->m_collider, walls[i]->m_collider);
			vec2 invNormal = { WallNormal.x *-1, WallNormal.y * -1 };
			vec2 playerDirection = Tank->GetMovementDirection();

			vec2 OverlapVec = CollisionManager::CalculateCollisionOverlap(Tank->m_collider, walls[i]->m_collider);
			vec2 collisionVector = { WallNormal.x * OverlapVec.x, WallNormal.y * OverlapVec.y };

			float xPos = Tank->GetTankX() + collisionVector.x;
			float yPos = Tank->GetTankY() + collisionVector.y;
			Tank->SetTankPos(xPos, yPos);


		}
	}*/

	if (msgQueue.size() != 0) {
		for (auto it = msgQueue.begin(); it != msgQueue.end(); it++)
		{
			delete *it;
			*it = nullptr;
		}
		msgQueue.clear();
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(0.1f); //Todo: add deltaTime.
	}
}

void PlayState::Enter()
{
}

void PlayState::Exit()
{
}
