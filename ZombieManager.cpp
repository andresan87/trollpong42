#include "ZombieManager.h"

using namespace gs2d;
using namespace gs2d::math;

const unsigned long ZombieManager::ZOMBIE_ADD_INTERVAL = 2000;

ZombieManager::ZombieManager(VideoPtr video, const std::vector<gs2d::SpritePtr>& sprites, BallPtr ball, SpritePtr bloodSprite) :
	m_ball(ball),
	m_bloodSprite(bloodSprite)
{
	m_lastAddTime = video->GetElapsedTime();
	m_sprites = sprites;
}

void ZombieManager::Add(ZombiePtr zombie)
{
	m_zombies.push_back(zombie);
}

void ZombieManager::AddZombies(gs2d::VideoPtr video)
{
	if (video->GetElapsedTime() - m_lastAddTime > ZOMBIE_ADD_INTERVAL)
	{
		SpritePtr sprite = m_sprites[Randomizer::Int(m_sprites.size()-1)];
		m_zombies.push_back(ZombiePtr(new Zombie(video, Vector2(video->GetScreenSizeF().x/2.0f, 0.0f), sprite)));
		m_lastAddTime = video->GetElapsedTime();
	}
}

void ZombieManager::Draw(gs2d::VideoPtr video)
{
	for (std::list<ZombiePtr>::iterator iter = m_zombies.begin(); iter != m_zombies.end(); iter++)
	{
		(*iter)->Draw(video);
	}
}

void ZombieManager::CheckZombieStatus(ZombiePtr zombie, EffectManagerPtr fxManager, VideoPtr video)
{
	const float radiusSum = m_ball->GetRadius() + (zombie->GetSprite()->GetRect().size.x / 4.0f);
	if (SquaredDistance(m_ball->GetPos(), zombie->GetPos()) < radiusSum*radiusSum)
	{
		zombie->Kill();
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, m_bloodSprite, zombie->GetPos(), 0.0f, 400, 0.0f,
					   Vector2(128, 128), 1.0f, false, false, 0.0f)));
		fxManager->Add(TemporaryEffectPtr(new SingleParticle(video, m_bloodSprite, zombie->GetPos(), 0.0f, 400, 0.0f,
					   Vector2(128, 128), 1.0f, false, false, 180.0f)));
	}
}

void ZombieManager::Update(VideoPtr video, InputPtr input, const unsigned long lastFrameDeltaTimeMS, EffectManagerPtr fxManager)
{
	for (std::list<ZombiePtr>::iterator iter = m_zombies.begin(); iter != m_zombies.end();)
	{
		if (!(*iter)->IsDead())
		{
			(*iter)->Update(video, input, lastFrameDeltaTimeMS);
			CheckZombieStatus(*iter, fxManager, video);
			iter++;
		}
		else
		{
			iter = m_zombies.erase(iter);
		}
	}
	AddZombies(video);
}
