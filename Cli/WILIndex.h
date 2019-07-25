#pragma once
#include <string>
using std::string;

#define _IMAGE_TILES				0
#define _IMAGE_TILES30				1
#define _IMAGE_TILES5				2
#define _IMAGE_SMTILES				3
#define _IMAGE_HOUSES				4
#define _IMAGE_CLIFFS				5
#define _IMAGE_DUNGEONS				6
#define _IMAGE_INNERS				7
#define _IMAGE_FUNITURES			8
#define _IMAGE_WALLS				9
#define _IMAGE_SMOBJECTS			10
#define _IMAGE_ANIMATIONS			11
#define _IMAGE_OBJECT1				12
#define _IMAGE_OBJECT2				13

#define _IMAGE_INTER				70
#define _IMAGE_M_HUMAN				71
#define _IMAGE_M_WEAPON1			72
#define _IMAGE_M_WEAPON2			73
#define _IMAGE_M_WEAPON3			74
#define _IMAGE_M_WEAPON4			75
#define _IMAGE_M_WEAPON5			76
#define _IMAGE_WM_HUMAN				77
#define _IMAGE_WM_WEAPON1			78
#define _IMAGE_WM_WEAPON2			79
#define _IMAGE_WM_WEAPON3			80
#define _IMAGE_WM_WEAPON4			81
#define _IMAGE_WM_WEAPON5			82

#define _IMAGE_M_HAIR				133
#define _IMAGE_M_HELMET1			134
#define _IMAGE_WM_HAIR				135
#define _IMAGE_WM_HELMET1			136
#define _IMAGE_M_HELMET2			146
#define _IMAGE_WM_HELMET2			147

#define _IMAGE_MAGIC				83
#define _IMAGE_ITEM_INVENTORY		84
#define _IMAGE_ITEM_EQUIP			85
#define _IMAGE_ITEM_GROUND			86
#define _IMAGE_MICON				87
#define _IMAGE_PROGUSE				88
#define _IMAGE_HORSE				89

#define _IMAGE_MONSTER1				90
#define _IMAGE_MONSTER2				91
#define _IMAGE_MONSTER3				92
#define _IMAGE_MONSTER4				93
#define _IMAGE_MONSTER5				94
#define _IMAGE_MONSTER6				95
#define _IMAGE_MONSTER7				96
#define _IMAGE_MONSTER8				97
#define _IMAGE_MONSTER9				98
#define _IMAGE_MONSTER10			99
#define _IMAGE_MONSTER11			100
#define _IMAGE_MONSTER12			101
#define _IMAGE_MONSTER13			102
#define _IMAGE_MONSTER14			103
#define _IMAGE_MONSTER15			104
#define _IMAGE_MONSTER16			105
#define _IMAGE_MONSTER17			106
#define _IMAGE_MONSTER18			107
#define _IMAGE_MONSTER19			108
#define _IMAGE_MONSTER20			109

#define _IMAGE_SMONSTER1			110
#define _IMAGE_SMONSTER2			111
#define _IMAGE_SMONSTER3			112
#define _IMAGE_SMONSTER4			113
#define _IMAGE_SMONSTER5			114
#define _IMAGE_SMONSTER6			115
#define _IMAGE_SMONSTER7			116	
#define _IMAGE_SMONSTER8			117
#define _IMAGE_SMONSTER9			118
#define _IMAGE_SMONSTER10			119	
#define _IMAGE_SMONSTER11			120
#define _IMAGE_SMONSTER12			121
#define _IMAGE_SMONSTER13			122
#define _IMAGE_SMONSTER14			123	
#define _IMAGE_SMONSTER15			124
#define _IMAGE_SMONSTER16			125
#define _IMAGE_SMONSTER17			126
#define _IMAGE_SMONSTER18			127	
#define _IMAGE_SMONSTER19			128
#define _IMAGE_SMONSTER20			129

#define _IMAGE_NPC					130
#define _IMAGE_MONMAGIC				131
#define _MAX_MONSTER_IMAGE			132

//死亡的怪物?
#define _IMAGE_D_MONSTER1			137
#define _IMAGE_D_SMONSTER1			138
#define _IMAGE_MAGICEX				139
#define _IMAGE_MONMAGICEX			140
#define _IMAGE_STOREITEM			141
#define _IMAGE_MONMAGICEX2			142
#define _IMAGE_MONSTER54			143
#define _IMAGE_FLAG					144
#define _IMAGE_MONMAGICEX3			145
#define _IMAGE_MonMagicEx4			148
#define _IMAGE_MAGICEX2				149




