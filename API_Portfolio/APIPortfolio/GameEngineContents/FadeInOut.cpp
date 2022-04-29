#include "FadeInOut.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngine/GameEngineRenderer.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>

FadeInOut::FadeInOut() :
	FadeSpeed_(400.0f),
	IsFadeIn_(false),
	IsFadeOut_(false),
	Value_(0)
{
}

FadeInOut::~FadeInOut() 
{
}

void FadeInOut::Start()
{
	Back = CreateRenderer("TitleBlackAlpha.bmp");
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);
	Back->SetAlpha(0);
}

static float Value = 0;
static float time = 0.0f;
void FadeInOut::Update()
{
	//time += GameEngineTime::GetDeltaTime();

	//Value = GameEngineMath::Lerp(255, 0, time);
	//Back->SetAlpha(Value);



	if (true == IsFadeIn_)
	{
		Value_ += GameEngineTime::GetDeltaTime() * FadeSpeed_;
		Back->SetAlpha(static_cast<int>(Value_));

		if (255 <= Value_)
		{
			IsFadeIn_ = false;
			Value_ = 255;
			Back->SetAlpha(Value_);
		}
	}
	else if (true == IsFadeOut_)
	{
		Value_ -= GameEngineTime::GetDeltaTime() * FadeSpeed_;
		Back->SetAlpha(static_cast<int>(Value_));

		if (0 >= Value_)
		{
			IsFadeOut_ = false;
			Value_ = 0;
			Back->SetAlpha(Value_);
		}
	}
}


void FadeInOut::Render()
{

}


