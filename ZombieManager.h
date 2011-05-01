#ifndef ZOMBIE_MANAGER_H_
#define ZOMBIE_MANAGER_H_

#include "Zombie.h"
#include "GameEntity.h"
#include "EffectManager.h"
#include "PawnManager.h"
#include "SpriteResourceManager.h"
#include <list>
#include <vector>

class ZombieManager
{
	std::list<ZombiePtr> m_zombies;
	std::vector<gs2d::str_type::string> m_spriteNames;
	std::vector<gs2d::str_type::string> m_bloodDecals;
	BallPtr m_ball;

	std::vector<gs2d::math::Vector2> m_normalizedSpawnSpots;
	std::size_t m_currentSpawnSpot;

	unsigned long m_lastAddTime;
	static const unsigned long ZOMBIE_ADD_INTERVAL;

	void AddZombies(gs2d::VideoPtr video);
	void CheckZombieStatus(SpriteResourceManager& spr, ZombiePtr zombie, EffectManagerPtr fxManager, gs2d::VideoPtr video, PawnManagerPtr pawnManager);
	std::size_t GetNextSpawnSpot();

public:
	static const std::size_t MAX_ZOMBIES;
	ZombieManager(gs2d::VideoPtr video, const std::vector<gs2d::str_type::string>& spriteNames, BallPtr ball,
		const std::vector<gs2d::str_type::string>& bloodDecals);
	void Add(ZombiePtr zombie);
	void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void Update(SpriteResourceManager& spr, gs2d::VideoPtr video, gs2d::InputPtr input, const unsigned long lastFrameDeltaTimeMS,
				EffectManagerPtr fxManager, PawnManagerPtr pawnManager);

};

typedef boost::shared_ptr<ZombieManager> ZombieManagerPtr;

#endif