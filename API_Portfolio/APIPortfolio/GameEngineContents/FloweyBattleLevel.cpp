#include "FloweyBattleLevel.h"
#include "BattleLevelActor.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>

FloweyBattleLevel::FloweyBattleLevel() 
{
}

FloweyBattleLevel::~FloweyBattleLevel() 
{
}

void FloweyBattleLevel::Loading()
{
	GameEngineActor* BackGround = CreateActor<BattleLevelActor>();
	GameEngineRenderer* Back = BackGround->CreateRenderer("BattleLevelBackGround.bmp", (int)BATTLELEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);

	GameEngineActor* Box = CreateActor<BattleLevelActor>();
	GameEngineRenderer* BoxRenderer = Box->CreateRendererToScale("TextBox.bmp", { 150,150 }, (int)BATTLELEVELORDER::BOX);


}

void FloweyBattleLevel::Update()
{
}

void FloweyBattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}


	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,420 });
	Player::MainPlayer->CamPosOff();
	//Player::MainPlayer->



}

void FloweyBattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
