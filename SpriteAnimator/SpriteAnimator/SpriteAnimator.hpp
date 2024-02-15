# pragma once
# include <Siv3D.hpp>

// SpriteAnimatorの設定を保持する構造体
struct SpriteConfig
{
	/// @brief スプライトシートの画像ファイル
	Texture texture;

	/// @brief スプライトシートのコマ数(行、列)
	Point spriteSize;

	/// @brief １コマの描画時間(秒)
	double frmTime;

	/// @brief 描画するサイズの倍率です。
	double resize;

	/// @brief アニメーションの開始位置(行、列)
	Point startIndex = { 0,0 };

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

	/// @brief 描画する座標です。(中心座標)
	Vec2 m_pos = { 0,0 };

	SpriteAnimator() = default;

	/// @brief SpriteAnimatorを作成します。
	/// @param config spriteSheetの設定です。
	/// @param pos 描画する座標です。
	/// @param startIndex 描画するコマの開始位置(行、列)です。
	SpriteAnimator(const SpriteConfig& config, const Vec2& pos, const Point& startIndex) :
		m_texture(config.texture),
		m_spriteSize(config.spriteSize),
		m_frmTime(config.frmTime),
		m_resize(config.resize),
		m_pos(pos),
		m_startIndex(startIndex)
	{}

	SpriteAnimator(const SpriteConfig& config, const Vec2& pos) :
		SpriteAnimator(config, pos, config.startIndex)
	{}

	// IEffect を継承した update 関数を実装
	bool update(double t) override
	{
		// 現在のコマを計算
		int32 currentFrm = m_startIndex.y * m_spriteSize.x + m_startIndex.x + static_cast<int32>(t / m_frmTime);

		m_index.x = currentFrm % m_spriteSize.x;
		m_index.y = currentFrm / m_spriteSize.x;

		// 現在のコマを描画
		m_texture.uv(static_cast<double>(m_index.x) / m_spriteSize.x, static_cast<double>(m_index.y) / m_spriteSize.y, 1.0 / m_spriteSize.x, 1.0 / m_spriteSize.y).scaled(m_resize).draw(Arg::center(m_pos));

		// 現在のコマがスプライトシートのコマ数を超えたら再生を終了
		return currentFrm < m_spriteSize.area();
	}
};
