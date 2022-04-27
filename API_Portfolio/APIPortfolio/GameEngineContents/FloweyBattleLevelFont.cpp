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


	//��ȭ�� ��� ��µǸ�
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
	}
}

void FloweyBattleLevelFont::Texts()
{
	if (1 == Count_)
	{
		Text_ = L"��Ʈ ����� ������? \n���� �� ��ȥ�̾�. \n�� ������ ������!";
	}
	else if (2 == Count_)
	{
		Text_ = L"�� ��ȥ�� ��������,  \nLV�� ���� �ø���  \n������ �� �־�.";
	}
	else if (3 == Count_)
	{
		Text_ = L"LV�� ���İ�?  \n�ٷ�, LOVE��, ����!";
	}
	else if (4 == Count_)
	{
		Text_ = L"LOVE�� �� �ʿ��� ��\n������, �׷���?";
	}
	else if (5 == Count_)
	{
		Text_ = L"����������,\n���� �� �����ٰ�!";
	}
	else
	{
		Text_ = L"";
	}
}
