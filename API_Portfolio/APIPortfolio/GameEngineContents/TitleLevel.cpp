#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>

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
	}
}

void TitleLevel::LevelChangeStart()
{

}