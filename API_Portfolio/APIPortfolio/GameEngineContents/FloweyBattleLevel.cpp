#include "FloweyBattleLevel.h"
#include "BattleLevelActor.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "FloweyBullet.h"
#include "HpBar.h"
#include "SoundPlayer.h"
#include "FloweyBattleLevelFont.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngine.h>



FloweyBattleLevel::FloweyBattleLevel() :
	Check_(false),
	PlayerPos_(float4::ZERO),
	CheckBullet_(false),
	IsDeathCheck(0),
	Count_(0),
	CurState_(PatternState::Talk),
	FloweyStateCount_(0),
	FloweyDeath(false),
	FloweyHurt(false)
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
		GameEngineRenderer* BoxRenderer = Box->CreateRendererToScale("TextBox_Square.bmp", { 200,200 }, (int)BATTLELEVELORDER::BOX, RenderPivot::CENTER, { 640 , 465 });
	}


	{


		WinkStar = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::ACTOR);
		WinkStarRenderer = WinkStar->CreateRenderer((int)BATTLELEVELORDER::ACTOR, RenderPivot::CENTER, { 730 , 170 });
		WinkStarRenderer->CreateAnimation("WinkStar.bmp","WinkStar" , 0, 6, 0.1f, false);
		WinkStarRenderer->ChangeAnimation("WinkStar");
		WinkStar->Off();

		//플라위 대화 이미지
		FloweyTalk = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::ACTOR);
		FloweyTalk->SetPosition({ 640 , 230 });
		FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)BATTLELEVELORDER::ACTOR , RenderPivot::CENTER);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Flowey_Idle", 0, 0, 0.4f, true);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Flowey_Talk", 0, 1, 0.2f, true);

		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Wink.bmp", "Flowey_Wink", 0, 0, 0, false);

		//표정1
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Sassy.bmp", "Flowey_Sassy_Idle", 0, 0, 0, false);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Sassy.bmp", "Flowey_Sassy", 0, 1, 0.2f, true);

		//표정2
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Mad.bmp", "Flowey_Mad_Idle", 0, 0, 0, false);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Mad.bmp", "Flowey_Mad", 0, 1, 0.2f, true);

		//표정3
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Evil.bmp", "Flowey_Evil_Idle", 0, 0, 0, false);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Evil.bmp", "Flowey_Evil", 0, 1, 0.2f, true);

		//표정4
		FloweyTalkRenderer->CreateAnimation("Flowey_Laugh.bmp", "Flowey_Laugh_Idle", 0, 0, 0, false);
		FloweyTalkRenderer->CreateAnimation("Flowey_Laugh.bmp", "Flowey_Laugh_Talk", 0, 1, 0.1f, true);
		FloweyTalkRenderer->CreateAnimation("Flowey_Laugh.bmp", "Flowey_Laugh", 0, 1, 0.05f, true);

		//side표정 1
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Side.bmp", "Flowey_Side_Idle", 0, 0, 0, true);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Side.bmp", "Flowey_Side", 0, 1, 0.2f, true);
		
		//side표정 2
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Side.bmp", "Flowey_Side_Idle2", 2, 2, 0, true);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Side.bmp", "Flowey_Side2", 2, 3, 0.2f, true);

		//hurt 표정
		FloweyTalkRenderer->CreateAnimation("Flowey_Hurt.bmp", "Flowey_Hurt", 0, 0, 0, false);

		FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
		FloweyTalkRenderer->SetTransColor(RGB(241, 95, 241));
		FloweyTalkRenderer->SetScale({ 120,120 });
		FloweyTalk->Off();
	}


	{
		Undyne = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::BACKGROUND);
		Undyne->SetPosition({ 1500,180 });
		UndyneRenderer = Undyne->CreateRenderer((int)BATTLELEVELORDER::BACKGROUND, RenderPivot::CENTER);
		UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle", 0, 67, 0.05f, true);
		UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle_Stop", 0, 0, 0, false);
		UndyneRenderer->ChangeAnimation("Idle_Stop");
		UndyneRenderer->SetScale({ 350,350 });

	}

	//Fire Projectile 
	{
		Fire_ = CreateActor<Fire>((int)BATTLELEVELORDER::BULLET);
		Fire_->SetPosition({ 1000,220 });
		Fire_->Off();


	}

	{

		Trigger_ = CreateActor<Trigger>();
		Trigger_->SetPosition({ 640,230 });
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


	{
		//플레이어 hp바
		HpBar_ = CreateActor<HpBar>((int)BATTLELEVELORDER::ACTOR);
		HpBar_->SetPosition({ 590, 600 });

	}


}

