# pragma once
# include <Siv3D.hpp>

// SpriteAnimatorの設定を保持する構造体
struct SpriteAnimatorConfig
{
	Texture texture;
	Point spriteSize;
	Point startIndex;
	Vec2 pos;
	double frmTime;
	double resize;

	SpriteAnimatorConfig() = default;

	/// @brief SpriteAnimatorConfigを作成します。
	/// @param texture spriteSheetの画像ファイル
	/// @param spriteSize spriteSheetのコマ数(行、列)
	/// @param startIndex spriteSheetの開始位置(行、列)
	/// @param pos 描画する座標
	/// @param frmTime 1コマの描画時間(秒)
	/// @param resize 描画するサイズの倍率
	SpriteAnimatorConfig(const Texture& texture, const Point& spriteSize, const Point& startIndex, const Vec2& pos, double frmTime, double resize):
		texture(texture),
		spriteSize(spriteSize),
		pos(pos),
		frmTime(frmTime),
		resize(resize)
	{
		// startIndexがスプライトシートの範囲外の場合はエラーを投げる
		if (spriteSize.x < startIndex.x || startIndex.x < 0 || spriteSize.y < startIndex.y || startIndex.y < 0)
		{
			throw Error(U"SpriteAnimator: startIndex is out of range");
		}
		else
		{
			this->startIndex = startIndex;
		}
	}

	SpriteAnimatorConfig(const Texture& texture, const Point& spriteSize, const Vec2& pos, double frmTime, double resize) :
		SpriteAnimatorConfig(texture, spriteSize, Point(0, 0), pos, frmTime, resize) {}

	SpriteAnimatorConfig(const Texture& texture, const Point& spriteSize, const Vec2& pos, double frmTime) :
		SpriteAnimatorConfig(texture, spriteSize, Point(0, 0), pos, frmTime, 1.0) {}

};

struct SpriteAnimator:IEffect
{
	/// @brief スプライトシートの画像ファイル
	Texture m_texture;

	/// @brief スプライトシートのコマ数(行、列)
	Point m_spriteSize = { 0,0 };

	/// @brief 現在表示しているコマの位置(行、列)
	Point m_index = { 0,0 };

	/// @brief アニメーションの開始位置(行、列)
	Point m_startIndex = { 0,0 };

	/// @brief １コマの描画時間(秒)
	double m_frmTime = 0.0;

	/// @brief 描画するサイズの倍率
	double m_resize = 1.0;

	/// @brief 描画する座標です。
	Vec2 m_pos = { 0,0 };

	SpriteAnimator() = default;


	SpriteAnimator(const SpriteAnimatorConfig& config) :
		m_texture(config.texture),
		m_spriteSize(config.spriteSize),
		m_startIndex(config.startIndex),
		m_pos(config.pos),
		m_frmTime(config.frmTime),
		m_resize(config.resize) {}

	// IEffectを継承したupdate関数を実装
	bool update(double t) override
	{
		// 現在のコマを計算
		int32 currentFrm = m_startIndex.y * m_spriteSize.x + m_startIndex.x + static_cast<int32>(t / m_frmTime);

		m_index.x = currentFrm % m_spriteSize.x;
		m_index.y = currentFrm / m_spriteSize.x;

		// 現在のコマを描画
		m_texture.uv(static_cast<double>(m_index.x) / m_spriteSize.x, static_cast<double>(m_index.y) / m_spriteSize.y, 1.0 / m_spriteSize.x, 1.0 / m_spriteSize.y).scaled(m_resize).draw(m_pos);

		// 現在のコマがスプライトシートのコマ数を超えたら再生を終了
		return currentFrm < m_spriteSize.area();
	}
};
