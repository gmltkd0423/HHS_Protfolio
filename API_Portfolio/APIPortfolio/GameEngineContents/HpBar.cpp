#include "HpBar.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

HpBar::HpBar() :
	PlayerMaxHp_(0),
	PlayerHp_(0),
	HpBarRed_(nullptr),
	HpBarYellow_(nullptr)
{
}

HpBar::~HpBar() 
{
}

void HpBar::Start()
{
	HpBarRed_ = CreateRenderer("Hp_Bar_Red.bmp", (int)BATTLELEVELORDER::ACTOR, RenderPivot::LEFT);
	HpBarYellow_ = CreateRenderer("Hp_Bar_Yellow.bmp", (int)BATTLELEVELORDER::ACTOR,RenderPivot::LEFT);
}

void HpBar::Update()
{
	PlayerMaxHp_ = static_cast<int>(Player::MainPlayer->GetMaxHp());
	PlayerHp_ = static_cast<int>(Player::MainPlayer->GetHp());

	float HpBarYellow_x = HpBarYellow_->GetImageScale().x * PlayerHp_ / PlayerMaxHp_;

	HpBarYellow_->SetScale({HpBarYellow_x ,HpBarYellow_->GetImageScale().y });

}

void HpBar::Render()
{

}
