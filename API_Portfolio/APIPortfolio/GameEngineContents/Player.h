#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
enum PlayerState
{
	Idle,
	Attck,
	Move,
	Max,
};

class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();
};

