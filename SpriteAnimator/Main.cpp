﻿# include <Siv3D.hpp> // Siv3D v0.6.13
# include "SpriteAnimator/SpriteAnimator.hpp"

void Main()
{
	Effect effect;

	Texture explosion{U"spriteSheet/explosion.png"};

	while (System::Update())
	{
		if (MouseL.down())
		{
			Print << U"表示します";
			effect.add<SpriteAnimator>(explosion, Point{ 8,2 }, Cursor::Pos(), 1.0, 0.05);
		}
		effect.update();
	}
}
