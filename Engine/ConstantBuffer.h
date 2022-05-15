#pragma once

// 
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(uint32 size, uint32 count);

	void Clear();
	D3D12_CPU_DESCRIPTOR_HANDLE PushData(int32 rootParamIndex, void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(uint32 index);

private:
	void CreateBuffer();
	void CreateView();

private:
	ComPtr<ID3D12Resource>	_cbvBuffer;
	BYTE* _mappedBuffer = nullptr; // 뚜껑을 열때 사용하는 buffer / memcpy
	uint32					_elementSize = 0;
	uint32					_elementCount = 0;

	ComPtr<ID3D12DescriptorHeap>		_cbvHeap; // Desp.Heap(CBV)
	D3D12_CPU_DESCRIPTOR_HANDLE			_cpuHandleBegin = {}; // 시작핸들 주소
	uint32								_handleIncrementSize = 0; // 몇칸을 띄워야 다음 핸들로 갈 수 있을지

	uint32					_currentIndex = 0; // 어디까지 그렸는지 추적
	                                           // 한 프레임을 다 그리게 되면 0으로 초기화
};

