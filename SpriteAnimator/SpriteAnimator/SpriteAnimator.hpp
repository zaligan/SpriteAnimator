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
	/// @brief SpriteAnimatorの設定を保持する構造体
	SpriteConfig m_config;

	/// @brief 現在表示しているコマの位置(行、列)
	Point m_index = { 0,0 };

	/// @brief 描画する座標です。(中心座標)
	Vec2 m_pos = { 0,0 };

	SpriteAnimator() = default;

	/// @brief SpriteAnimatorを作成します。
	/// @param config spriteSheetの設定です。
	/// @param pos 描画する座標です。
	/// @param startIndex 描画するコマの開始位置(行、列)です。
	SpriteAnimator(const SpriteConfig& config, const Vec2& pos, const Point& startIndex) :
		m_config(config),
		m_pos(pos)
	{
		m_config.startIndex = startIndex;
	}

	SpriteAnimator(const SpriteConfig& config, const Vec2& pos) :
		m_config(config),
		m_pos(pos)
	{}

	// IEffect を継承した update 関数を実装
	bool update(double t) override
	{
		// 現在のコマを計算
		int32 currentFrm = m_config.startIndex.y * m_config.spriteSize.x + m_config.startIndex.x + static_cast<int32>(t / m_config.frmTime);

		m_index.x = currentFrm % m_config.spriteSize.x;
		m_index.y = currentFrm / m_config.spriteSize.x;

		const ScopedRenderStates2D blend{ BlendState::Additive };
		// 現在のコマを描画
		m_config.texture.uv(static_cast<double>(m_index.x) / m_config.spriteSize.x, static_cast<double>(m_index.y) / m_config.spriteSize.y, 1.0 / m_config.spriteSize.x, 1.0 / m_config.spriteSize.y).scaled(m_config.resize).draw(Arg::center(m_pos));

		// 現在のコマがスプライトシートのコマ数を超えたら再生を終了
		return currentFrm < m_config.spriteSize.area();
	}
};
