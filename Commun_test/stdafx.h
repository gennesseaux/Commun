// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

// En-t�tes pour CppUnitTest
#include "CppUnitTest.h"

#include <vld.h>

//
#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

#include <string>
#include <vector>
#include <sstream>


// Linkage automatique avec la lib DObject
#pragma comment(lib, "DObject.lib")
#pragma comment(lib, "Outils.lib")
#pragma comment(lib, "SQLite.lib")
#pragma comment(lib, "RcReader.lib")


// Cr�ation d'une trace
#ifdef UNICODE
#define tstring wchar_t 
#else
#define tstring char                      
#endif

inline void trace(tstring* format, ...)
{
	static tstring buffer[2048];

	va_list args;
	va_start(args, format);
	wvsprintf(buffer, format, args);
	OutputDebugString(buffer);
	va_end(args);
}