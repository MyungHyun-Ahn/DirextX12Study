#pragma once

class GameObject;


class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

private:
	// 보통 벡터의 벡터나 벡터의 배열로 구분해서 저장해줌
	vector<shared_ptr<GameObject>> _gameObjects;
};
