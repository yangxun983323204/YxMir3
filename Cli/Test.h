#pragma once
#include "Test.h"

void TestImageLib_Load();
void TestImageLib_LoadImage();
void TestMyGfxCreateSpriteFromImage();
void TestMapLoad();
void TestDrawMapRect();

inline void Test() 
{
	TestImageLib_Load();
	TestImageLib_LoadImage();
	TestMyGfxCreateSpriteFromImage();
	TestMapLoad();
	TestDrawMapRect();
}