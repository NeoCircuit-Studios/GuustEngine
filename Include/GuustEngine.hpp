// NeoCircuit-Studios 2026 | Copyright All Rights Reserved
// GuustEngine
// GuustEngine.hpp 
// Engine Created: 18/09/2026
#pragma once

#if __WINDOWS__
#define _EXPORTBREAD
#endif

// stolen from NeoQuantumGameEngine

// __EXPORTBREAD_C is to export as c with GuustEngine.cpp/.h
// use _EXPORTBREAD for c++ export
#if defined(__EXPORTBREAD_C)
#   define ENGINE_API

#elif defined(_STATICBREAD)
#   define ENGINE_API

#elif defined(_EXPORTBREAD)
#   if defined(_WIN32) /*|| defined(_WIN64) || defined(_WINPC)*/
#       define ENGINE_API __declspec(dllexport)
#   elif defined(__GNUC__) || defined(__clang__) || defined(__linux__) /*|| defined(_VITONAX)*/
#       define ENGINE_API __attribute__((visibility("default")))
#   else
#       define ENGINE_API
#   endif

#elif defined(_INMPORTBREAD)
#   if defined(_WIN32) /*|| defined(_WIN64) || defined(_WINPC)*/
#       define ENGINE_API __declspec(dllimport)
#   else
#       define ENGINE_API
#   endif

#else
#   define ENGINE_API
#endif 

/*
// use this as intery point.. 
#if _DEBUG
int main(int argc, char* argv[])
#else
#if __WINDOWS__
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif // __WINDOWS__
#endif // _DEBUG

*/

// on windows define:
// #define __WINDOWS__

#if __WINDOWS__
#include <windows.h>
#endif

#include <cstdint>
#include <string>

struct AppConfig
{
	const char* WindowTitleName = "MyGame - GuustEngine";
	const char* AppVersion = "1.0.0.0";
	const char* AppIdentifier = "com.GuustEngine.mygame";
	const char* TitleID = "0000000000000000";
	const char* Creator = "MyGameStudio";
	const char* CreatorURL = "www.example.com";
	const char* Copyright = "Copyright 2026 All Rights Reserved";
	const char* AppType = "game"; // or mediaplayer or application

	double StartingFPS = 60.0f;

	uint16_t WindowW = 640;
	uint16_t WindowH = 480;
};

class EngineContext;
class PlatformContext;

class ENGINE_API GuustEngine
{
private:
	EngineContext* eEngineContext;
	EngineContext* GetEngineContext() {
		return eEngineContext;
	}
	PlatformContext* ePlatformContext;
	PlatformContext* GetPlatformContext() {
		return ePlatformContext;
	}
public:
	GuustEngine();
	~GuustEngine();

	bool Init(AppConfig &eAppConfig);

	void SetTargetRunning(bool value);
	bool IsTargetRunning();
	bool IsTargetSleeping();

	bool TargetShouldNotClose(); // does the same as IsTargetRunning but whatever
	/// <summary>
	/// Updates engine and set clears the buffers with back color
	/// </summary>
	/// <param name="r">Red 0-255</param>
	/// <param name="g">Green 0-255</param>
	/// <param name="b">Blue 0-255</param>
	/// <param name="a">Alpha (transparency) 0-255</param>
	void Update(int r, int g, int b, int a);

	void Destroy();
public:// fps
	// get the target, not the real fps
	double GetFPSTarget();
	// will be 0 if fps is == to target fps.
	double GetFrameTime();
	double GetDeltaTime();
	void SetFPS(double fps);
	// real time fps.
	double GetFPS();
public: // graphics:
	// TODO: make this int, including the underlying impl etc
	struct Rect
	{
		float x, y;
		float w, h;
	};

	// TODO: make this int, including the underlying impl etc
	struct Point 
	{
		float x;
		float y;
	};

	struct Texture
	{
		void* handle;
		const char* file = nullptr;
	};

	struct Color {
		int r;
		int g;
		int b;
		int a;
	};
	
	// DONT USE THIS FOR UI CALU!! (or scale) (use RenderW/H instead)
	int GetWindowW();
	int GetWindowH();

	// use these to scale youre UI etc.
	int GetRenderW();
	int GetRenderH();

	// is also called in Update();
	void Clear();
	void Swap();

