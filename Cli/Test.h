#pragma once
#include "Test.h"

void TestImageLib_Load();
void TestImageLib_LoadImage();
void TestMyGfxCreateSpriteFromImage();
void TestMapLoad();
void TestDrawMapRect();
void TestMapRender();
void TestActorRender();
void TestInputMgr();
void TestSoundMgr_LoadList();

inline void Test() 
{
	//TestImageLib_Load();
	//TestImageLib_LoadImage();
	//TestMyGfxCreateSpriteFromImage();
	//TestMapLoad();
	//TestDrawMapRect();
	//TestMapRender();
	//TestActorRender();
	TestInputMgr();
	//TestSoundMgr_LoadList();

	exit(0);
}