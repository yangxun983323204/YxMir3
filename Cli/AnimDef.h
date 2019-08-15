// ¸ÃÎÄ¼þ¶¨ÒåÐòÁÐÖ¡¶¯»­ todo

#pragma once
#include <stdint.h>

struct FrameAnim
{
	uint16_t First;
	uint16_t Count;
	uint16_t Delay;
};
struct AnimInstance : FrameAnim
{
	uint16_t End;
	uint16_t Current;
	uint16_t CurrentDelay;

	inline void Reset(const FrameAnim& anim,int offset) {
		this->First = anim.First+offset;
		this->Count = anim.Count;
		this->Delay = anim.Delay;
		this->End = this->First + this->Count;
		this->Current = this->First;
		this->CurrentDelay = 0;
	}
	inline void Update(uint32_t delta)
	{
		CurrentDelay += delta;
		if (CurrentDelay >= Delay)
		{
			Current += 1;
			CurrentDelay -= Delay;
			if (Current >= End)
				Current = First;
		}
	}
};
// todo
struct EffectFrameAnim :FrameAnim
{
};

static FrameAnim HeroAnim[_MAX_HERO_MTN]{
	{    0,  4, 200},			// _MT_STAND		
	{   80,  6, 100},			// _MT_ARROWATTACK	
	{  160,  5,  80},			// _MT_SPELL1		
	{  240,  5,  80},			// _MT_SPELL2		
	{  320,  1, 100},			// _MT_HOLD		
	{  400,  1, 100},			// _MT_PUSHBACK	
	{  480,  1, 100},			// _MT_PUSHBACKFLY	
	{  560,  3, 200},			// _MT_ATTACKMODE	
	{  640,  2, 300},			// _MT_CUT			
	{  720,  6,  85},			// _MT_ONEVSWING
	{  800,  6,  85},			// _MT_TWOVSWING	
	{  880,  6,  85},			// _MT_ONEHSWING	
	{  960,  6,  85},			// _MT_TWOHSWING	
	{ 1040,  6,  85},			// _MT_SPEARVSWING	
	{ 1120,  6,  85},			// _MT_SPEARHSWING	
	{ 1200,  3, 100},			// _MT_HITTED		
	{ 1280, 10,  70},			// _MT_WHEELWIND	
	{ 1360, 10,  90},			// _MT_RANDSWING	
	{ 1440, 10, 100},			// _MT_BACKDROPKICK
	{ 1520, 10, 120},			// _MT_DIE			
	{ 1600, 10, 100},			// _MT_SPECIALDIE	
	{ 1680,  6,  90},			// _MT_WALK		
	{ 1760,  6, 120},			// _MT_RUN			
	{ 1840,  6, 100},			// _MT_MOODEPO		
	{ 1920, 10, 100},			// _MT_ROLL		
	{ 2000,  4, 180},			// _MT_FISHSTAND	
	{ 2080,  3, 180},			// _MT_FISHHAND	
	{ 2160,  8, 180},			// _MT_FISHTHROW	
	{ 2240,  8, 180},			// _MT_FISHPULL	
	{ 2320,  4, 200},			// _MT_HORSESTAND	
	{ 2400,  6, 100},			// _MT_HORSEWALK	
	{ 2480,  6, 100},			// _MT_HORSERUN	
	{ 2560,  3, 100},			// _MT_HORSEHIT	
};
static FrameAnim MonsterAnim[_MAX_MON_MTN]{
	{     0,  4, 300},			// _MT_MON_STAND.
	{    80,  6, 130},			// _MT_MON_WALK.
	{   160,  6, 120},			// _MT_MON_ATTACK_A.
	{   240,  2, 300},			// _MT_MON_HITTED.
	{   320, 10, 150},			// _MT_MON_DIE.
	{   400,  6, 150},			// _MT_MON_ATTACK_B1.
	{   480, 10, 150},			// _MT_MON_SPELL_A2.
	{   560, 10, 150},			// _MT_MON_SPELL_B.
	{   640,  6, 150},			// _MT_MON_APPEAR.
	{   880,  1, 150},			// _MT_MON_SPECIAL_MTN.
};
static FrameAnim NPCAnim[_MAX_NPC_MTN]{
	{     0,  4, 300},			// _MT_NPC_STAND.
	{    30, 10, 300},			// _MT_NPC_ACT01.
	{    60,  6, 300},			// _MT_NPC_ACT02.
};

