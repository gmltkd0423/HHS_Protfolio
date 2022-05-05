#include "BattleLevel.h"
#include "ContentsEnums.h"
#include "BattleLevelActor.h"
#include "Player.h"
#include "Undyne.h"
#include "AttackBar.h"
#include "SoundPlayer.h"
#include "BattleLevelFont.h"
#include "UINumber.h"
#include "AttackEffect.h"
#include "HpBar.h"
#include "UINumber.h"
#include "Arrow.h"
#include "SpearUp.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

BattleLevel::BattleLevel() :
	FightButtonDir_({}),
	ActionButtonDir_({}),
	MercyButtonDir_({}),
	ItemButtonDir_({}),
	Timer_(0),
	BarTime_(0),
	BarCount_(0),
	TextCount_(0),
	EffectOn(false),
	IsText(false),
	NumberUIOn(false),
	PatternCount_(0)
{
}

BattleLevel::~BattleLevel() 
{
}

void BattleLevel::Loading()
{



	//백그라운드
	GameEngineActor* BackGround = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("BattleLevelBackGround.bmp",  (int)BATTLELEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);

	//총알 가리기용 이미지
	BackGround2 = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::TEXTBOX);
	Back2 = BackGround2->CreateRenderer("BattleLevelBackGround.bmp", (int)BATTLELEVELORDER::TEXTBOX);
	float4 Half2 = Back2->GetImage()->GetScale().Half();
	Back2->SetPivot(Half2);


	Undyne_ = CreateActor<Undyne>((int)BATTLELEVELORDER::TEXTBOX);
	Undyne_->SetPosition({ 720,185 });

	Button_ = CreateActor<UIButton>((int)BATTLELEVELORDER::BOX);
	Button_->SetPosition({ 250,680 });

	TextBox = CreateActor<Box>((int)BATTLELEVELORDER::BOX);
	TextBox->SetPosition({ 640,490 });


	AttackBar_ = CreateActor<AttackBar>((int)BATTLELEVELORDER::BOX);
	AttackBar_->SetPosition({ 640,490 });
	AttackBar_->GetRenderer()->Off();

	Effect_ = CreateActor< AttackEffect>((int)BATTLELEVELORDER::ACTOR);
	Effect_->SetPosition({ 650,185 });
	Effect_->Off();

	PlayerHpBar = CreateActor<HpBar>((int)BATTLELEVELORDER::ACTOR);
	PlayerHpBar->SetPosition({ 640,650 });


	UndyneHpBar = CreateActor < HpBar>((int)BATTLELEVELORDER::ACTOR);
	UndyneHpBar->SetPosition({ 600,210 });
	UndyneHpBar->Off();


	DamageNumber = CreateActor<UINumber>((int)BATTLELEVELORDER::ACTOR);
	DamageNumber->SetPosition({ 620,150 });
	DamageNumber->Off();


	Texts = CreateActor<BattleLevelFont>((int)BATTLELEVELORDER::ACTOR);



	//키생성
	{
		if (false == GameEngineInput::GetInst()->IsKey("UI_Left"))
		{
			GameEngineInput::GetInst()->CreateKey("UI_Left", VK_LEFT);
			GameEngineInput::GetInst()->CreateKey("UI_Right", VK_RIGHT);
			GameEngineInput::GetInst()->CreateKey("UI_Up", VK_UP);
			GameEngineInput::GetInst()->CreateKey("UI_Down", VK_DOWN);
			GameEngineInput::GetInst()->CreateKey("UI_Esc", VK_ESCAPE);
			GameEngineInput::GetInst()->CreateKey("UI_Action", 'Z');
		}
	}

	ChangeMenuState(MENUSTATE::SELECTMENU);
	ChangeFightState(FIGHTSTATE::None);
}

