#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :

class SoundPlayer :public GameEngineActor
{
public:

	static GameEngineSoundPlayer Bgm_;
	// constrcuter destructer
	SoundPlayer();
	~SoundPlayer();

	// delete Function
	SoundPlayer(const SoundPlayer& _Other) = delete;
	SoundPlayer(SoundPlayer&& _Other) noexcept = delete;
	SoundPlayer& operator=(const SoundPlayer& _Other) = delete;
	SoundPlayer& operator=(SoundPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	

public:


};

