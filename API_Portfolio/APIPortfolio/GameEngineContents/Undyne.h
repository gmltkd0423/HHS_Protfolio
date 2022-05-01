#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class Undyne :public GameEngineActor
{
public:
	// constrcuter destructer
	Undyne();
	~Undyne();

	// delete Function
	Undyne(const Undyne& _Other) = delete;
	Undyne(Undyne&& _Other) noexcept = delete;
	Undyne& operator=(const Undyne& _Other) = delete;
	Undyne& operator=(Undyne&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};