void FloweyBattleLevel::Update()
{

	//하트위치 이동
 	if (Player::MainPlayer->GetPosition().y < 460.0f && false == Check_)
	{
		Player::MainPlayer->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 70);
		if (Player::MainPlayer->GetPosition().y >= 460.0f)
		{
			Check_ = true;
			FloweyTalk->On();
			Speech_BubbleRenderer->On();
			Player::MainPlayer->Play();
		}
	}


	StateUpdate();


	CheckChangeLevelKey();

	if (true == GameEngineInput::GetInst()->IsPress("ChangeDebug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

}

void FloweyBattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,420 });
	Player::MainPlayer->SetSpeed(200.0f);
	Player::MainPlayer->CamPosOff();
	Player::MainPlayer->Stop();
	Player::MainPlayer->IsHeart();
	TextFont_ = CreateActor<FloweyBattleLevelFont>((int)BATTLELEVELORDER::ACTOR);


	ChangeState(PatternState::Talk);
	//Player::MainPlayer->

	if (nullptr == SoundPlayer::Bgm_.getControlHandle_())
	{
		SoundPlayer::Bgm_ = GameEngineSound::SoundPlayControl("03_Your_Best_Friend.flac");
	}

}

void FloweyBattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->SetSpeed(500.0f);
	Player::MainPlayer->IsFrisk();
	Player::MainPlayer->CamPosOn();
	Player::MainPlayer->NextLevelOn();
	Count_ = 0;

	if (nullptr != SoundPlayer::Bgm_.getControlHandle_())
	{
		SoundPlayer::Bgm_.Stop();
	}
}



void FloweyBattleLevel::ChangeState(PatternState _State)
{

	switch (_State)
	{
	case PatternState::Talk:
		TalkStart();
		break;
	case PatternState::Pattern1:
		Pattern1Start();
		break;
	case PatternState::Pattern2:
		Pattern2Start();
		break;
	case PatternState::Pattern3:
		Pattern3Start();
		break;
	case PatternState::Pattern4:
		Pattern4Start();
		break;
	default:
		break;
	}
	

	CurState_ = _State;
}

void FloweyBattleLevel::StateUpdate()
{
	switch (CurState_)
	{
	case PatternState::Talk:
		TalkUpdate();
		break;
	case PatternState::Pattern1:
		Pattern1Update();
		break;
	case PatternState::Pattern2:
		Pattern2Update();
		break;
	case PatternState::Pattern3:
		Pattern3Update();
		break;
	case PatternState::Pattern4:
		Pattern4Update();
		break;
	default:
		break;
	}
}



void FloweyBattleLevel::CheckChangeLevelKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel2"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangeTitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
}

void FloweyBattleLevel::TalkStart()
{

}

void FloweyBattleLevel::TalkUpdate()
{
	if (0 == Count_)
	{
		TextFont_->SetCount(Count_);
		FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
	}

	if (true == TextFont_->GetIsAllTextOut())
	{
		if (5 > Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
		}
	}

	if (5 == Count_)
	{

		Speech_Bubble->Off();


		FloweyTalkRenderer->ChangeAnimation("Flowey_Wink");
		WinkStar->On();

		Time_ += GameEngineTime::GetDeltaTime();

		if (0.8f <= Time_)
		{
			Time_ = 0;
			//pattern1은 Count_가 10부터 시작
			Count_ = 10;
			WinkStar->Off();
			ChangeState(PatternState::Pattern1);
			
		}
		
	}

	if (true == Player::MainPlayer->IsActionKeyDown() && true == TextFont_->GetIsAllTextOut())
	{
		Count_++;  // 1
		TextFont_->IsAllTextOutFalse();
		TextFont_->SetTextCount(0);

		TextFont_->SetCount(Count_);
		FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
	}
	
}

void FloweyBattleLevel::Pattern1Start()
{
	//pattern1은 Count_가 10부터 시작
	Count_ = 10;
	FloweyTalkRenderer->ChangeAnimation("Flowey_Side");
	Speech_Bubble->On();
	TextFont_->SetTextCount(0);
	TextFont_->IsAllTextOutFalse();

	BulletPos_[0] = { 490, 180 };
	BulletPos_[1] = { 560, 120 };
	BulletPos_[2] = { 640, 90 };
	BulletPos_[3] = { 710, 110 };
	BulletPos_[4] = { 790, 130 };
	
}

