// RcReader_test.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <vld.h>
#include <functional>
#include <memory>

//
#include "RcReader/RcReader.h"

// Linkage automatique avec la lib RcReader
#pragma comment(lib, "RcReader.lib")

//
using namespace std;
using namespace RcReader;


int _tmain(int argc, _TCHAR* argv[])
{
	//RcReader::CRcReader reader1("D:\\GOYER\\projet\\Applications GOYER\\Gps\\dev\\msvc7\\Gps.rc");

	RcReader::CRcReader reader2("D:\\GOYER\\projet\\Projet Perso\\Commun\\RcReader\\test\\RcReader_test.rc");


	return 0;
}

