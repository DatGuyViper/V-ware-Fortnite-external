#include <iostream>
#include <sstream>
#include <iomanip>
#include <mutex>
#include <filesystem>
#include <random>
#include <string>
#include <fstream>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../Driver/driver.h"
#include "../Game/Classes.h"
#include "../Extra/Crypt.h"
#include <windows.h>
#include <d3d9.h>
#include <Uxtheme.h>
#include <dwmapi.h>
#include <ctime>
#include "../ImGui/imgui_internal.h"
#include "../Extra/font.h"
#include <array>
#define NOMINMAX
#include <limits>
#pragma comment(lib, "d3d9.lib")
#include "../ImGui/bytes.hpp"
#include "../ImGui/hashes.hpp"
#include "../ImGui/blur.hpp"
#include "../ImGui/gui.hpp"
#include <io.h>
#include <tchar.h>
#include <math.h>
#include "../Rendering/Config.cpp"
#include "../Rendering/Loop.h"
#include "../stuff/aim.h"

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#define  IMGUI_DEFINE_MATH_OPERATORS
#define ALPHA    ( ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )


static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};



using namespace std;

uintptr_t procid = NULL;

float color_edit4[4] = { 1.00f, 1.00f, 1.00f, 1.000f };
float accent_color[4] = { Esp::AccentColor.x, Esp::AccentColor.y, Esp::AccentColor.z, Esp::AccentColor.w };

IDirect3DTexture9* scene = nullptr;
IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };

HWND GameHwnd = NULL;
MSG Message = { NULL };

void CloseProcesses(const char* processName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, &pe)) {
		do {
			if (_stricmp(pe.szExeFile, processName) == 0) {
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
				if (hProcess) {
					TerminateProcess(hProcess, 0);
					CloseHandle(hProcess);
				}
			}
		} while (Process32Next(hSnapshot, &pe));
	}

	CloseHandle_Spoofed(hSnapshot);
}


HRESULT InitializeDirectXOverlay() {
	SPOOF_FUNC;
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA), 0, DefWindowProcA_Spoofed, 0, 0, nullptr,
		LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW),
		nullptr, nullptr, ("Medal"), LoadIcon(nullptr, IDI_APPLICATION)
	};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	if (!RegisterClassExA_Spoofed(&wcex)) {
		return E_FAIL;
	}

	MyHwnd = CreateWindowExA_Spoofed(NULL, ("Medal"), ("MedalOverlay"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
	if (!MyHwnd) {
		return E_FAIL;
	}

	SetWindowLongA_Spoofed(MyHwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea_Spoofed(MyHwnd, &margin);
	ShowWindow_Spoofed(MyHwnd, SW_SHOW);

	SetLayeredWindowAttributes_Spoofed(MyHwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	UpdateWindow_Spoofed(MyHwnd);

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object))) {
		return E_FAIL;
	}

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = MyHwnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = ScreenWidth;
	p_Params.BackBufferHeight = ScreenHeight;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, MyHwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device))) {
		p_Object->Release();
		return E_FAIL;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	if (!ImGui_ImplWin32_Init(MyHwnd) || !ImGui_ImplDX9_Init(p_Device)) {
		p_Object->Release();
		return E_FAIL;
	}

	ImGui::GetStyle();
	p_Object->Release();

	return S_OK;
}



void CleanupD3D() {
	if (p_Device != NULL) {
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL) {
		p_Object->Release();
	}
}

bool rMenu = true;
bool rColorMenu = false;
int tab = 0;

int tab_count = 0, tabs = 0;
bool active = false;
float size_child = 0;


