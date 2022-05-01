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

	float Time_;
	float Timer_;
	bool IsHurt;
	bool IsIdle;
	bool IsShake;

	float4 MoveDir_;
	float4 Pos_;

public:
	void Hurt();
	void Idle();

private:
	void Shake();
};
