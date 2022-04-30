#include "Fire.h"
#include "GameEngineBase/GameEngineTime.h"
#include "ContentsEnums.h"
#include "GameEngine/GameEngineRenderer.h"

Fire::Fire()	:
	BlinkTimer_(1.5f),
	BlinkTime_(0),
	IsBlink_(false)
{
}

Fire::~Fire()
{
}

void Fire::Start()
{
	FireRenderer = CreateRenderer((int)BATTLELEVELORDER::BULLET);
	FireRenderer->CreateAnimation("Fire.bmp", "Fire", 0, 3, 0.1f, true);
	FireRenderer->SetAlpha(0);
}

void Fire::Update()
{
	Blink();

	if (BlinkTimer_ > 0.0f)
	{
		MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 0.5f;
		SetMove(MoveDir_);
	}

}

void Fire::Render()
{
}

void Fire::Blink()
{
	if (BlinkTimer_ > 0.0f)
	{
		IsBlink_ = true;
		//±ôºýÀÌ´Â ÀüÃ¼½Ã°£
		BlinkTimer_ -= GameEngineTime::GetDeltaTime();
		//±ôºýÀÌ´Â È½¼ö
		BlinkTime_ += GameEngineTime::GetDeltaTime();
		if (BlinkTime_ >= 0.2f)
		{
			BlinkTime_ = 0.0f;
			FireRenderer->SetAlpha(255);
		}
		else if (BlinkTime_ >= 0.1f)
		{
			FireRenderer->SetAlpha(0);
		}

		if (BlinkTimer_ <= 0.0f)
		{
			BlinkTimer_ = 0.0f;
			BlinkTime_ = 0.0f;
			FireRenderer->SetAlpha(255);
			IsBlink_ = false;
		}
	}
}