void Menu() {


	if (GetAsyncKeyState_Spoofed(VK_INSERT) & 1) rMenu = !rMenu;

	if (rMenu) {

		ImGui::Begin(skCrypt("VWARE"), NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		static bool bools[50]{};
		static int ints[50]{}, combo = 0;
		//std::vector<const char*> items = { "Option", "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", " Option 6", "Option 7", "Option 8", "Option 9" };
		static char buf[64];

		static float color[4] = { 1.f, 1.f, 1.f, 1.f };
		auto window = ImGui::GetCurrentWindow();
		auto draw = window->DrawList;
		auto pos = window->Pos;
		auto size = window->Size;

			gui.m_anim = ImLerp(gui.m_anim, 1.f, 0.045f);

			ImGui::SetWindowSize(ImVec2(690, 500));

			ImVec2 textPos1 = ImVec2(pos.x + (170 / 2) - (io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, skCrypt("VWARE")).x / 2 + 1), pos.y + 20);
			draw->AddText(io.Fonts->Fonts[1], io.Fonts->Fonts[1]->FontSize, textPos1, gui.accent_color.to_im_color(), skCrypt("VWARE "));

			ImVec2 textPos2 = ImVec2(pos.x + (170 / 2) - (io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, skCrypt("VWARE")).x / 2), pos.y + 20);
			draw->AddText(io.Fonts->Fonts[1], io.Fonts->Fonts[1]->FontSize, textPos2, GetColorU32(ImGuiCol_Text), skCrypt("VWARE"));

			ImVec2 lineStart = ImVec2(pos.x, pos.y + size.y - 50);
			ImVec2 lineEnd = ImVec2(pos.x + 170, pos.y + size.y - 50);
			draw->AddLine(lineStart, lineEnd, GetColorU32(ImGuiCol_WindowBg, 0.5f));

			ImVec2 imageStart = ImVec2(pos.x + 15, pos.y + size.y - 40);
			ImVec2 imageEnd = ImVec2(pos.x + 45, pos.y + size.y - 10);

			ImVec2 evropePos = ImVec2(pos.x + 50, pos.y + size.y - 40);
			draw->AddText(evropePos, gui.text.to_im_color(), skCrypt("VIPER"));


			SetCursorPos(ImVec2(10, 70));
			ImGui::BeginChild("##tabs", ImVec2(150, size.y - 120));

			gui.group_title(skCrypt("Aimbot"));
			if (gui.tab(reinterpret_cast<const char*>(ICON_FA_CROSSHAIRS), skCrypt("Aimbot"), gui.m_tab == 0) && gui.m_tab != 0)
				gui.m_tab = 0, gui.m_anim = 0.f;

			ImGui::Spacing(), ImGui::Spacing(), ImGui::Spacing();

			gui.group_title(skCrypt("Visuals"));
			if (gui.tab(reinterpret_cast<const char*>(ICON_FA_GHOST), skCrypt("Esp"), gui.m_tab == 1) && gui.m_tab != 1)
				gui.m_tab = 1, gui.m_anim = 0.f;

			if (gui.tab(reinterpret_cast<const char*>(ICON_FA_MOUSE), skCrypt("Misc"), gui.m_tab == 2) && gui.m_tab != 2)
				gui.m_tab = 2, gui.m_anim = 0.f;

			ImGui::Spacing(), ImGui::Spacing(), ImGui::Spacing();

			gui.group_title(skCrypt("About"));

			if (gui.tab(reinterpret_cast<const char*>(ICON_FA_CODE), skCrypt("About"), gui.m_tab == 4) && gui.m_tab != 4)
				gui.m_tab = 4, gui.m_anim = 0.f;

			ImGui::EndChild();

			SetCursorPos(ImVec2(190, 20));

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

			SetCursorPos(ImVec2(300, 20));
			ImGui::BeginChild("##subtabs", ImVec2(240, 25));

			ImVec2 windowPos = GetWindowPos();
			ImVec2 windowSize = GetWindowSize();
			ImVec2 windowPosMax(windowPos.x + windowSize.x, windowPos.y + windowSize.y);

			ImGui::EndChild();

			ImGui::PopStyleVar();

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, gui.m_anim);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 8));

			SetCursorPos(ImVec2(185, 81 - (5 * gui.m_anim)));
			ImGui::BeginChild("##childs", ImVec2(size.x - 200, size.y - 96));

			switch (gui.m_tab) {

			case 0:

				gui.group_box(reinterpret_cast<const char*>(ICON_FA_BULLSEYE_ARROW " Aimbot"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight() / 2 - ImGui::GetStyle().ItemSpacing.y / 2)); {
					ImGui::Checkbox(skCrypt("Aimbot"), &Features::rAimbot);
					ImGui::Checkbox(skCrypt("Vischeck"), &Features::rVisibleCheck);
					ImGui::Checkbox(skCrypt("Trigger bot"), &Features::rTriggerbot);
					ImGui::Checkbox(skCrypt("Prediction"), &Features::rPrediction);
				} gui.end_group_box();

				gui.group_box(reinterpret_cast<const char*>(ICON_FA_COG " Options"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight() / 2 - ImGui::GetStyle().ItemSpacing.y / 2)); {
					ImGui::Checkbox(skCrypt("Fov Circle"), &Features::rFovCircle);
					ImGui::Checkbox(skCrypt("Fov Fill"), &Features::rFovFill);
					ImGui::Checkbox(skCrypt("Fov Outline"), &Features::rFovCircleOut);
					ImGui::Checkbox(skCrypt("Aimline"), &Features::rAimline);
					ImGui::Checkbox(skCrypt("Aim Circle"), &Features::rAimCircle);
					ImGui::Checkbox(skCrypt("Ignore Bots"), &Features::rBotCheck);
					ImGui::Checkbox(skCrypt("Ignore Downed"), &Features::rDownedCheck);
					ImGui::Checkbox(skCrypt("Lock Target"), &Features::rLockTarget);
				} gui.end_group_box();

				ImGui::SameLine(), ImGui::SetCursorPosY(0);

				gui.group_box(reinterpret_cast<const char*>(ICON_FA_USER_CHART " Other"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight())); {
					ImGui::SliderInt(skCrypt("Fov Size"), &Features::rFovSize, 10, 1000);
					ImGui::SliderFloat(skCrypt("Smoothing"), &Features::rSmooth, 1.4f, 50.0f);
					ImGui::SliderFloat(skCrypt("Max Distance"), &Features::distanceDivisor, 100.0f, 1000.0f, "%.0f");
					if (ImGui::Button(skCrypt("Aim Key"))) {
						Features::waitingForAimKey = true;
					}
					if (Features::waitingForAimKey) {
						for (int key = 0x01; key < 0xFE; key++) {
							if (GetAsyncKeyState(key) & 0x8000) {
								Features::rAimkey = key;
								Features::waitingForAimKey = false;
								break;
							}
						}
					}
					ImGui::SameLine();
					ImGui::Text(skCrypt("Current: %s"), GetKeyName(Features::rAimkey));

					if (ImGui::Button(skCrypt("Trig Key"))) {
						Features::waitingForTrigKey = true;
					}
					if (Features::waitingForTrigKey) {
						for (int key = 0x01; key < 0xFE; key++) {
							if (GetAsyncKeyState(key) & 0x8000) {
								Features::rTrigkey = key;
								Features::waitingForTrigKey = false;
								break;
							}
						}
					}
					ImGui::SameLine();
					ImGui::Text(skCrypt("Current: %s"), GetKeyName(Features::rTrigkey));

				} gui.end_group_box();

				break;

			case 1:

				gui.group_box(reinterpret_cast<const char*>(ICON_FA_BOX " Box Esp"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight() / 2 - ImGui::GetStyle().ItemSpacing.y / 2)); {
					enum BoxType {
						NONE,
						FULL_BOX,
						CORNER_BOX,
						RGB_BOX,
						FULL_BOX_3D,
						ROUNDED_BOX,
						OUTLINES,
						FILL_BOX
					};

					static BoxType currentBoxType = NONE;

					auto CoolCheckboxMutual = [&](const char* label, BoxType boxType, bool& boxFlag) {
						bool isChecked = (currentBoxType == boxType);
						if (ImGui::Checkbox(label, &isChecked)) {
							if (isChecked) {
								currentBoxType = boxType;
								Esp::rFullbox = (boxType == FULL_BOX);
								Esp::rCornerBox = (boxType == CORNER_BOX);
								Esp::rRgbBox = (boxType == RGB_BOX);
								Esp::rFullbox3D = (boxType == FULL_BOX_3D);
								Esp::rRoundedBox = (boxType == ROUNDED_BOX);
								Esp::rRoundedBox = (boxType == ROUNDED_BOX);
							}
							else {

								currentBoxType = NONE;
							}
						}
						boxFlag = isChecked;
						};

					CoolCheckboxMutual(skCrypt("2D Box"), FULL_BOX, Esp::rFullbox);
					CoolCheckboxMutual(skCrypt("Corner Box"), CORNER_BOX, Esp::rCornerBox);
					CoolCheckboxMutual(skCrypt("RGB Box"), RGB_BOX, Esp::rRgbBox);
					CoolCheckboxMutual(skCrypt("3D Box"), FULL_BOX_3D, Esp::rFullbox3D);
				} gui.end_group_box();

				gui.group_box(reinterpret_cast<const char*>(ICON_FA_SKULL " Skeleton"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight() / 2 - ImGui::GetStyle().ItemSpacing.y / 2)); {
					ImGui::Checkbox(skCrypt("Radar"), &Esp::rRadar);
					ImGui::Checkbox(skCrypt("Skeleton"), &Esp::rSkeleton);
					ImGui::Checkbox(skCrypt("Feet"), &Esp::rfeet);
					ImGui::Checkbox(skCrypt("Joint"), &Esp::rjointEsp);
					ImGui::Checkbox(skCrypt("Head"), &Esp::rHead);
					ImGui::Checkbox(skCrypt("3D Head"), &Esp::rHeadBox);
				} gui.end_group_box();

				ImGui::SameLine(), ImGui::SetCursorPosY(0);

				gui.group_box(reinterpret_cast<const char*>(ICON_FA_COG " Options"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight())); {
					ImGui::Checkbox(skCrypt("Box Outlines"), &Esp::rboxOutlines);
					ImGui::Checkbox(skCrypt("Box Fill"), &Esp::rFillBoxs);
					ImGui::Checkbox(skCrypt("Skeleton Outline"), &Esp::rskelOutlines);
					ImGui::Checkbox(skCrypt("Skeleton Rainbow"), &Esp::rainbowMode);
					ImGui::SliderFloat(skCrypt("skel Thick"), &Esp::skeletonThicknessMultiplier, 0.5f, 5.0f);
					ImGui::SliderFloat(skCrypt("HeadBox Thick"), &Esp::HeadBoxThick, 0.5f, 5.0f);
					ImGui::SliderFloat(skCrypt("HeadBox size"), &Esp::HeadBoxSize, 1.0f, 50.0f);
					ImGui::SliderFloat(skCrypt("Box Width"), &Esp::boxWidthMultiplier, 0.5f, 2.5f);
					ImGui::SliderFloat(skCrypt("Box Thick"), &Esp::boxThicknessMultiplier, 1.0f, 7.0f);
					ImGui::ColorEdit4(skCrypt("Visible"), Esp::espcolor, ALPHA);
					ImGui::ColorEdit4(skCrypt("InVisible"), Esp::espcolor2, ALPHA);
					ImGui::ColorEdit4(skCrypt("Fill"), Esp::espcolor3, ALPHA);

					if (ImGui::Button(skCrypt("Save Config"))) {
						save_config();
					}

					if (ImGui::Button(skCrypt("Load Config"))) {
						load_config();
					}


				} gui.end_group_box();

				break;

			case 2:
				gui.group_box(reinterpret_cast<const char*>(ICON_FA_USER_CHART " Misc"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight())); {
					ImGui::Checkbox(skCrypt("Weapon Esp"), &Esp::rWeaponEsp);
					ImGui::Checkbox(skCrypt("Snapline"), &Esp::rSnaplines);
					ImGui::Checkbox(skCrypt("Rank"), &Esp::rRanked);
					ImGui::Checkbox(skCrypt("View Angle"), &Esp::rViewAngle);
					ImGui::Checkbox(skCrypt("Distance"), &Esp::rDistance);
					ImGui::Checkbox(skCrypt("Username"), &Esp::rUsername);
					ImGui::Checkbox(skCrypt("Platform"), &Esp::rPlatformname);
					ImGui::Checkbox(skCrypt("Render Count"), &Esp::rRenderCount);
					ImGui::Checkbox(skCrypt("FOV Arrows"), &Esp::rFovRadar);
					ImGui::Checkbox(skCrypt("Kills"), &Esp::rKills);
					ImGui::Checkbox(skCrypt("Level"), &Esp::rLevel);


				} gui.end_group_box();

				ImGui::SameLine(), ImGui::SetCursorPosY(0);
				gui.group_box(reinterpret_cast<const char*>(ICON_FA_USER_CHART " Options"), ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::GetStyle().ItemSpacing.x / 2, ImGui::GetWindowHeight())); {
					ImGui::Checkbox(skCrypt("MiscOutline"), &Esp::MiscOutline);
					ImGui::Checkbox(skCrypt("Array List"), &Features::ArrayList);

				} gui.end_group_box();
				break;

			case 4:
				gui.group_box(reinterpret_cast<const char*>(ICON_FA_USER_CHART " Misc"), ImVec2(ImGui::GetWindowWidth() / 1 - ImGui::GetStyle().ItemSpacing.x / 1, ImGui::GetWindowHeight())); {

					ImGui::Text(skCrypt("Dev"));

					if (ImGui::Selectable(skCrypt("VIPER"), false, ImGuiSelectableFlags_DontClosePopups))
					{
						system(skCrypt("start https://guns.lol/vipah"));
					}
				} 

				gui.end_group_box();


				break;
			}

			ImGui::EndChild();

			ImGui::PopStyleVar(2);

			ImVec2 mousePos = ImGui::GetMousePos();

			ImGui::GetForegroundDrawList()->AddCircleFilled(mousePos, 5.0f, ImColor(0, 0, 255, 255), 32);

		} ImGui::End();

		ImGui::PopStyleVar();
		ImGui::EndFrame();
	}


