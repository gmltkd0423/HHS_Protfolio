#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>


// Ό³Έν :
class AttackBar :public GameEngineActor
{
public:
	// constrcuter destructer
	AttackBar();
	~AttackBar();

	// delete Function
	AttackBar(const AttackBar& _Other) = delete;
	AttackBar(AttackBar&& _Other) noexcept = delete;
	AttackBar& operator=(const AttackBar& _Other) = delete;
	AttackBar& operator=(AttackBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* AttackBarRenderer;
	GameEngineImage* ColMap;



};
