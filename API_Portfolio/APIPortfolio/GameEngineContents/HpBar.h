#pragma once
#include <GameEngine/GameEngineActor.h>

enum class HpBarState
{
	Player,
	Undyne
};


// Ό³Έν :
class HpBar	: public GameEngineActor
{
public:
	// constrcuter destructer
	HpBar();
	~HpBar();

	// delete Function
	HpBar(const HpBar& _Other) = delete;
	HpBar(HpBar&& _Other) noexcept = delete;
	HpBar& operator=(const HpBar& _Other) = delete;
	HpBar& operator=(HpBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* HpBarRed_;
	GameEngineRenderer* HpBarYellow_;
	HpBarState CurState_;


	int Hp_;
	int MaxHp_;

	int ActorHp;
	int ActorMaxHp;

public:
	inline void SetState(HpBarState _State)
	{
		CurState_ = _State;
	}


	inline void SetActorHp(int _Hp)
	{
		ActorHp = _Hp;
	}


	inline void SetActorMaxHp(int _MaxHp)
	{
		ActorMaxHp = _MaxHp;
	}


};

