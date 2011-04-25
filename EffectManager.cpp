#include "EffectManager.h" 

using namespace gs2d;
using namespace gs2d::math;

void UpdateEffectList(std::list<TemporaryEffectPtr> &effects, VideoPtr video, const unsigned long elapsedTime, SpriteResourceManager& spr)
{
	for (std::list<TemporaryEffectPtr>::iterator iter = effects.begin(); iter != effects.end();)
	{
		if ((*iter)->IsOver())
		{
			iter = effects.erase(iter);
		}
		else
		{
			(*iter)->Update(video, elapsedTime, spr);
			 iter++;
		}
	}
}

void DrawEffectList(std::list<TemporaryEffectPtr> &effects, VideoPtr video, SpriteResourceManager& spr)
{
	for (std::list<TemporaryEffectPtr>::iterator iter = effects.begin(); iter != effects.end(); iter++)
	{
		(*iter)->Draw(video, spr);
	}
}

void EffectManager::Add(TemporaryEffectPtr effect, const bool ground)
{
	(ground ? m_groundEffects : m_mainEffects).push_back(effect);
}

void EffectManager::Update(VideoPtr video, const unsigned long elapsedTime, SpriteResourceManager& spr)
{
	UpdateEffectList(m_mainEffects, video, elapsedTime, spr);
	UpdateEffectList(m_groundEffects, video, elapsedTime, spr);
}

void EffectManager::DrawMain(VideoPtr video, SpriteResourceManager& spr)
{
	DrawEffectList(m_mainEffects, video, spr);
}

void EffectManager::DrawGround(VideoPtr video, SpriteResourceManager& spr)
{
	DrawEffectList(m_groundEffects, video, spr);
}