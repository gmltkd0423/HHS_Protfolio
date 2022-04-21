#include "Flowey.h"
#include <GameEngine/GameEngineRenderer.h>

Flowey::Flowey() 
{
}

Flowey::~Flowey() 
{
}

void Flowey::Start()
{
	AniRender_ = CreateRenderer();
	SetScale({ 60,60 });
	AniRender_->SetScale({ 60,60 });

	AniRender_->CreateAnimation("Flowey_Idle.bmp", "Idle", 0, 1, 0.15f, true);
	AniRender_->SetTransColor(RGB(255, 255, 255));

	AniRender_->ChangeAnimation("Idle");
}

void Flowey::Update()
{
}

void Flowey::Render()
{
}
