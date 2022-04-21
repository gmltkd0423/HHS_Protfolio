#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayLevel2Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayLevel2Actor();
	~PlayLevel2Actor();

	// delete Function
	PlayLevel2Actor(const PlayLevel2Actor& _Other) = delete;
	PlayLevel2Actor(PlayLevel2Actor&& _Other) noexcept = delete;
	PlayLevel2Actor& operator=(const PlayLevel2Actor& _Other) = delete;
	PlayLevel2Actor& operator=(PlayLevel2Actor&& _Other) noexcept = delete;

protected:

	void Start() override;

	void Render() override;
private:

};

