#pragma once
#include <GameEngine/GameEngineActor.h>
#include<GameEngine/GameEngineImage.h>

// Ό³Έν :
enum class PlayerState
{
	Idle,
	Move
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
	PlayerState CurState_;
	GameEngineRenderer* AniRender_;
	GameEngineImage* MapColImage_;
	float4 MoveDir_;
	std::string AnimationName_;
	std::string DirName_;

	bool IsMoveKey();
private:
	void Start() override;
	void Update() override;
	void Render() override;

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();


private:
	void CameraLock();
	bool IsKeyPress();
	bool IsKeyDown();
	bool IsKeyUp();
	void CheckWall(float4 _Value);

private:

	//fsm
	void IdleStart();
	void IdleUpdate();

	void MoveStart();
	void MoveUpdate();
	
};

