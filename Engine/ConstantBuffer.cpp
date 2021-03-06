#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	// 소멸될 때 뚜껑을 닫아줌 Unmap();
	// 소멸될 때에는 프로그램이 종료될 때이므로 구지 안해줘도 되긴 하지만
	// 깔끔하게 정리를 위해여 Unmap()을 해줌.
	if (_cbvBuffer)
	{
		if (_cbvBuffer != nullptr)
			_cbvBuffer->Unmap(0, nullptr);

		_cbvBuffer = nullptr;
	}
}



void ConstantBuffer::Init(CBV_REGISTER reg, uint32 size, uint32 count)
{
	_reg = reg;

	// 상수 버퍼는 256 바이트 배수로 만들어야 한다 - 원칙
	// 0 256 (298) 512 768  // 반올림을 하기 위해 255를 더해줌
	// 298을 넣으면 256이 아닌 512가 되고 싶음 // 256이 아닌 255를 더하는 이유 : 딱 256일때 512가 아닌 256으로 돌아오기 위함
	_elementSize = (size + 255) & ~255; // 256 배수로 떨어지지 않는 부분을 제거하는 코드
	// size 보다 같거나 큰 256의 배수로 만들어줌
	_elementCount = count;

	CreateBuffer(); // 안에다 만들수도 있지만 나중에 기능 추가할 수도 있으므로 분할 관리
	CreateView();
}

void ConstantBuffer::CreateBuffer()
{
	uint32 bufferSize = _elementSize * _elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	// GPU의 RAM 영역 할당

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_cbvBuffer));

	_cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&_mappedBuffer));
	// We do not need to unmap until we are done with the resource.  However, we must not write to
	// the resource while it is in use by the GPU (so we must use synchronization techniques).
}

void ConstantBuffer::CreateView()
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
	cbvDesc.NumDescriptors = _elementCount;
	cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	DEVICE->CreateDescriptorHeap(&cbvDesc, IID_PPV_ARGS(&_cbvHeap));

	_cpuHandleBegin = _cbvHeap->GetCPUDescriptorHandleForHeapStart();
	_handleIncrementSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	// GPU 사양마다 조금씩 달라지기 때문에 항상 _handleIncrementSize를 구해와야 한다.

	for (uint32 i = 0; i < _elementCount; ++i)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cbvHandle = GetCpuHandle(i);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = _cbvBuffer->GetGPUVirtualAddress() + static_cast<uint64>(_elementSize) * i;
		cbvDesc.SizeInBytes = _elementSize;   // CB size is required to be 256-byte aligned.
		// 버퍼의 주소와 사이즈를 담아서 View를 만들어주고 있음
		DEVICE->CreateConstantBufferView(&cbvDesc, cbvHandle);
	}
}

// _currentIndex를 0으로 밀어줌
// 한프레임을 다그렸을 때 실행
void ConstantBuffer::Clear()
{
	_currentIndex = 0;
}

// rootParamIndex : b0, b1중 뭘 골라야할지 골라줌
void ConstantBuffer::PushData(void* buffer, uint32 size)
{
	assert(_currentIndex < _elementCount); // 이 조건을 만족하지 않으면 크래시 : 디버깅 코드
	// 잘못 사용하는 버그를 방지
	assert(_elementSize == ((size + 255) & ~255));

	// 해당 인덱스 위치에 요청한 데이터를 카피
	::memcpy(&_mappedBuffer[_currentIndex * _elementSize], buffer, size);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = GetCpuHandle(_currentIndex);

	GEngine->GetTableDescHeap()->SetCBV(cpuHandle, _reg);
	_currentIndex++;
	// 나중에 실행 되겠지만 일감을 등록
	// D3D12_GPU_VIRTUAL_ADDRESS address = GetGpuVirtualAddress(_currentIndex);
	// CMD_LIST->SetGraphicsRootConstantBufferView(rootParamIndex, address);	
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(uint32 index)
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = _cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += index * _elementSize;
	return objCBAddress;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetCpuHandle(uint32 index)
{
	// _cpuHandleBegin에다가 index * _handleIncrementSize를 더 해달라는 의미

	/* 
	// 아래 함수와 완전히 같은 기능
	D3D12_CPU_DESCRIPTOR_HANDLE handle = _cpuHandleBegin;
	handle.ptr += index * _handleIncrementSize;
	return handle;
	*/
	// 원하는 인덱스의 핸들을 꺼내옴
	// 첫번째 주소에서 인덱스만큼 이동한 값의 핸들을 리턴
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(_cpuHandleBegin, index * _handleIncrementSize);
}