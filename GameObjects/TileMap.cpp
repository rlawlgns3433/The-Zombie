#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	:GameObject(name)
{
	sortLayer = -1;
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipX ? -scale.y : scale.y;

	transform.scale(scaleX, scaleY, position.x, position.y);
	transform.rotate(rotation, position.x, position.y);
	transform.translate(position - origin);

	SetBoundary();
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f posOffsets[4] = {
		{0,0},
		{size.x,0},
		{size.x,size.y},
		{0,size.y}
	};

	for (int i = 0; i < count.y; ++i)
	{
		for (int j = 0; j < count.x; ++j)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
				texIndex = 3;

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(size.x * j, size.y * i);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = (quadIndex * 4) + k;
				va[vertexIndex].position = quadPos + posOffsets[k];
				va[vertexIndex].texCoords = sf::Vector2f(0, texIndex * size.y) + posOffsets[k];
			}
		}
	}

	SetBoundary();
}

void TileMap::Init()
{
	GameObject::Init();
	SetSpriteSheetId("graphics/background_sheet.png");
	//50x50
	Set({ 20, 20 }, { 50.f, 50.f });
}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);

}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;

	window.draw(va, state);
}

void TileMap::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	originPreset = preset;
	sf::FloatRect bound = va.getBounds();
	origin.x = bound.width * ((int)originPreset % 3) * 0.5f;
	origin.y = bound.height * ((int)originPreset % 3) * 0.5f;

	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta);
	UpdateTransform();
}

void TileMap::SetBoundary()
{
	boundaryLT.x = position.x - ((cellCount.x / 2.f - 1) * cellSize.x)*scale.x;
	boundaryLT.y = position.y - ((cellCount.y / 2.f - 1) * cellSize.y)*scale.y;
	boundaryRB.x = position.x + ((cellCount.x / 2.f - 1) * cellSize.x)*scale.x;
	boundaryRB.y = position.y + ((cellCount.y / 2.f - 1) * cellSize.y)*scale.y;
}

std::pair<const sf::Vector2f&, const sf::Vector2f&> TileMap::GetBoundary() const
{
	return std::make_pair(boundaryLT, boundaryRB);
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	GameObject::SetScale(scale);
	UpdateTransform();

}

void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);
	UpdateTransform();
}

void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);
	UpdateTransform();
}

void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	UpdateTransform();
}

sf::FloatRect TileMap::GetLocalBoundsT() const
{
	sf::FloatRect bounds = va.getBounds();
	bounds.left = origin.x;
	bounds.top = origin.y;
	return bounds;
}

sf::FloatRect TileMap::GetGlobalBoundsT() const
{
	sf::FloatRect bounds = va.getBounds();
	return transform.transformRect(bounds);
}