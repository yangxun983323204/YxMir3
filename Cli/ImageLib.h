// ͼƬ��
#pragma once
#include <stdint.h>
#include <string>

using std::string;

#pragma pack(1)
// �ɵ���Դ��ʽ
//struct Index2
//{
//	char Title[40];
//	int32_t Count;
//	int32_t* Data;
//};
//struct LibHeader2
//{
//	char Title[40];
//	int32_t Count;
//};
//struct LibBlock2
//{
//	int16_t Width;
//	int16_t Height;
//	int16_t PivotX;
//	int16_t PivotY;
//	int32_t ImgLength;
//};
// �µ���Դ��ʽ
struct Index3
{
	char Title[20];
	int32_t Count;
	int32_t* Data;
};
struct LibHeader3
{
	int16_t HasCompress;
	char Title[20];
	int16_t Version;
	int32_t Count;
};
struct LibBlock3
{
	int16_t Width;
	int16_t Height;
	int16_t PivotX;
	int16_t PivotY;
	char HasShadow;
	int16_t ShadowPosX;
	int16_t ShadowPosY;
	int32_t ImgLength;
};
#pragma pack()
struct MyColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	MyColor() {
		r = g = b = a = 0;
	}
	MyColor(int16_t c16) {
		r = (c16 & 0xF800) >> 8;
		g = (c16 & 0x07E0) >> 3;
		b = (c16 & 0x001F) << 3;
		a = 0xFF;
	}
	float RateR() { return r / 255.0f; }
	float RateG() { return g / 255.0f; }
	float RateB() { return b / 255.0f; }

	const static uint32_t MaskR;
	const static uint32_t MaskG;
	const static uint32_t MaskB;
	const static uint32_t MaskA;
};
struct Image
{
	int16_t Width;
	int16_t Height;
	int16_t PivotX;
	int16_t PivotY;
	char HasShadow;
	int16_t ShadowPosX;
	int16_t ShadowPosY;

	MyColor* Pixels;
	// todo ��ɫ�ɱ��ı�ǣ��ƻ����м�¼

	Image(){}
	inline Image(LibBlock3 *block3) 
	{
		Width = block3->Width;
		Height = block3->Height;
		PivotX = block3->PivotX;
		PivotY = block3->PivotY;
		HasShadow = block3->HasShadow;
		ShadowPosX = block3->ShadowPosX;
		ShadowPosY = block3->ShadowPosY;
	}
};
#pragma pack(8)
class ImageLib
{
public:
	ImageLib();
	~ImageLib();

	void Load(string wixPath);
	inline void BeginBatch();
	inline void EndBatch();
	Image *LoadImage(uint32_t index);
	Image *LoadImageExt(uint32_t index, MyColor chooseColor1, MyColor chooseColor2);

	static string GUID(string wixPath, uint32_t index);
private:
	void SetPath(string wixPath);
	
	string mWixPath;
	string mWilPath;

	int16_t mVersion;
	Index3 *mIdx3;
	FILE *mWilFile;

	bool mBatch;

	inline static int WixOffset(int version) 
	{
		switch (version) {
		case 17:
			return 24;
		case 5000:
			return 28;
		case 6000:
			return 32;
		default:
			throw "offset == -1";
		}
	}
	inline static int WilOffset(int version)
	{
		switch (version) {
		case 17:
			return 17;
		case 5000:
			return 21;
		case 6000:
			return 21;
		default:
			throw "offset == -1";
		}
	}

	const static unsigned char KeyNone;// ͸��
	const static unsigned char KeyConst;
	const static unsigned char KeyOverlay1;
	const static unsigned char KeyOverlay2;
};
#pragma pack()


