# include "SpriteAnimator.hpp"

SpriteAnimator::SpriteAnimator(const Texture& texture, const Point& spriteSize, double frmTime, double resize):
	m_texture(texture),
	m_spriteSize(spriteSize),
	m_frmTime(frmTime),
	m_resize(resize)
{}

bool SpriteAnimator::update(double t)
{
	return false;
}
