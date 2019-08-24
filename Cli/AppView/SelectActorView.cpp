#include "SelectActorView.h"
#include "../MyGfx.h"
#include "../Common.h"
#include "../SoundMgr.h"

#define IMG_IDX_SELECT_CHR_BACK				50// ±³¾°
#define IMG_IDX_SELECT_CREATE				51
#define IMG_IDX_SELECT_DELETE				53
#define IMG_IDX_SELECT_START				55
#define IMG_IDX_SELECT_EXIT					57

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

#define MP3_SELECT "SelChr.mp3"
#define MP3_TOCREATECHAR					"ToCreateChr.mp3"
#define MP3_TOSELECTCHAR					"ToSelectChr.mp3"
#define MP3_STARTGAME						"StartGame.mp3"

SelectActorView::SelectActorView()
{
	ImageLib lib;
	lib.Load(".\\Data\\Interface1c.wil");
	GuiHelper helper(&lib);

	MyGfx::Instance()->Resize(640, 480);
	UI = new YxGUI::Canvas();
	UI->SetLocalSize(640, 480);

	_bg = MyGfx::CreateSpriteFromImage(lib.LoadImage(IMG_IDX_SELECT_CHR_BACK));

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
	delete _bg;
	_bg = nullptr;
}

void SelectActorView::Draw()
{
	MyGfx::Instance()->DrawCommand(_bg, 0, 0, MyGfx::Layer::Bottom);
	UI->Draw();
}

bool SelectActorView::HandleEvent(SDL_Event & e)
{
	return UI->HandleEvent(e);
}

void SelectActorView::OnShow()
{
	UI->Visiable = true;
	SoundMgr::Instance()->PlayMusic(MP3_SELECT, 0, true);
}

void SelectActorView::OnHide()
{
	UI->Visiable = false;
}

void SelectActorView::Binding()
{
	Exit->onClick += [this]() {
		MyGfx::Instance()->Exit();
	};
}
