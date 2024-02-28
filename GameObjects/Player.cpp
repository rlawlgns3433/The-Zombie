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
	
	bound.setFillColor(sf::Color::Magenta);
	bound.setRadius(1.f);
	Utils::SetOrigin(bound, Origins::MC);


	scene = SCENE_MGR.GetScene(SceneIds::SceneGame);

	switch (type)
	{
		case TYPES::MAN:
			weapon = new Gun(this); // Type�� ���� �б� �ʿ�
			weapon->Init();
			weapon->Reset();
			break;
		case TYPES::FIREBAT:
			weapon = new Gun(this); // Type�� ���� �б� �ʿ�
			weapon->Init();
			weapon->Reset();
			break;
		case TYPES::READDEATH:
			weapon = new Sword(this); // Type�� ���� �б� �ʿ�
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
	hud->SetExp(currentExp, maxExp);
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
	float lookAngle = Utils::Angle(mouseWorldPos - GetPosition());
	Utils::Rotate(look, lookAngle);

	if (type != TYPES::READDEATH)
	{
		SetRotation(lookAngle);
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


	//����
	if (hp == 0)
	{
		onDie();

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
	currentExp += value * xExp;
	hud->SetExp(currentExp, maxExp);
	if (currentExp >= maxExp)
	{
		currentExp -= maxExp;
		maxExp *= 1.3; // roundDown
		level++;
		LevelUp();
		hud->SetExp(currentExp, maxExp);
		return true;
	}
	return false;
}

void Player::AddStat(DataLevelUp data)
{
	//HP
	maxHp = std::max(1, maxHp + data.maxHp);
	AddHp(data.maxHp);
	hud->SetHp(hp, maxHp);

	speed += data.speed;

	xExp += data.xExp;
	hud->SetExp(currentExp, maxExp);

	weapon->AddDamage(data.damage);
	weapon->AddShotInterval(data.shotInterval);
	weapon->AddReloadSpeed(data.reloadInterval);
	weapon->AddMaxAmmo(data.maxAmmo);
	weapon->AddLevel(data.weaponUp);
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

void Player::onDie()
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
