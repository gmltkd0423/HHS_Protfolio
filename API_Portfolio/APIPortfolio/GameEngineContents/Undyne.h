#pragma once
#include <GameEngine/GameEngineActor.h>



// Ό³Έν :
class Undyne :public GameEngineActor
{
public:
	// constrcuter destructer
	Undyne();
	~Undyne();

	// delete Function
	Undyne(const Undyne& _Other) = delete;
	Undyne(Undyne&& _Other) noexcept = delete;
	Undyne& operator=(const Undyne& _Other) = delete;
	Undyne& operator=(Undyne&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* UndyneRenderer;
	int Hp;
	int MaxHp;


	float Time_;
	float Timer_;
	bool IsHurt;
	bool IsIdle;
	bool IsShake;
	bool IsDamaged;

	bool IsRight;
	bool IsLeft;

	float4 MoveDir_;
	float4 Pos_;
	float4 RightPos_;
	float4 LeftPos_;

public:
	void Hurt();
	void Idle();
	void GetDamaged(int _Damage);

	GameEngineRenderer* GetRenderer()
	{
		return UndyneRenderer;
	}
	bool GetIsHurt()
	{
		return IsHurt;
	}

	bool GetIsIdle()
	{
		return IsIdle;
	}

	int GetHp()
	{
		return Hp;
	}

	int GetMaxHp()
	{
		return MaxHp;
	}

private:
	void Shake();

};
