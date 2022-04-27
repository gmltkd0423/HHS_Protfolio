#include "PlayLevel2Font.h"

PlayLevel2Font::PlayLevel2Font() :
	Time_(0.1f),
	Timer_(0),
	Count_(0),
	TextCount_(0),
	IsAllTextOut(false),
	IsTalkEnd_(false)
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

	RealText_ = Text_.substr(0, TextCount_);

	TextFont_.Draw(RealText_, { 470.0f, 30.0f }, RGB(255, 255, 255), 55, 45);


	//��ȭ�� ��� ��µǸ�
	if (Text_.size() == RealText_.size())
	{
		IsAllTextOut = true;
	}
}

void PlayLevel2Font::Texts()
{
	if (1 == Count_)
	{
		Text_ = L"*  �ݰ���!\n*  ��  �̸���  �ö���.\n*   ���  ��  �ö�����!!";
	}
	else if (2 == Count_)
	{
		Text_ = L"*  ����...";
	}
	else if (3 == Count_)
	{
		Text_ = L"*  ��  ��  ���ϼ����\n    ó���ΰ�  ������,\n    �׷���?";
	}
	else if (4 == Count_)
	{
		Text_ = L"*  �̷�,  ����\n    ���ž��ڳ�.";
	}
	else if (5 == Count_)
	{
		Text_ = L"*  �̰���  �  ������\n    ������  �˷���߰ڴµ�!";
	}
	else if (6 == Count_)
	{
		Text_ = L"*  �۰�  ������  ����\n    �˷���߰ڳ�.";
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
