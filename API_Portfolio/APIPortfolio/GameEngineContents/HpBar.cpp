#include "HpBar.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

HpBar::HpBar() :
	PlayerMaxHp_(0),
	PlayerHp_(0)
{
}

HpBar::~HpBar() 
{
}

void HpBar::Start()
{
	HpBarRed_ = CreateRenderer("Hp_Bar_Red.bmp", (int)BATTLELEVELORDER::ACTOR);
	HpBarYellow_ = CreateRenderer("Hp_Bar_Yellow.bmp", (int)BATTLELEVELORDER::ACTOR);
	FullHpBar_ = HpBarYellow_->GetScale().x;
}

void HpBar::Update()
{
	PlayerMaxHp_ = Player::MainPlayer->GetMaxHp();
	PlayerHp_ = Player::MainPlayer->GetHp();

	int HpBarYellow_x = HpBarYellow_->GetImageScale().x * PlayerHp_ / PlayerMaxHp_;
	float HpBarXPivot = (FullHpBar_ - HpBarYellow_x) / 2;
	HpBarYellow_->SetScale({ static_cast<float>(HpBarYellow_x),HpBarYellow_->GetImageScale().y });

	if (HpBarYellow_->GetScale().x < PlayerMaxHp_)
	{
		HpBarYellow_->SetPivot({ -HpBarXPivot ,0 });
	}
}

void HpBar::Render()
{
}
