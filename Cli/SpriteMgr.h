#pragma once
#include "WILIndex.h"
#include "ImageLib.h"
#include "MyGfx.h"
#include "Map.h"

using std::map;

class SpriteMgr
{
public:
	SpriteMgr();
	~SpriteMgr();
	// �Ƿ�����Ҫ��Դ�Ĺ������������ɵ�����ui������Ƿֿ������
	bool IsMain() { return _isMain; }
	void InitMainLibs();
	// �ֶ���ʼ��wil��Ϣ������������֧�ִ˷���
	bool ManulInitLibs(uint32_t fileIdx,std::string filePath);
	Sprite *GetSprite(uint32_t fileIdx,uint32_t imgIdx);
	// ��ЩӰ������ԭͼ�任�����ģ�����ֱ���ز�
	Sprite *GetShadow(Sprite *base);
	Sprite *GetBuiltinSprite(uint8_t idx);
	ImageLib* GetLib(uint32_t idx) { return &mLibs[idx]; }

	static SpriteMgr *Main();
	
	const static uint8_t IdxBuiltinCross;
	const static uint8_t IdxBuiltinVLine;
private:
	bool _isMain;
	struct LibImgCache
	{
		uint16_t size;
		Sprite** sprites;
	};

	Sprite* CreateOrthShadow(Sprite *base);
	Sprite* CreateProjShadow(Sprite *base);
	void ClearCache();

	ImageLib mLibs[_MAX_IMAGE];
	LibImgCache mSpriteMap[_MAX_IMAGE];

	static bool Inited;
	static uint16_t	BuiltinSpriteCount;
	static Sprite** BuiltinSprite;
	static void Init();

	static SpriteMgr *_inst;
};