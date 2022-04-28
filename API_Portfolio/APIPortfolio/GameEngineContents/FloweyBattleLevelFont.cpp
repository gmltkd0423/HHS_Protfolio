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

	if (24 == Count_)
	{
		TextFont_.Draw(RealText_, { 780.0f, 180.0f }, RGB(0, 0, 0), 120, 120);
	}
	else
	{
		TextFont_.Draw(RealText_, { 760.0f, 170.0f }, RGB(0, 0, 0), 35, 35);
	}

	//대화가 모두 출력되면
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
	}
}

void FloweyBattleLevelFont::Texts()
{
	if (0 == Count_)
	{
		Text_ = L"하트 모양이 보이지? \n저게 네 영혼이야. \n네 존재의 정수지!";
	}
	else if (1 == Count_)
	{
		Text_ = L"네 영혼은 약하지만,  \nLV를 많이 올리면  \n강해질 수 있어.";
	}
	else if (2 == Count_)
	{
		Text_ = L"LV가 뭐냐고?  \n바로, LOVE지, 물론!";
	}
	else if (3 == Count_)
	{
		Text_ = L"LOVE가 좀 필요한 것\n같은데, 그렇지?";
	}
	else if (4 == Count_)
	{
		Text_ = L"걱정하지마,\n내가 좀 나눠줄게!";
	}
	else if(10 == Count_)
	{
		Text_ = L"여기 지하세계에선,\nLOVE를...";
	}
	else if (11 == Count_)
	{
		Text_ = L"작고 하얀...\n'친절 알갱이' 로\n서로 나누지.";
	}
	else if (12 == Count_)
	{
		Text_ = L"준비됐어?";
	}
	else if (13 == Count_)
	{
		Text_ = L"움직여!\n친절을 최대한\n많이 받는거야!";
	}
	else if (14 == Count_)
	{
		Text_ = L"이봐 친구,\n놓쳐버렸잖아.";
	}
	else if (15 == Count_)
	{
		Text_ = L"다시 해보자고,\n알았지?";
	}
	else if (18 == Count_)
	{
		Text_ = L"장난치는거야?\n너 무뇌아니?\n달려. 가라고. 저.\n총알로!!!";
	}
	else if (19 == Count_)
	{
		Text_ = L"장난치는거야?\n너 무뇌아니?\n달려. 가라고. 저.\n친절로!!!";
	}
	else if (22 == Count_)
	{
		Text_ = L"눈치채고 있었던\n거지,\n응?";
	}
	else if (23 == Count_)
	{
		Text_ = L"그저 날 괴롭히고\n싶었을 뿐이었어.";
	}
	else if (24 == Count_)
	{
		Text_ = L"죽 어.";
	}
	else
	{
		Text_ = L"";
	}
}
