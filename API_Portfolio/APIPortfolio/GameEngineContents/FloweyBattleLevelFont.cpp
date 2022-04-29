#include "FloweyBattleLevelFont.h"

FloweyBattleLevelFont::FloweyBattleLevelFont() :
	TextTime_(0.1f),
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


	if (24 == Count_)
	{
		TextFont_.Draw(RealText_, { 780.0f, 180.0f }, RGB(0, 0, 0), 120, 120);
	}
	else
	{
		TextFont_.Draw(RealText_, { 760.0f, 170.0f }, RGB(0, 0, 0), 35, 35);
	}

	//��ȭ�� ��� ��µǸ�
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
		Timer_ = 0;
	}
}

void FloweyBattleLevelFont::Texts()
{
	if (0 == Count_)
	{
		Text_ = L"��Ʈ ����� ������? \n���� �� ��ȥ�̾�. \n�� ������ ������!";
	}
	else if (1 == Count_)
	{
		Text_ = L"�� ��ȥ�� ��������,  \nLV�� ���� �ø���  \n������ �� �־�.";
	}
	else if (2 == Count_)
	{
		Text_ = L"LV�� ���İ�?  \n�ٷ�, LOVE��, ����!";
	}
	else if (3 == Count_)
	{
		Text_ = L"LOVE�� �� �ʿ��� ��\n������, �׷���?";
	}
	else if (4 == Count_)
	{
		Text_ = L"����������,\n���� �� �����ٰ�!";
	}
	else if(10 == Count_)
	{
		Text_ = L"���� ���ϼ��迡��,\nLOVE��...";
	}
	else if (11 == Count_)
	{
		Text_ = L"�۰� �Ͼ�...\n'ģ�� �˰���' ��\n���� ������.";
	}
	else if (12 == Count_)
	{
		Text_ = L"�غ�ƾ�?";
	}
	else if (13 == Count_)
	{
		Text_ = L"������!\nģ���� �ִ���\n���� �޴°ž�!";
	}
	else if (14 == Count_)
	{
		Text_ = L"�̺� ģ��,\n���Ĺ����ݾ�.";
	}
	else if (15 == Count_)
	{
		Text_ = L"�ٽ� �غ��ڰ�,\n�˾���?";
	}
	else if (18 == Count_)
	{
		Text_ = L"�峭ġ�°ž�?\n�� �����ƴ�?\n�޷�. �����. ��.\n�Ѿ˷�!!!";
	}
	else if (19 == Count_)
	{
		Text_ = L"�峭ġ�°ž�?\n�� �����ƴ�?\n�޷�. �����. ��.\nģ����!!!";
	}
	else if (22 == Count_)
	{
		Text_ = L"��ġä�� �־���\n����,\n��?";
	}
	else if (23 == Count_)
	{
		Text_ = L"���� �� ��������\n�;��� ���̾���.";
	}
	else if (24 == Count_)
	{
		Text_ = L"�� ��.";
	}
	else
	{
		Text_ = L"";
	}
}

void FloweyBattleLevelFont::TextSounds()
{
	TextTime_ -= GameEngineTime::GetDeltaTime();
	Timer_ += GameEngineTime::GetDeltaTime();

	if (0 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.7f || Timer_ >= 1.4f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (1 == Count_)
	{

		if (0 >= TextTime_)
		{
			TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
			TextTime_ = 0.1f;
		}
	}
	else if (2 == Count_)
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
	else if (3 == Count_)
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
	else if (4 == Count_)
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
			if (Timer_ <= 0.5f || Timer_ >= 1.3f)
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
	else if (8 == Count_)
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
	else if (9 == Count_)
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
	else if (10 == Count_)
	{
		if (0 >= TextTime_)
		{

			TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
			TextTime_ = 0.1f;

		}
	}
	else if (11 == Count_)
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
	else if (12 == Count_)
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
	else if (13 == Count_)
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
	else if (14 == Count_)
	{
		if (0 >= TextTime_)
		{

			TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
			TextTime_ = 0.1f;

		}
	}
	else if (15 == Count_)
	{
		if (0 >= TextTime_)
		{
			TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
			TextTime_ = 0.1f;
		}
	}
	else if (16 == Count_)
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
	else if (17 == Count_)
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
	else if (18 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.7f || Timer_ >= 1.3f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (19 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.7f || Timer_ >= 1.3f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (20 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.7f || Timer_ >= 1.3f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (21 == Count_)
	{
		if (0 >= TextTime_)
		{
			if (Timer_ <= 0.7f || Timer_ >= 1.3f)
			{
				TextSound_.SoundPlayOneShot("snd_floweytalk1.wav");
				TextTime_ = 0.1f;
			}
		}
	}
	else if (22 == Count_)
	{
		if (0 >= TextTime_)
		{

				TextSound_.SoundPlayOneShot("snd_floweytalk2.wav");
				TextTime_ = 0.1f;
			
		}
	}
	else if (23 == Count_)
	{
		if (0 >= TextTime_)
		{

				TextSound_.SoundPlayOneShot("snd_floweytalk2.wav");
				TextTime_ = 0.1f;
			
		}
	}
	else if (24 == Count_)
	{
		if (0 >= TextTime_)
		{

				TextSound_.SoundPlayOneShot("snd_floweytalk2.wav");
				TextTime_ = 0.1f;
			
		}
	}
	else
	{

	}
}
