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
	// add youre code here
	return 0;
}