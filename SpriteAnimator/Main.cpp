# include <Siv3D.hpp> // Siv3D v0.6.13
# include "SpriteAnimator/SpriteAnimator.hpp"

void Main()
{
	Effect effect;

	// スプライトシートの画像ファイルを読み込みます。
	Texture explosion{U"spriteSheet/explosion.png"};

	// 描画する座標です。
	Vec2 pos = {0,0};

	// スプライトシートのコマ数(行、列)を指定します。
	Point spriteSize{ 8,2 };

	// アニメーションの開始位置(行、列)を指定します。
	Point startPoint{ 0,0 };

	// スプライトシートの設定を保持する構造体を作成します。
	SpriteConfig config(explosion, spriteSize, 0.05, 1.5, startPoint);

	while (System::Update())
	{
		pos = Cursor::Pos();

		if (MouseL.down())
		{
			//エフェクトを追加します。
			effect.add<SpriteAnimator>(config, pos);
		}

		//エフェクトの状態を更新します。
		effect.update();
	}
}
