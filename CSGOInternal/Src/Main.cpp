// Coded by: S1vde
#include "Includes.h"


// Main hack thread
DWORD WINAPI OnDllAttach(HMODULE hModule)
{
	// Allocate the console
	AllocConsole();
	// f file
	FILE* f;
	// Open f file
	freopen_s(&f, "CONOUT$", "w", stdout);

	// Wait for the game to initialize. serverbrowser.dll is the last module loaded.
	while (!serverBrowserBase) {
		serverBrowserBase = (DWORD)GetModuleHandle(L"serverbrowser.dll");
		if (!serverBrowserBase)
			Sleep(100);
	}

	// Notify the user that the injection has started
	std::cout << "[*] Injecting..." << "\n";
	std::cout << "[*] Initializing structures & getting base addresses..." << "\n";

	// Get client's base address
	clientBase = (DWORD)GetModuleHandle(L"client.dll");
	// Get engine's base address
	engineBase = (DWORD)GetModuleHandle(L"engine.dll");

	// Create the feature structures
	g_Aimbot = new Aimbot;
	g_ESP = new ESP;
	g_Misc = new Misc;

	// Notify that offset dumper is being initialized
	std::cout << "[*] Initializing dumper..." << "\n";
	// Initialize the offset dumper
	Dumper::Initialize();
	// Notify that we are writing into file
	//std::cout << "[*] Writing dumped offsets to a file..." << "\n";
	// Write all dumped offsets to a file
	//Dumper::WriteToFile();
	//std::cout << "[*] Downloading offsets from hazedumper's github..." << "\n";
	//system("curl -o csgo.hpp https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.hpp");
	// Offests dumped
	std::cout << "[*] Done! Offsets saved at a file named CSGO.hpp at csgo directory." << "\n";
	// Notify that we are hooking
	std::cout << "[*] Initializing hooks..." << "\n";
	// Initialize hooks
	Hooks::Initialize();

	// Notify that injection was successfully completed
	std::cout << "[*] Injection complete!" << "\n";

	// While the user did not press the uninject button
	while (!GetAsyncKeyState(VK_END))
		// Wait until he presses it :)
		Sleep(10);

	// Clean the console
	system("cls");

	// Notify that Uninjection has been initiated
	std::cout << "[*] Uninjection initiated..." << "\n";

	// Notify that hooks are being unhooked
	std::cout << "[*] Unhooking hooks..." << "\n";
	// Unhook the hooks
	Hooks::Unhook();
	// Notify that CSGO's directory is being cleaned up
	std::cout << "[*] Cleaning up..." << "\n";
	// Deletes the dumped offsets file
	Dumper::Cleanup();

	// Delete the created structures
	delete g_Aimbot;
	delete g_ESP;
	delete g_Misc;

	// Say good bye :)
	std::cout << "[*] Closing the console & unloading the module. Good bye :)" << "\n";

	// Begins a countdown in reverse from 3 to 0
	for (int i = 3; i != 0; --i)
	{
		// After each second
		Sleep(1000);

		// Prints the remaining time
		std::cout << i << "\n";
	}

	// Close f
	fclose(f);
	// Close the console
	FreeConsole();
	// Unload the module
	FreeLibraryAndExitThread(hModule, 0);

	// Return 0
	return 0;
}

// DllMain
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Create the main thread when the module is injected
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}