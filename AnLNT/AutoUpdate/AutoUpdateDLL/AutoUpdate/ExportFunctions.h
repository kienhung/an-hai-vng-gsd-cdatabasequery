#pragma once
BOOL __declspec( dllexport )AutoDetectGameUpdate(LPCTSTR strInput);

#include "Include/LogWriter.h"
#pragma comment (lib, "lib/Log.lib")

extern CLogWriter			g_LogWriter;