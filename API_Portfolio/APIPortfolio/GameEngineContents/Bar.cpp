#include "Bar.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineRandom.h>

int Bar::BarCount_ = 0;
int Bar::KeyDownCount_ = 0;
int Bar::Damage_ = 0;

Bar::Bar()	:
	IsKeyDown(false),
	Timer_(0.6f)
{
	MyBarCount_ = BarCount_;
	BarCount_++;
}

Bar::~Bar()
{
}

void Bar::Start()
{
	BarRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	BarRenderer->CreateAnimation("Judg_Bar.bmp", "BarAni", 0, 1, 0.1f, true);
	BarRenderer->CreateAnimation("Judg_Bar.bmp", "Bar_Idle", 0, 0, 0, false);
	BarRenderer->ChangeAnimation("Bar_Idle");
	BarRenderer->SetScale({ 25,200 });

	AttackBar_ColMap = GameEngineImageManager::GetInst()->Find("AttackBar_ColMap.bmp");
	if (nullptr == AttackBar_ColMap)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	if (false == GameEngineInput::GetInst()->IsKey("BarKey_Down"))
	{
		GameEngineInput::GetInst()->CreateKey("BarKey_Down", 'Z');
	}
}



void Bar::Update()
{

	if (false == IsKeyDown)
	{
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 500.0f;
	}
	else
	{
		MoveDir_ = float4::ZERO;
		Timer_ -= GameEngineTime::GetDeltaTime();
		
	}

	if (0 >= Timer_)
	{
		Off();
	}

	SetMove(MoveDir_);
	CheckJudgMent();
}

//bool KeyCheck_ = false;

void Bar::Render()
{
	KeyCheck_ = false;
}


void Bar::CheckJudgMent()
{
	float4 Pos_ = GetPosition();
	int Color = AttackBar_ColMap->GetImagePixel(Pos_);

	//if (false == KeyCheck_ && true == GameEngineInput::GetInst()->IsDown("BarKey_Down"))
	//{
	//	if (KeyDownCount_ == MyBarCount_)
	//	{
	//		KeyCheck_ = true;
	//		KeyDownCount_++;

			if (MyBarCount_ == KeyDownCount_ &&  RGB(255, 255, 255) == Color && true == GameEngineInput::GetInst()->IsDown("BarKey_Down"))
			{
				BarRenderer->ChangeAnimation("BarAni");
				GameEngineRandom Ran;
				int Randomint = Ran.RandomInt(0, 30);
				Damage_ += Randomint;
				KeyDownCount_++;
				MoveDir_ = float4::ZERO;

			}
			else if (MyBarCount_ == KeyDownCount_ && RGB(255, 0, 0) == Color && true == GameEngineInput::GetInst()->IsDown("BarKey_Down"))
			{
				BarRenderer->ChangeAnimation("BarAni");
				GameEngineRandom Ran;
				int Randomint = Ran.RandomInt(30, 60);
				Damage_ += Randomint;
				KeyDownCount_++;
				MoveDir_ = float4::ZERO;
			}
			else if (MyBarCount_ == KeyDownCount_ && RGB(0, 0, 255) == Color && true == GameEngineInput::GetInst()->IsDown("BarKey_Down"))
			{
				BarRenderer->ChangeAnimation("BarAni");
				GameEngineRandom Ran;
				int Randomint = Ran.RandomInt(60, 100);
				Damage_ += Randomint;
				KeyDownCount_++;
				MoveDir_ = float4::ZERO;
			}

	//		return;
	//	}

	//	//b++;
	//}
	//return;

}
