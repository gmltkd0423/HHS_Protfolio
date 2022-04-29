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
		Text_ = L"오래  전,  인간과  괴물,\n두  종족이  지구를  통치했다.";
	}
	else if (1 == Count_)
	{
		Text_ = L"어느 날,  두  종족간에\n전쟁이  발발했다.";
	}
	else if (2 == Count_)
	{
		Text_ = L"길고  긴  싸움  끝에,\n인간이  승리했다.";
	}
	else if (3 == Count_)
	{
		Text_ = L"그들은  마법  주문을\n이용하여  괴물들을\n땅  속에  봉인했다.";
	}
	else if (4 == Count_)
	{
		Text_ = L"많은  시간이  흐른  뒤...";
	}
	else if (5 == Count_)
	{
		Text_ = L"에봇  산,\n201X년";
	}
	else if (6 == Count_)
	{
		Text_ = L"전설에  따르면\n산에  오른  이는  절대\n돌아오지  못한다고  한다.";
	}
	else
	{
		Text_ = L"";
	}
}
