#include <GuustEngine.hpp>

#if _DEBUG
int main(int argc, char* argv[])
#else
#if __WINDOWS__
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif // __WINDOWS__
#endif // _DEBUG
{
	bool IsRight = true;
	bool IsUnder = true;

	GuustEngine* eGuustEngine = new GuustEngine;
	AppConfig eAppConfig;
	eAppConfig.WindowTitleName = "ScreenSaver - GuustEngine";
	eAppConfig.AppIdentifier = "Com.GuustEngine.ScreenSaver";

	if (!eGuustEngine->Init(eAppConfig))
	{
		ERRORLOG("Could not init the Engine!");
	}

	GuustEngine::Rect Panel;
	GuustEngine::Rect Button;

	GuustEngine::Rect ButtonRect;
	ButtonRect.x = 0;
	ButtonRect.y = 0;
	ButtonRect.w = 891;
	ButtonRect.h = 631;

	GuustEngine::Rect BackgroundRect;
	BackgroundRect.x = (float)((eGuustEngine->GetWindowW() - 500) / 2);
	BackgroundRect.y = (float)((eGuustEngine->GetWindowH() - 400) / 2);
	BackgroundRect.w = 500;
	BackgroundRect.h = 400;

	Panel.x = (float)((eGuustEngine->GetWindowW() - 500) / 2);
	Panel.y = (float)((eGuustEngine->GetWindowH() - 400) / 2);
	Panel.w = 500;
	Panel.h = 400;

	Button.x = Panel.x;
	Button.y = Panel.y;

	eGuustEngine->SetFPS(60);

	bool IsPaused = false;
	while (eGuustEngine->TargetShouldNotClose())
	{
		eGuustEngine->Update(0,0,0,255);

#if __WINDOWS__
		if (ImGUI::BeginMainMenuBar())
		{
			ImGUI::Text(STRING("FPS: " + TOSTRING(eGuustEngine->GetFPS())).c_str());
			ImGUI::Text(STRING("Deltatime: " + TOSTRING(eGuustEngine->GetDeltaTime())).c_str());
			ImGUI::Text(STRING("Frametime: " + TOSTRING(eGuustEngine->GetFrameTime())).c_str());
			ImGUI::Text(STRING("Fpstarget: " + TOSTRING(eGuustEngine->GetFPSTarget())).c_str());
			ImGUI::Text(STRING("Window: " + TOSTRING(eGuustEngine->GetWindowW()) + STRING("x") + TOSTRING(eGuustEngine->GetWindowH())).c_str());
			ImGUI::Text(STRING("Render: " + TOSTRING(eGuustEngine->GetRenderW()) + STRING("x") + TOSTRING(eGuustEngine->GetRenderH())).c_str());
			if (ImGUI::Button("Pause")) {
				IsPaused = !IsPaused;
			}

			ImGUI::EndMainMenuBar();
		}
#endif
		// set green
		eGuustEngine->SetDrawColor(0, 255, 0, 255);
		eGuustEngine->DrawRect(Button);
		eGuustEngine->DrawRect(Panel);
	
		Button.w = 100;
		Button.h = 100;

		if (!IsPaused)
		{
			Button.x += IsRight ? 10 : -8;
			Button.y += IsUnder ? 7 : -5;
		}

		if (Button.x <= Panel.x || Button.x >= Panel.w - 30) {
			IsRight = !IsRight;
		}
		if (Button.y <= Panel.y || Button.y >= Panel.h - 60) {
			IsUnder = !IsUnder;
		}

#if __WINDOWS__
		if (ImGUI::Begin("Button-Info"))
		{
			ImGUI::Text(STRING("Button.x:" + TOSTRING(Button.x)).c_str());
			ImGUI::Text(STRING("Button.y:" + TOSTRING(Button.y)).c_str());
		}
		ImGUI::End();

		if (ImGUI::Begin("Panel-Info"))
		{
			ImGUI::Text(STRING("Panel.x:" + TOSTRING(Panel.x)).c_str());
			ImGUI::Text(STRING("Panel.y:" + TOSTRING(Panel.y)).c_str());
			ImGUI::Text(STRING("Panel.w:" + TOSTRING(Panel.w)).c_str());
			ImGUI::Text(STRING("Panel.h:" + TOSTRING(Panel.h)).c_str());
		}
		ImGUI::End();
#endif

		eGuustEngine->Swap();
	}

	eGuustEngine->Destroy();

	delete eGuustEngine;
	eGuustEngine = nullptr;
}