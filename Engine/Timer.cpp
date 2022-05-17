#include "pch.h"
#include "Timer.h"


void Timer::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU 클럭
}

void Timer::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++; // 업데이트문이 얼마나 실행됬는지 계산
	_frameTime += _deltaTime; // 누적시간을 더해줌

	if (_frameTime > 1.f) // 1초가 넘어가면 0으로 셋팅
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime); // 평균 구하기

		_frameTime = 0.f;
		_frameCount = 0;
	}
}