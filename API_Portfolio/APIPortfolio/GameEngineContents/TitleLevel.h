#pragma once
#include <GameEngine/GameEngineLevel.h>
#include<GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
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
	void LevelChangeStart() override;
	void LevelEnd();

private:
	GameEngineSoundPlayer Bgm_;
	float BgmTime_;
};

