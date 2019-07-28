#include <string>;
#include <control.h>;
//#include <d3d.h>;
//#include <dshow.h>;
#include "..\StdAfx.h"
#include "..\WindHorn\WHEngine.h"        //这个头文件中包含了d3d.h，如果上面再包含则出现二义性。
#include "..\WindHorn\WHWilImage.h"        //包含外部库函数的声明（窗口引擎类）
#include "..\Common\DblList.h"        //避免编译错误，将模板类头文件从预编译头文件中移出,vc6.0会出现内部错误!

#include "..\GFun.h"
#include "..\Define.h"

//连接时使用的外部库所在的目录,
//作为参数时要使用“\\”,作为字符串时“\”或“\\”都 可以。
#pragma comment(lib, "..\\..\\Mir3_Clint\\Lib\\WindHorn.lib")

#define WIDTH        800
#define HEIGHT        492
#define DEPTH        16
//图形主窗口对象，注意这里创建了主窗口对象，
//需要时再通过定制这个窗口对象实现需要的窗口。
CWHDXGraphicWindow                g_xMainWnd(WIDTH, HEIGHT, DEPTH);              //注意构造函数参数列表指定一个硬件支持的模式
CImageHandler                        g_xImage;                                                        //图像处理器
CMapHandler                                g_xMap;                                                                //地图处理器

void RenderObject(INT nLoopTime);