void FloweyBattleLevel::Pattern1Update()
{
	////플레이어가 맞았는지 검사
	if (1 == Player::MainPlayer->GetHp())
	{
		for (int i = 0; i < 5; ++i)
		{
			Bullets_[i]->Off();
		}
		SoundPlayer::Bgm_.Stop();
		ChangeState(PatternState::Pattern3);
		return;
	}

	//처음시작했을때 한번만 호출되는애들
	{
		if (10 == Count_ && false == CheckBullet_)
		{
			TextFont_->SetCount(Count_);
			FloweyTalkRenderer->ChangeAnimation("Flowey_Side");

			for (int i = 0; i < 5; ++i)
			{
				Bullets_[i] = CreateActor<FloweyBullet>();
				Bullets_[i]->SetPosition(FloweyTalk->GetPosition());
			}
			CheckBullet_ = true;
		}

		//시작하면 총알 위치로 보내기
		if (true == CheckBullet_)
		{
			for (int i = 0; i < 5; ++i)
			{
				Dir[i] = (BulletPos_[i] - Bullets_[i]->GetPosition());
				Dir[i].Normal2D();

				Bullets_[i]->SetMove(Dir[i] * GameEngineTime::GetDeltaTime() * 100.0f);
			}
		}
	}





//첫대화
//////////////////////////////////////////////////////////////



	//텍스트가 모두 출력됐을때
	if (true == TextFont_->GetIsAllTextOut())
	{
		if (10 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Side_Idle");
			
		}
		else if(11 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Side_Idle2");
		}
		else if (14 == Count_ || 15 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Sassy_Idle");
		}
		else if(18 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Mad_Idle");
		}
		else if (20 == Count_ || 21 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
		}
		else if (22 == Count_ || 23 == Count_ || 24 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Evil_Idle");
			
		}
		else
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
		}



		//Count_ == 13일땐 첫번재 총알 발사
		if (13 == Count_)
		{

			CheckBullet_ = false;
			for (int i = 0; i < 5; ++i)
			{
				Bullets_[i]->SetCount(Count_);
			}


			Time_ += GameEngineTime::GetDeltaTime();
			if (1.0f < Time_)
			{
				Speech_Bubble->Off();
				Time_ = 0;
			}



			for (int i = 0; i < 5; ++i)
			{
				if (true == Bullets_[i]->GetDeathCheck())
				{
					Bullets_[i]->Off();
				}
			}

			if (false == Bullets_[0]->IsUpdate() &&
				false == Bullets_[1]->IsUpdate() &&
				false == Bullets_[2]->IsUpdate() &&
				false == Bullets_[3]->IsUpdate() &&
				false == Bullets_[4]->IsUpdate()
				)
			{
				Count_++;
			}

		}

		
	}

	
//두번째 대화
//flowey sassy
////////////////////////////////////////////////////////////////////


	if (14 == Count_ && 0 == FloweyStateCount_)
	{
		Speech_Bubble->On();
		FloweyTalkRenderer->ChangeAnimation("Flowey_Sassy");
		TextFont_->SetCount(Count_);
		TextFont_->SetTextCount(0);
		FloweyStateCount_++;

		//idle상태로 안가게만들어줌
		TextFont_->IsAllTextOutFalse();
	}


	if (16 == Count_)
	{
		for (int i = 0; i < 5; ++i)
		{
			Bullets_[i]->SetPosition(BulletPos_[i]);
			Bullets_[i]->SetDeathCheck();
			Bullets_[i]->On();
			Bullets_[i]->SetCount(Count_);
		}
		Count_++;

	
	}
	else if (17 == Count_)
	{
		Speech_Bubble->Off();
		FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");

		for (int i = 0; i < 5; ++i)
		{
			if (true == Bullets_[i]->GetDeathCheck())
			{
				Bullets_[i]->Off();
			}
		}

		if (false == Bullets_[0]->IsUpdate() &&
			false == Bullets_[1]->IsUpdate() &&
			false == Bullets_[2]->IsUpdate() &&
			false == Bullets_[3]->IsUpdate() &&
			false == Bullets_[4]->IsUpdate()
			)
		{
			Count_++;  //18
		}
	}

