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
	Hp_(20),
	MaxHp_(20),
	IsHit(false),
	Invincible(false)

{
}



Player::~Player()
{
}



void Player::Start()
{
	//�����ϼ��ִ� ��Ȳ������ bool�� true�� �����ϼ�����
	//false�� �����ϼ�����
	IsMove_ = true;

	//SetScale({ 60,60 });

	//heart ������
	{
		Heart_ = CreateRendererToScale("Heart.bmp", { 20,20 },(int)PlayerOrder::Heart);
		Heart_->SetTransColor(RGB(255, 102, 255));
		Heart_->Off();
	}


	PlayerCollision_ = CreateCollision("Player" , {20, 20});
	//frisk �ִϸ��̼�
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


	//Ű����
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
	GetDamaged();

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
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
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
	if(false == Heart_->IsUpdate())
	{
		Heart_->On();
		Frisk_->Off();
	}
	
}

void Player::IsFrisk()
{
	if (false == Frisk_->IsUpdate())
	{
		Heart_->Off();
		Frisk_->On();
	}
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


void Player::Blink()
{
	if (BlinkTimer_ > 0.0f)
	{
		IsBlink_ = true;
		//�����̴� ��ü�ð�
		BlinkTimer_ -= GameEngineTime::GetDeltaTime();
		//�����̴� Ƚ��
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
			IsHit = false;
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


	if (MapSizeX < GetLevel()->GetCameraPos().x + CamRectX)		// ī�޶� x��ġ�� �� ũ�⺸�� Ŀ����
	{
		CurCameraPos.x = MapSizeX - CamRectX;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeY < GetLevel()->GetCameraPos().y + CamRectY)		// ī�޶� y��ġ�� �� ũ�⺸�� Ŀ����
	{
		CurCameraPos.y = MapSizeY - CamRectY;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}



void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}


void Player::GetDamaged()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision_->CollisionResult("Bullet", ColList,CollisionType::Rect, CollisionType::Rect))
	{
		Hp_ -= 19;
	}

	if (true == PlayerCollision_->CollisionResult("Arrow", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		if (false == IsHit && false == Invincible)
		{
			Hp_ -= 2;
			BlinkTimer_ = 2.0f;
			IsHit = true;
		}
	}
}

void Player::CollisionCheck(float4 _value)
{
	float4 MyPos = GetPosition();
	float4 MyRightPos =float4({ 25.0f,0.0f }) + _value;
	float4 MyLeftPos = float4({ -25.0f,0.0f }) + _value;
	float4 MyBotPos =  float4({ 0.0f,30.0f })+ _value;
	float4 MyTopPos = float4({ 0.0f,-30.0f })+ _value;


	if (false == PlayerCollision_->NextPosCollisionCheck("BoxCol", MyRightPos))
	{
		_value.x = 0;
	}
	if (false == PlayerCollision_->NextPosCollisionCheck("BoxCol", MyLeftPos))
	{
		_value.x = 0;
	}
	if (false == PlayerCollision_->NextPosCollisionCheck("BoxCol", MyBotPos))
	{
		_value.y = 0;
	}
	if (false == PlayerCollision_->NextPosCollisionCheck("BoxCol", MyTopPos))
	{
		_value.y = 0;
	}
		
	
	SetMove(_value);
	
}


void Player::CheckWall(float4 _Value)
{




	float4 DownPos = GetPosition() + float4({0, 40}) + _Value;
	float4 RightPos = GetPosition() + float4({ 30,0  }) + _Value;
	float4 LeftPos = GetPosition() + float4({ -30, 0 }) + _Value;
	float4 UpPos = GetPosition() + float4({ 0, -40 }) + _Value;

	int DownColor = MapColImage_->GetImagePixel(DownPos);
	int RightColor = MapColImage_->GetImagePixel(RightPos);
	int LeftColor = MapColImage_->GetImagePixel(LeftPos);
	int UpColor = MapColImage_->GetImagePixel(UpPos);



	if (RGB(0, 0, 0) != DownColor	&&
		RGB(0, 0, 0) != RightColor &&
		RGB(0, 0, 0) != UpColor && 
		RGB(0, 0, 0) != LeftColor  )
	{
		SetMove(_Value);
	}
}


void Player::HeartOff()
{
	Heart_->Off();
}


void Player::HeartOn()
{

	Heart_->On();
}