#include "Undyne.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTime.h>
#include "ContentsEnums.h"
#include <math.h>

Undyne::Undyne() :
	IsHurt(false),
	IsIdle(false),
	IsShake(false),
	Time_(0.2f),
	Timer_(1.0f)
{
}

Undyne::~Undyne()
{
}

void Undyne::Start()
{
	UndyneRenderer = CreateRenderer((int)BATTLELEVELORDER::BACKGROUND);
	UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle", 0, 67, 0.04f, true);
	UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle_Stop", 0, 0, 0, false);
	UndyneRenderer->CreateAnimation("Undyne_Hurt.bmp", "Hurt", 0, 0, 0, false);
	UndyneRenderer->ChangeAnimation("Idle");
	UndyneRenderer->SetScale({ 550,380 });
}

void Undyne::Update()
{
	Shake();
}

void Undyne::Render()
{
}

void Undyne::Hurt()
{

	IsHurt = true;

}

void Undyne::Idle()
{

	UndyneRenderer->ChangeAnimation("Idle");
	IsIdle = true;

}

void Undyne::Shake()
{
	if (true == IsHurt)
	{

		UndyneRenderer->ChangeAnimation("Hurt");
		if (false == IsShake)
		{
			Pos_ = GetPosition();
			RightPos_.x = GetPosition().x + 100.0f;
			MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;
		}

		IsShake = true;
		if (0.0f <= Timer_)
		{
			GameEngineRandom Ran;
			float Randomfloat = Ran.RandomInt(1.0f, 4.0f);
			Timer_ -= GameEngineTime::GetDeltaTime();
			Time_ -= GameEngineTime::GetDeltaTime();

			if (GetPosition().x <= RightPos_.x)
			{
				
				//MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;
				MoveDir_.Normal2D();
				SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 1000.0f);
			}
			//SetPosition( {GetPosition().x + Randomfloat,GetPosition().y});
			
		
	
			//	SetPosition({ GetPosition().x - Randomfloat,GetPosition().y });
\

			if (0.0f >= Timer_)
			{
				Timer_ = 1.0f;
				Time_ = 0.0f;
				SetPosition(Pos_);
				IsShake = false;
				IsHurt = false;
				UndyneRenderer->ChangeAnimation("Idle");
			}
		}
		//IsHurt = false;
	}
}
