# include <Siv3D.hpp> // Siv3D v0.6.13
# include "SpriteAnimator/SpriteAnimator.hpp"

void Main()
{
	Effect effect;

	Texture explosion{U"spriteSheet/explosion.png"};

	Vec2 pos = {0,0};

	Point spriteSize{ 8,2 };

	Point startPoint{ 0,0 };

	while (System::Update())
	{
		pos = Cursor::Pos();

		if (MouseL.down())
		{
			//エフェクトを追加します。
			SpriteAnimatorConfig config(explosion, spriteSize, startPoint, pos, 0.05, 1);
			effect.add<SpriteAnimator>(config);
		}

		//エフェクトの状態を更新します。
		effect.update();
	}
}
