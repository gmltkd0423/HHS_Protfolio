#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCollision.h>

Player* Player::MainPlayer = nullptr;


Player::Player() :
	MoveDir_(float4::ZERO),
	IsMove_(false),
	MapSizeX(0),
	MapSizeY(0),
	CamRectX(0),
	CamRectY(0),
	CamPos_(true),
	Speed_(500.0f),
	IsBlink_(false),
	BlinkTime_(0),
	BlinkTimer_(0),
	Time_(0),
	IsChange_(false),
	Hp_(20)

{
}



Player::~Player()
{
}



void Player::Start()
{
	//움직일수있는 상황에대한 bool값 true면 움직일수있음
	//false면 움직일수없음
	IsMove_ = true;

	//SetScale({ 60,60 });

	//heart 랜더러
	{
		Heart_ = CreateRendererToScale("Heart.bmp", { 20,20 },(int)PlayerOrder::Heart);
		Heart_->SetTransColor(RGB(255, 102, 255));
		Heart_->Off();
	}


	PlayerCollision_ = CreateCollision("Player" , {20, 20});
	//frisk 애니메이션
	{
		Frisk_ = CreateRenderer((int)PlayerOrder::Frisk);
		Frisk_->SetScale({ 70,90 });

		Frisk_->CreateAnimation("Move_Down.bmp", "MoveDown", 0, 3, 0.15f, true);
		Frisk_->CreateAnimation("Move_Down.bmp", "MoveDownIdle", 0, 0, 0.15f, true);
		Frisk_->CreateAnimation("Move_Up.bmp", "MoveUp", 0, 3, 0.15f, true);
		Frisk_->CreateAnimation("Move_Up.bmp", "MoveUpIdle", 0, 0, 0.15f, true);
		Frisk_->CreateAnimation("Move_Right.bmp", "MoveRight", 0, 1, 0.15f, true);
		Frisk_->CreateAnimation("Move_Right.bmp", "MoveRightIdle", 0, 0, 0.15f, true);
		Frisk_->CreateAnimation("Move_Left.bmp", "MoveLeft", 0, 1, 0.15f, true);
		Frisk_->CreateAnimation("Move_Left.bmp", "MoveLeftIdle", 0, 0, 0.15f, true);
		Frisk_->ChangeAnimation("MoveDownIdle");
		Frisk_->SetTransColor(RGB(255, 255, 255));

	}


	//키생성
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Action", 'Z');
	}

	CurState_ = PlayerState::Idle;



	LevelRegist("MainPlayer");
}


void Player::Update()
{
	if (true == PlayerCollision_->CollisionCheck("Bullet"))
	{
		Hp_ -= 19;
	}

	StateUpdate();

	if (CamPos_ == true)
	{
		GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());
		CameraLock();
	}

	Blink();
	ChangeToHeart();


}



void Player::Render()
{
	//DebugRectRender();
}

void Player::CollisionImage(const std::string& _Name)
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find(_Name);

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}
}

void Player::ChangeState(PlayerState _State)
{

	if (_State != CurState_)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		default:
			break;
		}

		CurState_ = _State;
	}
}

void Player::StateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	default:
		break;
	}
}

void Player::IsHeart()
{
	Heart_->On();
	Frisk_->Off();
}

void Player::IsFrisk()
{
	Heart_->Off();
	Frisk_->On();
}

bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown("Action"))
	{
		return false;
	}
	return true;
}


bool Player::IsPressAnyMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight")
		)
	{
		return false;
	}
	return true;
}

bool Player::IsKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsDown("MoveUp") &&
		false == GameEngineInput::GetInst()->IsDown("MoveDown") &&
		false == GameEngineInput::GetInst()->IsDown("MoveRight") 
		)
	{
		return false;
	}
	return true;
}

bool Player::IsKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") 
		)
	{
		return false;
	}
	return true;
}

bool Player::IsKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsUp("MoveUP") &&
		false == GameEngineInput::GetInst()->IsUp("MoveDown") &&
		false == GameEngineInput::GetInst()->IsUp("MoveRight") 
		)
	{
		return false;
	}

	return true;
}

void Player::CheckWall(float4 _Value)
{
	float4 NextPos = GetPosition() + _Value;
	int Color = MapColImage_->GetImagePixel(NextPos);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
}

void Player::Blink()
{
	if (BlinkTimer_ > 0.0f)
	{
		IsBlink_ = true;
		//깜빡이는 전체시간
		BlinkTimer_ -= GameEngineTime::GetDeltaTime();
		//깜빡이는 횟수
		BlinkTime_ += GameEngineTime::GetDeltaTime();
		if (BlinkTime_>=0.2f)
		{
			BlinkTime_ = 0.0f;
			Heart_->SetAlpha(255);
		}
		else if(BlinkTime_>=0.1f)
		{
			Heart_->SetAlpha(0);
		}

		if (BlinkTimer_ <= 0.0f)
		{
			BlinkTimer_ = 0.0f;
			BlinkTime_ = 0.0f;
			Heart_->SetAlpha(255);
			IsBlink_ = false;
		}
	}
}

void Player::ChangeToHeart()
{
	if (true == IsChange_)
	{
		if (false == Heart_->IsUpdate())
		{
			Heart_->On();
			SetBlinkTimer(1.0f);
		}
		Time_ += GameEngineTime::GetDeltaTime();

		if (1.0f <= Time_)
		{
			Frisk_->Off();
			IsChange_ = false;
		}
	}

}



void Player::Play()
{
	IsMove_ = true;
}


void Player::Stop()
{
	IsMove_ = false;
	MoveDir_ = float4::ZERO;
	Frisk_->ChangeAnimation("MoveUpIdle");
}

void Player::CameraLock()
{

	if (strcmp(GetLevel()->GetNameConstPtr(), "PlayLevel") == 0)
	{
		MapSizeX = 2300;
		MapSizeY = 1000;
		CamRectX = 1280;
		CamRectY = 720;
	}
	else if (strcmp(GetLevel()->GetNameConstPtr(), "PlayLevel2") == 0)
	{
		MapSizeX = 1280;
		MapSizeY = 1500;
		CamRectX = 1280;
		CamRectY = 720;
	}

	float4 CurCameraPos = GetLevel()->GetCameraPos();

	if (0 > GetLevel()->GetCameraPos().x)	
	{
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)		
	{
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}


	if (MapSizeX < GetLevel()->GetCameraPos().x + CamRectX)		// 카메라 x위치가 맵 크기보다 커지면
	{
		CurCameraPos.x = MapSizeX - CamRectX;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeY < GetLevel()->GetCameraPos().y + CamRectY)		// 카메라 y위치가 맵 크기보다 커지면
	{
		CurCameraPos.y = MapSizeY - CamRectY;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}



void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}