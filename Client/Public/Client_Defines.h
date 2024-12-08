#pragma once

namespace Client 
{
	static const unsigned int g_iWinCX = 1280;
	static const unsigned int g_iWinCY = 720;

	enum LEVEL {  LEVEL_REDPLANET, LEVEL_EXOPLANET, LEVEL_VENUSPLANET, LEVEL_MAGMAPLANET, LEVEL_SELECTPLANET, LEVEL_SUNPLANET, LEVEL_CHARACTERSELECT, LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_END };
	enum class TIMER { TIMER_DEFAULT, TIMER_FRAME, TIMER_END};
}

extern HWND g_hWnd;
extern HINSTANCE g_hInst;

extern bool bRedClear;
extern bool bExoClear;
extern bool bMagmaClear;
extern bool bSunClear;

extern bool   g_bCamera;

using namespace Client;