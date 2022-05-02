#pragma once
#include <GameEngine/GameEngineActor.h>
#include<GameEngine/GameEngineImage.h>

// Ό³Έν :
enum class PlayerState
{
	Idle,
	Move
};

enum class PlayerOrder
{
	Frisk = 1000 , 
	Heart
};
//static enum class PlayerLevelState
//{
//	PlayLevel,
//	PlayLevel2,
//	BattleLevel,
//};


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
	GameEngineRenderer* Frisk_;
	GameEngineRenderer* Heart_;
	GameEngineCollision* PlayerCollision_;
	GameEngineImage* MapColImage_;
	float4 MoveDir_;
	std::string AnimationName_;
	std::string DirName_;

	float Time_;
	float Speed_;
	bool IsBlink_;
	bool IsMove_;
	bool CamPos_;
	bool IsChange_;
	float MapSizeX;
	float MapSizeY;
	float CamRectX;
	float CamRectY;
	float BlinkTime_;
	float BlinkTimer_;
	int Hp_;
	int MaxHp_;


private:
	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:
	void ChangeState(PlayerState _State);
	void ChangeToHeart();
	void StateUpdate();
	void Play();
	void Stop();
	
	void SetIsChange()
	{
		IsChange_ = true;
	}

	void SetBlinkTimer(float _BlinkTimer)
	{
		BlinkTimer_ = _BlinkTimer;
	}
	
	void IsHeart();
	void IsFrisk();

	bool IsActionKeyDown();

	bool GetIsMove()
	{
		return IsMove_;
	}

	float4 GetMoveDir()
	{
		return MoveDir_;
	}

	void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	int GetMaxHp()
	{
		return MaxHp_;
	}

	int GetHp()
	{
		return Hp_;
	}


	float GetSpeed()
	{
		return Speed_;
	}
	bool IsPressAnyMoveKey();

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

	GameEngineRenderer* GetFrisk()
	{
		return Frisk_;
	}

	void Reset()
	{
		IsChange_ = false;
		CamPos_ = true;
		IsMove_ = true;
		IsBlink_ = false;
		IsFrisk();
	}


public:

private:
	void CameraLock();
	bool IsKeyPress();
	bool IsKeyDown();
	bool IsKeyUp();
	void CheckWall(float4 _Value);
	void Blink();
	void GetDamaged();
	void CollisionCheck();


private:

	//fsm
	void IdleStart();
	void IdleUpdate();

	void MoveStart();
	void MoveUpdate();
};

