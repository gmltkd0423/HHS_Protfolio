#include "SpearUp.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include<GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>

SpearUp::SpearUp()	:
	Value(255),
	Timer_(0.7f),
	IsUp(false),
	IsSound(false)
{
}

SpearUp::~SpearUp()
{
}

void SpearUp::Start()
{
	SpearRenderer = CreateRenderer((int)BATTLELEVELORDER::UPARROW);
	SpearRenderer->SetImage("Spear_Up.bmp");
	SpearRenderer->SetTransColor(RGB(0, 0, 0));
	SpearUpCol = CreateCollision("Arrow", { 35,100 });
}

void SpearUp::Update()
{
	if (490 >= GetPosition().y)
	{
		if (true == IsUp)
		{
			IsUp = false;
		}
		SpearUpCol->Death();
		MoveDir_ = float4::ZERO;
		Value -= GameEngineTime::GetDeltaTime()*4;
		SpearRenderer->SetAlpha(Value);
		SpearRenderer->SetTransColor(RGB(0, 0, 0));

		if (0 >= Value)
		{
			Death();
		}
	}
	else
	{
		if (550 >= GetPosition().y)
		{

			MoveDir_ = float4::ZERO;
			Timer_ -= GameEngineTime::GetDeltaTime();
			if (0 >= Timer_)
			{
				if (IsSound == false)
				{
					SpearSound.SoundPlayOneShot("snd_arrow.wav");
					IsSound = true;
				}

				MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 150.0f;
				SetMove(MoveDir_);
				IsUp = true;
			}
		}
		else
		{
			MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 150.0f;
			SetMove(MoveDir_);
		}
	}
}

void SpearUp::Render()
{
}
