#include "FadeInOut.h"
#include "ContentsEnums.h"
#include "GameEngine/GameEngineRenderer.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>

FadeInOut::FadeInOut() :
	FadeSpeed_(100.0f),
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
	Back = CreateRenderer("TitleBlack.bmp");
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);
	Back->SetAlpha(0);
}


void FadeInOut::Update()
{
	if (true == IsFadeIn_)
	{
		Value_ += static_cast<int>(GameEngineTime::GetDeltaTime() * FadeSpeed_);
		Back->SetAlpha(Value_);

		if (255 <= Value_)
		{
			IsFadeIn_ = false;
		}
	}

	if (true == IsFadeOut_)
	{
		Value_ -= static_cast<int>(GameEngineTime::GetDeltaTime() * FadeSpeed_);
		Back->SetAlpha(Value_);

		if (0 >= Value_)
		{
			IsFadeOut_ = false;
		}
	}
}

void FadeInOut::Render()
{

}


