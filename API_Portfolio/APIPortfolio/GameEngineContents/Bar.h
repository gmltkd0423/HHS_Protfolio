#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>


// Ό³Έν :
class Bar :public GameEngineActor
{
public:
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
	static int Damage_;
	float4 MoveDir_;
	void CheckJudgMent();

	bool IsKeyDown;

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
};
