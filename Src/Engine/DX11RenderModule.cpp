
#include "RenderModule.hpp"
#include "CoreModule.hpp"
#include "Framework.hpp"

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

//#include <d3dx11.h>
//#include <xnamath.h>


namespace Verge3D {

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
//#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

#define SAFE_RELEASE(p) if(p) p->Release(); p = nullptr;


enum class ShaderType : uint32_t {
		Vertex,
		Pixel,
		//Compute
};



class DX11RenderContext : public RenderContext {


public:

	FLOAT clearColor[4];

	DX11RenderContext(const RenderContextInfo& info_) : RenderContext(info_) {}
	ID3D11RenderTargetView* colorRenderTarget = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* immediateContext = nullptr;

	bool setSize(const WindowSize& windowSize) {

		destroyResources();
		swapChain->ResizeBuffers(2, windowSize.width, windowSize.height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		DebugLog("Set size %u, %u", windowSize.width, windowSize.height);
		createResources();

		return true;

	}

	void createResources() {

		ID3D11Texture2D* backBuffer = NULL;

		HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
		assert(hr == S_OK);

		hr = device->CreateRenderTargetView(backBuffer, NULL, &colorRenderTarget);
		backBuffer->Release();

	}

	void destroyResources() {
		immediateContext->OMSetRenderTargets(1, &colorRenderTarget, nullptr);
		SAFE_RELEASE(colorRenderTarget);
	}

};


class DX11RenderModule : public RenderModule {

	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;
	IDXGIFactory * factory;

public:

	~DX11RenderModule() {}


	bool init(Framework* framework);
	void shutdown();
	void update(float td);

	RenderContext* createRenderContext(const RenderContextInfo&);
	void destroyRenderContext(RenderContext*);

	void beginFrame(RenderContext*);
	void endFrame();
	
	void drawScene(RenderScene*, const SceneView&);


	void _compileShader(MemoryBuffer* sourceBuffer, ShaderType shaderType);

};

void DX11RenderModule::_compileShader(MemoryBuffer* sourceBuffer, ShaderType shaderType) {

	const char* entryPointNames[] = {"VSMain", "PSMain"};
	const char* targetNames[] = { "vs_4_0", "ps_4_0" };

	ID3DBlob* codeBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT res = D3DCompile(
		sourceBuffer->getPtr(), 
		sourceBuffer->getSize(), 
		"", 
		nullptr, 
		nullptr, 
		entryPointNames[(uint32_t)shaderType],
		targetNames[(uint32_t)shaderType],
		0, 
		0, 
		&codeBlob, 
		&errorBlob);

	if (errorBlob) {
			//error()
			String str((const char*)errorBlob->GetBufferPointer());
			error(str.w_str());
			SAFE_RELEASE(errorBlob);
	}

	if (codeBlob) {
			SAFE_RELEASE(codeBlob);
	}

}

bool DX11RenderModule::init(Framework* framework) {

	RenderModule::init(framework);


	factory = nullptr;
	HRESULT hr;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&factory));

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	/*

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_WARP,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	*/

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	D3D_FEATURE_LEVEL* featureLevels2 = nullptr;

	device = nullptr;
	immediateContext = nullptr;

	HRESULT res = D3D11CreateDevice(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&device,
		featureLevels2,
		&immediateContext);

	info(L"DX11RenderModule intialized...");
	error(L"Failed");


	//SharedPtr<MemoryBuffer> mb = getFramework()->findModule<CoreModule>()->getFileSystemManager()->loadFile("Shader.fx");
	SharedPtr<MemoryBuffer> mb = getFramework()->findModule<CoreModule>()->getFileSystemManager()->loadFile("RenderCascadeScene.hlsl");

	///SharedPtr<MemoryBuffer> mb = getFramework()->findModule<CoreModule>()->getFileSystemManager()->loadFile("Shader.fx");
	for (int i = 0; i < 100; i++) {
		_compileShader(mb, ShaderType::Vertex);
		_compileShader(mb, ShaderType::Pixel);
	}
	

	return true;
}

void DX11RenderModule::shutdown() {

	SAFE_RELEASE(factory);
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(device);

	RenderModule::shutdown();
}

void DX11RenderModule::update(float td) {

}


RenderContext* DX11RenderModule::createRenderContext(const RenderContextInfo& info) {

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 2;
	swapChainDesc.OutputWindow = info.hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferDesc.Width = info.size.width;
	swapChainDesc.BufferDesc.Height = info.size.height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;


	IDXGISwapChain* swapChain = nullptr;

	HRESULT hr = factory->CreateSwapChain(device, &swapChainDesc, &swapChain);

	DX11RenderContext* rc = new DX11RenderContext(info);
	rc->swapChain = swapChain;
	rc->device = device;
	rc->immediateContext = immediateContext;
	rc->createResources();


	static float color = 0.0;
	color += 0.25;
	rc->clearColor[0] = color;
	rc->clearColor[1] = color;
	rc->clearColor[0] = color;
	rc->clearColor[3] = 1;

	return rc;
}

void DX11RenderModule::destroyRenderContext(RenderContext* rc_) {

	DX11RenderContext* rc = static_cast<DX11RenderContext*>(rc_);
	rc->destroyResources();
	SAFE_RELEASE(rc->swapChain);
}

void DX11RenderModule::beginFrame(RenderContext* rc) {

	currentRenderContext = rc;
	int i = 0;

}

void DX11RenderModule::endFrame() {

	DX11RenderContext* rc = static_cast<DX11RenderContext*>(currentRenderContext);

	ID3D11RenderTargetView* colorRenderTarget = rc->colorRenderTarget;
	//FLOAT clearColor[4] = {1.0, 0.0, 0.0, 1.0 };
	rc->clearColor[0] = (float)rand() / RAND_MAX;
	immediateContext->ClearRenderTargetView(colorRenderTarget, rc->clearColor);

	rc->swapChain->Present(0, 0);

}


void DX11RenderModule::drawScene(RenderScene*, const SceneView&) {

}



RenderModule* CreateRenderModule() {

	return new DX11RenderModule;

}

}