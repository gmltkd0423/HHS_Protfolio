#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>


// ???? :
class Bar :public GameEngineActor
{
public:
	static int BarCount_;
	static int KeyDownCount_;
	static int Damage_;
	// constrcuter destructer
	Bar();
	~Bar();

	// delete Function
	Bar(const Bar& _Other) = delete;
	Bar(Bar&& _Other) noexcept = delete;
	Bar& operator=(const Bar& _Other) = delete;
	Bar& operator=(Bar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* BarRenderer;
	GameEngineImage* AttackBar_ColMap;
	float4 MoveDir_;
	void CheckJudgMent();
	int MyBarCount_;
	bool IsKeyDown;
	//bool KeyCheck_;

	float Timer_;
public:
	inline void SetDamage(int _Damage)
	{
		Damage_ += _Damage;
	}

	int GetDamage()
	{
		return Damage_;
	}


	void SetIsKeyDownTrue()
	{
		IsKeyDown = true;;
	}
};
