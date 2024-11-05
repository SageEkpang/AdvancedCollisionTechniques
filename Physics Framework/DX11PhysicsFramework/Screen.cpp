#include "Screen.h"

void Screen::BeginRendering()
{
	// Clear Buffers
	float ClearColor[4] = { 0.25f, 0.25f, 0.75f, 1.0f }; // red,green,blue,alpha
	_immediateContext->OMSetRenderTargets(1, &_frameBufferView, _depthBufferView);
	_immediateContext->ClearRenderTargetView(_frameBufferView, ClearColor);
	_immediateContext->ClearDepthStencilView(_depthBufferView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set Up Buffers and Render Scene
	_immediateContext->VSSetShader(_vertexShader, nullptr, 0);
	_immediateContext->PSSetShader(_pixelShader, nullptr, 0);

	_immediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
	_immediateContext->PSSetConstantBuffers(0, 1, &_constantBuffer);
	_immediateContext->PSSetSamplers(0, 1, &_samplerLinear);

	// Change this for the surface material stuff
	_cbData.surface.AmbientMtrl = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_cbData.surface.DiffuseMtrl = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_cbData.surface.SpecularMtrl = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	// Needed for GameObjects
	// _cbData.World = XMMatrixTranspose();

	// Set texture
	//if (gameObject->HasTexture())
	//{
	//	_immediateContext->PSSetShaderResources(0, 1, gameObject->GetTextureRV());
	//	_cbData.HasTexture = 1.0f;
	//}
	//else
	//{
	//	_cbData.HasTexture = 0.0f;
	//}

	//Write constant buffer data onto GPU
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	_immediateContext->Map(_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	memcpy(mappedSubresource.pData, &_cbData, sizeof(_cbData));
	_immediateContext->Unmap(_constantBuffer, 0);
}

void Screen::EndRendering()
{

	_swapChain->Present(0, 0);
}

Screen::Screen(std::string screenName)
{

}

Screen::~Screen()
{
	delete _camera;

	if (_immediateContext)_immediateContext->Release();

	if (_frameBufferView)_frameBufferView->Release();
	if (_depthBufferView)_depthBufferView->Release();
	if (_depthStencilBuffer)_depthStencilBuffer->Release();
	if (_swapChain)_swapChain->Release();
	if (_CWcullMode)_CWcullMode->Release();
	if (_CCWcullMode)_CCWcullMode->Release();
	if (_vertexShader)_vertexShader->Release();
	if (_inputLayout)_inputLayout->Release();
	if (_pixelShader)_pixelShader->Release();
	if (_constantBuffer)_constantBuffer->Release();

	if (_cubeVertexBuffer)_cubeVertexBuffer->Release();
	if (_cubeIndexBuffer)_cubeIndexBuffer->Release();
	if (_planeVertexBuffer)_planeVertexBuffer->Release();
	if (_planeIndexBuffer)_planeIndexBuffer->Release();
	if (_objMeshData.IndexBuffer) _objMeshData.IndexBuffer->Release();
	if (_objMeshData.VertexBuffer)_objMeshData.VertexBuffer->Release();

	if (_DSLessEqual) _DSLessEqual->Release();
	if (_RSCullNone) _RSCullNone->Release();

	if (_samplerLinear)_samplerLinear->Release();
	if (_StoneTextureRV)_StoneTextureRV->Release();
	if (_GroundTextureRV)_GroundTextureRV->Release();
	if (_HerculesTextureRV)_HerculesTextureRV->Release();

	if (_dxgiDevice)_dxgiDevice->Release();
	if (_dxgiFactory)_dxgiFactory->Release();
	if (_device)_device->Release();
}

void Screen::Update(float deltaTime)
{
	static ULONGLONG frameStart = GetTickCount64();

	ULONGLONG frameNow = GetTickCount64();
	float deltaTime = (frameNow - frameStart) / 1000.0f;
	frameStart = frameNow;

	static float simpleCount = 0.0f;
	simpleCount += deltaTime;

	// Update camera
	float angleAroundZ = XMConvertToRadians(_cameraOrbitAngleXZ);

	float x = _cameraOrbitRadius * cos(angleAroundZ);
	float z = _cameraOrbitRadius * sin(angleAroundZ);

	XMFLOAT3 cameraPos = _camera->GetPosition();
	cameraPos.x = x;
	cameraPos.z = z;

	_camera->SetPosition(cameraPos);
	_camera->Update();

}

HRESULT Screen::Initialise(HINSTANCE hInstance, int nShowCmd)
{
	HRESULT hr = S_OK;

	hr = CreateWindowHandle(hInstance, nShowCmd);
	if (FAILED(hr)) return E_FAIL;

	hr = CreateD3DDevice();
	if (FAILED(hr)) return E_FAIL;

	hr = CreateSwapChainAndFrameBuffer();
	if (FAILED(hr)) return E_FAIL;

	hr = InitShadersAndInputLayout();
	if (FAILED(hr)) return E_FAIL;

	hr = InitVertexIndexBuffers();
	if (FAILED(hr)) return E_FAIL;

	hr = InitPipelineStates();
	if (FAILED(hr)) return E_FAIL;

	hr = InitRunTimeData();
	if (FAILED(hr)) return E_FAIL;

	return hr;
}

bool Screen::HandleKeyboard(MSG msg)
{
	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HRESULT Screen::CreateWindowHandle(HINSTANCE hInstance, int nCmdShow)
{
	return E_NOTIMPL;
}

HRESULT Screen::CreateD3DDevice()
{
	return E_NOTIMPL;
}

HRESULT Screen::CreateSwapChainAndFrameBuffer()
{
	return E_NOTIMPL;
}

HRESULT Screen::InitShadersAndInputLayout()
{
	return E_NOTIMPL;
}

HRESULT Screen::InitVertexIndexBuffers()
{
	return E_NOTIMPL;
}

HRESULT Screen::InitPipelineStates()
{
	return E_NOTIMPL;
}

HRESULT Screen::InitRunTimeData()
{
	return E_NOTIMPL;
}