float custom_fabsf(float x) {

	__m128 x_vec = _mm_set_ss(x);
	x_vec = _mm_and_ps(x_vec, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
	return _mm_cvtss_f32(x_vec);
}

WPARAM MainLoop() {
	SPOOF_FUNC;
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, MyHwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage_Spoofed(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow_Spoofed();

		SetWindowPos_Spoofed(MyHwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		if (hwnd_active == GameHwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos_Spoofed(MyHwnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect_Spoofed(GameHwnd, &rc);
		ClientToScreen_Spoofed(GameHwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameHwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState_Spoofed(VK_LBUTTON) & 0x8000) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].y = io.MousePos.y;
		}
		else {
			io.MouseDown[0] = false;
		}

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {
			old_rc = rc;
			screen_width = rc.right;
			ScreenHeight = rc.bottom;

			p_Params.BackBufferWidth = screen_width;
			p_Params.BackBufferHeight = ScreenHeight;

			SetWindowPos_Spoofed(MyHwnd, HWND_TOP, xy.x, xy.y, screen_width, ScreenHeight, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		io.Fonts->AddFontFromMemoryTTF(museo500_binary, sizeof museo500_binary, 14);
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		io.Fonts->AddFontFromMemoryTTF(&font_awesome_binary, sizeof font_awesome_binary, 13, &icons_config, icon_ranges);

		io.Fonts->AddFontFromMemoryTTF(museo900_binary, sizeof museo900_binary, 28);

		blur::device = p_Device;

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::StyleColorsDark();
		Render1();
		loop();
		Menu();
		ImGui::EndFrame();

		p_Device->SetRenderState(D3DRS_ZENABLE, false);
		p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (p_Device->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_Device->EndScene();
		}

		HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Device->Reset(&p_Params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanupD3D();
	DestroyWindow(MyHwnd);

	return Message.wParam;
}

void cache_loop() {
	while (true) {
		cache();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

int main() {
	LI_FN(SetConsoleTitleA)(skCrypt(("V-Ware Public")));

	if (!handler::find_driver()) {
		MessageBox(NULL, skCrypt("Error loading driver!"), skCrypt(""), NULL);
		exit(0);
	}
	SonyDriverHelper::api::Init();

	HWND hwnd = NULL;
	while (!hwnd) {
		system(skCrypt("cls"));
		std::cout << skCrypt("Waiting for game...") << std::endl;
		hwnd = FindWindowA_Spoofed(NULL, skCrypt("Fortnite  "));
		if (hwnd) break;
		Sleep(3000);
	}
	system(skCrypt("cls"));

	handler::process_id = handler::find_process(skCrypt("FortniteClient-Win64-Shipping.exe"));

    virtualaddy = handler::find_image();
	auto cr3 = handler::fetch_cr3();


	std::cout << skCrypt("Base Address -> ") << virtualaddy << std::endl;
	std::cout << skCrypt("CR3 -> ") << cr3 << std::endl;

	std::thread cache_thread(cache_loop);
	cache_thread.detach();

	Hook_start();
	InitializeDirectXOverlay();
	MainLoop();
}
