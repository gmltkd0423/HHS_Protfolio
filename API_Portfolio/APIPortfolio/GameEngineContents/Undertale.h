#pragma once
#include <GameEngine/GameEngine.h>

// ���� : �������� ������� ������ �����ϱ� �׳� ���͵�����̶� �������ϴ�.
//       �����е��� ���� �ڽ��� ������� ���ӿ� �´� �̸��� �̳༮���� �ٿ��ֽø� �˴ϴ�.
class Undertale : public GameEngine
{
public:
	// constrcuter destructer
	Undertale();
	~Undertale();

	// delete Function
	Undertale(const Undertale& _Other) = delete;
	Undertale(Undertale&& _Other) noexcept = delete;
	Undertale& operator=(const Undertale& _Other) = delete;
	Undertale& operator=(Undertale&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

