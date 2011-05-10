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

	void AddZombies(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void CheckZombieStatus(SpriteResourceManager& spr, ZombiePtr zombie, EffectManagerPtr fxManager,
		gs2d::VideoPtr video, gs2d::AudioPtr audio, PawnManagerPtr pawnManager);
	std::size_t GetNextSpawnSpot();

public:
	void FillSpritePtrs(const gs2d::VideoPtr& video, SpriteResourceManager& spr);
	static const std::size_t MAX_ZOMBIES;
	ZombieManager(gs2d::VideoPtr video, const std::vector<gs2d::str_type::string>& spriteNames, BallPtr ball,
		const std::vector<gs2d::str_type::string>& bloodDecals);
	void Draw(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void Update(SpriteResourceManager& spr, gs2d::VideoPtr video,
				gs2d::InputPtr input, gs2d::AudioPtr audio, const unsigned long lastFrameDeltaTimeMS,
				EffectManagerPtr fxManager, PawnManagerPtr pawnManager);

};

typedef boost::shared_ptr<ZombieManager> ZombieManagerPtr;

#endif