#include "HpBar.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "Undyne.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

HpBar::HpBar() :
	MaxHp_(0),
	Hp_(0),
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

		MaxHp_ = ActorMaxHp;
		Hp_ = ActorHp;

		float HpBarYellow_x = HpBarYellow_->GetImageScale().x * Hp_ / MaxHp_;

		HpBarYellow_->SetScale({ HpBarYellow_x ,HpBarYellow_->GetImageScale().y });
}

void HpBar::Render()
{

}

