#include "UIButton.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Trigger.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

UIButton::UIButton()	:
	ButtonSize({165,63}),
	bFightButton(false),
	bActionButton(false),
	bMercyButton(false),
	bItemButton(false),
	Time_(0.2f),
	Timer_(1.0f),
	IsShake(false),
	SetPos(false)
{
}

UIButton::~UIButton()
{
}

void UIButton::Start()
{
	//FightButton
	{
		FightButton = CreateRenderer((int)BATTLELEVELORDER::BOX);
		FightButton->SetImage("FightButton2.bmp");
		FightButton->SetIndex(0);
		FightButtonCollision = CreateCollision("Fight_Col", { ButtonSize });
	}

	//ActionButton
	{
		ActionButton = CreateRenderer((int)BATTLELEVELORDER::BOX);
		ActionButton->SetImage("ActionButton.bmp");
		ActionButton->SetIndex(0);
		ActionButton->SetPivot({ ButtonSize.x + 100,0 });
		ActionButtonCollision = CreateCollision("Action_Col", { ButtonSize });
		ActionButtonCollision->SetPivot({ ActionButton->GetPivot() });
	}

	//MercyButton
	{
		MercyButton = CreateRenderer((int)BATTLELEVELORDER::BOX);
		MercyButton->SetImage("MercyButton.bmp");
		MercyButton->SetIndex(0);
		MercyButton->SetPivot({ ButtonSize.x*2 + 200,0 });
		MercyButtonCollision = CreateCollision("Mercy_Col", { ButtonSize });
		MercyButtonCollision->SetPivot({ MercyButton->GetPivot() });
	}

	//ItemButton
	{
		ItemButton = CreateRenderer((int)BATTLELEVELORDER::BOX);
		ItemButton->SetImage("ItemButton.bmp");
		ItemButton->SetIndex(0);
		ItemButton->SetPivot({ ButtonSize.x*3 + 300,0 });
		ItemButtonCollision = CreateCollision("Item_Col", { ButtonSize });
		ItemButtonCollision->SetPivot({ ItemButton->GetPivot() });
	}
}

void UIButton::Update()
{
	CheckCollision();
	Shake();
}

void UIButton::Render()
{
}

void UIButton::CheckCollision()
{
	//fightbutton
	if (true == FightButtonCollision->CollisionCheck("Player"))
	{
		FightButton->SetIndex(1);
		bFightButton = true;
	}
	else
	{
		FightButton->SetIndex(0);
		bFightButton = false;
	}


	//actionbutton
	if (true == ActionButtonCollision->CollisionCheck("Player"))
	{
		ActionButton->SetIndex(1);
		bActionButton = true;
	}
	else
	{
		ActionButton->SetIndex(0);
		bActionButton = false;
	}


	//mercybutton
	if (true == MercyButtonCollision->CollisionCheck("Player"))
	{
		MercyButton->SetIndex(1);
		bMercyButton = true;
	}
	else
	{
		MercyButton->SetIndex(0);
		bMercyButton = false;
	}


	//itembutton
	if (true == ItemButtonCollision->CollisionCheck("Player"))
	{
		ItemButton->SetIndex(1);
		bItemButton = true;
	}
	else
	{
		ItemButton->SetIndex(0);
		bItemButton = false;
	}
}

void UIButton::Shake()
{
	if (true == IsShake)
	{
		if (false == SetPos)
		{
			float4 RanPos_ = { 3.0f,3.0f };


			Pos_ = GetPosition();
			RightDownPos_ = GetPosition() + RanPos_;
			LeftTopPos_ = GetPosition() - RanPos_;

		}

		SetPos = true;

		if (0.0f <= Timer_)
		{
			Timer_ -= GameEngineTime::GetDeltaTime();
			Time_ += GameEngineTime::GetDeltaTime();

			if (0.0f <= Time_ && false == IsRightDown)
			{
				MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.0f;
				MoveDir2_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 100.0f;
				SetMove(MoveDir_);
				SetMove(MoveDir2_);

				if (GetPosition().x >= RightDownPos_.x && GetPosition().y >= RightDownPos_.y)
				{
					IsRightDown = true;
					RightDownPos_.x -= 1.0f;
					RightDownPos_.y -= 1.0f;
					//MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;

					IsLeftTop = false;
				}
			}
			else if (0.1f <= Time_ && false == IsLeftTop)
			{
				MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 100.0f;
				MoveDir2_ = float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
				SetMove(MoveDir_);
				SetMove(MoveDir2_);
				if (GetPosition().x <= LeftTopPos_.x && GetPosition().y <= LeftTopPos_.y)
				{
					IsLeftTop = true;
					IsRightDown = false;
					LeftTopPos_.x += 1.0f;
					LeftTopPos_.y += 1.0f;
					Time_ = 0.0f;
				}


			}

			if (0.0f >= Timer_)
			{
				Timer_ = 1.0f;
				SetPosition(Pos_);
				IsShake = false;
				SetPos = false;
			}
		}
	}
}