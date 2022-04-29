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
	//��ȭ��������
	if (6 < Count_)
	{
		IsTalkEnd_ = true;
	}

	//����� �ؽ�Ʈ �Է��س��� �Լ�
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


	//��ȭ�� ��� ��µǸ�
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
		Text_ = L"*  �ݰ���!\n*  ��  �̸���  �ö���.\n*  ���  ��  �ö�����!!";
	}
	else if (2 == Count_)
	{
		Text_ = L"*  ����...";
	}
	else if (3 == Count_)
	{
		Text_ = L"*  ��  ��  ���ϼ����\n   ó���ΰ�  ������,\n   �׷���?";
	}
	else if (4 == Count_)
	{
		Text_ = L"*  �̷�,  ����\n   ���ž��ڳ�.";
	}
	else if (5 == Count_)
	{
		Text_ = L"*  �̰���  �  ������\n   ������  �˷���߰ڴµ�!";
	}
	else if (6 == Count_)
	{
		Text_ = L"*  �۰�  ������  ����\n   �˷���߰ڳ�.";
	}
	else if (7 == Count_)
	{
		Text_ = L"*  �غ�ƴ�?   \n*  ����!";
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
