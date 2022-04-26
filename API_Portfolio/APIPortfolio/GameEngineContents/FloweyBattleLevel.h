#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include "FloweyBullet.h"


// Ό³Έν :
class FloweyBattleLevel	:public GameEngineLevel
{
public:
	// constrcuter destructer
	FloweyBattleLevel();
	~FloweyBattleLevel();

	// delete Function
	FloweyBattleLevel(const FloweyBattleLevel& _Other) = delete;
	FloweyBattleLevel(FloweyBattleLevel&& _Other) noexcept = delete;
	FloweyBattleLevel& operator=(const FloweyBattleLevel& _Other) = delete;
	FloweyBattleLevel& operator=(FloweyBattleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
private:
	bool Check_;
	bool CheckBullet_;

private:
	GameEngineActor* FloweyTalk;
	GameEngineRenderer* FloweyTalkRenderer;
	GameEngineActor* Speech_Bubble;
	GameEngineRenderer* Speech_BubbleRenderer;
	float4 PlayerPos_;



	int IsDeathCheck;


private:
	void CreateBullet();
	void CheckDeath();
	void CheckChageLevelKey();
};

