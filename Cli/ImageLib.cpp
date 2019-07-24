#include "ImageLib.h"
#include <assert.h>

const uint32_t MyColor::MaskR = 0x000000ff;
const uint32_t MyColor::MaskG = 0x0000ff00;
const uint32_t MyColor::MaskB = 0x00ff0000;
const uint32_t MyColor::MaskA = 0xff000000;

const unsigned char ImageLib::KeyNone = 0xc0;// ͸��
const unsigned char ImageLib::KeyConst = 0xc1;
const unsigned char ImageLib::KeyOverlay1 = 0xc2;
const unsigned char ImageLib::KeyOverlay2 = 0xc3;


ImageLib::ImageLib()
{
	mIdx3 = nullptr;
	mWilFile = nullptr;
	mBatch = false;
}


ImageLib::~ImageLib()
{
	EndBatch();
	delete mIdx3;
	mIdx3 = nullptr;
}

void ImageLib::Load(string wixPath)
{
	SetPath(wixPath);
	// ��wil�ļ���ȡ�汾��
	auto fpeekVer = fopen(mWilPath.c_str(), "rb");
	fseek(fpeekVer, 22, SEEK_SET);
	fread(reinterpret_cast<void*>(&mVersion), 2, 1, fpeekVer);
	fclose(fpeekVer);

	FILE* f = fopen(mWixPath.c_str(), "rb");
	mIdx3 = new Index3();
	fread(reinterpret_cast<void*>(mIdx3), sizeof(Index3) - 4, 1, f);
	mIdx3->Data = new int32_t[mIdx3->Count];
	fseek(f, WixOffset(mVersion), SEEK_SET);
	fread(reinterpret_cast<void*>(mIdx3->Data), sizeof(int32_t), mIdx3->Count, f);
	fclose(f);
}

void ImageLib::BeginBatch()
{
	if (mWilFile==nullptr)
	{
		mWilFile = fopen(mWilPath.c_str(), "rb");
	}
	mBatch = true;
}

void ImageLib::EndBatch()
{
	if (mWilFile != nullptr)
	{
		fclose(mWilFile);
		mWilFile = nullptr;
	}
	mBatch = false;
}

Image *ImageLib::LoadImage(uint32_t index)
{
	return LoadImageExt(index, MyColor(0xffff), MyColor(0xffffff));
}

Image *ImageLib::LoadImageExt(uint32_t index, MyColor chooseColor1, MyColor chooseColor2)
{
	int32_t address;
	assert(index < mIdx3->Count);
	if (index >= mIdx3->Count)
		return nullptr;
	address = mIdx3->Data[index];
	assert(address > 0);
	if (address<=0)
		return nullptr;
	if (mWilFile == nullptr)
		mWilFile = fopen(mWilPath.c_str(), "rb");
	fseek(mWilFile, address, SEEK_SET);
	

	int32_t dataLen;
	auto block3 = new LibBlock3();
	fread(reinterpret_cast<void*>(block3), sizeof(LibBlock3), 1, mWilFile);
	Image *img = new Image(block3);
	dataLen = block3->ImgLength;
	img->Pixels = new MyColor[img->Width * img->Height];
	memset(reinterpret_cast<void*>(img->Pixels), 0, img->Width*img->Height * sizeof(MyColor));// ��Ϊ��ɫ
	auto rawbuffer = new int16_t[dataLen];
	fseek(mWilFile, address, SEEK_SET);
	fseek(mWilFile, WilOffset(mVersion), SEEK_CUR);
	fread(reinterpret_cast<void*>(rawbuffer), 2, dataLen, mWilFile);
	if (!mBatch && mWilFile != nullptr)
	{
		fclose(mWilFile);
		mWilFile = nullptr;
	}
	assert(
		rawbuffer[1] == KeyNone ||
		rawbuffer[1] == KeyConst ||
		rawbuffer[1] == KeyOverlay1 ||
		rawbuffer[1] == KeyOverlay2);
	
	size_t w = img->Width;
	size_t rawBeginAt = 0;
	size_t rawEndAt = 0;
	size_t rawNowAt = 0;
	size_t dstNowRowAt = 0;
	MyColor chooseColor;
	for (size_t row = 0; row < img->Height; ++row)
	{
		rawEndAt += rawbuffer[rawBeginAt++];
		rawNowAt = rawBeginAt;
		dstNowRowAt = 0;
		while (rawNowAt < rawEndAt)
		{
			uint16_t type = rawbuffer[rawNowAt++];
			uint16_t cntCpy = rawbuffer[rawNowAt++];
			switch (type)
			{
			case KeyNone:
				break;
			case KeyConst:
				for (size_t t = 0; t < cntCpy; t++)
				{
					img->Pixels[row*w +dstNowRowAt+t] = MyColor(rawbuffer[rawNowAt+t]);
				}
				rawNowAt += cntCpy;
				break;
			case KeyOverlay1:
				chooseColor = chooseColor1;
			case KeyOverlay2:
				chooseColor = chooseColor2;
				for (size_t t = 0; t < cntCpy; t++)
				{
					// ���ǲ�����������ɫ�����ֻ�������
					img->Pixels[row*w + dstNowRowAt+t] = MyColor(rawbuffer[rawNowAt + t]);
				}
				rawNowAt += cntCpy;
				break;
			default:
				break;
			}
			dstNowRowAt += cntCpy;
		}
		rawEndAt++;
		rawBeginAt = rawEndAt;
	}
	return img;
}

void ImageLib::SetPath(string wixPath)
{
	mWixPath = wixPath;
	mWilPath = wixPath.substr(0, wixPath.length() - 4) + ".wil";
}
