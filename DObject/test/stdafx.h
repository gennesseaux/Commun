// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

#include <string>
#include <vector>
#include <sstream>


// Création d'une trace
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
