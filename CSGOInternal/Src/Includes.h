#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include <tchar.h>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <filesystem>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "SDK/Utils/Utils.h"
#include "SDK/Math/Math.h"
#include "SDK/Dumper/Dumper.h"
#include "SDK/CSGO/CSGO.h"
#include "SDK/Dx/dx.h"
#include "SDK/Dx/Draw/Draw.h"
#include "SDK/Player/Player.h"

#include "Hooks/Hooks.h"

#include "Features/Aimbot/Aimbot.h"
#include "Features/Misc/Misc.h"
#include "Features/Visuals/ESP.h"