/*EffectFrameAnim EffectAnim[_MAX_EFFECT]{
	{  230,  236, 100, _IMAGE_MAGIC,       _SKILL_BANWOL, 3, 4, 100, 100, 100, 100, 100, 170},	// ¹Ý¿ù°ø°Ý 12½Ã.
	{   60,   70, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 100, 100, 100, 100, 160, 100, 255, 255, 255, _BLEND_NORMAL},	// ¾Ï¿¬¼ú ½ÃÀü.
	{   90,   98, 100, _IMAGE_MAGIC,     _SKILL_FIREWIND, 3, 4, 100, 100, 100, 100, 140, 180},	// È­¿°Ç³.
	{ 1820, 1828, 100, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4, 100, 100, 100, 100, 140, 180},	// ¿°»çÀå ½ÃÀü.
	{    0,    9, 100, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 100, 100, 100, 170, 100, 100},	// ·ÚÈ¥°Ý½ÃÀü.
	{  110,  129, 100, _IMAGE_MAGIC,    _SKILL_SPACEMOVE, 3, 4, 100, 100, 100, 170, 100, 100},	// ¾Æ°øÇà¹ý.
	{  130,  140, 100, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 100, 100, 100, 170, 100, 100},	// »çÀÚÀ±È¸½ÃÀü.
	{ 1820, 1828, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 3, 4, 100, 100, 100, 100, 140, 180},	// È­¿°Àå.
	{  600,  610, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 100, 100, 100, 140, 100, 120},	// È¸º¹¼ú.
	{  630,  640, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 100, 100, 100, 170, 100, 100},	// °á°è.
	{  660,  670, 100, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 3, 4, 100, 100, 100, 140, 100, 120},	// ´ëÈ¸º¹.
																					//	SetEffectInfo(&m_stEffectSpr[11],  690,  704, 100, _IMAGE_MAGIC,  _SKILL_LIGHTFLOWER, 3, 4, 100, 100, 100, 170, 100, 100);	// ·Ú¼³È­.
	{  690,  704, 100, _IMAGE_MAGIC,  _SKILL_LIGHTFLOWER, 3, 4, 150, 100,  50, 150, 100,  50},	// ·Ú¼³È­.	
	{ 1970, 1978,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 3, 4, 100, 100, 100, 170, 100, 100},	// ·ÚÀÎÀå.
	{  740,  750, 100, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 100, 100, 100, 120, 100, 120},	// ¹é°ñ¼ÒÈ¯¼ú.
	{  770,  780, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 3, 4, 100, 100, 100, 170, 100, 100},	// ºù¼³Ç³.
	{  870,  890, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4, 100, 100, 100, 100, 100, 170},	// Å½±âÆÄ¿¬.
	{  910,  920, 100, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 3, 4, 100, 100, 100, 100, 140, 180},	// Áö¿°¼ú.
	{  940,  950, 100, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 3, 4, 100, 100, 100, 100, 140, 180},	// Æø¿­ÆÄ.
	{ 1560, 1569, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 3, 4, 100, 100, 100, 100, 140, 180},	// ±Ý°­È­¿°Àå.
	{  320,  326, 100, _IMAGE_MAGIC,        _SKILL_ERGUM, 3, 4, 100, 100, 100, 100, 100, 170},	// ¾î°Ë¼ú.
	{ 1350, 1356, 100, _IMAGE_MAGIC,         _SKILL_YEDO, 3, 4, 100, 100, 100, 100, 100, 170},	// ¿¹µµ°Ë¹ý.
	{ 1470, 1476, 100, _IMAGE_MAGIC,    _SKILL_FIRESWORD, 3, 4, 100, 100, 100, 100, 140, 180},	// ¿°È­°á.
	{ 1430, 1445, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 3, 4, 100, 100, 100, 170, 100, 100},	// °­°Ý.
	{  810,  820, 100, _IMAGE_MAGIC,        _SKILL_CLOAK, 3, 4, 150, 150, 150, 200, 150, 180},	// Àº½Å.
	{ 2080, 2086, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 3, 4, 150, 100,  50, 200, 150, 100},	// Ç×¸¶Áø¹ý.
	{ 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 3, 4, 150, 180, 200, 180, 200, 220},	// ´ëÁö¿øÈ£.
	{ 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 3, 4, 100, 150, 200, 150, 200, 250},	// Æø»ì°è.
	{ 2080, 2086, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 3, 4, 150, 150, 150, 200, 150, 180},	// ´ëÀº½Å.
	{ 2180, 2190, 100, _IMAGE_MAGIC,     _SKILL_JUMPSHOT, 3, 4, 150, 150, 150, 200, 150, 180},	// Á¡ÇÁ¼¦.
	{ 2270, 2280, 100, _IMAGE_MAGIC,    _SKILL_RANDSWING, 3, 4, 150, 150, 150, 200, 150, 180},	// ·£´ý½ºÀ®.
	{ 2080, 2086, 100, _IMAGE_MAGIC,		_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255},	// ½Å¼ö¼ÒÈ¯.

	{ 1680, 1686, 100, _IMAGE_MONMAGIC, _MONMAGIC_NUMAGUMGI, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255},			// ÁÖ¼úÀÇ¸·.
};*/
/*EffectFrameAnim MagicAnim[_MAX_MAGIC]{
	{   70,   88, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 190, 220, 190, 190, 240, 190, 255, 255, 255, _BLEND_NORMAL}, // ¾Ï¿¬¼ú.
	{ 1900, 1960,  50, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4,  70,  90, 110,  90, 120, 150},	// ¿°»çÀå.
	{   10,   30,  50, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 200, 100, 100, 250, 150, 150},	// ·ÚÈ¥°Ý.
	{  140,  159,  50, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 200, 100, 100, 100,  75,  50},	// »çÀÚÀ±È¸.
	{  420,  425,  20, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 100, 150, 200, 150, 200, 250},	// È­¿°Àå.
	{  610,  620, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 200, 140, 170, 230, 170, 200},	// È¸º¹¼ú.
	{  640,  650, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 120,  60,  60, 150,  80,  80},	// °á°è.
	{  670,  680,  50, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 4, 5, 200, 140, 170, 230, 170, 200},//200, 100, 100, 250, 150, 150);	// ´ëÈ¸º¹.
	{ 2050, 2056,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 2, 3, 150, 100, 100, 200, 150, 150},	// ·ÚÀÎÀå.
	{  750,  760, 155, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 150, 150, 150, 200, 150, 180},	// ¹é°ñ¼ÒÈ¯¼ú.
	{  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 5, 6, 255, 123,   0, 255, 123,   0, 255, 255, 255, _BLEND_LIGHTINV, 0, 1 },	// ºù¼³Ç³.
																																	//	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 4, 5, 220, 150, 150, 250, 170, 170);	// ºù¼³Ç³.
	{  840,  850, 100, _IMAGE_MAGIC,       _SKILL_SHIELD, 3, 4, 100, 100, 100, 100, 140, 180},	// ÁÖ¼úÀÇ¸·.
	{  890,  900, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4,  75,  75,  75, 100,  75,  50},	// Å½±âÆÄ¿¬.
	{  920,  930, 120, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 4, 5,  40,  60,  80,  60,  80, 100},	// Áö¿°¼ú.
	{  980,  983, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 100, 150, 200, 150, 200, 250, 255, 255, 255, _BLEND_NORMAL, 255},	// Æø»ì°è.
	{  980,  983, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 2, 3, 150, 100,  50, 200, 150, 100, 255, 255, 255, _BLEND_NORMAL, 255},	// Ç×¸¶Áø¹ý.
	{  980,  983, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 2, 3, 150, 180, 200, 180, 200, 220, 255, 255, 255, _BLEND_NORMAL, 255},	// ´ëÁö¿øÈ£.
	{  950,  970, 100, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 5, 6, 100, 150, 200, 150, 200, 250},	// Æø¿­ÆÄ.
	{ 1640, 1646,  20, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 100, 150, 200, 150, 200, 250},	// ±Ý°­È­¿°Àå.
																							//	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 5, 6, 250, 150, 150, 255, 200, 200);	// °­°Ý.
	{ 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 20, 21, 255, 125, 50, 255, 255, 255 },	// °­°Ý.
	{  980,  983, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 2, 3, 150, 150, 150, 200, 150, 180},	// ´ëÀº½Å.
	{  110,  129,  60, _IMAGE_MAGIC,   _SKILL_SPACEMOVE2, 3, 4, 100, 100, 100, 100, 100, 100},	// ¾Æ°øÇà¹ý2.
	{  110,  129, 100, _IMAGE_MAGIC,   _SKILL_SPACEMOVE3, 3, 4, 100, 100, 100, 100, 100, 100},	// ¾Æ°øÇà¹ý3.
	
																							//~~~ Monster Magic Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	{    0,    4, 100, _IMAGE_MONMAGIC,    _MONMAGIC_KEPAL, 2, 3, 100, 100, 100, 150, 150, 150},
	{  300,  320, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE, 2, 3, 100, 100,  50, 150, 150,  75},
	{   20,   30, 100, _IMAGE_MONMAGIC,   _MONMAGIC_BLACK1, 2, 3, 100, 100, 100, 150, 150, 150},
	{   40,   50, 100, _IMAGE_MONMAGIC,   _MONMAGIC_BLACK2, 2, 3, 100, 100, 100, 150, 150, 150},
	{   80,   86, 100, _IMAGE_MONMAGIC,  _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150},
	{  200,  208, 100, _IMAGE_MONMAGIC, _MONMAGIC_GREATANT, 2, 3, 100, 100, 100, 150, 150, 150},
	{  280,  289, 100, _IMAGE_MONMAGIC,	   _MONMAGIC_RED1, 2, 3, 100, 100, 100, 150, 150, 150 },
	{   40,   50, 100, _IMAGE_MONMAGIC,     _MONMAGIC_RED2, 2, 3, 100, 100, 100, 150, 150, 150},
	{  220,  227, 100, _IMAGE_MONMAGIC,      _MONMAGIC_ANT, 2, 3, 100, 100, 100, 150, 150, 150},
	{  240,  246, 100, _IMAGE_MONMAGIC,  _MONMAGIC_WORKANT, 2, 3, 100, 100, 100, 150, 150, 150},
	{  440,  446, 100, _IMAGE_MONMAGIC, _MONMAGIC_COWGHOST, 2, 3, 100, 100, 100, 150, 150, 150},	// ¿ì¸é±Í¿Õ.
	{  980,  986, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINSU, 2, 3, 100, 100, 100, 150, 150, 150},	// ½Å¼ö.
	{  600,  606, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE, 2, 3, 100, 100, 100, 150, 150, 150},	// Á»ºñ.
	{  720,  728, 100, _IMAGE_MONMAGIC, _MONMAGIC_JUMAWANG, 2, 3, 100, 100, 100, 150, 150, 150},	// ÁÖ¸¶¿Õ.
	
	{ 1240, 1241, 100, _IMAGE_MONMAGIC,         _MONMAGIC_CHIM, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255},	// ´ÙÅ©Ä§.
	{ 1400, 1401, 100, _IMAGE_MONMAGIC,        _MONMAGIC_ARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255},	// ±Ã¼ö°æºñÈ­»ì.
	{ 1070, 1071, 100, _IMAGE_MONMAGIC,      _MONMAGIC_MAARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255},	// ¸¶±Ã»çÈ­»ì.
	{  800,  806, 100, _IMAGE_MONMAGIC,      _MONMAGIC_DUALAXE, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255},	// ½Öµµ³¢ÇØ°ñ´øÁö±â.
	{  520,  527, 100, _IMAGE_MONMAGIC,     _MONMAGIC_COWFLAME, 2, 3, 100, 100, 100, 150, 150, 150},	// È­¿°¿ì¸é±Í.
	{  360,  370, 100, _IMAGE_MONMAGIC,  _MONMAGIC_BIGGINE_ATT, 2, 3, 100, 100, 100, 150, 150, 150},	// ÃË·æ½Å °ø°Ý.
	{  380,  400, 100, _IMAGE_MONMAGIC, _MONMAGIC_BIGGINE_CHAR, 2, 3, 100, 100, 100, 150, 150, 150},	// ÃË·æ½Å¿¡ °ø°Ý´çÇÔ.
	{  320,  330,  70, _IMAGE_MONMAGIC,     _MONMAGIC_SANDFISH, 2, 3, 100, 100, 100, 150, 150, 150,  10,  10,  10, _BLEND_LIGHTINV, 0 },		// »ç¾î°ø°Ý.
	{  260,  266, 100, _IMAGE_MONMAGIC,       _MONMAGIC_BAODIE, 2, 3, 100, 100, 100, 150, 150, 150 },	// ¹Ùº¸´ÞµåÁ×À½.
	{  880,  886, 150, _IMAGE_MONMAGIC,        _MONMAGIC_SSEGI, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15 },		// ½û±â³ª¹æÅ¸¾×.
	{   60,   70, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINGI_DIE, 2, 3, 100, 100, 100, 150, 150, 150},	// ¸ó½ºÅÍÁ×±â. °æ°©¿Ê±â»ç, È«ÀÇ, ÈæÀÇ¸¶¹ý»ç. // ¹æÇâ±¸º°Àº ¾ø´Ù.
	{  680,  689, 100, _IMAGE_MONMAGIC,     _MONMAGIC_HUSU_DIE, 2, 3, 100, 100, 100, 150, 150, 150},	// Çã¼ö¾ÆºñÁ×±â.
	{  700,  708, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE_DIE, 2, 3, 100, 100, 100, 150, 150, 150},	// Á»ºñÁ×±â.
	{
	{  980,  983, 10, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255 },	// ½Å¼ö.
	
	{  1770,  1790, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE1, 2, 3, 100, 100,  50, 150, 150,  75 },
};*/
/*EffectFrameAnim ExplosionAnim[_MAX_EXPLOSION]{
	{  200,  220,  80, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 4, 5, 200, 150,  60, 255, 170, 100, 255, 255, 255, _BLEND_LIGHTINV, 0, 1},// Ç×¸¶Áø¹ý.
	{  170,  190,  80, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 4, 5, 120, 170, 220, 160, 210, 255, 255, 255, 255, _BLEND_LIGHTINV, 0, 1 },// ´ëÁö¿øÈ£.
	{  580,  590, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 120, 170, 220, 160, 210, 255},	// È­¿°Àå.
	{ 1140, 1150, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 120, 170, 220, 160, 210, 255},	// Æø»ì°è.
	{ 1800, 1810, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 120, 170, 220, 160, 210, 255},	// ±Ý°­È­¿°Àå.
	{  820,  830, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 4, 5, 200, 210, 190, 200, 150, 180},	// ´ëÀº½Å.
																							//~~~ Monster Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	{  100,  110, 100, _IMAGE_MONMAGIC, _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150 },	// ¹æÇâ±¸º°Àº ¾ø´Ù.
	
	{ 2360, 2379, 100, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255 },	// ½Å¼ö.
};*/