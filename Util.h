#ifndef UTIL_H_
#define UTIL_H_

#include "../gs2d/src/gs2dframework.h"

inline void DrawFPSRate(gs2d::VideoPtr video)
{
	gs2d::str_type::stringstream ss;
	ss << video->GetFPSRate();
	video->DrawBitmapText(gs2d::math::Vector2(0,0), ss.str(), GS_L("Verdana20_shadow.fnt"), gs2d::GS_COLOR(100,255,255,255));
}

inline void DrawShadow(gs2d::VideoPtr video, gs2d::SpritePtr shadowSprite, const gs2d::math::Vector2& pos, const float radius)
{
	const gs2d::GS_ALPHA_MODE am = video->GetAlphaMode();
	video->SetAlphaMode(gs2d::GSAM_PIXEL);
	const float size = radius * 2.4f;
	const gs2d::GS_COLOR color(100, 255, 255, 255);
	shadowSprite->DrawShaped(pos, gs2d::math::Vector2(size, size), color, color, color, color, 0.0f);
	video->SetAlphaMode(am);
}

inline float AssertFPS(gs2d::VideoPtr video)
{
	const static float fpsCap = 60.0f;
	const static float minFps = 10.0f;
	const float fps = video->GetFPSRate();
	if (fps <= 0.0f)
	{
		video->Message(GS_L("FPS is 0!"), gs2d::GSMT_WARNING);
		return 1.0f;
	}
	else if (fps > fpsCap)
	{
		return fpsCap;
	}
	else if (fps < minFps)
	{
		return minFps;
	}
	return fps;
}

inline void Clamp(gs2d::math::Vector2& pos, const float radius, const gs2d::math::Rect2Df& rect)
{
	const gs2d::math::Vector2 pawnRect = gs2d::math::Vector2(radius, radius);
	const gs2d::math::Vector2 min = rect.pos + pawnRect;
	const gs2d::math::Vector2 max = rect.pos + rect.size - pawnRect;

	if (pos.x < min.x)
		pos.x = min.x;
	if (pos.y < min.y)
		pos.y = min.y;

	if (pos.x > max.x)
		pos.x = max.x;
	if (pos.y > max.y)
		pos.y = max.y;
}

inline gs2d::math::Vector2 ClampLength(const gs2d::math::Vector2& dir, const float max)
{
	gs2d::math::Vector2 r = dir;
	if (r.Length() > max)
	{
		r = gs2d::math::Normalize(r) * max;
	}
	return r;
}

inline bool IsInArea(const gs2d::math::Vector2& pos, const gs2d::math::Rect2Df& area, const gs2d::math::Vector2& origin = gs2d::math::Vector2(0.0f, 0.0f))
{
	const gs2d::math::Vector2 offset = area.size * origin * -1.0f;
	if (pos.x < area.pos.x + offset.x || pos.x > area.pos.x + area.size.x + offset.x
		|| pos.y < area.pos.y + offset.y || pos.y > area.pos.y + area.size.y + offset.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline gs2d::math::Vector2 ReflectVector(const gs2d::math::Vector2& dir, const gs2d::math::Vector2& normal)
{
	return (dir - normal * 2 * (gs2d::math::DP2(normal, dir)));
}

#endif