//세번째대화
//flowey_mad
//////////////////////////////////////////////////////////////////


	if (18 == Count_ && 1 == FloweyStateCount_)
	{
		Speech_Bubble->On();
		TextFont_->SetCount(Count_);
		TextFont_->SetTextCount(0);
		FloweyStateCount_++;
		//TextFont_->IsAllTextOutFalse();
		FloweyTalkRenderer->ChangeAnimation("Flowey_Mad");
	}

	if (19 == Count_)
	{
		for (int i = 0; i < 5; ++i)
		{
			Bullets_[i]->SetPosition(BulletPos_[i]);
			Bullets_[i]->SetDeathCheck();
			Bullets_[i]->On();
			Bullets_[i]->SetCount(Count_);
		}
		Count_++;

	}
	else if (20 == Count_)
	{
		Time_ += GameEngineTime::GetDeltaTime();
		if (1.0f <= Time_)
		{
			Speech_Bubble->Off();
			Time_ = 0;
		}

		for (int i = 0; i < 5; ++i)
		{
			if (true == Bullets_[i]->GetDeathCheck())
			{
				Bullets_[i]->Off();
			}
		}

		if (false == Bullets_[0]->IsUpdate() &&
			false == Bullets_[1]->IsUpdate() &&
			false == Bullets_[2]->IsUpdate() &&
			false == Bullets_[3]->IsUpdate() &&
			false == Bullets_[4]->IsUpdate()
			)
		{
			Count_++;  //21
			Time_ = 0;
		}

	}

//네번째대화
//flowey laugh
////////////////////////////////////////////////////////////////////

	if(21 == Count_ && 2 == FloweyStateCount_)
	{
		Time_ += GameEngineTime::GetDeltaTime();

		if (1.5f < Time_)
		{
			SoundPlayer::Bgm_.Stop();
			FloweyTalkRenderer->ChangeAnimation("Flowey_Evil");
			if (2.2f < Time_)
			{
				Count_++;   //22
				Speech_Bubble->On();
				TextFont_->SetCount(Count_);
				TextFont_->SetTextCount(0);
				TextFont_->IsAllTextOutFalse();
				FloweyStateCount_++;
			}
		}
	}






///////////////////////////////////////////////////////////////////
	//z키를눌러 텍스트출력
	if (true == Player::MainPlayer->IsActionKeyDown() && true == TextFont_->GetIsAllTextOut())
	{
		if (13 == Count_ || 19 == Count_)
		{
			return;
		}

		Count_++;  // 1
		TextFont_->IsAllTextOutFalse();

		if (19 != Count_)
		{
			TextFont_->SetTextCount(0);	
		}

		TextFont_->SetCount(Count_);
		

		if (24 == Count_)
		{
			ChangeState(PatternState::Pattern2);
		}

		if (11 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Side");
		}
		else if (15 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Sassy");
		}
		else if( 22 == Count_ || 23 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Evil");
		}
		else
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
		}
	}


	if (11 == Count_)
	{
		Time_ += GameEngineTime::GetDeltaTime();
		if (0.8 < Time_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Side2");
			Time_ = 0;
		}
	}






}



void FloweyBattleLevel::Pattern2Start()
{
	Angle = 0.0f;
	Time_ = 0.03f;
	Count_ = 23;
	FloweyStateCount_ = 3;
	Speech_Bubble->Off();
	FloweyTalkRenderer->ChangeAnimation("Flowey_Evil_Idle");


}


void FloweyBattleLevel::CreateBulletCircle()
{

	if (360.0f <= Angle)
	{
		if (23 == Count_)
		{
			Count_++;
		}
		return;
	}

	Time_ -= GameEngineTime::GetDeltaTime();

	if (0.0f < Time_)
	{
		return;
	}
	Player::MainPlayer->Stop();

	Angle += 3.0f;

	float4 Dir = float4::DegreeToDirectionFloat4(Angle);
	Dir *= 120.0f;
	NewBullet = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
	NewBullet->SetPosition(Player::MainPlayer->GetPosition() + Dir);
	NewBullet->SetRendererOrder((int)BATTLELEVELORDER::BULLET);
	NewBullet->SetCount(Count_);
	BulletList_.push_back(NewBullet);
	Time_ = 0.03f;
}




void FloweyBattleLevel::Pattern2Update()
{
	//Count == 23
	CreateBulletCircle();
	//Count == 24


	if (true == TextFont_->GetIsAllTextOut())
	{
		if (24 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Evil_Idle");
		}
		else if (25 == Count_)
		{
			Speech_Bubble->Off();
		}


	}

	if (24 == Count_ && 3 == FloweyStateCount_)
	{
		Speech_Bubble->On();
		FloweyTalkRenderer->ChangeAnimation("Flowey_Evil");
		TextFont_->SetCount(Count_);
		TextFont_->SetTextCount(0);
		FloweyStateCount_++;
		Player::MainPlayer->Play();
		//idle상태로 안가게만들어줌
		TextFont_->IsAllTextOutFalse();
	}


	if (true == Player::MainPlayer->IsActionKeyDown() &&
		true == TextFont_->GetIsAllTextOut() &&
		24 <= Count_
		)
	{
		Count_++;  // 1
		if (25 == Count_)
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Laugh");
			FloweySound.SoundPlayOneShot("snd_floweylaugh.wav");
			TextFont_->SetTextCount(0);
			TextFont_->SetCount(Count_);
			//총알이 생성되는동안 z키를눌러도 총알이 안움직이게 해준다.
			for (size_t i = 0; i < BulletList_.size(); i++)
			{
				BulletList_[i]->SetPhaseStart();
			}
		}
	}



	//patter4로 넘어가기
	for (size_t i = 0; i < BulletList_.size(); i++)
	{
		if (true == BulletList_[i]->GetPhaseEnd())
		{
			BulletList_.clear();
			ChangeState(PatternState::Pattern4);
		}
	}


}


