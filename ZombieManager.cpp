#include "ZombieManager.h"

using namespace gs2d;
using namespace gs2d::math;

const unsigned long ZombieManager::ZOMBIE_ADD_INTERVAL = 1000;
const std::size_t ZombieManager::MAX_ZOMBIES = 40;

ZombieManager::ZombieManager(VideoPtr video, const std::vector<gs2d::str_type::string>& spriteNames, BallPtr ball,
							 const std::vector<str_type::string>& bloodDecals) :
	m_ball(ball),
	m_normalizedSpawnSpots(4),
	m_currentSpawnSpot(0),
	m_bloodDecals(bloodDecals)
{
	m_lastAddTime = video->GetElapsedTime();
	m_spriteNames = spriteNames;
	m_normalizedSpawnSpots[0] = Vector2(0, 0);
	m_normalizedSpawnSpots[1] = Vector2(1, 0);
	m_normalizedSpawnSpots[2] = Vector2(1, 1);
	m_normalizedSpawnSpots[3] = Vector2(0, 1);
}

std::size_t ZombieManager::GetNextSpawnSpot()
{
	const std::size_t current = m_currentSpawnSpot++;
	if (m_currentSpawnSpot >= m_normalizedSpawnSpots.size())
	{
		m_currentSpawnSpot = 0;
	}
	return current;
}

void ZombieManager::Add(ZombiePtr zombie)
{
	m_zombies.push_back(zombie);
}

void ZombieManager::AddZombies(gs2d::VideoPtr video)
{
	if (m_zombies.size() < MAX_ZOMBIES)
	{
		if (video->GetElapsedTime() - m_lastAddTime > ZOMBIE_ADD_INTERVAL)
		{
			const Vector2 spawnPos = m_normalizedSpawnSpots[GetNextSpawnSpot()] * video->GetScreenSizeF();

			str_type::string spriteName = m_spriteNames[Randomizer::Int(m_spriteNames.size()-1)];
			m_zombies.push_back(ZombiePtr(new Zombie(video, spawnPos, spriteName)));
			m_lastAddTime = video->GetElapsedTime();
		}
	}
}

void ZombieManager::Draw(gs2d::VideoPtr video, SpriteResourceManager& spr)
{
	for (std::list<ZombiePtr>::iterator iter = m_zombies.begin(); iter != m_zombies.end(); iter++)
	{
		(*iter)->Draw(spr, video);
	}
}

void ZombieManager::CheckZombieStatus(SpriteResourceManager& spr, ZombiePtr zombie, EffectManagerPtr fxManager, VideoPtr video, PawnManagerPtr pawnManager)
{
	SpritePtr zombieSprite = spr.GetSprite(video, zombie->GetSpriteName());

	const float rectSize = zombieSprite->GetRect().size.x;
	const float radiusSum = m_ball->GetRadius(spr, video) + (rectSize / 4.0f);
	if (SquaredDistance(m_ball->GetPos(), zombie->GetPos()) < radiusSum*radiusSum)
	{
		zombie->Kill();
		pawnManager->AddToScore(m_ball->GetTouchOwnerId(), 1);

		// SpritePtr bloodSprite = spr.GetSprite(video, GS_L("blood01.png"), 6, 1);
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, GS_L("blood01.png"), zombie->GetPos(), 0.0f, 400, 0.0f,
					   Vector2(128, 128), 1.0f, false, false, 0.0f)));
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, GS_L("blood01.png"), zombie->GetPos(), 0.0f, 400, 0.0f,
					   Vector2(128, 128), 1.0f, false, false, 180.0f)));

		const float size = 64.0f + Randomizer::Float(64.0f);

		// SpritePtr decalSprite = spr.GetSprite(video, m_bloodDecals[Randomizer::Int(10) % 2]);
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, m_bloodDecals[Randomizer::Int(10) % 2], zombie->GetPos(), 0.0f, 14000, 0.0f,
					   Vector2(size, size), 1.0f, false, true, Randomizer::Float(360.0f), false)), true);
	}
}

void ZombieManager::Update(SpriteResourceManager& spr, VideoPtr video, InputPtr input, const unsigned long lastFrameDeltaTimeMS, EffectManagerPtr fxManager, PawnManagerPtr pawnManager)
{
	for (std::list<ZombiePtr>::iterator iter = m_zombies.begin(); iter != m_zombies.end();)
	{
		if (!(*iter)->IsDead())
		{
			(*iter)->Update(video, input, lastFrameDeltaTimeMS);
			CheckZombieStatus(spr, *iter, fxManager, video, pawnManager);
			iter++;
		}
		else
		{
			iter = m_zombies.erase(iter);
		}
	}
	AddZombies(video);
}
