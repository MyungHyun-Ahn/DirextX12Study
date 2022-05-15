#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(vector<Vertex>& vec) // 벡터에 Vertex를 받는다. 위치정보 + 색상정보
{
	_vertexCount = static_cast<uint32>(vec.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex); // buffer size 만큼 공간을 만든다

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	// GPU 공간 할당
	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer)); // 원격으로 GPU의 공간을 가리킴

	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vec[0], bufferSize); // GPU 쪽 메모리에 복사
	_vertexBuffer->Unmap(0, nullptr); // Mesh는 데이터가 평생 바뀌지 않을 것이므로 바로 닫지만
	                                  // constant buffer 같은 경우에는 필요없을 때 닫을 것임

	// Initialize the vertex buffer view.
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
	_vertexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기	
}


// 그려주는 부분
void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)

	// TODO
	// 1번과 2번이 동시에 실행
	// 1) Buffer에다가 데이터 세팅 - 즉시 일어나고
	// 2) Buffer의 주소를 register에다가 셋팅 - 나중에 일어난다
	// CMD_LIST->SetGraphicsRootConstantBufferView(0, ??);
	
	GEngine->GetCB()->PushData(0, &_transform, sizeof(_transform)); // b0
	GEngine->GetCB()->PushData(1, &_transform, sizeof(_transform)); // b1

	CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
}