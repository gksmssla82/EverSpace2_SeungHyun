#pragma once

#pragma warning (disable : 4244)
#pragma warning (disable : 26495)
#pragma warning (disable : 4477)
#pragma warning (disable : 4005)
#pragma warning (disable : 4251)
#pragma warning (disable : 4305)

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <process.h>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <tchar.h>
#include <assert.h>
#include <fstream>
#include <string>
#include <future>


#include "Engine_Typedef.h"
#include "Engine_Function.h"
#include "Engine_Functor.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG

#define D3D_SCALE				0x001
#define D3D_ROTATE				0x002
#define D3D_TRANS			    0x004
#define D3D_ALL					0x007

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

using namespace Engine;
using namespace std;

#include <io.h>
#pragma comment(lib, "fmodex64_vc.lib")

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")