void BattleLevel::Update()
{
	MenuStateUpdate();
	FightStateUpdate();

	if (true == GameEngineInput::GetInst()->IsPress("ChangeDebug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

	CheckEscape();
}

void BattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	Player::MainPlayer->IsHeart();
	Player::MainPlayer->SetSpeed(150.0f);
	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->CamPosOff();
	Player::MainPlayer->SetPosition({ 191.0f, 680.0f });
	Player::MainPlayer->Stop();

	PlayerHpBar->SetActorHp(Player::MainPlayer->GetHp());
	PlayerHpBar->SetActorMaxHp(Player::MainPlayer->GetMaxHp());
	UndyneHpBar->SetActorHp(Undyne_->GetHp());
	UndyneHpBar->SetActorMaxHp(Undyne_->GetMaxHp());

	SoundPlayer::Bgm_ = GameEngineSound::SoundPlayControl("mus_x_undyne.ogg");
}

void BattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void BattleLevel::ChangeMenuState(MENUSTATE _State)
{
	if (_State != CurMenuState_)
	{
		switch (_State)
		{
		case MENUSTATE::SELECTMENU:
			MenuSelectStart();
			break;
		case MENUSTATE::FIGHTMENU:
			FightMenuStart();
			break;
		case MENUSTATE::ACTIONMENU:
			ActionMenuStart();
			break;
		case MENUSTATE::MERCYMENU:
			break;
		case MENUSTATE::ITEMMENU:
			break;
		default:
			break;
		}

		CurMenuState_ = _State;
	}
}

void BattleLevel::MenuStateUpdate()
{
	switch (CurMenuState_)
	{
	case MENUSTATE::SELECTMENU:
		MenuSelectUpdate();
		break;
	case MENUSTATE::FIGHTMENU:
		FightMenuUpdate();
		break;
	case MENUSTATE::MERCYMENU:
		break;
	case MENUSTATE::ACTIONMENU:
		ActionMenuUpdate();
		break;
	case MENUSTATE::ITEMMENU:
		break;
	default:
		break;
	}
}

void BattleLevel::ChangeFightState(FIGHTSTATE _State)
{
	if (FightState_ != _State)
	{
		switch (_State)
		{
		case FIGHTSTATE::Talk:
			TalkStart();
			break;
		case FIGHTSTATE::Pattern1:
			Pattern1Start();
			break;
		case FIGHTSTATE::Pattern2:
			Pattern2Start();
			break;
		case FIGHTSTATE::Pattern3:
			Pattern3Start();
			break;
		case FIGHTSTATE::Pattern4:
			Pattern4Start();
			break;
		case FIGHTSTATE::None:
			break;
		default:
			break;
		}
	}
	FightState_ = _State;
}

void BattleLevel::FightStateUpdate()
{

	switch (FightState_)
	{
	case FIGHTSTATE::Talk:
		TalkUpdate();
		break;
	case FIGHTSTATE::Pattern1:
		Pattern1Update();
		break;
	case FIGHTSTATE::Pattern2:
		Pattern2Update();
		break;
	case FIGHTSTATE::Pattern3:
		Pattern3Update();
		break;
	case FIGHTSTATE::Pattern4:
		Pattern4Update();
		break;
	case FIGHTSTATE::None:
		return;
	default:
		break;
	}
}

/// <summary>
/// ///////////////////////////////////////패턴 1 /////////////////////////////////////
/// </summary>

void BattleLevel::Pattern1Start()
{
	TextBox->SetState(BoxState::Battle1);
	SpearCount_ = 0;
	Timer_ = 1.0f;
	PatternTime_ = 10.0f;
	TextBox->SetIsChangeFalse();
}

void BattleLevel::CreateSpear()
{

	if (SpearCount_ == 30)
	{
		return;
	}


	Timer_ -= GameEngineTime::GetDeltaTime();
	if (0.0f <= Timer_)
	{
		return;

	}


	GameEngineRandom Ran;
	float Posx = Ran.RandomFloat(400.0f,800.0f);
	float Posy = Ran.RandomFloat(300.0f, 650.0f);
	SpearArrow* Spear = CreateActor<SpearArrow>((int)BATTLELEVELORDER::ACTOR);
	Spear->SetPosition({ Posx,Posy });
	SpearCount_++;
	Timer_ = 1.0f;
}



void BattleLevel::Pattern1Update()
{
	if (true == TextBox->GetIsChange())
	{
		Player::MainPlayer->SetPosition(TextBox->GetPosition());
		Player::MainPlayer->Play();
		TextBox->SetIsChangeFalse();
		Undyne_->GetRenderer()->ChangeAnimation("Idle");
		Undyne_->GetRenderer()->SetAlpha(150);
		TextBox->SetState(BoxState::None);
	}

	PlayerHpBar->SetActorHp(Player::MainPlayer->GetHp());


	if (false == TextBox->GetIsChange())
	{
		CreateSpear();
	}

	PatternTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= PatternTime_)
	{
		ChangeFightState(FIGHTSTATE::Talk);
	}
}


