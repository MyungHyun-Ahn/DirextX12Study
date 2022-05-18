#include "pch.h"
#include "MonoBehaviour.h"

// 부모 클래스에서 생성자를 만들어 주었으므로 여기서 만들어주어야함
MonoBehaviour::MonoBehaviour() : Component(COMPONENT_TYPE::MONO_BEHAVIOUR)
{

}

MonoBehaviour::~MonoBehaviour()
{

}