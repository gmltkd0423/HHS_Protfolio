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


	//if (Text_.size() != RealText_.size())
	//{
	//	TextSounds();
	//}

	TextFont_.Draw(RealText_, { 200.0f, 400.0f }, RGB(255, 255, 255), 55, 55);

	//��ȭ�� ��� ��µǸ�
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
		Text_ = L"������ �����ߴ�...";
	}
	else if (1 == Count_)
	{
		Text_ = L"* �ٶ��� ���¢�� �ִ�...";
	}
	else if (2 == Count_)
	{
		Text_ = L"* ������ �����߷ȴ�";
	}
	else if (3 == Count_)
	{
		Text_ = L"* �һ��� �����";
	}
	else if (4 == Count_)
	{
		Text_ = L"* ���캸��";
	}
	else if (5 == Count_)
	{
		Text_ = L"*�һ�� ����� 99ATK 99DEF\n*������ ���ϱ� ����\n ������ �ǻ�� �� ����.";
	}
	else if (6 == Count_)
	{
		Text_ = L"*��������";
	}
	else if (7 == Count_)
	{
		Text_ = L"*����ġ�� ������ �����ߴ�.";
	}
	else if (8 == Count_)
	{
		Text_ = L"*��������";
	}
	else if (9 == Count_)
	{
		Text_ = L"*�˼����� ���� �ھƿ�����.";
	}
	else if (10 == Count_)
	{
		Text_ = L"*����";
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
