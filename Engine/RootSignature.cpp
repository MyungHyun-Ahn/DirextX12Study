#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0), // b0~b4 5개
	};

	CD3DX12_ROOT_PARAMETER param[1]; // b0와 b1이 겹치면 안됨
	//param[0].InitAsConstantBufferView(0); // 0번 -> b0 -> CBV 
	//param[1].InitAsConstantBufferView(1); // 1번 -> b1 -> CBV
	// SHADER_VISILITY 중요
	param[0].InitAsDescriptorTable(_countof(ranges), ranges); // _countof 매크로 함수 ranges의 size를 반환



	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param); // D3D12_DEFAULT 기본적인 서명
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 입력 조립기 단계

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&_signature));
}