#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>


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

};

