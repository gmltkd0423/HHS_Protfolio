#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayLevel2BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayLevel2BackGround();
	~PlayLevel2BackGround();

	// delete Function
	PlayLevel2BackGround(const PlayLevel2BackGround& _Other) = delete;
	PlayLevel2BackGround(PlayLevel2BackGround&& _Other) noexcept = delete;
	PlayLevel2BackGround& operator=(const PlayLevel2BackGround& _Other) = delete;
	PlayLevel2BackGround& operator=(PlayLevel2BackGround&& _Other) noexcept = delete;

protected:

	void Start() override;

	void Render() override;
private:

};

