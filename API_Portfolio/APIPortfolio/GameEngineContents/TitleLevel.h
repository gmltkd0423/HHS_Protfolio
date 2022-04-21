#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>


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
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelEnd();
	void ChangeBackGround();
	void Init();

private:
	GameEngineSoundPlayer Bgm_;
	GameEngineActor* TitleImage_[20];
	GameEngineRenderer* TitleRenderer_[20];
	float BgmTime_;
	float Time_;
};

