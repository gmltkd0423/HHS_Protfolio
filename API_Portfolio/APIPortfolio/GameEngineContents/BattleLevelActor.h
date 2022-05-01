#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class BattleLevelActor	:public GameEngineActor
{
public:
	// constrcuter destructer
	BattleLevelActor();
	~BattleLevelActor();

	// delete Function
	BattleLevelActor(const BattleLevelActor& _Other) = delete;
	BattleLevelActor(BattleLevelActor&& _Other) noexcept = delete;
	BattleLevelActor& operator=(const BattleLevelActor& _Other) = delete;
	BattleLevelActor& operator=(BattleLevelActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;
private:

};

