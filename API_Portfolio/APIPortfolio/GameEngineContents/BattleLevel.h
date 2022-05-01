#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "UIButton.h"
#include "Undyne.h"

enum class BATTLELEVELSTATE
{
	FLOWEY,
	NONE
};

// Ό³Έν :
class BattleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BattleLevel();
	~BattleLevel();

	// delete Function
	BattleLevel(const BattleLevel& _Other) = delete;
	BattleLevel(BattleLevel&& _Other) noexcept = delete;
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	void BattleStateUpdate(BATTLELEVELSTATE _State);

	void Battle_Flowey();
	void UISetting();
private:
	BATTLELEVELSTATE CurState_;
	UIButton* Button_;
	Undyne* Undyne_;



private:
	void CheckPlayerKey();
};

