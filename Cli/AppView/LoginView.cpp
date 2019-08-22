#include "LoginView.h"
#include "../WILIndex.h"
#include "../MyGfx.h"
#include "../Common.h"
#include "../SoundMgr.h"

#define LOGIN_BUTTON_COUNT			4
#define LOGIN_INPUT_COUNT			2
#define LOGIN_IMAGE_COUNT			4

#define POS_ID_INS_X				173
#define POS_ID_INS_Y				435
#define POS_PASS_INS_X				370
#define POS_PASS_INS_Y				435

#define _LEFT_LOGIN					0
#define _TOP_LOGIN					372
#define _RIGHT_LOGIN				640
#define _BOTTOM_LOGIN				480

#define _LEFT_ID_PASS				150
#define _TOP_ID_PASS				65

#define IMG_IDX_LOGIN_BACK			0
#define _LEFT_INTRO				0
#define _TOP_INTRO				60
#define _RIGHT_INTRO			640
#define _BOTTOM_INTRO			420

#define _IMG_IDX_LOGIN_BORDER		1
#define _IMG_IDX_LOGIN_IDPASS		2
#define _IMG_IDX_BTN_LOGIN			10
#define _IMG_IDX_BTN_NEW			12
#define _IMG_IDX_BTN_CHANGE			14
#define _IMG_IDX_BTN_EXIT			16


#define _LEFT_LOGIN_BTN				475
#define _LEFT_NEW_BTN				205
#define _LEFT_CHANGE_BTN			325
#define _LEFT_EXIT_BTN				475
#define _TOP_LOGIN_BTNS				8
#define _TOP_LOGIN_BTN				65

LoginView::LoginView() {
	MyGfx::Instance()->Resize(640, 480);
	UI = new YxGUI::Canvas();
	UI->SetLocalSize(640,480);
	Bg = new YxGUI::Image();
	UI->AddChild(Bg);
	/*Login = new YxGUI::Button();
	UI->AddChild(Login);
	Exit = new YxGUI::Button();
	UI->AddChild(Exit);*/

	_lib.Load(".\\Data\\Interface1c.wil");

	auto sBg = _lib.LoadImage(IMG_IDX_LOGIN_BACK);
	Bg->SetLocalPos(_LEFT_INTRO, _TOP_INTRO);
	Bg->SetSprite(MyGfx::CreateSpriteFromImage(sBg),true);
	Bg->SetAsNativeSize();

	SoundMgr::Instance()->PlayMusic("Opening.wav", true);
}

LoginView::~LoginView() 
{
	delete UI;
}

void LoginView::Draw()
{
	UI->Draw();
}

bool LoginView::HandleEvent(SDL_Event & e)
{
	return UI->HandleEvent(e);
}
