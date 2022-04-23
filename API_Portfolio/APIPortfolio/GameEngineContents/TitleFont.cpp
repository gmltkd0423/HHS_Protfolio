#include "TitleFont.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineTime.h>


TitleFont::TitleFont() :
	Time_(0.0f),
	FontSizeX_(80.0f),
	FontSizeY_(80.0f),
	Title1TextOn(true),
	Count_(0),
	TextPos_({235 , 470})
{
}

TitleFont::~TitleFont() 
{
}

void TitleFont::Start()
{
	Count_ = 0;

	GameEngineDirectory Dir;
	Dir.MoveParent("API_Portfolio");
	Dir.Move("APIPortfolio");
	Dir.Move("Resources");
	Dir.Move("Fonts");

	std::vector<GameEngineFile> AllFontFileList = Dir.GetAllFile("ttf");

	TextFont_.Load(AllFontFileList[1].GetFullPath());

	//��Ʈ���� �׽�Ʈ�� �ؽ�Ʈ
	/*TestFont.Load("enbrodwy.ttf");
	TestFont2.Load("arial.ttf");*/
}

void TitleFont::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();
}

void TitleFont::Render()
{
	//��Ʈ���� �׽�Ʈ�� �ؽ�Ʈ
	/*TestFont.Draw("�ٶ��� �� �¹��� Ÿ����", { 100.0f,100.0f }, 100, 50);
	TestFont.Draw("abcdefghijklmnopqrstuwxyz", { 100.0f,200.0f }, 100, 50);
	TestFont2.Draw("�ٶ��� �� �¹��� Ÿ����", { 100.0f,300.0f }, 100, 50);
	TestFont2.Draw("abcdefghijklmnopqrstuwxyz", { 100.0f,400.0f }, 100, 50);*/

	TitleText();


}


void TitleFont::TitleText()
{

	//ù��° Ÿ��Ʋ
	if ( 0 == Count_)
	{
		if (0.1 < Time_)
		{
			TextFont_.Draw("��", { 235, 470 }, FontSizeX_, FontSizeY_);
		}

		if (0.2f < Time_)
		{
			TextFont_.Draw("��", { 305, 470 }, FontSizeX_, FontSizeY_);
		}


		if (0.3f < Time_)
		{
			TextFont_.Draw("��", { 415, 470 }, FontSizeX_, FontSizeY_);
		}


		if (0.4f < Time_)
		{
			TextFont_.Draw(",", { 485, 470 }, FontSizeX_, FontSizeY_);
		}


		if (0.9f < Time_)
		{
			TextFont_.Draw("��", { 565, 470 }, FontSizeX_, FontSizeY_);
		}


		if (1.0f < Time_)
		{
			TextFont_.Draw("��", { 635, 470 }, FontSizeX_, FontSizeY_);
		}


		if (1.1f < Time_)
		{
			TextFont_.Draw("��", { 705, 470 }, FontSizeX_, FontSizeY_);
		}

		if (1.2f < Time_)
		{
			TextFont_.Draw("��", { 815, 470 }, FontSizeX_, FontSizeY_);
		}

		if (1.3f < Time_)
		{
			TextFont_.Draw("��", { 885, 470 }, FontSizeX_, FontSizeY_);
		}

		if (1.4f < Time_)
		{
			TextFont_.Draw(",", { 955, 470 }, FontSizeX_, FontSizeY_);
		}

		//�ι�°��/////////////////////////////////////////

		if (1.9f < Time_)
		{
			TextFont_.Draw("��", { 235, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.0f < Time_)
		{
			TextFont_.Draw("��", { 345, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.1f < Time_)
		{
			TextFont_.Draw("��", { 415, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.2f < Time_)
		{
			TextFont_.Draw("��", { 485, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.3f < Time_)
		{
			TextFont_.Draw("��", { 595, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.4f < Time_)
		{
			TextFont_.Draw("��", { 665, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.5f < Time_)
		{
			TextFont_.Draw("��", { 735, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.6f < Time_)
		{
			TextFont_.Draw("��", { 845, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.7f < Time_)
		{
			TextFont_.Draw("ġ", { 915, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.8f < Time_)
		{
			TextFont_.Draw("��", { 985, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.9f < Time_)
		{
			TextFont_.Draw("��", { 1055, 550 }, FontSizeX_, FontSizeY_);
		}

		if (3.0f < Time_)
		{
			TextFont_.Draw(".", { 1125, 550 }, FontSizeX_, FontSizeY_);
		}

		if (4.0f < Time_)
		{
			Count_++;
			Time_ = 0.0f;
		}
	}

	//�ι�° Ÿ��Ʋ
	if (1 == Count_)
	{
		if (0.1 < Time_)
		{
			TextFont_.Draw("��", { 235, 470 }, FontSizeX_, FontSizeY_);
		}

		if (0.2f < Time_)
		{
			TextFont_.Draw("��", { 305, 470 }, FontSizeX_, FontSizeY_);
		}


		if (0.3f < Time_)
		{
			TextFont_.Draw("��", { 415, 470 }, FontSizeX_, FontSizeY_);
		}


		if (0.4f < Time_)
		{
			TextFont_.Draw(",", { 485, 470 }, FontSizeX_, FontSizeY_);
		}


		if (0.9f < Time_)
		{
			TextFont_.Draw("��", { 565, 470 }, FontSizeX_, FontSizeY_);
		}


		if (1.0f < Time_)
		{
			TextFont_.Draw("��", { 675, 470 }, FontSizeX_, FontSizeY_);
		}


		if (1.1f < Time_)
		{
			TextFont_.Draw("��", { 735, 470 }, FontSizeX_, FontSizeY_);
		}

		if (1.2f < Time_)
		{
			TextFont_.Draw("��", { 805, 470 }, FontSizeX_, FontSizeY_);
		}

		if (1.3f < Time_)
		{
			TextFont_.Draw("��", { 875, 470 }, FontSizeX_, FontSizeY_);
		}

		//�ι�°��/////////////////////////////////////////

		if (1.4f < Time_)
		{
			TextFont_.Draw("��", { 235, 550 }, FontSizeX_, FontSizeY_);
		}

		if (1.5f < Time_)
		{
			TextFont_.Draw("��", { 305, 550 }, FontSizeX_, FontSizeY_);
		}

		if (1.6f < Time_)
		{
			TextFont_.Draw("��", { 375, 550 }, FontSizeX_, FontSizeY_);
		}

		if (1.7f < Time_)
		{
			TextFont_.Draw("��", { 485, 550 }, FontSizeX_, FontSizeY_);
		}

		if (1.8f < Time_)
		{
			TextFont_.Draw("��", { 555, 550 }, FontSizeX_, FontSizeY_);
		}

		if (1.9f < Time_)
		{
			TextFont_.Draw("��", { 625, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.0f < Time_)
		{
			TextFont_.Draw("��", { 695, 550 }, FontSizeX_, FontSizeY_);
		}

		if (2.1f < Time_)
		{
			TextFont_.Draw(".", { 765, 550 }, FontSizeX_, FontSizeY_);
		}

		if (4.0f < Time_)
		{
			Count_++;
			Time_ = 0.0f;
		}
	}

}
