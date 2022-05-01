#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "UIButton.h"
#include "Undyne.h"

enum class MENUSTATE
{
	SELECTMENU,
	FIGHTMENU,
	MERCYMENU,
	ACTIONMENU,
	ITEMMENU,
};


enum class FIGHTSTATE
{
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
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
	MENUSTATE CurMenuState_;
	UIButton* Button_;
	Undyne* Undyne_;




private:
	void UIKeyMove();
	void SelectButton();

	void UISetting();


//state
private:
	void ChangeMenuState(MENUSTATE _State);
	void MenuStateUpdate();


	void MenuSelectStart();
	void MenuSelectUpdate();

	void FightMenuStart();
	void FightMenuUpdate();

	void ActionMenuStart();
	void ActionMenuUpdate();
};

