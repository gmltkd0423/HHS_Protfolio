#include "TitleTime.h"
#include <GameEngineBase/GameEngineTime.h>

float TitleTime::TitleTime_ = 0.0f;

TitleTime::TitleTime() 
{
}

TitleTime::~TitleTime() 
{
}

void TitleTime::Start()
{

}

void TitleTime::Update()
{
	TitleTime_ += GameEngineTime::GetDeltaTime();
}

