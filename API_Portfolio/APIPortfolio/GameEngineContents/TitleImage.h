#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class TitleImage : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleImage();
	~TitleImage();

	// delete Function
	TitleImage(const TitleImage& _Other) = delete;
	TitleImage(TitleImage&& _Other) noexcept = delete;
	TitleImage& operator=(const TitleImage& _Other) = delete;
	TitleImage& operator=(TitleImage&& _Other) noexcept = delete;
	
public:

protected:
	void Start() override;
	void Update() override;
private:

};

