#include "..\include\Mouse.h"
#include "..\include\TextureManager.h"

Mouse::Mouse()
{	
}

Mouse::~Mouse()
{
}

void Mouse::Init()
{
	TextureManager::GetInstance()->LoadTexture("Cursor", "assets\\cursor.png");
}
