#include "LoginView.h"
#include "../MyGfx.h"
#include "../Common.h"
#include "../SoundMgr.h"
#include "ViewMgr.h"

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


#define _LEFT_INTRO				0
#define _TOP_INTRO				60
#define _RIGHT_INTRO			640
#define _BOTTOM_INTRO			420

#define  IMG_IDX_LOGIN_BACK			0
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
	ImageLib lib;
	lib.Load(".\\Data\\Interface1c.wil");
	GuiHelper helper(&lib);

	MyGfx::Instance()->Resize(640, 480);
	UI = new YxGUI::Canvas();
	UI->SetLocalSize(640,480);

	Bg = helper.CreateImage(IMG_IDX_LOGIN_BACK);
	UI->AddChild(Bg);
	Bg->SetLocalPos(_LEFT_INTRO, _TOP_INTRO);

	Border = helper.CreateImage(_IMG_IDX_LOGIN_BORDER);
	UI->AddChild(Border);
	Border->SetColor({255,255,255,128});
	Border->SetLocalPos(_LEFT_LOGIN, _TOP_LOGIN);

	Login = helper.CreateButton(_IMG_IDX_BTN_LOGIN);
	Border->AddChild(Login);
	Login->SetLocalPos(_LEFT_LOGIN_BTN, _TOP_LOGIN_BTN);

	New = helper.CreateButton(_IMG_IDX_BTN_NEW);
	Border->AddChild(New);
	New->SetLocalPos(_LEFT_NEW_BTN, _TOP_LOGIN_BTNS);

	Change = helper.CreateButton(_IMG_IDX_BTN_CHANGE);
	Border->AddChild(Change);
	Change->SetLocalPos(_LEFT_CHANGE_BTN, _TOP_LOGIN_BTNS);

	Exit = helper.CreateButton(_IMG_IDX_BTN_EXIT);
	Border->AddChild(Exit);
	Exit->SetLocalPos(_LEFT_EXIT_BTN, _TOP_LOGIN_BTNS);

	InputBg = helper.CreateImage(_IMG_IDX_LOGIN_IDPASS);
	Border->AddChild(InputBg);
	InputBg->SetLocalPos(_LEFT_ID_PASS, _TOP_ID_PASS);

	ID = helper.CreateInputField(-1);
	UI->AddChild(ID);
	ID->MaxChar = 12;
	ID->SetLocalSize(96, 20);
	ID->SetLocalPos(POS_ID_INS_X+6, POS_ID_INS_Y+4);// �е�ƫ��������ֵ

	PW = helper.CreateInputField(-1);
	UI->AddChild(PW);
	PW->MaxChar = 12;
	PW->IsPassword = true;
	PW->SetLocalSize(96, 20);
	PW->SetLocalPos(POS_PASS_INS_X+6, POS_PASS_INS_Y+4);

	Binding();
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

void LoginView::OnShow()
{
	UI->Visiable = true;
	SoundMgr::Instance()->PlayMusic("Opening.wav", 0, true);
}

void LoginView::OnHide()
{
	UI->Visiable = false;
}

void LoginView::Binding()
{
	Login->onClick += [this]() {
		ViewMgr::Instance()->ShowView(ViewMgr::ViewIndex::Select);// test
	};
	Exit->onClick += [this]() {
		MyGfx::Instance()->Exit();
	};
}