/*
win32程序主进程的启动代码块调用的窗口主函数
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG        msg;        //用于保存从消息队列检索到的消息
						   //调CWHDXGraphicWindow对象的方法创建一个DX窗口
	INT        h = g_xMainWnd.Create(
		hInstance,                //应用程序进程句柄
		"Mir3 mapview ",                //主窗口标题
		NULL,                //菜单
		NULL,                //图标
		_DXG_SCREENMODE_WINDOW,                //窗口模式。
											   //_DXG_SCREENMODE_FULLSCREEN,        //全屏模式
		_DXG_DEVICEMODE_PRIMARY | _DXG_DEVICEMODE_D3D | _DXG_DEVICEMODE_ZBUFFER    //主表面、D3D、Z缓冲
		);
	DWORD        dwStyle;
	dwStyle = GetWindowStyle(g_xMainWnd.GetSafehWnd());        //取得DX图形窗口的风格
	dwStyle &amp;
	= ~dwStyle;        //原始窗口风格清零
	dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;
	SetWindowLong(g_xMainWnd.GetSafehWnd(), GWL_STYLE, dwStyle);        //重新设置窗口风格
	g_xMainWnd.CenterMainWindow();
	//设置主窗口显示特性
	ShowWindow(g_xMainWnd.GetSafehWnd(),
		SW_SHOW
		);
	g_xImage.LoadAllImage();                //加载所有图像库
	g_xMap.LoadMapImage(&amp; g_xImage);       //加载指向构成地图的瓷砖图像库的指针
											   //开始游戏的观察点单元坐标
	g_xMap.m_shStartViewTileX = 0;        //358察看0.map        察看238
	g_xMap.m_shStartViewTileY = 0;        //264察看0.map        察看238
										  //加载指定名字的地图数据
	g_xMap.LoadMapData("zzz1");        //这里给m_wSavedMapBuffer缓冲区加载了解密后的图像数据
									   //绘制地图的地面。
	WORD *pwSrc = g_xMap.m_wSavedMapBuffer;                //地图的一个视区的图像数据源缓冲区24*24个48*32的瓷砖范围
														   //下面的代码块可以替换g_xMainWnd.DrawWithImagePerLineClipRgn函数调用。
	{
		DDSURFACEDESC2        ddsd;
		//取得后缓冲区指针
		LPDIRECTDRAWSURFACE7 pBackBuffer = g_xMainWnd.GetBackBuffer();
		if (pBackBuffer != NULL)
		{
			//初始化DD表面描述结构
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			ddsd.lpSurface = NULL;
			//锁定后缓冲区表面
			pBackBuffer->;
			Lock(NULL, &amp; ddsd, DDLOCK_WAIT, NULL);
			if (!ddsd.lpSurface)                        return FALSE;           //锁定失败返回
			WORD *pwdDst;
			pwdDst = (WORD *)ddsd.lpSurface;       //使用16位指针指向后缓冲区表面，
												   //按列(按行)绘制后缓冲区表面，16位色深每次拷贝2个字节.
												   //这里(0,0) 是目标矩形的左上角，WIDTH，HEIGHT 是目标矩形的宽高，
												   //目标矩形与DD主表面必须有交集矩形
												   //注意，源缓冲区可以看成是_VIEW_CELL_X_COUNT*_CELL_WIDTH*_VIEW_CELL_Y_COUNT*_CELL_HEIGHT*16的表面，
			for (INT Y = 0; Y < HEIGHT; Y++)                                //目标矩形高
				for (INT X = 0; X < WIDTH; X++)                              //目标矩形宽
																			 //for (INT Y = 0 ; Y <HEIGHT; Y++)
				{
					memcpy(&amp; pwdDst[Y * (ddsd.lPitch >; >; 1) + X], &amp; pwSrc[Y * _VIEW_CELL_X_COUNT * _CELL_WIDTH + X], 2);
				}
			pBackBuffer->;
			Unlock(NULL);        //解锁
		}
	}
	g_xMainWnd.CenterMainWindow();
	DWORD dwLastTime, dwTime, dwDelay;        //用于纪录最后时间，时间，延时等数据的全局变量
	dwLastTime = dwTime = dwDelay = 0;        //初值为0
											  //消息循环
	while (TRUE)
	{
		if (PeekMessage(&amp; msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (0 == GetMessage(&amp; msg, NULL, 0, 0))
				return (int)msg.wParam;
			TranslateMessage(&amp; msg);
			DispatchMessage(&amp; msg);
		}
		//没有消息处理就来呈现场景，也就是将后缓冲区表面交换到主表面，若失败则重建主窗口对象的表面。
		else
		{
			dwTime = timeGetTime();        //获取系统当前消息循环的滴答数
			dwDelay = dwTime - dwLastTime;        //当前消息循环滴答数减去上一次的消息循环的滴答数为两次消息处理的延时间隔。
			dwLastTime = dwTime;        //保存当前滴答数为最近一次消息循环的时间
			if (dwDelay != 0)
				RenderObject(dwDelay);        //渲染地图上的物体
			if (FAILED(g_xMainWnd.Present()))
				g_xMainWnd.RestoreSurfaces();
		}
	}//end while
	return msg.wParam;        //将消息参数返回给进程主代码块
}

void RenderObject(INT nLoopTime)
{
	INT         nStartX, nStartY;
	INT  nObjFileIdx, nImgIdx, nArrayNum;
	BOOL bFocused = FALSE;
	BOOL bLongObj = FALSE;
	BOOL bBlend = FALSE;
	BOOL bDrawShadow = TRUE;
	g_xMap.SetAniTileFrame(nLoopTime);        //设置地图上的动画帧
											  // 以地图单元为单位扫描地图的可视区域
	for (INT nXCnt = g_xMap.m_shStartViewTileX; nXCnt < g_xMap.m_shStartViewTileX + _VIEW_CELL_X_COUNT; nXCnt++)
	{
		for (INT nYCnt = g_xMap.m_shStartViewTileY; nYCnt < g_xMap.m_shStartViewTileY + _VIEW_CELL_Y_COUNT; nYCnt++)
		{
			//扫描按列进行，外循环纵向达到或超过地图边界则说明扫描完毕，应该退出循环。
			if (nXCnt >; = g_xMap.m_stMapFileHeader.shWidth)
				break;
			//内循环横向达到或超过地图边界则说明横向一列扫描完毕，继续扫描下一列。
			if (nYCnt >; = g_xMap.m_stMapFileHeader.shHeight || nXCnt < 0 || nYCnt < 0)
				continue;
			//由当前二维地图单元坐标换算出一维地图单元数组的索引
			nArrayNum = nYCnt + nXCnt * g_xMap.m_stMapFileHeader.shHeight;
			// 渲染底层对象 ,底层对象索引文件合法。
			if (g_xMap.m_pstCellInfo[nArrayNum].bFileIdx2 != 255)
			{
				// 底层对象索引号合法
				if (g_xMap.m_pstCellInfo[nArrayNum].wObj2 != 65535)
				{
					//注意如何从单元结构的bFileIdx成员计算出图像库文件的索引号，这个算法必须与对应的图像存储一致。
					//这里bFileIdx2的低4位是底层对象图像库文件的索引，先绘制底层对象，再绘制顶层对象。
					nObjFileIdx = (g_xMap.m_pstCellInfo[nArrayNum].bFileIdx2 &0X0F);
					//底层图像在图像库里的索引号
					nImgIdx = g_xMap.m_pstCellInfo[nArrayNum].wObj2;
					//图像库文件索引合法，0~2是背景瓷砖。
					if (nObjFileIdx > 2 && nObjFileIdx < 14)
					{
						//当前图像设置成功
						assert(nImgIdx > = 0 && nImgIdx <= 0x7fffffff);
						if (g_xMap.m_pxTileImg[nObjFileIdx]->; NewSetIndex(nImgIdx))          //有了对象文件库和图像索引就可以定位对象图像了
						{
							//图像的宽高合乎规定
							if (g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shWidth == 48 &&
							g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight >= 32)
							{
								bBlend = FALSE;        //非混合绘制
													   //        nImgIdx += g_xMap.GetDoorImgIdx(nXCnt, nYCnt);        //越过门，门由单独的代码处理
													   //底层动画
								if (g_xMap.m_pstCellInfo[nArrayNum].bObj2Ani != 255)
								{
									BYTE  bTickType;
									SHORT shAniCnt;
									//计算滴答类型和动画帧数
									bTickType = (g_xMap.m_pstCellInfo[nArrayNum].bObj2Ani & amp; 0X70) >;
									>;
									4;
									shAniCnt = g_xMap.m_pstCellInfo[nArrayNum].bObj2Ani & amp;
									0X0F;
									//计算是否混合绘制
									if ((g_xMap.m_pstCellInfo[nArrayNum].bObj2Ani & amp; 0X80) >; >; 7)
										bBlend = TRUE;
									//得到动画图像索引并设置为当前图像
									nImgIdx += g_xMap.m_bAniTileFrame[bTickType][shAniCnt];
									assert(nImgIdx >; = 0 & amp; &amp; nImgIdx <= 0x7fffffff);
									g_xMap.m_pxTileImg[nObjFileIdx]->;
									NewSetIndex(nImgIdx);
								}
								if (!bBlend)           //非混合绘制
								{
									g_xMainWnd.DrawWithImageForCompClipRgn(
										(nXCnt - g_xMap.m_shStartViewTileX)*_CELL_WIDTH - g_xMap.m_shViewOffsetX,
										(nYCnt - g_xMap.m_shStartViewTileY)*_CELL_HEIGHT - g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight + _CELL_HEIGHT - g_xMap.m_shViewOffsetY,
										g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shWidth,
										g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight,
										(WORD *)g_xMap.m_pxTileImg[nObjFileIdx]->; m_pbCurrImage,
										_CLIP_WIDTH, _CLIP_HEIGHT);
									//        return;
								}
								else        //混合绘制
								{
								}
							}//if图像的宽高合乎规定
						}//if当前图像设置成功
					}//if图像库文件索引合法
				}//if底层对象索引号合法
			}//当前单元的底层图像库文件索引合法
			 //渲染顶层对象
			 //顶层对象库文件索引合法
			if (g_xMap.m_pstCellInfo[nArrayNum].bFileIdx1 != 255)
			{
				//顶层对象索引合法
				if (g_xMap.m_pstCellInfo[nArrayNum].wObj1 != 65535)
				{
					//bFileIdx1 &amp; 0X0F是低4位表示顶层对象图像库文件的索引
					nObjFileIdx = (g_xMap.m_pstCellInfo[nArrayNum].bFileIdx1 & amp; 0X0F);
					nImgIdx = g_xMap.m_pstCellInfo[nArrayNum].wObj1;
					//在规定的对象文件索引范围
					if (nObjFileIdx >; 2 & amp; &amp; nObjFileIdx < 14)
					{
						//成功设置当前图像
						assert(nImgIdx >; = 0 & amp; &amp; nImgIdx <= 0x7fffffff);
						if (g_xMap.m_pxTileImg[nObjFileIdx]->; NewSetIndex(nImgIdx))
						{
							//画面尺寸符合规范
							if (g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shWidth == 48 & amp; &amp;
							g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight >; = 32)
							{
								bBlend = FALSE;
								//        nImgIdx += g_xMap.GetDoorImgIdx(nXCnt, nYCnt);        //越过门
								if (!bBlend)
									g_xMainWnd.DrawWithImageForCompClipRgn(
										(nXCnt - g_xMap.m_shStartViewTileX)*_CELL_WIDTH - g_xMap.m_shViewOffsetX,
										(nYCnt - g_xMap.m_shStartViewTileY)*_CELL_HEIGHT - g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight + _CELL_HEIGHT - g_xMap.m_shViewOffsetY,
										g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shWidth,
										g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight,
										(WORD *)g_xMap.m_pxTileImg[nObjFileIdx]->; m_pbCurrImage,
										_CLIP_WIDTH, _CLIP_HEIGHT);
								else
								{
									g_xImage.AddTextr(_TEXTR_FILE_MAP, nObjFileIdx, nImgIdx);
									LPDIRECTDRAWSURFACE7 lpddsTextr = g_xImage.GetTextrImg(_TEXTR_FILE_MAP, nObjFileIdx, nImgIdx);
									nStartX = (nXCnt - g_xMap.m_shStartViewTileX) * _CELL_WIDTH - g_xMap.m_shViewOffsetX;
									nStartY = -(nYCnt - g_xMap.m_shStartViewTileY) * _CELL_HEIGHT - g_xMap.m_pxTileImg[nObjFileIdx]->;
									m_lpstNewCurrWilImageInfo->;
									shHeight + _CELL_HEIGHT - g_xMap.m_shViewOffsetY;
									D3DMATERIAL7 mtrl;
									D3DVECTOR        vecTrans(nStartX, nStartY, 0);
									D3DVECTOR        vecScale(g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shWidth, g_xMap.m_pxTileImg[nObjFileIdx]->; m_lpstNewCurrWilImageInfo->; shHeight, 1);
									D3DUtil_InitMaterial(mtrl, (FLOAT)255 / 255.0f, (FLOAT)255 / 255.0f, (FLOAT)255 / 255.0f);
									mtrl.diffuse.a = 1.0f / 255.0f;
									g_xMainWnd.Get3DDevice()->;
									SetMaterial(&amp; mtrl);
									g_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), vecTrans, vecScale, mtrl, lpddsTextr);
								}
							}//画面尺寸符合规范
						}//成功设置当前图像
					}//在规定的对象文件索引范围
				}//顶层对象索引合法
			}//渲染顶层对象
		}//for
	}//for
	 // 48*32
}