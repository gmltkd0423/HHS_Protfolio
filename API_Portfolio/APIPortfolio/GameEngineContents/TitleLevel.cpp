#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleImage.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "ContentsEnums.h"

TitleLevel::TitleLevel():
	Time_(0.0f)
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Init()
{
	for (int i = 0; i < 15; ++i)
	{
		TitleImage_[i] = CreateActor<TitleImage>();
	}

	TitleRenderer_[(int)TITLEORDER::TITLE] = TitleImage_[(int)TITLEORDER::TITLE]->CreateRendererToScale("Title.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE);
	TitleRenderer_[(int)TITLEORDER::TITLE1] = TitleImage_[(int)TITLEORDER::TITLE1]->CreateRendererToScale("Title1.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE1);
	TitleRenderer_[(int)TITLEORDER::TITLE2] = TitleImage_[(int)TITLEORDER::TITLE2]->CreateRendererToScale("Title2.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE2);
	TitleRenderer_[(int)TITLEORDER::TITLE3] = TitleImage_[(int)TITLEORDER::TITLE3]->CreateRendererToScale("Title3.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE3);
	TitleRenderer_[(int)TITLEORDER::TITLE4] = TitleImage_[(int)TITLEORDER::TITLE4]->CreateRendererToScale("Title4.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE4);
	TitleRenderer_[(int)TITLEORDER::TITLE5] = TitleImage_[(int)TITLEORDER::TITLE5]->CreateRendererToScale("Title5.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE5);
	TitleRenderer_[(int)TITLEORDER::TITLE6] = TitleImage_[(int)TITLEORDER::TITLE6]->CreateRendererToScale("Title6.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE6);
	TitleRenderer_[(int)TITLEORDER::TITLE7] = TitleImage_[(int)TITLEORDER::TITLE7]->CreateRendererToScale("Title7.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE7);
	TitleRenderer_[(int)TITLEORDER::TITLE8] = TitleImage_[(int)TITLEORDER::TITLE8]->CreateRendererToScale("Title8.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE8);
	TitleRenderer_[(int)TITLEORDER::TITLE9] = TitleImage_[(int)TITLEORDER::TITLE9]->CreateRendererToScale("Title9.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE9);
	TitleRenderer_[(int)TITLEORDER::BACKGROUND] = TitleImage_[(int)TITLEORDER::BACKGROUND]->CreateRendererToScale("TitleBackGround.bmp", { 1280, 720 }, (int)TITLEORDER::BACKGROUND);
	TitleRenderer_[(int)TITLEORDER::BACKGROUND]->SetTransColor(RGB(255, 255, 255));
	

	TitleImage_[(int)TITLEORDER::TITLE9]->SetPosition({ TitleImage_[(int)TITLEORDER::TITLE9]->GetPosition().x,TitleImage_[(int)TITLEORDER::TITLE9]->GetPosition().y - 300 });
	
}


void TitleLevel::Loading()
{
	Init();

	
}

void TitleLevel::Update()
{

	ChangeBackGround();
	

	
	if (true == GameEngineInput::GetInst()->IsPress("ChangeLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
		LevelEnd();
	}

	BgmTime_ -= GameEngineTime::GetDeltaTime();
	if(0>=BgmTime_)
	{
		Bgm_.Stop();
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Bgm_ = GameEngineSound::SoundPlayControl("01_Once_Upon_a_Time.flac");
	BgmTime_ = 30.0f;
}

void TitleLevel::LevelEnd()
{
	Bgm_.Stop();
	TitleImage_[(int)TITLEORDER::TITLE]->Death();
	Time_ = 0.0f;
}

void TitleLevel::ChangeBackGround()
{
	Time_ += GameEngineTime::GetDeltaTime();


	if (2.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE1]->Death();
	}


	if (4.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE2]->Death();
	}


	if (6.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE3]->Death();
	}


	if (8.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE4]->Death();
	}


	if (10.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE5]->Death();
	}


	if (12.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE6]->Death();
	}


	if (14.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE7]->Death();
	}


	if (16.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE8]->Death();
	}

	if (18.0f < Time_)
	{
		if (TitleImage_[(int)TITLEORDER::TITLE9]->GetPosition().y - 50 <= GameEngineWindow::GetInst().GetScale().Half().y)
		{
			TitleImage_[(int)TITLEORDER::TITLE9]->SetMove(float4::DOWN * 100.0f * GameEngineTime::GetDeltaTime());
		}
	}

	if (25.0f < Time_)
	{
		TitleImage_[(int)TITLEORDER::TITLE9]->Death();
		TitleImage_[(int)TITLEORDER::BACKGROUND]->Death();
	}
}
