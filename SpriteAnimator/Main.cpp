# include <Siv3D.hpp> // Siv3D v0.6.13
# include "SpriteAnimator/SpriteAnimator.hpp"

void Main()
{
	Texture explosion{U"spriteSheet/explosion.png"};

	SpriteAnimator spriteAnimator{ explosion,Point{1,1},1.0,1.0 };

	while (System::Update())
	{
		explosion.drawAt(200, 200);
	}
}
