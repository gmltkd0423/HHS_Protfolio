#include "PlayLevel2Font.h"

PlayLevel2Font::PlayLevel2Font() :
	Time_(0.1f),
	Timer_(0),
	Count_(0),
	TextCount_(0),
	IsAllTextOut(false),
	IsTalkEnd_(false),
	TextTime_(0.2f)
{
}

PlayLevel2Font::~PlayLevel2Font() 
{
}

void PlayLevel2Font::Start()
{
	Count_ = 0;
	TextCount_ = 0;
	Timer_ = 0;
	IsAllTextOut = false;
	IsTalkEnd_ = false;
}

void PlayLevel2Font::Update()
{
}

void PlayLevel2Font::Render()
{
	//대화가끝나면
	if (6 < Count_)
	{
		IsTalkEnd_ = true;
	}

	//출력할 텍스트 입력해놓은 함수
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


	if (Text_.size() != RealText_.size())
	{
		TextSounds();
	}

	RealText_ = Text_.substr(0, TextCount_);

	TextFont_.Draw(RealText_, { 470.0f, 30.0f }, RGB(255, 255, 255), 55, 45);


	//대화가 모두 출력되면
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
		Timer_ = 0;
	}
}

void PlayLevel2Font::Texts()
{
	if (1 == Count_)
	{
		Text_ = L"*  반가워!\n*  내  이름은  플라위.\n*  노란  꽃  플라위야!!";
	}
	else if (2 == Count_)
	{
		Text_ = L"*  흐음...";
	}
	else if (3 == Count_)
	{
		Text_ = L"*  너  이  지하세계는\n   처음인가  보구나,\n   그렇지?";
	}
	else if (4 == Count_)
	{
		Text_ = L"*  이런,  정말\n   정신없겠네.";
	}
	else if (5 == Count_)
	{
		Text_ = L"*  이곳이  어떤  곳인지\n   누군가  알려줘야겠는데!";
	}
	else if (6 == Count_)
	{
		Text_ = L"*  작고  힘없는  나라도\n   알려줘야겠네.";
	}
	else if (7 == Count_)
	{
		Text_ = L"*  준비됐니?   \n*  간다!";
	}
	else
	{
		Text_ = L"";
	}

}

void PlayLevel2Font::TextSounds()
{
	TextTime_ -= GameEngineTime::GetDeltaTime();
	Timer_ += GameEngineTime::GetDeltaTime();

	if (1 == Count_)
	{

		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.7f || Timer_ >= 1.4f )
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (2 == Count_)
	{

		if (0 >= TextTime_)
		{
			TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
			TextTime_ = 0.1f;
		}
	}
	else if (3 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 2.6f || Timer_ >= 3.1f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (4 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.6f || Timer_ >= 1.0f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (5 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 1.2f || Timer_ >= 1.7f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (6 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 1.2f || Timer_ >= 1.7f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	
	}
	else if (7 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.5f || Timer_ >= 1.3f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else
	{
	
	}
}
