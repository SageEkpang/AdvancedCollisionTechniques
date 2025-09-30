#include "WindowManager.h"
#include "ScreenManager.h"
#include <windows.h>
#include <comdef.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	std::unique_ptr<WindowManager> m_WindowApplication = std::make_unique<WindowManager>(hInstance, nCmdShow);
	std::unique_ptr<ScreenManager> m_ScreenApplication = std::make_unique<ScreenManager>(m_WindowApplication->GetDevice());

	// Main message loop
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			bool handled = false;

			if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
			{
			}
			else if (WM_QUIT == msg.message)
				break;

			handled = m_WindowApplication->HandleEvents(msg);
			if (!handled)
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
		else
		{
			// NOTE: Being Rendering the Content after Initialisation
			m_WindowApplication->BeginRendering();

				m_ScreenApplication->Process();

				// NOTE: Show screen content
				m_ScreenApplication->Showcase(
					*m_WindowApplication->GetConstantBufferData(), 
					m_WindowApplication->GetConstantBuffer(), 
					m_WindowApplication->GetImmediateContext(), 
					m_WindowApplication->GetDevice()
				);

				// NOTE: Show GUI for the different Screens
				m_ScreenApplication->GUIShowcase(
					m_WindowApplication->GetImmediateContext(),
					m_WindowApplication->GetDevice());

			m_WindowApplication->EndRendering();
		}
	}

	return (int)msg.wParam;
}