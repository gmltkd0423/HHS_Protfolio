#pragma once

enum class RenderPivot
{
	CENTER,
	BOT,
	LEFT
};

enum class RenderScaleMode
{
	Image,
	User,
};

enum class CollisionType
{
	Point,
	Circle,
	Rect,
	Max
};

enum class EngineMax
{
	RENDERORDERMAX = 2147483647,
};
