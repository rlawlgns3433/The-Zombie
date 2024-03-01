#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "Item.h"
#include "UIHUD.h"
#include "Crosshair.h"
#include "Gun.h"
#include "PlayerTable.h"
#include "LevelUpTable.h"
#include "FlameThrower.h"
#include "Weapon.h"
#include "Sword.h"


Player::Player(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/player.png";
	sortLayer = 5;
}

void Player::Init()
{
	const DATA_PLAYER& data = DT_PLAYER->Get(type);

	textureId = data.textureId;
	hp = maxHp = data.maxHp;
	speed = data.speed;

	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

	bound.setFillColor(sf::Color::Cyan);
	bound.setRadius(GetGlobalBounds().width/3);
	Utils::SetOrigin(bound, Origins::MC);


	scene = SCENE_MGR.GetScene(SceneIds::SceneGame);

	switch (type)
	{
	case TYPES::MAN:
		weapon = new Gun(this); // Type 맨
		weapon->Init();
		weapon->Reset();
		break;
	case TYPES::FIREBAT:
		weapon = new FlameThrower(this); // Type 파이어벳
		weapon->Init();
		weapon->Reset();
		break;
	case TYPES::READDEATH:
		weapon = new Sword(this); // Type 검사
		weapon->Init();
		weapon->Reset();
		break;
	}
}

void Player::Release()
{
	SpriteGo::Release();
	weapon->Release();
	delete weapon;
}

void Player::Reset()
{
	SpriteGo::Reset();
	weapon->Reset();
	active = true;

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
	hud = dynamic_cast<UIHUD*>(SCENE_MGR.GetCurrentScene()->FindGo("UIHUD"));

	hud->SetHp(hp, maxHp);
	hud->SetExp(currentExp, maxExp, level);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	weapon->Update(dt);

	damagedTimer += dt;

	//ĳ���� ȸ��	
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//sf::Vector2f mouseWorldPos = InputMgr::GetMousePos() + SCENE_MGR.GetCurrentScene()->GetViewCenter() - sf::Vector2f(FRAMEWORK.GetWindow().getSize()) * 0.5f;
	look = Utils::GetNormalize(mouseWorldPos - GetPosition());

	if (type != TYPES::READDEATH)
	{
		SetRotation(Utils::Angle(look));
	}

	//ĳ���� �̵�
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2f tempPos(GetPosition() + direction * speed * dt);

	//�浹 �˻�
	boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	// 
	//�浹 �˻�: ��
	if (tempPos.x < boundary.first.x)
		Utils::ElasticCollision(tempPos.x, boundary.first.x, 0.f);
	if (tempPos.x > boundary.second.x)
		Utils::ElasticCollision(tempPos.x, boundary.second.x, 0.f);
	if (tempPos.y < boundary.first.y)
		Utils::ElasticCollision(tempPos.y, boundary.first.y, 0.f);
	if (tempPos.y > boundary.second.y)
		Utils::ElasticCollision(tempPos.y, boundary.second.y, 0.f);

	SetPosition(tempPos);


	//Die
	if (hp == 0)
	{
		OnDie();
	}
	//LevelUp
	if (currentExp >= maxExp)
	{
		currentExp -= maxExp;
		maxExp *= 1.2; // roundDown
		level++;
		LevelUp();
		hud->SetExp(currentExp, maxExp, level);
	}

}

void Player::DebugUpdate(float dt)
{
	bound.setPosition(position);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	weapon->Draw(window);
}

void Player::DebugDraw(sf::RenderWindow& window)
{
	window.draw(bound);
}

void Player::OnDamage(int damage)
{
	if (damagedTimer >= damagedInterval)
	{
		damagedTimer = 0.f;
		if (!invincibility) { hp = std::max(hp - damage, 0); }
		hud->SetHp(hp, maxHp);
		SOUND_MGR.PlaySfx("sound/hit.wav");
	}
}

void Player::RangeOnDamage(int damage)
{
	hp = std::max(hp - damage, 0);
	hud->SetHp(hp, maxHp);
	SOUND_MGR.PlaySfx("sound/hit.wav");
}

void Player::AddExp(int value)
{
	currentExp += value * xExp;
	hud->SetExp(currentExp, maxExp, level);
}

void Player::AddStat(DataLevelUp data)
{
	//HP
	maxHp = std::max(1, maxHp + data.maxHp);
	AddHp(data.maxHp);
	hud->SetHp(hp, maxHp);

	speed = std::max(0.f, speed + data.speed);

	xExp += data.xExp;

	weapon->AddDamage(data.damage);
	weapon->AddShotInterval(data.shotInterval);
	weapon->AddReloadSpeed(data.reloadInterval);
	weapon->AddMaxAmmo(data.maxAmmo);
	weapon->AddLevel(data.weaponUp);
	weapon->AddProjectile(data.projectile);
}

void Player::AddHp(int value)
{
	hp = std::min(hp + value, maxHp);
	hud->SetHp(hp, maxHp);
}

void Player::LevelUp()
{
	dynamic_cast<SceneGame*>(scene)->SetStatus(SceneGame::Status::LEVELUP);
}

void Player::SetPlayerType(Player::TYPES type)
{
	this->type = type;

	Init();
}

void Player::OnDie()
{
	active = false;
	SOUND_MGR.PlaySfx("sound/splat.wav");
	SOUND_MGR.PlayBGM("sound/SellBuyMusic2.wav");
	dynamic_cast<SceneGame*>(scene)->SetStatus(SceneGame::Status::DIE);
}

void Player::onItem(Item* item)
{
	SOUND_MGR.PlaySfx("sound/pickup.wav");
	switch (item->GetType())
	{
	case Item::Types::AMMO:
		weapon->AddTotalAmmo(item->GetValue());
		break;
	case Item::Types::HEALTH:
		AddHp(item->GetValue());
		break;
	case Item::Types::EXP:
		AddExp(item->GetValue());
		break;
	}
}
