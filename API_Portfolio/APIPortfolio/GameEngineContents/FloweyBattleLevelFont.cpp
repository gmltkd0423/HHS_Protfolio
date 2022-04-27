#include "FloweyBattleLevelFont.h"

FloweyBattleLevelFont::FloweyBattleLevelFont() :
	Time_(0.1f),
	Timer_(0),
	Count_(0),
	IsAllTextOut(false),
	TextCount_(0)
{
}

FloweyBattleLevelFont::~FloweyBattleLevelFont() 
{
}

void FloweyBattleLevelFont::Start()
{
	Count_ = 0;
	TextCount_ = 0;
	Timer_ = 0;
	IsAllTextOut = false;
}

void FloweyBattleLevelFont::Update()
{
}

void FloweyBattleLevelFont::Render()
{
	
	
	Texts();

	if (Text_.size() == 0)
	{
		return;
	}

	Time_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Time_)
	{
		TextCount_++;
		Time_ = 0.1f;
	}

	RealText_ = Text_.substr(0, TextCount_);

	TextFont_.Draw(RealText_, {760.0f, 170.0f }, RGB(0, 0, 0), 35, 35);


	//대화가 모두 출력되면
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
	}
}

void FloweyBattleLevelFont::Texts()
{
	if (1 == Count_)
	{
		Text_ = L"하트 모양이 보이지? \n저게 네 영혼이야. \n네 존재의 정수지!";
	}
	else if (2 == Count_)
	{
		Text_ = L"네 영혼은 약하지만,  \nLV를 많이 올리면  \n강해질 수 있어.";
	}
	else if (3 == Count_)
	{
		Text_ = L"LV가 뭐냐고?  \n바로, LOVE지, 물론!";
	}
	else if (4 == Count_)
	{
		Text_ = L"LOVE가 좀 필요한 것\n같은데, 그렇지?";
	}
	else if (5 == Count_)
	{
		Text_ = L"걱정하지마,\n내가 좀 나눠줄게!";
	}
	else
	{
		Text_ = L"";
	}
}
