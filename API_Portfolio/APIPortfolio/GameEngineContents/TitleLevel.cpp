#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleImage.h"
#include "Player.h"
#include "TitleFont.h"
#include "FadeInOut.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "ContentsEnums.h"

TitleLevel::TitleLevel():
	Time_(0.0f),
	Count_(0)
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Init()
{

	Text_ = CreateActor<TitleFont>((int)TITLEORDER::TEXT);

	for (int i = 0; i < 15; ++i)
	{
		TitleImage_[i] = CreateActor<TitleImage>();
	}

	TitleRenderer_[(int)TITLEORDER::TITLE] = TitleImage_[(int)TITLEORDER::TITLE]->CreateRendererToScale("Title.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE);
	float4 Half = TitleRenderer_[(int)TITLEORDER::TITLE]->GetImage()->GetScale().Half();
	TitleRenderer_[(int)TITLEORDER::TITLE]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE1] = TitleImage_[(int)TITLEORDER::TITLE1]->CreateRendererToScale("Title1.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE1);
	TitleRenderer_[(int)TITLEORDER::TITLE1]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE2] = TitleImage_[(int)TITLEORDER::TITLE2]->CreateRendererToScale("Title2.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE2);
	TitleRenderer_[(int)TITLEORDER::TITLE2]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE3] = TitleImage_[(int)TITLEORDER::TITLE3]->CreateRendererToScale("Title3.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE3);
	TitleRenderer_[(int)TITLEORDER::TITLE3]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE4] = TitleImage_[(int)TITLEORDER::TITLE4]->CreateRendererToScale("Title4.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE4);
	TitleRenderer_[(int)TITLEORDER::TITLE4]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE5] = TitleImage_[(int)TITLEORDER::TITLE5]->CreateRendererToScale("Title5.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE5);
	TitleRenderer_[(int)TITLEORDER::TITLE5]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE6] = TitleImage_[(int)TITLEORDER::TITLE6]->CreateRendererToScale("Title6.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE6);
	TitleRenderer_[(int)TITLEORDER::TITLE6]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE7] = TitleImage_[(int)TITLEORDER::TITLE7]->CreateRendererToScale("Title7.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE7);
	TitleRenderer_[(int)TITLEORDER::TITLE7]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE8] = TitleImage_[(int)TITLEORDER::TITLE8]->CreateRendererToScale("Title8.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE8);
	TitleRenderer_[(int)TITLEORDER::TITLE8]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE9] = TitleImage_[(int)TITLEORDER::TITLE9]->CreateRendererToScale("Title9.bmp", { 1280, 720 }, (int)TITLEORDER::TITLE8);
	TitleRenderer_[(int)TITLEORDER::TITLE9]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::TITLE10] = TitleImage_[(int)TITLEORDER::TITLE10]->CreateRendererToScale("Title10.bmp", { 1280, 1000 }, (int)TITLEORDER::TITLE9);
	TitleRenderer_[(int)TITLEORDER::TITLE10]->SetPivot({640, -90});
	TitleRenderer_[(int)TITLEORDER::BACKGROUND] = TitleImage_[(int)TITLEORDER::BACKGROUND]->CreateRendererToScale("TitleBackGround.bmp", { 1280, 720 }, (int)TITLEORDER::BACKGROUND);
	TitleRenderer_[(int)TITLEORDER::BACKGROUND]->SetPivot(Half);
	TitleRenderer_[(int)TITLEORDER::BACKGROUND]->SetTransColor(RGB(255, 255, 255));
	
	FadeEffect_ = CreateActor<FadeInOut>((int)TITLEORDER::BACKGROUND);

	
}


void TitleLevel::Loading()
{

}

void TitleLevel::Update()
{

	ChangeBackGround();
	FadeInOutBackGround();
	
	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}
	
	if(true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel2"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}
	
	if (true == GameEngineInput::GetInst()->IsPress("ChangeBattleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BattleLevel");
	}


}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr != Player::MainPlayer)
	{
		Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
		Player::MainPlayer->CamPosOff();
	}

	//초기화함수
	Init();
	Bgm_ = GameEngineSound::SoundPlayControl("01_Once_Upon_a_Time.flac");


}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Bgm_.Stop();
	TitleImage_[(int)TITLEORDER::TITLE]->Death();
	Time_ = 0.0f;

	for (int i = 0; i < 15; ++i)
	{
		TitleImage_[i]->Death();
	}
	Text_->Death();

	if (nullptr != Player::MainPlayer)
	{
		Player::MainPlayer->CamPosOn();
	}
}

void TitleLevel::ChangeBackGround()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (6.0f < Time_ && 0 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE1]->Death();
		++Count_;
	}


	if (10.0f < Time_ && 1 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE2]->Death();
		++Count_;
	}


	if (12.0f < Time_ && 2 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE3]->Death();
		++Count_;
	}


	if (16.0f < Time_ && 3 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE4]->Death();
		++Count_;
	}


	if (20.0f < Time_ && 4 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE5]->Death();
		++Count_;
	}


	if (24.0f < Time_ && 5 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE6]->Death();
		++Count_;
	}


	if (28.0f < Time_ && 6 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE7]->Death();
		++Count_;
	}


	if (32.0f < Time_ && 7 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE8]->Death();
		++Count_;
	}


	if (36.0f < Time_ && 8 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE9]->Death();
		++Count_;
	}

	if (40.0f < Time_ && 9 == Count_)
	{
		if (TitleImage_[(int)TITLEORDER::TITLE10]->GetPosition().y <= 650)
		{
			TitleImage_[(int)TITLEORDER::TITLE10]->SetMove(float4::DOWN * 100.0f * GameEngineTime::GetDeltaTime());
		}
		++Count_;
	}

	if (50.0f < Time_ && 10 == Count_)
	{
		TitleImage_[(int)TITLEORDER::TITLE10]->Death();
		TitleImage_[(int)TITLEORDER::BACKGROUND]->Death();
		++Count_;
	}
}

void TitleLevel::FadeInOutBackGround()
{
	if (4.0f < Time_ && 0 == Count_)
	{
		FadeEffect_->FadeIn();
	}
}
