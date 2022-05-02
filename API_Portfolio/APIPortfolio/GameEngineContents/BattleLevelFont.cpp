#include "BattleLevelFont.h"

BattleLevelFont::BattleLevelFont() :
	TextTime_(0.1f),
	Timer_(0),
	Count_(0),
	IsAllTextOut(false),
	TextCount_(0)
{
}

BattleLevelFont::~BattleLevelFont()
{
}

void BattleLevelFont::Start()
{
	Count_ = 0;
	TextCount_ = 0;
	Timer_ = 0;
	IsAllTextOut = false;
}

void BattleLevelFont::Update()
{
}

void BattleLevelFont::Render()
{


	Texts();

	if (Text_.size() == 0)
	{
		return;
	}

	TextTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= TextTime_)
	{
		TextCount_++;
		TextTime_ = 0.1f;
	}

	RealText_ = Text_.substr(0, TextCount_);


	if (Text_.size() != RealText_.size())
	{
		TextSounds();
	}

	TextFont_.Draw(RealText_, { 760.0f, 170.0f }, RGB(0, 0, 0), 35, 35);

	//대화가 모두 출력되면
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
		Timer_ = 0;
	}
}

void BattleLevelFont::Texts()
{
	if (0 == Count_)
	{
		Text_ = L"하트 모양이 보이지? \n저게 네 영혼이야. \n네 존재의 정수지!";
	}
	
	else
	{
		Text_ = L"";
	}
}

void BattleLevelFont::TextSounds()
{
	//TextTime_ -= GameEngineTime::GetDeltaTime();
	//Timer_ += GameEngineTime::GetDeltaTime();

	//if (0 == Count_)
	//{
	//	if (0 >= TextTime_)
	//	{
	//		if (Timer_ <= 0.7f || Timer_ >= 1.4f)
	//		{
	//			TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
	//			TextTime_ = 0.1f;
	//		}
	//	}
	//}
	
}
