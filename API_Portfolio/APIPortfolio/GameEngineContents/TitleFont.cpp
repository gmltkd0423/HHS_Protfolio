#include "TitleFont.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>




TitleFont::TitleFont() :
	Time_(0.1f),
	Timer_(0),
	Count_(0),
	TextCount_(0),
	SoundTime_(0.15f)

{
}

TitleFont::~TitleFont() 
{
}

void TitleFont::Start()
{
	Count_ = 0;
	TextCount_ = 0;
	Timer_ = 0;
}

void TitleFont::Update()
{

}

void TitleFont::Render()
{
	Timer_ += GameEngineTime::GetDeltaTime();

	if (6.0f <= Timer_)
	{
		Timer_ = 0;
		Count_++;
		TextCount_ = 0;
	}

	Texts();

	Time_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Time_)
	{
		TextCount_++;
		Time_ = 0.1f;
	}
	SoundTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= SoundTime_)
	{
		SoundTime_ = 0.15f;
		if (Text_.size() != RealText_.size())
		{
			TextSound_.SoundPlayOneShot("SND_TXT2.wav");
		}
	}
	RealText_ = Text_.substr(0, TextCount_);



	if (5 == Count_)
	{
		TextFont_.Draw(RealText_, { 550.0f, 470.0f }, RGB(255, 255, 255), 80, 70);
	}
	else
	{
		TextFont_.Draw(RealText_, { 230.0f, 470.0f }, RGB(255, 255, 255), 80, 70);
	}

}

void TitleFont::Texts()
{
	if (0 == Count_)
	{
		Text_ = L"����  ��,  �ΰ���  ����,\n��  ������  ������  ��ġ�ߴ�.";
	}
	else if (1 == Count_)
	{
		Text_ = L"��� ��,  ��  ��������\n������  �߹��ߴ�.";
	}
	else if (2 == Count_)
	{
		Text_ = L"���  ��  �ο�  ����,\n�ΰ���  �¸��ߴ�.";
	}
	else if (3 == Count_)
	{
		Text_ = L"�׵���  ����  �ֹ���\n�̿��Ͽ�  ��������\n��  �ӿ�  �����ߴ�.";
	}
	else if (4 == Count_)
	{
		Text_ = L"����  �ð���  �帥  ��...";
	}
	else if (5 == Count_)
	{
		Text_ = L"����  ��,\n201X��";
	}
	else if (6 == Count_)
	{
		Text_ = L"������  ������\n�꿡  ����  �̴�  ����\n���ƿ���  ���Ѵٰ�  �Ѵ�.";
	}
	else
	{
		Text_ = L"";
	}
}
