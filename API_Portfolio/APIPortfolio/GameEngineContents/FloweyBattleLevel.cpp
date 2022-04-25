#include "FloweyBattleLevel.h"
#include "BattleLevelActor.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>

FloweyBattleLevel::FloweyBattleLevel() :
	Check_(false)
{
}

FloweyBattleLevel::~FloweyBattleLevel() 
{
}

void FloweyBattleLevel::Loading()
{
	//백그라운드
	{
		GameEngineActor* BackGround = CreateActor<BattleLevelActor>();
		GameEngineRenderer* Back = BackGround->CreateRenderer("BattleLevelBackGround.bmp", (int)BATTLELEVELORDER::BACKGROUND);
		float4 Half = Back->GetImage()->GetScale().Half();
		Back->SetPivot(Half);
	}

	//네모 이미지
	{
		GameEngineActor* Box = CreateActor<BattleLevelActor>();
		GameEngineRenderer* BoxRenderer = Box->CreateRendererToScale("TextBox_Square.bmp", { 250,250 }, (int)BATTLELEVELORDER::BOX, RenderPivot::CENTER, { 640 , 465 });
	}


	{
		//플라위 대화 이미지
		FloweyTalk = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::ACTOR);
		FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)BATTLELEVELORDER::ACTOR , RenderPivot::CENTER,{640 , 230});
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Talk_Idle", 0, 1, 0.4f, true);
		FloweyTalkRenderer->ChangeAnimation("Talk_Idle");
		FloweyTalkRenderer->SetTransColor(RGB(241, 95, 241));
		FloweyTalkRenderer->SetScale({ 120,120 });
		FloweyTalk->Off();
	}

	{
		//말풍선
		Speech_Bubble = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::BOX);
		Speech_BubbleRenderer = Speech_Bubble->CreateRenderer((int)BATTLELEVELORDER::BOX, RenderPivot::CENTER, { 890 , 240 });
		Speech_BubbleRenderer->SetImage("Speech_Bubble.bmp");
		Speech_BubbleRenderer->SetScale({ 387, 160 });
		Speech_BubbleRenderer->SetTransColor(RGB(255, 102, 255));
		Speech_BubbleRenderer->Off();
	}


}

void FloweyBattleLevel::Update()
{
	if (Player::MainPlayer->GetPosition().y < 460.0f && false == Check_)
	{
		Player::MainPlayer->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 70);
		if (Player::MainPlayer->GetPosition().y >= 460.0f)
		{
			Check_ = true;
			FloweyTalk->On();
			Speech_BubbleRenderer->On();
		}
	}

}

void FloweyBattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}


	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,420 });
	Player::MainPlayer->SetSpeed(200.0f);
	Player::MainPlayer->CamPosOff();
	//Player::MainPlayer->



}

void FloweyBattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
