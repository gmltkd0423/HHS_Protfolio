#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "UIButton.h"
#include "Undyne.h"
#include "Box.h"
#include "AttackBar.h"
#include "Bar.h"
#include "AttackEffect.h"
#include "BattleLevelFont.h"
#include "SpearArrow.h"
#include<GameEngineBase/GameEngineSound.h>

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
	Talk,
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
};

// ���� :
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
	MENUSTATE PrevMenuState_;
	UIButton* Button_;
	Undyne* Undyne_;
	Box* TextBox;
	BattleLevelFont* Texts;
	AttackBar* AttackBar_;
	AttackEffect* Effect_;
	Bar* Judge_Bar;
	Bar* BarList[3];
	SpearArrow* Spear_;
	float BarTime_;
	int BarCount_;
	int TextCount_;
	GameEngineSound EffectSound_;


	float4 FightButtonDir_;
	float4 ActionButtonDir_;
	float4 MercyButtonDir_;
	float4 ItemButtonDir_;

	float Timer_;
	bool HurtEnd;
	bool EffectOn;
	bool IsText;



private:
	void UIKeyMove();
	void SelectButton();
	void CheckEscape();
	void ShakeActor();

	void UISetting();
	void CreateBar();

	int Count_;

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

