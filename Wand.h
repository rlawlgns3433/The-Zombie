#pragma once
#include "Weapon.h"

class Player;

class Wand : public Weapon
{
private:
	std::vector<InputMgr::SFGM_COMBO*> comboList;

	void Combo();
	void Reload();

protected:
	float playerSpeed;
	float comboTimer = 0.f;
	float comboTimeLimit = 3.f;
	bool isChanneling = false;
	int comboSelected = 0;
	float perfectTimer = 0.f;

public:
	Wand(Player* player, const std::string& name = "");
	~Wand() override = default;
	Wand(const Wand&) = delete;
	Wand(Wand&&) = delete;
	Wand& operator=(const Wand&) = delete;
	Wand& operator=(Wand&&) = delete;

	void Release() override;
	void Update(float dt) override;
	void Attack() override;

	void MagicChanneling();
	void MagicAttack();
	void MagicExcellent();
	void MagicPerfect();
	void MagicCancle();

};

