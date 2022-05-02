#include "AttackEffect.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

AttackEffect::AttackEffect()
{
}

AttackEffect::~AttackEffect() 
{
}

void AttackEffect::Start()
{
	EffectRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	EffectRenderer->CreateAnimation("Attack_Effect.bmp", "Effect", 0, 4, 0.05f, true);
	EffectRenderer->ChangeAnimation("Effect");
	EffectRenderer->SetTransColor(RGB(241, 95, 241));
}

void AttackEffect::Update()
{
}

void AttackEffect::Render()
{
}

void AttackEffect::Shake()
{


}
