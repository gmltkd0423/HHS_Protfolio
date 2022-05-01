#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class BattleLevelFont :public GameEngineActor
{
public:
	// constrcuter destructer
	BattleLevelFont();
	~BattleLevelFont();

	// delete Function
	BattleLevelFont(const BattleLevelFont& _Other) = delete;
	BattleLevelFont(BattleLevelFont&& _Other) noexcept = delete;
	BattleLevelFont& operator=(const BattleLevelFont& _Other) = delete;
	BattleLevelFont& operator=(BattleLevelFont&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};
