#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	/*
	// 아래 코드와 같은 의미
	for (size_t i = 0; i < _gameObjects.size(); i++)
	{
		const shared_ptr<GameObject>& gameObject = _gameObjects[i];
	}
	*/

	// 안에있는 데이터를 읽기만 한다면 훨씬 더 가독성이 좋음
	// shared_ptr를 레퍼런스로 받게되면 레퍼런스 카운트를 증가시키지 않음
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findIt != _gameObjects.end())
	{
		_gameObjects.erase(findIt);
	}
}