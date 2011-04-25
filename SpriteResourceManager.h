#ifndef SPRITE_RESOURCE_MANAGER_H_
#define SPRITE_RESOURCE_MANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include <map>

class SpriteResourceManager
{
	std::map<gs2d::str_type::string, gs2d::SpritePtr> m_sprites;
	static const gs2d::str_type::string m_defaultSpritePath;

public:

	void ReleaseAll();
	gs2d::SpritePtr operator[] (const gs2d::str_type::string& fileName);
	gs2d::SpritePtr GetSprite(const gs2d::VideoPtr& video, const gs2d::str_type::string& fileName, const unsigned int columns = 0, const unsigned int rows = 0);
};

#endif