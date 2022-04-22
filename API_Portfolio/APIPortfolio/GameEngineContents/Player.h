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
	static Player* MainPlayer;
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

	bool IsMove_;
	bool CamPos_;
	float MapSizeX;
	float MapSizeY;
	float CamRectX;
	float CamRectY;
private:
	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();
	void Play();
	void Stop();
	bool IsActionKeyDown();

	bool GetIsMove()
	{
		return IsMove_;
	}

	float4 GetMoveDir()
	{
		return MoveDir_;
	}

	void SetColImage(GameEngineImage* _Image)
	{
		MapColImage_ = _Image;
	}

	void CamPosOff()
	{
		CamPos_ = false;
	}

	void CamPosOn()
	{
		CamPos_ = true;
	}

	void CollisionImage(const std::string& _Name);
	GameEngineImage* GetColImage()
	{
		return MapColImage_;
	}

	GameEngineRenderer* GetAniRender()
	{
		return AniRender_;
	}

public:

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

