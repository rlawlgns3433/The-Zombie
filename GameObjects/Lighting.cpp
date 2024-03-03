#include "pch.h"
#include "Lighting.h"
#include "SceneGame.h"

Lighting::Lighting(Scene* sc, const std::string& name)
	:Projectile(name)
{
	scene = sc;
	sortLayer = 1;

}

Lighting::~Lighting()
{
	Release();
}

void Lighting::Init()
{
	lines = sf::VertexArray(sf::TriangleStrip, 2);
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	SetPosition(mouseWorldPos);
	firstPos = mouseWorldPos;
	circle.setTexture(RES_MGR_TEXTURE.Get("graphics/lightningCircle.png"));
	Utils::SetOrigin(circle, Origins::MC);
	circle.setPosition(firstPos);
	circle.setColor({ 255, 255, 255, 255 });
	circle.setScale(0.15f, 0.15f);
}

void Lighting::Reset()
{
	zombies.clear();
	sortedZombies.clear();
	isHit = false;
	isDischarge = false;
	hitCount = 0;
	lines.resize(2);
}

void Lighting::Update(float dt)
{
	Projectile::Update(dt);

	if (isHit && !isDischarge)
	{
		Discharge();
	}

	timer -= dt;
	damageTimer += dt;

	//번개가 번쩍번쩍쓰
	for (int i = 0; i < lines.getVertexCount(); i++)
	{
		lines[i].color.a = timer * 254 + i * 50;
	}

	//0.2초마다 초기화 : 총 5번 감전
	if (damageTimer >= damageInterval)
	{
		damageTimer = 0.f;
		Reset();
		circle.setScale(Utils::RandomRange(0.1f, 0.2f) * (rand() % 2 - 0.5f) * 2
			, Utils::RandomRange(0.1f, 0.2f) * (rand() % 2 - 0.5f) * 2);
		circle.setRotation(Utils::RandomRange(0.f, 360.f));
	}

	//삭제
	if (timer <= 0.f)
	{
		scene->DeleteGo(this);
	}
}

void Lighting::FixedUpdate(float dt)
{
	Projectile::FixedUpdate(dt);
}

void Lighting::Draw(sf::RenderWindow& window)
{
	window.draw(lines, &(RES_MGR_TEXTURE.Get("graphics/lightning.png")));
	window.draw(circle);
}

bool Lighting::CheckCollision(SpriteGo* zombie)
{
	if (Utils::Distance(zombie->GetPosition(), firstPos) <= 500.f)
	{
		zombies.push_back(zombie);
		DamageDecrease();
		return true;
	}
}
void Lighting::Create(Scene* sc)
{
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(sc);
	Player* player = sceneGame->GetPlayer();
	int count = player->GetWeapon()->GetProjectileCount();

	Lighting* light = new Lighting(sc);

	light->Init();
	light->Reset();
	light->damage = player->GetWeapon()->GetDamage() * 2;
	light->damageDecrease += player->GetWeapon()->GetLevel() * 0.05f;
	light->timer += player->GetWeapon()->GetLevel() * 0.21f;
	light->maxHit += (player->GetWeapon()->GetProjectileCount() - 1) * 2;
	sceneGame->AddGo(light);
	sceneGame->bullets.push_back(light);
}

void Lighting::Hit()
{
	if (++hitCount == maxHit)
	{
		isHit = true;
	}
}

void Lighting::EndOfCheckZombie()
{
	isHit = true;
}

void Lighting::Discharge()
{
	SOUND_MGR.PlaySfx("sound/magic/lightningDOT.wav");
	isDischarge = true;
	SortAndSetPosition();

	if (!sortedZombies.empty())
	{
		sf::Vector2f zombiePos = sortedZombies[0]->GetPosition();
		sf::Vector2f nextDirec = sortedZombies[0]->GetPosition() - firstPos;
		auto point = Utils::DressInRow(firstPos, nextDirec, 2, 24.f);

		lines[0].position = point.front();
		lines[1].position = point.back();
	}
	for (int i = 0, count = 0; i < lines.getVertexCount(); i++)
	{
		if (i % 2 == 0)
		{
			count++;
		}
		lines[i].texCoords = { 300.f / 5 * (count - 1) , (i % 2) * 24.f };
	}
}

void Lighting::SortAndSetPosition()
{
	if (zombies.empty())
	{
		return;
	}

	//현재 위치에서 가장 가까운 좀비를 탐색
	float minDistance = -1.f;
	SpriteGo* minZombie = nullptr;
	for (auto ptr : zombies)
	{
		sf::Vector2f zombiePos = ptr->GetPosition();
		float distance = Utils::Distance(zombiePos, position);
		if (minDistance == -1.f)
		{
			minDistance = distance;
		}
		else
		{
			minDistance = std::min(distance, minDistance);
		}

		if (distance == minDistance)
		{
			minZombie = ptr;
		}
	}
	//가장 가까운 위치로 현재 위치를 변경, 선택된 좀비를 다른 리스트로 옮긴다.
	sf::Vector2f newPos = minZombie->GetPosition(); //좀비가 없으면 이 함수도 실행되지 않기 때문에 괜찮다.
	auto lightPos = Utils::DressInRow(newPos, newPos - position, 2, 24.f);
	position = newPos;
	zombies.remove(minZombie);
	sortedZombies.push_back(minZombie);

	sf::Vertex light1(lightPos.front());
	sf::Vertex light2(lightPos.back());
	lines.append(light1);
	lines.append(light2);

	//좀비를 전부 정렬할때까지 반복. O(n!)의 시간복잡도, 현재 n=5.
	SortAndSetPosition();
}

void Lighting::DamageDecrease()
{
	if (damage > 10)
	{
		damage = damage * damageDecrease;
		if (damage < 10)
		{
			damage = 10;
		}
	}
}
