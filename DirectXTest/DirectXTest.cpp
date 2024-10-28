// DirectXTest.cpp : Определяет точку входа для приложения.
//были подключены зависимости - d3d11.lib; dxgi.lib; d3dcompiler.lib
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

//Инициалищация окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreateSimpleWindow(HINSTANCE hInstance, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"DirectXWindowClass";
    WNDCLASS wc = {};
    wc.hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"DirectX 11 Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);
    
    if (hwnd == nullptr)
    {
        return nullptr;
    }
    ShowWindow(hwnd, nCmdShow);
    return hwnd;
}

//Инициализация DirectX11
ComPtr < ID3D11Device> device;
ComPtr<ID3D11DeviceContext> context;
ComPtr<IDXGISwapChain> swapChain;
ComPtr<ID3D11RenderTargetView> renderTargetView;

bool initilizeDirectX(HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 800; //Отображение разрешения в виде окна
    sd.BufferDesc.Height = 600;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    HRESULT  hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, swapChain.GetAddressOf(), device.GetAddressOf(), nullptr, context.GetAddressOf());

    if (FAILED(hr))
    {
        return false;
    }

    ComPtr<ID3D11Texture2D> backBuffer;
    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
    if (FAILED(hr))
    {
        return false;
    }

    hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}

//Главный цикл рендера
void Render()
{

}