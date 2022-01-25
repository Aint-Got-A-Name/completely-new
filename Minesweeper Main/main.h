#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

#define ClickTrai 0x5A
#define ClickPhai 0x58
#define ConsoleWidth 80
#define ConsoleHeigth 35

struct CauTrucBang
{
	short SDong = 0;
	short SCot = 0;
	short SSoBom = 0;
	short SSoODaMo = 0;
	short SSoCo = 0;
};

struct CauTrucO
{
	bool BCoBom = false;
	bool BDaMo = false;
	bool BCamCo = false;
	short SBomLanCan = 0;
};

struct Timer
{
	short SSec;
	short SMinute;
};

extern short STrang, SViTriChon, STongMuc;
