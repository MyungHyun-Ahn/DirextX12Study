#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	// �Ҹ�� �� �Ѳ��� �ݾ��� Unmap();
	// �Ҹ�� ������ ���α׷��� ����� ���̹Ƿ� ���� �����൵ �Ǳ� ������
	// ����ϰ� ������ ���ؿ� Unmap()�� ����.
	if (_cbvBuffer)
	{
		if (_cbvBuffer != nullptr)
			_cbvBuffer->Unmap(0, nullptr);

		_cbvBuffer = nullptr;
	}
}



void ConstantBuffer::Init(uint32 size, uint32 count)
{
	// ��� ���۴� 256 ����Ʈ ����� ������ �Ѵ� - ��Ģ
	// 0 256 (298) 512 768  // �ݿø��� �ϱ� ���� 255�� ������
	// 298�� ������ 256�� �ƴ� 512�� �ǰ� ���� // 256�� �ƴ� 255�� ���ϴ� ���� : �� 256�϶� 512�� �ƴ� 256���� ���ƿ��� ����
	_elementSize = (size + 255) & ~255; // 256 ����� �������� �ʴ� �κ��� �����ϴ� �ڵ�
	// size ���� ���ų� ū 256�� ����� �������
	_elementCount = count;

	CreateBuffer(); // �ȿ��� ������� ������ ���߿� ��� �߰��� ���� �����Ƿ� ���� ����
}

void ConstantBuffer::CreateBuffer()
{
	uint32 bufferSize = _elementSize * _elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	// GPU�� RAM ���� �Ҵ�

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


// _currentIndex�� 0���� �о���
// ���������� �ٱ׷��� �� ����
void ConstantBuffer::Clear()
{
	_currentIndex = 0;
}

// rootParamIndex : b0, b1�� �� �������� �����
void ConstantBuffer::PushData(int32 rootParamIndex, void* buffer, uint32 size)
{
	assert(_currentIndex < _elementSize); // �� ������ �������� ������ ũ���� : ����� �ڵ�

	// �ش� �ε��� ��ġ�� ��û�� �����͸� ī��
	::memcpy(&_mappedBuffer[_currentIndex * _elementSize], buffer, size);

	// ���߿� ���� �ǰ����� �ϰ��� ���
	D3D12_GPU_VIRTUAL_ADDRESS address = GetGpuVirtualAddress(_currentIndex);
	CMD_LIST->SetGraphicsRootConstantBufferView(rootParamIndex, address);
	_currentIndex++;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(uint32 index)
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = _cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += index * _elementSize;
	return objCBAddress;
}