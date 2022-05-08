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
		Text_ = L"영웅이 등장했다...";
	}
	else if (1 == Count_)
	{
		Text_ = L"* 바람이 울부짖고 있다...";
	}
	else if (2 == Count_)
	{
		Text_ = L"* 영웅을 쓰러뜨렸다";
	}
	else if (3 == Count_)
	{
		Text_ = L"* 불사의 언다인";
	}
	else if (4 == Count_)
	{
		Text_ = L"* 살펴보기";
	}
	else if (5 == Count_)
	{
		Text_ = L"*불사신 언다인 99ATK 99DEF\n*세상을 구하기 위해\n 의지로 되살아 난 영웅.";
	}
	else if (6 == Count_)
	{
		Text_ = L"*도망가기";
	}
	else if (7 == Count_)
	{
		Text_ = L"*도망치려 했으나 실패했다.";
	}
	else if (8 == Count_)
	{
		Text_ = L"*무적포션";
	}
	else if (9 == Count_)
	{
		Text_ = L"*알수없는 힘이 솟아오른다.";
	}
	else if (10 == Count_)
	{
		Text_ = L"*없음";
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
