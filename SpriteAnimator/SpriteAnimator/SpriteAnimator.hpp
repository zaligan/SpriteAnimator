# pragma once
# include <Siv3D.hpp>

class SpriteAnimator:IEffect
{
public:

	SpriteAnimator() = default;

	/// @brief SpriteAnimatorを作成します。
	/// @param texture アニメーションするスプライトシートです。
	/// @param spriteSize スプライトシートに描かれているコマ数（行、列）です。
	/// @param frmTime １コマの描画時間です。
	/// @param resize 描画サイズの倍率です。
	SpriteAnimator(const Texture& texture, const Point& spriteSize, double frmTime, double resize);

	/// @brief アニメーションの状態を更新します。
	/// @param t アニメーションを開始してからの時間（秒）です。
	/// @return 次のフレームもアニメーションを継続する場合 trueを返します。
	bool update(double t) override;

private:

	/// @brief スプライトシートの画像ファイル
	Texture m_texture;

	/// @brief スプライトシートのコマ数(行、列)
	Point m_spriteSize;

	/// @brief 現在表示しているコマの位置(行、列)
	Point m_index;

	/// @brief １コマの描画時間(秒)
	double m_frmTime;

	/// @brief 描画するサイズの倍率
	double m_resize = 1.0;
};