/// <summary>
/// /////////////////패턴2 /////////////////////////////////////////////
/// </summary>
void BattleLevel::Pattern2Start()
{
	TextBox->SetState(BoxState::Battle2);
	SpearUpCount_ = 0;
	Timer_ = 1.3f;
	PatternTime_ = 10.0f;
	float4 Half2 = Back2->GetImage()->GetScale().Half();
	Back2->SetPivot({ Half2.x,Half2.y + 530.0f });
	TextBox->GetRenderer()->SetTransColor(RGB(0, 0, 0));
}

void BattleLevel::CreateUpSpear()
{
	if (SpearUpCount_ == 10)
	{
		return;
	}

	Timer_ -= GameEngineTime::GetDeltaTime();
	if (0.0f <= Timer_)
	{
		return;

	}

	SpearUpPos[0] = { 607,600 };
	SpearUpPos[1] = { 640,600 };
	SpearUpPos[2] = { 673,600 };

	GameEngineRandom Ran;
	Ran.RandomInt(0, 2);
	int RandomInt = Ran.RandomInt(0, 2);


	SpearUp* Spear = CreateActor<SpearUp>((int)BATTLELEVELORDER::UPARROW);
	Spear->SetPosition(SpearUpPos[RandomInt]);
	SpearUpCount_++;
	Timer_ = 1.3f;

}



void BattleLevel::Pattern2Update()
{

	if (true == TextBox->GetIsChange())
	{
		Player::MainPlayer->SetPosition(TextBox->GetPosition());
		Player::MainPlayer->Play();
		TextBox->SetIsChangeFalse();
		Undyne_->GetRenderer()->ChangeAnimation("Idle");
		Undyne_->GetRenderer()->SetAlpha(150);
		TextBox->SetState(BoxState::None);
	}

	PlayerHpBar->SetActorHp(Player::MainPlayer->GetHp());

	if (false == TextBox->GetIsChange())
	{
		CreateUpSpear();
	}
	

	if (SpearUpCount_ == 10)
	{
		float4 Half2 = Back2->GetImage()->GetScale().Half();
		Back2->SetPivot( Half2 );
		TextBox->GetRenderer()->SetTransColor(RGB(255, 0, 0));
		ChangeFightState(FIGHTSTATE::Talk);
	}

}


//패턴3/////////////////////////////////////////////////////////////////////
void BattleLevel::Pattern3Start()
{
	TextBox->SetState(BoxState::Battle3);
	ArrowCount_ = 0;
	Timer_ = 2.0f;
	PatternTime_ = 2.0f;
}
void BattleLevel::CreateArrow()
{
	if (ArrowCount_ == 20)
	{
		return;
	}

	Timer_ -= GameEngineTime::GetDeltaTime();
	if (0 <= Timer_)
	{
		return;
	}

	Arrow* Arrow_ = CreateActor<Arrow>((int)BATTLELEVELORDER::ACTOR);
	ArrowCount_++;
	Timer_ = 0.6f;
}
void BattleLevel::Pattern3Update()
{
	if (true == TextBox->GetIsChange())
	{
		Player::MainPlayer->SetPosition(TextBox->GetPosition());
		TextBox->SetIsChangeFalse();
		Undyne_->GetRenderer()->ChangeAnimation("Idle");
		Undyne_->GetRenderer()->SetAlpha(150);
		TextBox->SetState(BoxState::None);
	}

	PlayerHpBar->SetActorHp(Player::MainPlayer->GetHp());

	if (false == TextBox->GetIsChange())
	{
		CreateArrow();
	}

	if (ArrowCount_ >= 20)
	{
		PatternTime_ -= GameEngineTime::GetDeltaTime();
		if(0 >= PatternTime_)
		{
			ChangeFightState(FIGHTSTATE::Talk);
		}
	}

}


//패턴4//////////////////////////////////////////////////////////////////////////////
void BattleLevel::Pattern4Start()
{
}

void BattleLevel::Pattern4Update()
{
}




void BattleLevel::TalkStart()
{
	Texts->IsAllTextOutFalse();
	Player::MainPlayer->HeartOff();
	Player::MainPlayer->Stop();
	TextBox->SetState(BoxState::Text);
	Undyne_->GetRenderer()->SetAlpha(255);
	TextCount_ = 1;
}




