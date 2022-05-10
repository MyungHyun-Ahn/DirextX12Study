#include "pch.h"
#include "Device.h"

void Device::Init()
{
#ifdef _DEBUG
	
	::D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController));
	_debugController->EnableDebugLayer();

#endif

	// DXGI(DirectX Graphics Infrastuctusds)
	// Direct3D�� �Բ����� API
	// - ��ü ȭ�� ��� ��ȯ
	// - �����Ǵ� ���÷��� ��� ���� ��
	// CreateDXGIFactory
	// - riid : ����̽��� COM ID
	// - ppDevice : ������ ��ġ�� �Ű������� ����
	::CreateDXGIFactory(IID_PPV_ARGS(&_dxgi));

	// CreateDevice
	// - ���÷��� �����(�׷��� ī��)�� ��Ÿ���� ��ü
	// - pAdapter : nullptr �����ϸ� �ý��� �⺻ ���÷��� �����
	// - MinmumFeatureLevel : ���� ���α׷��� �䱸�ϴ� �ּ� ��� ����
	// - riid : ����̽��� COM ID
	// - ppDevice : ������ ��ġ�� �Ű������� ����
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));

}
