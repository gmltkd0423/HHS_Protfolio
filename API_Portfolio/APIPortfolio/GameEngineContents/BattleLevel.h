#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "UIButton.h"
#include "Undyne.h"
#include "Box.h"
#include "AttackBar.h"
#include "Bar.h"
#include "AttackEffect.h"
#include "BattleLevelFont.h"
#include "UINumber.h"
#include "SpearArrow.h"
#include "HpBar.h"
#include "SpearUp.h"
#include "UINumber.h"
#include "HpText.h"
#include "SpearCircle.h"
#include "Shield.h"
#include<GameEngineBase/GameEngineSound.h>

enum class MENUSTATE
{
	SELECTMENU,
	FIGHTMENU,
	MERCYMENU,
	ACTIONMENU,
	ITEMMENU,
	NONE
};


enum class FIGHTSTATE
{
	None,
	Talk,
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
	End
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
	MENUSTATE PrevMenuState_;

	FIGHTSTATE FightState_;
	UIButton* Button_;
	Undyne* Undyne_;
	Box* TextBox;
	BattleLevelFont* Texts;
	AttackBar* AttackBar_;
	AttackEffect* Effect_;
	Bar* Judge_Bar;
	Bar* BarList[3];
	SpearArrow* Spear_;
	HpBar* PlayerHpBar;
	HpBar* UndyneHpBar;
	UINumber* DamageNumber;
	Shield* Shield_;
	HpText* HpText_;

	GameEngineActor* BackGround2;
	GameEngineRenderer* Back2;

	float Angle;
	float BarTime_;
	int BarCount_;
	int TextCount_;
	int ArrowCount_;
	int CircleSpearCount_;
	bool RandomPattern;

	bool IsCreateSpear;

	int PatternCount_;
	float ShakeTimer_;
	GameEngineSound EffectSound_;


	float4 FightButtonDir_;
	float4 ActionButtonDir_;
	float4 MercyButtonDir_;
	float4 ItemButtonDir_;

	float Timer_;
	bool HurtEnd;
	bool EffectOn;
	bool IsText;
	bool NumberUIOn;
	int AttackCount;
	int MercyCount;
	int ItemCount;
	bool PlayerInvin;
	float SpinAngle;

private:
	void UIKeyMove();
	void SelectButton();
	void CheckEscape();
	void ShakeActor();


	void CreateBar();
	void CreateSpear();
	void CreateUpSpear();
	void CreateCircleSpear();
	void CreateArrow();

	int Count_;
	int SpearCount_;
	int SpearUpCount_;
	bool IsEnd;
	float PatternTime_;
	int ActionCount;
	float4 SpearUpPos[3];
	float4 PrevPos;

//state
private:
	void ChangeMenuState(MENUSTATE _State);
	void MenuStateUpdate();

	void ChangeFightState(FIGHTSTATE _State);
	void FightStateUpdate();

	void Pattern1Start();
	void Pattern1Update();

	void Pattern2Start();
	void Pattern2Update();

	void Pattern3Start();
	void Pattern3Update();

	void Pattern4Start();
	void Pattern4Update();

	void TalkStart();
	void TalkUpdate();

	void EndStart();
	void EndUpdate();


	void MenuSelectStart();
	void MenuSelectUpdate();

	void FightMenuStart();
	void FightMenuUpdate();

	void ActionMenuStart();
	void ActionMenuUpdate();

	void MercyMenuStart();
	void MercyMenuUpdate();

	void ItemMenuStart();
	void ItemMenuUpdate();

	
};

