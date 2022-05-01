#include "Box.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

Box::Box()
{
}

Box::~Box()
{
}

void Box::Start()
{
	TextBox = CreateRendererToScale("TextBox.bmp", { 1000,230 }, (int)BATTLELEVELORDER::BOX);
}

void Box::Update()
{
}

void Box::Render()
{
}
