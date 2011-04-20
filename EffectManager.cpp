#include "EffectManager.h" 

using namespace gs2d;
using namespace gs2d::math;

void UpdateEffectList(std::list<TemporaryEffectPtr> &effects, VideoPtr video, const unsigned long elapsedTime)
{
	for (std::list<TemporaryEffectPtr>::iterator iter = effects.begin(); iter != effects.end();)
	{
		if ((*iter)->IsOver())
		{
			iter = effects.erase(iter);
		}
		else
		{
			(*iter)->Update(video, elapsedTime);
			 iter++;
		}
	}
}

void DrawEffectList(std::list<TemporaryEffectPtr> &effects, VideoPtr video)
{
	for (std::list<TemporaryEffectPtr>::iterator iter = effects.begin(); iter != effects.end(); iter++)
	{
		(*iter)->Draw(video);
	}
}

void EffectManager::Add(TemporaryEffectPtr effect, const bool ground)
{
	(ground ? m_groundEffects : m_mainEffects).push_back(effect);
}

void EffectManager::Update(VideoPtr video, const unsigned long elapsedTime)
{
	UpdateEffectList(m_mainEffects, video, elapsedTime);
	UpdateEffectList(m_groundEffects, video, elapsedTime);
}

void EffectManager::DrawMain(VideoPtr video)
{
	DrawEffectList(m_mainEffects, video);
}

void EffectManager::DrawGround(VideoPtr video)
{
	DrawEffectList(m_groundEffects, video);
}