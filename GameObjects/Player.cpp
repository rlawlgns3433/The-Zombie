#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "Item2.h"
#include "UIHUD.h"
#include "Crosshair.h"
#include "Gun.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/player.png";
	sortLayer = 5;
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

	scene = SCENE_MGR.GetScene(SceneIds::SceneGame);
	gun = new Gun("Gun");
	gun->Init();
	gun->Reset();
	dynamic_cast<SceneGame*>(scene)->AddGo(gun);

}

void Player::Release()
{
	SpriteGo::Init();
}

void Player::Reset()
{
	SpriteGo::Reset();
	active = true;

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
	hud = dynamic_cast<UIHUD*>(SCENE_MGR.GetCurrentScene()->FindGo("UIHUD"));

	hud->SetHp(hp, maxHp);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	damagedTimer += dt;

	//Ä³ï¿½ï¿½ï¿½ï¿½ È¸ï¿½ï¿½	
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//sf::Vector2f mouseWorldPos = InputMgr::GetMousePos() + SCENE_MGR.GetCurrentScene()->GetViewCenter() - sf::Vector2f(FRAMEWORK.GetWindow().getSize()) * 0.5f;
	float lookAngle = Utils::Angle(mouseWorldPos - GetPosition());
	Utils::Rotate(look, lookAngle);
	SetRotation(lookAngle);

	//Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½Ìµï¿½
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2f tempPos(GetPosition() + direction * speed * dt);

	//ï¿½æµ¹ ï¿½Ë»ï¿½
	boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	// 
	//ï¿½æµ¹ ï¿½Ë»ï¿½: ï¿½ï¿½
	if (tempPos.x < boundary.first.x)
		Utils::ElasticCollision(tempPos.x, boundary.first.x, 0.f);
	if (tempPos.x > boundary.second.x)
		Utils::ElasticCollision(tempPos.x, boundary.second.x, 0.f);
	if (tempPos.y < boundary.first.y)
		Utils::ElasticCollision(tempPos.y, boundary.first.y, 0.f);
	if (tempPos.y > boundary.second.y)
		Utils::ElasticCollision(tempPos.y, boundary.second.y, 0.f);

	SetPosition(tempPos);



	//ï¿½ï¿½ï¿½ï¿½
	if (hp == 0)
	{
		onDie();
		SOUND_MGR.PlaySfx("sound/splat.wav");
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::onDamage(int damage)
{
	if (damagedTimer >= damagedInterval)
	{
		damagedTimer = 0.f;
		hp = std::max(hp - damage, 0);
		hud->SetHp(hp, maxHp);
		SOUND_MGR.PlaySfx("sound/hit.wav");
	}
}

bool Player::AddExp(int value)
{
	currentExp += value;
	if (currentExp >= maxExp)
	{
		currentExp -= maxExp;
		maxExp *= 1.05; // Àý»èµÇ´Â °Å ÀÏ´Ü ½Å°æ ¾È¾²°Ú½À´Ï´Ù.
		level++;
		return true;
	}
	return false;
}

void Player::AddMaxHp(int value)
{
	maxHp += value;
	hp += value;
	hud->SetHp(hp, maxHp);
}

void Player::onDie()
{
	active = false;
	SOUND_MGR.PlayBGM("sound/SellBuyMusic2.wav");
	dynamic_cast<SceneGame*>(scene)->SetStatus(SceneGame::Status::DIE);
}

void Player::onItem(Item2* item)
{
	SOUND_MGR.PlaySfx("sound/pickup.wav");
	switch (item->GetType())
	{
	case Item2::Types::AMMO:
		gun->AddTotalAmmo(item->GetValue());
		hud->SetAmmo(gun->GetAmmo(), gun->GetTotalAmmo());
		break;
	case Item2::Types::HEALTH:
		hp = std::min(hp+item->GetValue(),maxHp);
		hud->SetHp(hp,maxHp);
		break;
	}
}