void FloweyBattleLevel::Pattern3Start()
{
	Angle = 0.0f;
	Time_ = 0.03f;
	Count_ = 30;
	FloweyStateCount_ = 3;
	Speech_Bubble->On();
	FloweyTalkRenderer->ChangeAnimation("Flowey_Laugh_Talk");

}


void FloweyBattleLevel::Pattern3Update()
{

	if (30 == Count_ && 3 == FloweyStateCount_)
	{
		Speech_Bubble->On();
		FloweyTalkRenderer->ChangeAnimation("Flowey_Laugh_Talk");
		TextFont_->SetCount(Count_);
		TextFont_->SetTextCount(0);
		FloweyStateCount_++;
	}

	if (true == TextFont_->GetIsAllTextOut())
	{
		FloweyTalkRenderer->ChangeAnimation("Flowey_Laugh_Idle");
	}


	if (true == Player::MainPlayer->IsActionKeyDown() && true == TextFont_->GetIsAllTextOut())
	{
		Count_++;  // 1
		TextFont_->SetCount(Count_);
		TextFont_->SetTextCount(0);
		TextFont_->IsAllTextOutFalse();
		FloweyTalkRenderer->ChangeAnimation("Flowey_Laugh_Talk");

		if (33 == Count_)
		{
			ChangeState(PatternState::Pattern2);
		}
	}
}

void FloweyBattleLevel::Pattern4Start()
{

	FloweyTalkRenderer->ChangeAnimation("Flowey_Laugh_Idle");
	Time_ = 0;
	Angle = 0;
}

void FloweyBattleLevel::Pattern4Update()
{
	Time_ += GameEngineTime::GetDeltaTime();
	if (1.0f < Time_)
	{
		FloweyTalkRenderer->ChangeAnimation("Flowey_Mad_Idle");
		Fire_->On();
	}
	
	if (true == Trigger_->GetFireDeath())
	{
		FloweyTalkRenderer->ChangeAnimation("Flowey_Hurt");

		if (FloweyHurt == false)
		{
			FloweyHurtSound.SoundPlayOneShot("floweyhitsound.mp3");
			FloweyHurt = true;
		}
		MoveDir_ += float4::LEFT *  GameEngineTime::GetDeltaTime() * 100.0f;
		MoveDir2_ = float4::UP * GameEngineTime::GetDeltaTime() * 200.0f;

		FloweyTalk->SetMove(MoveDir_ * GameEngineTime::GetDeltaTime()*10);
		FloweyTalk->SetMove(MoveDir2_);


		if (-50.0f >= FloweyTalk->GetPosition().x ||
			800.0f <= FloweyTalk->GetPosition().y)
		{
			FloweyTalk->Off();
			FloweyDeath = true;
		}


		if (true == FloweyDeath)
		{
			if (690.0f <= Undyne->GetPosition().x)
			{
				MoveDir3_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 250.0f;

				Undyne->SetMove(MoveDir3_);
			}
			else
			{
				GameEngine::GetInst().ChangeLevel("PlayLevel2");
			}
		}

	}

}



void FloweyBattleLevel::ResetAll()
{
	/*Check_ = false;
	CheckBullet_=false;
	PhaseEnd=false;
	Time_=0;
	Count_=0;
	FloweyStateCount_ = 0;
	Angle=0.0f;

	FloweyTalk->Death();;
	FloweyTalkRenderer->Death();

	Undyne->Death();
	UndyneRenderer->Death();

	Fire_->Death();
	Trigger_->Death();


	WinkStar->Death();
	WinkStarRenderer->Death();

	Speech_Bubble->Death();
	Speech_BubbleRenderer->Death();

	TextFont_->Death();
	PlayerPos_={};
	
	for (size_t i = 0; i < 5; i++)
	{
		BulletPos_[i]={};
		Bullets_[i]->Death();
		Dir[i] = {};
	}

	NewBullet->Death();
	HpBar_->Death();

	IsDeathCheck=false;
	CurState_ = PatternState::Talk;

	if (0 != BulletList_.size())
	{
		BulletList_.clear();
	}*/
}
