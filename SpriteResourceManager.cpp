#include "SpriteResourceManager.h"

using namespace gs2d;
using namespace gs2d::math;

const str_type::string SpriteResourceManager::m_defaultSpritePath = GS_L("assets/textures/");

inline SpritePtr SetupSpriteRects(SpritePtr sprite, const unsigned int columns, const unsigned int rows)
{
	if (columns != 0 && rows != 0)
	{
		if (sprite->GetNumColumns() != columns || sprite->GetNumRows() != rows)
		{
			sprite->SetupSpriteRects(columns, rows);
		}
	}
	return sprite;
}

SpritePtr SpriteResourceManager::GetSprite(const VideoPtr& video, const str_type::string& fileName, const unsigned int columns, const unsigned int rows)
{
	std::map<str_type::string, SpritePtr>::iterator iter = m_sprites.find(fileName);
	if (iter == m_sprites.end())
	{
		SpritePtr sprite = video->CreateSprite(m_defaultSpritePath + fileName, GS_ZERO, 0, 0);
		if (sprite)
		{
			m_sprites[fileName] = sprite;
			video->Message(fileName + GS_L(": resource loaded"), GSMT_INFO);
			return SetupSpriteRects(sprite, columns, rows);
		}
		else
		{
			return SpritePtr();
		}
	}
	else
	{
		return SetupSpriteRects(iter->second, columns, rows);
	}
}

void SpriteResourceManager::ReleaseAll()
{
	m_sprites.clear();
}

SpritePtr SpriteResourceManager::operator[] (const str_type::string& fileName)
{
	std::map<str_type::string, SpritePtr>::iterator iter = m_sprites.find(fileName);
	if (iter == m_sprites.end())
	{
		return iter->second;
	}
	else
	{
		return SpritePtr();
	}
}
