// NeoCircuit-Studios 2026 | Copyright All Rights Reserved
// GuustEngine 
// build with version: 1.1.0.0
#include <GuustEngine.hpp>

int main() {
	GuustEngine* engine = new GuustEngine();
	AppConfig config;

	config.WindowTitleName = "Grid - GuustEngine";

	engine->Init(config);

	constexpr int MaxGridSize = 8;
	constexpr int BoxSizeWH = 50;

	GuustEngine::Rect Grid;

	while (engine->TargetShouldNotClose()) {
		engine->Update(31, 31, 30,255);

		// center the grid always.
		int ScreenW = (engine->GetRenderW() - engine->GetRenderW()) + (engine->GetRenderW() / 2) - ((BoxSizeWH * MaxGridSize) /2);
		int ScreenH = (engine->GetRenderH() - engine->GetRenderH()) + (engine->GetRenderH() / 2) - ((BoxSizeWH * MaxGridSize) /2);

		for (int x = 0; x < MaxGridSize; x++) {
			for (int y = 0; y < MaxGridSize; y++) {
				Grid.x = ScreenW + x * BoxSizeWH;
				Grid.y = ScreenH + y * BoxSizeWH;
				Grid.w = BoxSizeWH;
				Grid.h = BoxSizeWH;
				engine->SetDrawColor(209, 139, 71, 255);
				engine->DrawRectFull(Grid);
				engine->SetDrawColor(255, 255, 255, 255);
				engine->DrawRect(Grid);
				// when on is even the other one is odd
				if ((x + y) % 2 == 0) {
					engine->SetDrawColor(255, 206, 158, 255);
					engine->DrawRectFull(Grid);
				}
				engine->SetDrawColor(255, 255, 255, 255);
				engine->DrawRect(Grid);
			}
		}

		INFOLOG(STRING("Grid.x: ") + TOSTRING(Grid.x));
		INFOLOG(STRING("Grid.y: ") + TOSTRING(Grid.y));

		engine->Swap();
	}

	engine->Destroy();

	engine = nullptr;
	delete engine;
}