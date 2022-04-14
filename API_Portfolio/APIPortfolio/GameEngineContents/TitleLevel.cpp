#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0,"TitleBackGround");
	GameEngineInput::GetInst()->CreateKey("Change_PlayLevel", VK_RETURN);

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("Change_PlayLevel"))
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

void TitleLevel::LevelChangeStart()
{
	Bgm_ = GameEngineSound::SoundPlayControl("01_Once_Upon_a_Time.flac");
	BgmTime_ = 20.0f;
}

void TitleLevel::LevelEnd()
{
	Bgm_.Stop();
}