#define _IMAGE_INTEREX				70	//已经没有这个文件了，用gameinter代替


#define _MAX_IMAGE					150



static string WilList[150] =
{
	".\\Data\\tilesc.wil",								//0
	".\\Data\\tiles30c.wil",							//1
	".\\Data\\Tiles5c.wil",								//2
	".\\Data\\smtilesc.wil",							//3
	".\\Data\\housesc.wil",								//4
	".\\Data\\cliffsc.wil",								//5
	".\\Data\\dungeonsc.wil",							//6
	".\\Data\\innersc.wil",								//7
	".\\Data\\furnituresc.wil",							//8
	".\\Data\\wallsc.wil",								//9
	".\\Data\\smobjectsc.wil",							//10
	".\\Data\\animationsc.wil",							//11
	".\\Data\\object1c.wil",							//12
	".\\Data\\object2c.wil",							//13

	".\\Data\\Wood\\tilesc.wil",						//14
	".\\Data\\Wood\\tiles30c.wil",						//15
	".\\Data\\Wood\\Tiles5c.wil",						//16
	".\\Data\\Wood\\smtilesc.wil",						//17
	".\\Data\\Wood\\housesc.wil",						//18
	".\\Data\\Wood\\cliffsc.wil",						//19
	".\\Data\\Wood\\dungeonsc.wil",						//20
	".\\Data\\Wood\\innersc.wil",						//21
	".\\Data\\Wood\\furnituresc.wil",					//22
	".\\Data\\Wood\\wallsc.wil",						//23
	".\\Data\\Wood\\smobjectsc.wil",					//24
	".\\Data\\Wood\\animationsc.wil",					//25
	".\\Data\\Wood\\object1c.wil",						//26
	".\\Data\\Wood\\object2c.wil",						//27

	".\\Data\\Sand\\tilesc.wil",						//28
	".\\Data\\Sand\\tiles30c.wil",						//29
	".\\Data\\Sand\\Tiles5c.wil",						//30
	".\\Data\\Sand\\smtilesc.wil",						//31
	".\\Data\\Sand\\housesc.wil",						//32
	".\\Data\\Sand\\cliffsc.wil",						//33
	".\\Data\\Sand\\dungeonsc.wil",						//34
	".\\Data\\Sand\\innersc.wil",						//35
	".\\Data\\Sand\\furnituresc.wil",					//36
	".\\Data\\Sand\\wallsc.wil",						//37
	".\\Data\\Sand\\smobjectsc.wil",					//38
	".\\Data\\Sand\\animationsc.wil",					//39
	".\\Data\\Sand\\object1c.wil",						//40
	".\\Data\\Sand\\object2c.wil",						//41

	".\\Data\\Snow\\tilesc.wil",						//42
	".\\Data\\Snow\\tiles30c.wil",						//43
	".\\Data\\Snow\\Tiles5c.wil",						//44
	".\\Data\\Snow\\smtilesc.wil",						//45
	".\\Data\\Snow\\housesc.wil",						//46
	".\\Data\\Snow\\cliffsc.wil",						//47
	".\\Data\\Snow\\dungeonsc.wil",						//48
	".\\Data\\Snow\\innersc.wil",						//49
	".\\Data\\Snow\\furnituresc.wil",					//50
	".\\Data\\Snow\\wallsc.wil",						//51
	".\\Data\\Snow\\smobjectsc.wil",					//52
	".\\Data\\Snow\\animationsc.wil",					//53
	".\\Data\\Snow\\object1c.wil",						//54
	".\\Data\\Snow\\object2c.wil",						//55

	".\\Data\\Forest\\tilesc.wil",						//56
	".\\Data\\Forest\\tiles30c.wil",					//57
	".\\Data\\Forest\\Tiles5c.wil",						//58
	".\\Data\\Forest\\smtilesc.wil",					//59
	".\\Data\\Forest\\housesc.wil",						//60
	".\\Data\\Forest\\cliffsc.wil",						//61
	".\\Data\\Forest\\dungeonsc.wil",					//62
	".\\Data\\Forest\\innersc.wil",						//63
	".\\Data\\Forest\\furnituresc.wil",					//64
	".\\Data\\Forest\\wallsc.wil",						//65
	".\\Data\\Forest\\smobjectsc.wil",					//66
	".\\Data\\Forest\\animationsc.wil",					//67
	".\\Data\\Forest\\object1c.wil",					//68
	".\\Data\\Forest\\object2c.wil",					//69

	".\\Data\\GameInter.wil",							//70
	".\\Data\\M-Hum.wil",								//71
	".\\Data\\M-Weapon1.wil",							//72
	".\\Data\\M-Weapon2.wil",							//73
	".\\Data\\M-Weapon3.wil",							//74
	".\\Data\\M-Weapon4.wil",							//75
	".\\Data\\M-Weapon5.wil",							//76
	".\\Data\\WM-Hum.wil",								//77
	".\\Data\\WM-Weapon1.wil",							//78
	".\\Data\\WM-Weapon2.wil",							//79
	".\\Data\\WM-Weapon3.wil",							//80
	".\\Data\\WM-Weapon4.wil",							//81
	".\\Data\\WM-Weapon5.wil",							//82

	".\\Data\\Magic.wil",								//83
	".\\Data\\Inventory.wil",							//84
	".\\Data\\Equip.wil",								//85
	".\\Data\\Ground.wil",								//86
	".\\Data\\MIcon.wil",								//87
	".\\Data\\ProgUse.wil",								//88
	".\\Data\\Horse.wil",								//89

	".\\Data\\Mon-1.wil",								//90
	".\\Data\\Mon-2.wil",								//91
	".\\Data\\Mon-3.wil",								//92
	".\\Data\\Mon-4.wil",								//93
	".\\Data\\Mon-5.wil",								//94
	".\\Data\\Mon-6.wil",								//95
	".\\Data\\Mon-7.wil",								//96
	".\\Data\\Mon-8.wil",								//97
	".\\Data\\Mon-9.wil",								//98
	".\\Data\\Mon-10.wil",								//99
	".\\Data\\Mon-11.wil",								//100
	".\\Data\\Mon-12.wil",								//101
	".\\Data\\Mon-13.wil",								//102
	".\\Data\\Mon-14.wil",								//103
	".\\Data\\Mon-15.wil",								//104
	".\\Data\\Mon-16.wil",								//105
	".\\Data\\Mon-17.wil",								//106
	".\\Data\\Mon-18.wil",								//107
	".\\Data\\Mon-19.wil",								//108
	".\\Data\\Mon-20.wil",								//109
	".\\Data\\MonS-1.wil",								//110
	".\\Data\\MonS-2.wil",								//111
	".\\Data\\MonS-3.wil",								//112
	".\\Data\\MonS-4.wil",								//113
	".\\Data\\MonS-5.wil",								//114
	".\\Data\\MonS-6.wil",								//115
	".\\Data\\MonS-7.wil",								//116
	".\\Data\\MonS-8.wil",								//117
	".\\Data\\MonS-9.wil",								//118
	".\\Data\\MonS-10.wil",								//119
	".\\Data\\MonS-11.wil",								//120
	".\\Data\\MonS-12.wil",								//121
	".\\Data\\MonS-13.wil",								//122
	".\\Data\\MonS-14.wil",								//123
	".\\Data\\MonS-15.wil",								//124
	".\\Data\\MonS-16.wil",								//125
	".\\Data\\MonS-17.wil",								//126
	".\\Data\\MonS-18.wil",								//127
	".\\Data\\MonS-19.wil",								//128
	".\\Data\\MonS-20.wil",								//129

	".\\Data\\NPC.wil",									//130
	".\\Data\\MonMagic.wil",							//131
	".\\Data\\MonImg.wil",								//132	¹ÖÎïÍ·Ïñ
	".\\Data\\M-Hair.wil",								//133
	".\\Data\\M-Helmet1.wil",							//134
	".\\Data\\WM-Hair.wil",								//135
	".\\Data\\WM-Helmet1.wil",							//136
	".\\Data\\DMon-1.wil",								//137
	".\\Data\\DMonS-1.wil",								//138
	".\\Data\\MagicEx.wil",								//139
	".\\Data\\MonMagicEx.wil",							//140
	".\\Data\\StoreItem.wil",							//141
	".\\Data\\MonMagicEx2.wil",							//142
	".\\Data\\Mon-54.wil",								//143
	".\\Data\\Flag.wil",								//144
	".\\Data\\MonMagicEx3.wil",							//145
	".\\Data\\M-Helmet2.wil",							//146
	".\\Data\\WM-Helmet2.wil",							//147
	".\\Data\\MonMagicEx4.wil",							//148
	".\\Data\\MagicEx2.wil"								//149
};