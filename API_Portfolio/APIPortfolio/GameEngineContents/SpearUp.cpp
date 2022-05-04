#include "SpearUp.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include<GameEngineBase/GameEngineTime.h>

SpearUp::SpearUp()	:
	Value(255)
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
	SpearSound.SoundPlayOneShot("snd_arrow.wav");
}

void SpearUp::Update()
{
	if (490 >= GetPosition().y)
	{
		MoveDir_ = float4::ZERO;
		Value -= GameEngineTime::GetDeltaTime();
		SpearRenderer->SetAlpha(Value);
		SpearRenderer->SetTransColor(RGB(0, 0, 0));

		if (0 >= Value)
		{
			Death();
		}
	}
	else
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 150.0f;
		SetMove(MoveDir_);
	}
}

void SpearUp::Render()
{
}
