#include "SpearArrow.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include "SoundPlayer.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineCollision.h>

SpearArrow::SpearArrow() :
	Timer_(1.0f),
	LookPlayer(false)
{

}

SpearArrow::~SpearArrow() 
{

}

void SpearArrow::Start()
{
	SpearRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	SpearRenderer->SetImage("Spear2.bmp");
	SpearRenderer->SetIndex(0);
	SpearRenderer->SetRotationFilter("Spear4.bmp");
	Angle = 0.0f;
	SpearRenderer->SetTransColor(RGB(0, 0, 0));
	SpearCol = CreateCollision("Arrow", { 35,90 });
}

void SpearArrow::Update()
{
	Angle += 360.0f * GameEngineTime::GetDeltaTime();
	Timer_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Timer_)
	{
		if(false == LookPlayer)
		{
			SpearSound.SoundPlayOneShot("snd_arrow.wav");
			float Degree = float4::VectorXYtoDegree(GetPosition(), Player::MainPlayer->GetPosition());
			SpearRenderer->SetRotationZ(Degree + 180.0f);
			MoveDir_ = (Player::MainPlayer->GetPosition() - GetPosition()) * GameEngineTime::GetDeltaTime() * 1.5f;
			LookPlayer = true;
		}
	
		SetMove(MoveDir_);
	}
	else
	{

		SpearRenderer->SetRotationZ(Angle);
	}
}

void SpearArrow::Render()
{
}
