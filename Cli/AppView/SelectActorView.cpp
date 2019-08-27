#include "SelectActorView.h"
#include "../MyGfx.h"
#include "../Common.h"
#include "../SoundMgr.h"

#define IMG_IDX_SELECT_CHR_BACK				50// 背景
#define IMG_IDX_SELECT_CREATE				51
#define IMG_IDX_SELECT_DELETE				53
#define IMG_IDX_SELECT_START				55
#define IMG_IDX_SELECT_EXIT					57

#define IDX_IMG_MALE_WAR					200
#define IDX_IMG_MALE_WAR_FIRE				260
#define IDX_IMG_MALE_WAR_FIRE_KEEP			320
#define IDX_IMG_MALE_WAR_FIRE_BACK			380

#define CHAR_STAND_ANIM_COUNT	11
#define CHR_ANI_COUNT			20
#define CHAR_ANI_KEEP_COUNT		12
#define CHAR_ANI_BACK_COUNT		8

#define ANIMATION_TICK			200
#define BLEND_TICK				50

// Position of Select buttons
#define SELECT_CHAR_NEW_BTN_POS_X			442
#define SELECT_CHAR_NEW_BTN_POS_Y			98
#define SELECT_CHAR_ERASE_BTN_POS_X			81
#define SELECT_CHAR_ERASE_BTN_POS_Y			247
#define SELECT_CHAR_START_BTN_POS_X			263
#define SELECT_CHAR_START_BTN_POS_Y			53
#define SELECT_CHAR_EXIT_BTN_POS_X			29
#define SELECT_CHAR_EXIT_BTN_POS_Y			441

#define MP3_BG "SelChr.mp3"
#define MP3_TOCREATECHAR					"ToCreateChr.mp3"
#define MP3_TOSELECTCHAR					"ToSelectChr.mp3"
#define MP3_STARTGAME						"StartGame.mp3"

SelectActorView::SelectActorView()
{
	auto lib = _spriteMgr.GetLib(IdxInterface);;
	GuiHelper helper(lib);

	MyGfx::Instance()->Resize(640, 480);
	UI = new YxGUI::Canvas();
	UI->SetLocalSize(640, 480);

	_bg = _spriteMgr.GetSprite(IdxInterface, IMG_IDX_SELECT_CHR_BACK);

	Create = helper.CreateButton(IMG_IDX_SELECT_CREATE, true);
	UI->AddChild(Create);
	Create->SetLocalPos(SELECT_CHAR_NEW_BTN_POS_X, SELECT_CHAR_NEW_BTN_POS_Y);

	Delete = helper.CreateButton(IMG_IDX_SELECT_DELETE, true);
	UI->AddChild(Delete);
	Delete->SetLocalPos(SELECT_CHAR_ERASE_BTN_POS_X, SELECT_CHAR_ERASE_BTN_POS_Y);

	Start = helper.CreateButton(IMG_IDX_SELECT_START, true);
	UI->AddChild(Start);
	Start->SetLocalPos(SELECT_CHAR_START_BTN_POS_X, SELECT_CHAR_START_BTN_POS_Y);

	Exit = helper.CreateButton(IMG_IDX_SELECT_EXIT, true);
	UI->AddChild(Exit);
	Exit->SetLocalPos(SELECT_CHAR_EXIT_BTN_POS_X, SELECT_CHAR_EXIT_BTN_POS_Y);

	Binding();
}

SelectActorView::~SelectActorView()
{
	_bg = nullptr;
}
const int offsetX = -32;
const int offsetY = -51;
void SelectActorView::Draw(uint32_t ms)
{
	MyGfx::Instance()->DrawCommand(_bg, 0, 0, MyGfx::Layer::Bottom);
	// 渲染角色
	Vector2UInt posArray[] = {
		{ 310 + offsetX,310 + offsetY },	// 1
		{ 300 + offsetX,270 + offsetY },	// 2-1
		{ 360 + offsetX,310 + offsetY },	// 2-2
		{ 250 + offsetX,270 + offsetY },	// 3-1
		{ 320 + offsetX,310 + offsetY },	// 3-2
		{ 390 + offsetX,340 + offsetY }		// 3-3
	};
	int x, y;
	for (size_t i = 0; i < _roleCount; i++)
	{
		int idx = IDX_IMG_MALE_WAR + _roles[i].Gender * 300 + _roles[i].Job * 600;
		auto sp = _spriteMgr.GetSprite(IdxInterface, idx);
		x = posArray[i + _roleCount - 1].x;
		y = posArray[i + _roleCount - 1].y;
		MyGfx::Instance()->DrawCommand(sp, x, y, MyGfx::Layer::Mid);
	}
	//
	UI->Draw();
}

bool SelectActorView::HandleEvent(SDL_Event & e)
{
	return UI->HandleEvent(e);
}

void SelectActorView::OnShow()
{
	UI->Visiable = true;
	SoundMgr::Instance()->PlayMusic(MP3_BG, 0, true);
}

void SelectActorView::OnHide()
{
	UI->Visiable = false;
}

void SelectActorView::SetRoleList(Role roles[], uint8_t size)
{
	_roleCount = size > 3 ? 3 : size;
	for (size_t i = 0; i < _roleCount; i++)
	{
		_roles[i] = roles[i];
	}
}

void SelectActorView::Binding()
{
	Exit->onClick += [this]() {
		MyGfx::Instance()->Exit();
	};
}
