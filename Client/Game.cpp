#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"

// shared_ptr<GameObject> gameObject = make_shared<GameObject>();
//// Material : 아래 쉐이더 관련 클래스들을 묶어서 관리
// shared_ptr<Mesh> mesh = make_shared<Mesh>();
////shared_ptr<Shader> shader = make_shared<Shader>();
////shared_ptr<Texture> texture = make_shared<Texture>();

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}

void Game::Update()
{
	GEngine->Update();
}
