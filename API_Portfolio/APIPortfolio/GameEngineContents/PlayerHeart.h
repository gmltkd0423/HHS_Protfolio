#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class PlayerHeart	:public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHeart();
	~PlayerHeart();

	// delete Function
	PlayerHeart(const PlayerHeart& _Other) = delete;
	PlayerHeart(PlayerHeart&& _Other) noexcept = delete;
	PlayerHeart& operator=(const PlayerHeart& _Other) = delete;
	PlayerHeart& operator=(PlayerHeart&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

