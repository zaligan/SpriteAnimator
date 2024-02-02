# pragma once
# include <Siv3D.hpp>

struct SpriteAnimator:IEffect
{
	/// @brief スプライトシートの画像ファイル
	Texture m_texture;

	/// @brief スプライトシートのコマ数(行、列)
	Point m_spriteSize = { 0,0 };

	/// @brief 現在表示しているコマの位置(行、列)
	Point m_index = { 0,0 };

	/// @brief １コマの描画時間(秒)
	double m_frmTime = 0.0;

	/// @brief 描画するサイズの倍率
	double m_resize = 1.0;

	/// @brief 描画する座標です。
	Vec2 m_pos = { 0,0 };

	SpriteAnimator() = default;

	/// @brief アニメーションを作成します。
	/// @param texture アニメーションするスプライトシートです。
	/// @param spriteSize スプライトシートに描かれているコマ数（行、列）です。
	/// @param pos 描画する座標です。
	/// @param resize 描画サイズの倍率です。
	/// @param frmTime 1コマの描画時間(秒)です。
	explicit SpriteAnimator(const Texture& texture, const Point& spriteSize, const Vec2& pos, double resize, double frmTime) :
		m_texture(texture),
		m_spriteSize(spriteSize),
		m_pos(pos),
		m_frmTime(frmTime),
		m_resize(resize) {}

	/// @brief アニメーションの状態を更新します。
	/// @param t アニメーションを開始してからの時間（秒）です。
	/// @return 次のフレームもアニメーションを継続する場合 trueを返します。
	bool update(double t) override
	{
		int32 currentFrm = t / m_frmTime;

		m_index.x = currentFrm % m_spriteSize.x;
		m_index.y = currentFrm / m_spriteSize.x;

		m_texture.uv(static_cast<double>(m_index.x) / m_spriteSize.x, static_cast<double>(m_index.y) / m_spriteSize.y, 1.0 / m_spriteSize.x, 1.0 / m_spriteSize.y).scaled(m_resize).drawAt(m_pos);

		return m_index.y <= m_spriteSize.y;
	}
};
