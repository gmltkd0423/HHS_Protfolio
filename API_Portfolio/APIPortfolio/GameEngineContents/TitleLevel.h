#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineFont.h>
#include "FadeInOut.h"


// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
	friend class TitleImage;
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevle) override;
	void ChangeBackGround();
	void FadeInOutBackGround();
	void Init();
	void CheckChangeLevelKey();


private:
	FadeInOut* FadeEffect_;
	GameEngineActor* TitleImage_[20];
	GameEngineRenderer* TitleRenderer_[20];
	GameEngineActor* Text_;

	float Time_;
	int Count_;
};

