#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include "FloweyBullet.h"
#include "FloweyBattleLevelFont.h"
#include <GameEngineBase/GameEngineSound.h>


enum class PatternState
{
	Talk,
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4
};

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
	float Time_;
	int Count_;
	int FloweyStateCount_;
	float Angle;

private:
	GameEngineActor* FloweyTalk;
	GameEngineRenderer* FloweyTalkRenderer;

	GameEngineActor* WinkStar;
	GameEngineRenderer* WinkStarRenderer;

	GameEngineActor* Speech_Bubble;
	GameEngineRenderer* Speech_BubbleRenderer;

	FloweyBattleLevelFont* TextFont_;
	float4 PlayerPos_;

	GameEngineSound FloweySound;

	float4 BulletPos_[5];
	FloweyBullet* Bullets_[5];
	FloweyBullet* NewBullet;

	float4 Dir[5];
	int IsDeathCheck;
	PatternState CurState_;


private:

	void CheckChangeLevelKey();

	void ChangeState(PatternState _State);
	void StateUpdate();

	void CreateBulletCircle();

	void TalkStart();
	void TalkUpdate();
	
	void Pattern1Start();
	void Pattern1Update();

	void Pattern2Start();
	void Pattern2Update();
};

