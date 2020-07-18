#include "ImageLib.h"
#include <assert.h>

const uint32_t ImageLib::MaskR = 0x000000ff;
const uint32_t ImageLib::MaskG = 0x0000ff00;
const uint32_t ImageLib::MaskB = 0x00ff0000;
const uint32_t ImageLib::MaskA = 0xff000000;

const unsigned char ImageLib::KeyNone = 0xc0;// 透明
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
	Clear();
}

bool ImageLib::Load(string path)
{
	SetPath(path);
	Clear();
	// 从wil文件获取版本号
	auto fpeekVer = fopen(mWilPath.c_str(), "rb");
	//assert(fpeekVer != nullptr);
	if (fpeekVer == nullptr) {
		mLoaded = false;
		return false;
	}
	fseek(fpeekVer, 22, SEEK_SET);
	fread(reinterpret_cast<void*>(&mVersion), 2, 1, fpeekVer);
	fclose(fpeekVer);

	FILE* f = fopen(mWixPath.c_str(), "rb");
	if (f == nullptr) {
		mLoaded = false;
		return false;
	}
	mIdx3 = new Index3();
	fread(reinterpret_cast<void*>(mIdx3), sizeof(Index3) - 4, 1, f);
	mIdx3->Data = new int32_t[mIdx3->ImgCount];
	fseek(f, WixOffset(mVersion), SEEK_SET);
	fread(reinterpret_cast<void*>(mIdx3->Data), sizeof(int32_t), mIdx3->ImgCount, f);
	fclose(f);
	mLoaded = true;
	return true;
}

bool ImageLib::IsLoaded()
{
	return mLoaded;
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
	assert(index < mIdx3->ImgCount);
	if (index >= mIdx3->ImgCount)
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
	memset(reinterpret_cast<void*>(img->Pixels), 0, img->Width*img->Height * sizeof(MyColor));// 置为黑色透明
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
					// 考虑不在这里做颜色变更，只做个标记
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

bool ImageLib::EnableAt(uint32_t index)
{
	if (index >= mIdx3->ImgCount)
		return false;
	if(mIdx3->Data[index] <= 0)
		return false;
	return true;
}

uint32_t ImageLib::ImgCount()
{
	return mIdx3->ImgCount;
}

void ImageLib::SetPath(string path)
{
	mWixPath = path.substr(0, path.length() - 4) + ".wix";
	mWilPath = path.substr(0, path.length() - 4) + ".wil";
}

void ImageLib::Clear()
{
	if (mIdx3 != nullptr) {
		delete mIdx3;
		mIdx3 = nullptr;
	}
	if (mWilFile != nullptr)
	{
		fclose(mWilFile);
		mWilFile = nullptr;
	}
}