void BattleLevel::TalkUpdate()
{

	//if (TextCount_ == 1)
	//{
	//	Texts->SetCount(TextCount_);
	//	Texts->IsAllTextOutFalse();
	//	Texts->SetTextCount(0);
	//	TextCount_++;
	//}

	if (true == TextBox->GetIsChange())
	{
		Texts->On();
		Texts->SetCount(TextCount_);
		Texts->SetTextCount(0);
		TextBox->SetIsChangeFalse();
		TextBox->SetState(BoxState::None);
	}


	if (true == Texts->GetIsAllTextOut())
	{
		if (true == Player::MainPlayer->IsActionKeyDown())
		{
			Texts->IsAllTextOutFalse();
			ChangeMenuState(MENUSTATE::SELECTMENU);
			ChangeFightState(FIGHTSTATE::None);
		}
	}

}





void BattleLevel::UISetting()
{
}





//판정바
void BattleLevel::CreateBar()
{
	if (3 <= Count_)
	{
		return;
	}

	Timer_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Timer_)
	{
		Judge_Bar = CreateActor<Bar>((int)BATTLELEVELORDER::ACTOR);
		Judge_Bar->SetPosition({ 100,490 });
		BarList[Count_] = Judge_Bar;
		Count_++;
		if (Count_ == 1)
		{
			Timer_ = 0.1f;
		}
		else
		{
			Timer_ = 0.2f;
		}
	}


}


void BattleLevel::UIKeyMove()
{

	if (true == GameEngineInput::GetInst()->IsDown("UI_Left"))
	{
		if (191.0f >= Player::MainPlayer->GetPosition().x)
		{
			Player::MainPlayer->SetPosition({ 191,680 });
			return;
		}
		float4 Dir = Player::MainPlayer->GetPosition();
		Dir.x -= 265.0f;
		Player::MainPlayer->SetPosition(Dir);
		EffectSound_.SoundPlayOneShot("snd_squeak.wav");
	}

	if (true == GameEngineInput::GetInst()->IsDown("UI_Right"))
	{
		if (986.0f <= Player::MainPlayer->GetPosition().x)
		{
			Player::MainPlayer->SetPosition({ 986,680 });
			return;
		}

		float4 Dir = Player::MainPlayer->GetPosition();
		Dir.x += 265.0f;
		Player::MainPlayer->SetPosition(Dir);
		EffectSound_.SoundPlayOneShot("snd_squeak.wav");

	}
}

void BattleLevel::SelectButton()
{
	//Fight버튼을 눌럿다면
	if (true == Button_->GetbFightButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		PrevMenuState_ = MENUSTATE::FIGHTMENU;
		ChangeMenuState(MENUSTATE::FIGHTMENU);
		FightButtonDir_ = Player::MainPlayer->GetPosition();
		EffectSound_.SoundPlayOneShot("snd_select.wav");
	}
	else if (true == Button_->GetbActionButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		PrevMenuState_ = MENUSTATE::ACTIONMENU;
		ChangeMenuState(MENUSTATE::ACTIONMENU);
		ActionButtonDir_ = Player::MainPlayer->GetPosition();
		EffectSound_.SoundPlayOneShot("snd_select.wav");
	}
	else if (true == Button_->GetbMercyButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		PrevMenuState_ = MENUSTATE::MERCYMENU;
		ChangeMenuState(MENUSTATE::MERCYMENU);
		MercyButtonDir_ = Player::MainPlayer->GetPosition();
		EffectSound_.SoundPlayOneShot("snd_select.wav");
	}
	else if (true == Button_->GetbItemButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		PrevMenuState_ = MENUSTATE::ITEMMENU;
		ChangeMenuState(MENUSTATE::ITEMMENU);
		ItemButtonDir_ = Player::MainPlayer->GetPosition();
		EffectSound_.SoundPlayOneShot("snd_select.wav");
	}

}

void BattleLevel::CheckEscape()
{
	if (MENUSTATE::ACTIONMENU == CurMenuState_	||
		MENUSTATE::FIGHTMENU == CurMenuState_	||
		MENUSTATE::MERCYMENU == CurMenuState_ || 
		MENUSTATE::ITEMMENU == CurMenuState_)
	{
		if (true == GameEngineInput::GetInst()->IsDown("UI_Esc"))
		{
			EffectSound_.SoundPlayOneShot("snd_select.wav");
			if (MENUSTATE::FIGHTMENU == CurMenuState_)
			{
				AttackBar_->Off();
				Judge_Bar->Off();
				for (size_t i = 0; i < 3; i++)
				{
					if (nullptr != BarList[i])
					{
						BarList[i]->Death();
					}
				}
			}


			PrevMenuState_ = CurMenuState_;
			ChangeMenuState(MENUSTATE::SELECTMENU);

			
		}
	}


}

