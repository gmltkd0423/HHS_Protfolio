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
	Time_(0.0f),
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
	UndyneRenderer->ChangeAnimation("Hurt");
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
		if (false == IsShake)
		{
			Pos_ = GetPosition();
		}

		IsShake = true;
		if (0.0f <= Timer_)
		{
			Timer_ -= GameEngineTime::GetDeltaTime();
			Time_ += GameEngineTime::GetDeltaTime();
			if (0.2f <= Time_)
			{
				Time_ = 0.0f;
				GameEngineRandom Ran;
				float Randomfloat = Ran.RandomInt(1.0f, 5.0f);
				//float x  = sin(Randomfloat * 10.0f)* powf(0.5f, Randomfloat);
				SetPosition( {GetPosition().x + 3,GetPosition().y});
			}
			else if (0.1f <= Time_)
			{
				GameEngineRandom Ran;
				float Randomfloat = Ran.RandomInt(1.0f, 5.0f);
				//float x = sin(Randomfloat * 10.0f) * powf(0.5f, Randomfloat);
				SetPosition({ GetPosition().x - 3,GetPosition().y });
			}

			if (0.0f >= Timer_)
			{
				Timer_ = 0.0f;
				Time_ = 0.0f;
				SetPosition(Pos_);
				IsShake = false;
			}
		}
	}
}
