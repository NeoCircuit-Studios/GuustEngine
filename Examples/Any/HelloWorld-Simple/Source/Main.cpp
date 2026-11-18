// use the engine
// this file is in 'Include\' in the repo
#include <GuustEngine.hpp>

int main() {
	// make copy (object)
	GuustEngine* engine = new GuustEngine();
	AppConfig config;

	// start engine
	engine->Init(config);

	// update engine
	while (engine->TargetShouldNotClose()) {
		// update systems
		engine->Update(0, 0, 0, 0);
		// set color picker to green
		//			r   g   b   a
		engine->SetDrawColor(0, 255, 0, 255);
		// write text for debug at x200,y200
		//                     x    y
		engine->DrawDebugText(200, 200, "Hello World!");
		// clear the screen and reset.
		engine->Swap();
	}

	// when engine not updating anymore
	// stop the engine
	engine->Destroy();

	// remove the copy (object) we made.
	engine = nullptr;
	delete engine;
}