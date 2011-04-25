#ifndef EFFECT_MANAGER_H_
#define EFFECT_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include "TemporaryEffect.h"
#include "SpriteResourceManager.h"
#include <list>

class EffectManager
{
	std::list<TemporaryEffectPtr> m_mainEffects;
	std::list<TemporaryEffectPtr> m_groundEffects;

public:
	void Add(TemporaryEffectPtr effect, const bool ground = false);
	void Update(gs2d::VideoPtr video, const unsigned long elapsedTime, SpriteResourceManager& spr);
	void DrawMain(gs2d::VideoPtr video, SpriteResourceManager& spr);
	void DrawGround(gs2d::VideoPtr video, SpriteResourceManager& spr);
};

typedef boost::shared_ptr<EffectManager> EffectManagerPtr;

#endif