void BattleLevel::ShakeActor()
{
	Button_->SetIsShakeTrue();
	TextBox->SetIsShakeTrue();
	AttackBar_->SetIsShakeTrue();
}

void BattleLevel::MenuSelectStart()
{
	if (MENUSTATE::FIGHTMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(FightButtonDir_);
	}
	else if (MENUSTATE::ACTIONMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(ActionButtonDir_);
	}
	else if (MENUSTATE::MERCYMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(MercyButtonDir_);
	}
	else if (MENUSTATE::ITEMMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(ItemButtonDir_);

	}

	Texts->Off();
	Player::MainPlayer->HeartOn();
	Player::MainPlayer->Stop();
}


void BattleLevel::MenuSelectUpdate()
{
	UIKeyMove();
	SelectButton();
}

void BattleLevel::FightMenuStart()
{
	Count_ = 0;
	AttackBar_->GetRenderer()->On();
	Bar::BarCount_ = 0;
	Bar::KeyDownCount_ = 0;
	Bar::Damage_ = 0;
	Timer_ = 0.8f;
	HurtEnd = false;
	BarCount_ = 0;
	EffectOn = false;
	IsText = false;
	ShakeTimer_ = 0.5f;
	Texts->Off();
}

void BattleLevel::FightMenuUpdate()
{
	//
	CreateBar();


	//이펙트가 나오고
	if (true == EffectOn)
	{
		Effect_->On();
		ShakeActor();
		Timer_ -= GameEngineTime::GetDeltaTime();
		//약간의 딜레이후 효과들
		if (0 >= Timer_)
		{
			EffectSound_.SoundPlayOneShot("snd_damage.wav");
			Effect_->Off();
			Undyne_->Hurt();
			Undyne_->GetDamaged(Bar::Damage_);
			UndyneHpBar->On();
			UndyneHpBar->SetActorHp(Undyne_->GetHp());
			DamageNumber->SetValue(Bar::Damage_);
			DamageNumber->On();
			HurtEnd = true;  // 흔들리는게 다끝나고나면
			EffectOn = false;
		}
	}

	//상자 모양 변경
	// 
	//넘버UI 위아래로 이동
	{
		if (HurtEnd == true)
		{
			float4 MoveDir = float4::UP * GameEngineTime::GetDeltaTime() * 200.0f;
			DamageNumber->SetMove(MoveDir);
			if (120 >= DamageNumber->GetPosition().y)
			{
				HurtEnd = false;
				NumberUIOn = true;
			}
		}

		if (NumberUIOn == true)
		{
			float4 MoveDir = float4::DOWN * GameEngineTime::GetDeltaTime() * 200.0f;
			DamageNumber->SetMove(MoveDir);
			if (180 <= DamageNumber->GetPosition().y)
			{
				//언다인 피가 0이하로가면 
			/*	if (0 >= Undyne_->GetHp())
				{

				}*/

				NumberUIOn = false;
				AttackBar_->GetRenderer()->Off();
				DamageNumber->Off();
				UndyneHpBar->Off();

				if (PatternCount_ == 0)
				{
					ChangeFightState(FIGHTSTATE::Pattern1);
					PatternCount_++;
				}
				else if (PatternCount_ == 1)
				{
					PatternCount_++;
					ChangeFightState(FIGHTSTATE::Pattern2);
				}
				else if(PatternCount_==2)
				{
					ChangeFightState(FIGHTSTATE::Pattern3);
				}
				else
				{
					ChangeFightState(FIGHTSTATE::Pattern1);
				}
			}
		}
	}

	//바 3번입력
	if (3 <= Count_ && 6>Count_ && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		BarCount_ = Count_ - 3;
		BarList[BarCount_]->SetIsKeyDownTrue();
		Count_++;

		if (BarCount_ == 2)
		{
			EffectOn = true;
		}
	}





}

void BattleLevel::ActionMenuStart()
{
}

void BattleLevel::ActionMenuUpdate()
{
	int a = 0;
}



