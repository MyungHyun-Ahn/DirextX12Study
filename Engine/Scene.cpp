#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	/*
	// �Ʒ� �ڵ�� ���� �ǹ�
	for (size_t i = 0; i < _gameObjects.size(); i++)
	{
		const shared_ptr<GameObject>& gameObject = _gameObjects[i];
	}
	*/

	// �ȿ��ִ� �����͸� �б⸸ �Ѵٸ� �ξ� �� �������� ����
	// shared_ptr�� ���۷����� �ްԵǸ� ���۷��� ī��Ʈ�� ������Ű�� ����
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