	void SetDrawColor(int r, int g, int b, int a);
	// from 0.0 to 1.0.
	bool SetTextureColorMode(GuustEngine::Texture* texture, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void DrawRect(GuustEngine::Rect eRect);
	void DrawRectFull(GuustEngine::Rect eRect);
	bool DrawRectArrays(GuustEngine::Rect eRect[], int count);
	bool DrawLine(float x1, float y1, float x2, float y2);
	bool DrawLineArrays(GuustEngine::Point ePoint[], int count);
	bool DrawPoint(float x, float y);
	bool DrawPointArrays(GuustEngine::Point ePoint[], int count);

	// DEBUG ONLY
	bool DrawDebugText(float x, float y, const char* text);

	GuustEngine::Texture* LoadTexture(const char* Imagefile);
	bool DrawTexture(GuustEngine::Rect srcRect, GuustEngine::Rect dstRect, GuustEngine::Texture* eTexture);
	bool UnloadTexture(GuustEngine::Texture* eTexture);
public: // Audio

	struct Audio 
	{
		void* handle;
		bool issound = false;
		bool ismusic = false;
		const char* file = nullptr;
	};

	bool SetAudioEngineVolume(float volume);
	float GetAudioEngineVolume();
	// value between 0.0f to 1.0f.
	bool SetAudioVolume(float volume, GuustEngine::Audio* Audio); // 0.0f - 1.0f
	float GetAudioVolume(GuustEngine::Audio* Audio);
	// load a .mp3 or as streaming from disk.
	// is good for long/big music files like background music. 
	// A .WAV WILL CAUSE A MEMORY LEAK HERE!!
	GuustEngine::Audio* LoadMusic(const char* audiofile);
	// Load a .wav to RAM to play as sound, good for
	// sound effects like shooting. 
	GuustEngine::Audio* LoadSound(const char* audiofile);
	bool PlayAudio(GuustEngine::Audio* Audio);
	bool PauseAudio(GuustEngine::Audio* Audio);
	void FreeAudio(GuustEngine::Audio* Audio);
	// Change audio pitch with recommend value between 1.0f-4.0f, 
	// with 1.1f being already very good. (depending on the source)
	// can NOT be 0.0f. and this can NOT be navigate.
	// this does speed up the audio playback.
	// if the value is invalid then it will be set to 1.0f.
	// a value of 0.2f or lower gives a cool free horor effect of
	// your sound.
	bool SetAudioPitch(float pitch, GuustEngine::Audio* Audio);
	float GetAudioPitch(GuustEngine::Audio* Audio);
	bool IsAudioPlaying(GuustEngine::Audio* Audio);
	bool IsAudioDone(GuustEngine::Audio* Audio); // check if the audio is to the end of the file
	void SetAudioLooping(bool loop, GuustEngine::Audio* Audio);
	bool IsAudioLooping(GuustEngine::Audio* Audio);
};

class LogManager;

#define STRING std::string
#define TOSTRING std::to_string

// will only log in debug
class ENGINE_API Log
{
public:
	static void Info(STRING line);
	static void Error(STRING line);
	static void Warning(STRING line);
	static void Debug(STRING line);

};

#define INFOLOG Log::Info
#define ERRORLOG Log::Error
#define DEBUGLOG Log::Debug

class ENGINE_API ImGUI
{
public:
	static bool Begin(const char* title, bool Resize = true, bool Move = true);
	static void End();

	static void BeginGroup();
	static void EndGroup();


	static void Text(const char* text);
	static void TextColored(float r, float g, float b, float a, const char* text);
	static bool Button(const char* title);
	static bool RadioButton(const char* title, bool active);
	static bool CheckBox(const char* title, bool Checked);
	static bool SliderFloat(const char* title, float value, float min, float max);
	static bool SliderInt(const char* title, int value, int min, int max);
	static bool InputText(const char* title, char textbuffer[128]);
	static bool InputTextMultiline(const char* title, char textbuffer[128], int lineheight = 20);
	static bool ColorPicker(const char* title, float color[4]);
	// value from 0.0f-1.0f
	static void Progressbar(float value,float w = -1.0f, float h = 0.0f, const char* text = nullptr);
	static void SameLine();
	static void NewLine();
	static void Spacing();
	/*
		if (ImGUI::Begin("GuustEngine"))
		{
			ImGUI::Text("Bread");
		}
		ImGUI::End();
	*/
public:
	static bool BeginMainMenuBar();
	static bool BeginMenu(const char* text, bool enabled = true);
	static bool MenuItem(const char* text1, const char* shortcut = nullptr, bool selected = false, bool enabled = true);
	static void Separator();
	static void EndMenu();
	static void EndMainMenuBar();
	/*
		if (ImGUI::BeginMainMenuBar())
		{
			if (ImGUI::BeginMenu("File"))
			{
				if (ImGUI::MenuItem("New"))
				{
					//INFOLOG("BREAD");
				}
				ImGUI::EndMenu();
			}
			ImGUI::EndMainMenuBar();
		}
	*/
	/*
	* // handy for engine debugging..
	if (ImGUI::BeginMainMenuBar())
	{
		ImGUI::Text(STRING("FPS: " + TOSTRING(eGuustEngine->GetFPS())).c_str());
		ImGUI::Text(STRING("Deltatime: " + TOSTRING(eGuustEngine->GetDeltaTime())).c_str());
		ImGUI::Text(STRING("Frametime: " + TOSTRING(eGuustEngine->GetFrameTime())).c_str());
		ImGUI::Text(STRING("Fpstarget: " + TOSTRING(eGuustEngine->GetFPSTarget())).c_str());
		ImGUI::Text(STRING("Window: " + TOSTRING(eGuustEngine->GetWindowW()) + STRING("x") + TOSTRING(eGuustEngine->GetWindowH())).c_str());
		ImGUI::Text(STRING("Render: " + TOSTRING(eGuustEngine->GetRenderW()) + STRING("x") + TOSTRING(eGuustEngine->GetRenderH())).c_str());

		ImGUI::EndMainMenuBar();
	}
	*/
public:

};