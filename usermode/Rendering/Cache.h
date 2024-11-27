#include "../Game/Classes.h"

int get_fps()
{
	using namespace chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;

	count++;

	if (duration_cast<milliseconds>(now - last).count() > 1000) {
		fps = count;
		count = 0;
		last = now;
	}

	return fps;
}

const char* targetOptions[] = {
	"Head",
	"Lower Head",
	"Neck",
	"Chest",
	"Human Pelvis",
	"Spine 1",
	"Spine 2",
	"Spine 3",
	"L Collarbone",
	"L Upperarm",
	"L Forearm 1",
	"L Forearm 23",
	"L Forearm 2",
	"L Forearm 3",
	"L Palm",
	"L Hand",
	"R Collarbone",
	"R Upperarm",
	"R Forearm 1",
	"R Forearm 23",
	"R Forearm 2",
	"R Forearm 3",
	"R Hand",
	"R Palm",
	"L Thigh 1",
	"L Thigh 2",
	"L Thigh 3",
	"L Calf",
	"L Foot 2",
	"L Foot",
	"L Toe",
	"R Thigh 1",
	"R Thigh 2",
	"R Thigh 3",
	"R Calf",
	"R Foot 2",
	"R Foot",
	"R Toe"
};

const char* GetKeyName(int keyCode) {
	switch (keyCode) {
	case VK_LBUTTON: return "Left Mouse Button";
	case VK_RBUTTON: return "Right Mouse Button";
	case VK_MBUTTON: return "Middle Mouse Button";
	case VK_XBUTTON1: return "X Button 1";
	case VK_XBUTTON2: return "X Button 2";
	case VK_BACK: return "Backspace";
	case VK_TAB: return "Tab";
	case VK_RETURN: return "Enter";
	case VK_SHIFT: return "Shift";
	case VK_CONTROL: return "Control";
	case VK_MENU: return "Alt";
	case VK_PAUSE: return "Pause";
	case VK_CAPITAL: return "Caps Lock";
	case VK_ESCAPE: return "Escape";
	case VK_SPACE: return "Spacebar";
	case VK_PRIOR: return "Page Up";
	case VK_NEXT: return "Page Down";
	case VK_END: return "End";
	case VK_HOME: return "Home";
	case VK_LEFT: return "Left Arrow";
	case VK_UP: return "Up Arrow";
	case VK_RIGHT: return "Right Arrow";
	case VK_DOWN: return "Down Arrow";
	case VK_SELECT: return "Select";
	case VK_PRINT: return "Print";
	case VK_EXECUTE: return "Execute";
	case VK_SNAPSHOT: return "Print Screen";
	case VK_INSERT: return "Insert";
	case VK_DELETE: return "Delete";
	case VK_HELP: return "Help";

	case '0': return "0";
	case '1': return "1";
	case '2': return "2";
	case '3': return "3";
	case '4': return "4";
	case '5': return "5";
	case '6': return "6";
	case '7': return "7";
	case '8': return "8";
	case '9': return "9";

	case 'A': return "A";
	case 'B': return "B";
	case 'C': return "C";
	case 'D': return "D";
	case 'E': return "E";
	case 'F': return "F";
	case 'G': return "G";
	case 'H': return "H";
	case 'I': return "I";
	case 'J': return "J";
	case 'K': return "K";
	case 'L': return "L";
	case 'M': return "M";
	case 'N': return "N";
	case 'O': return "O";
	case 'P': return "P";
	case 'Q': return "Q";
	case 'R': return "R";
	case 'S': return "S";
	case 'T': return "T";
	case 'U': return "U";
	case 'V': return "V";
	case 'W': return "W";
	case 'X': return "X";
	case 'Y': return "Y";
	case 'Z': return "Z";

	case VK_NUMPAD0: return "Numpad 0";
	case VK_NUMPAD1: return "Numpad 1";
	case VK_NUMPAD2: return "Numpad 2";
	case VK_NUMPAD3: return "Numpad 3";
	case VK_NUMPAD4: return "Numpad 4";
	case VK_NUMPAD5: return "Numpad 5";
	case VK_NUMPAD6: return "Numpad 6";
	case VK_NUMPAD7: return "Numpad 7";
	case VK_NUMPAD8: return "Numpad 8";
	case VK_NUMPAD9: return "Numpad 9";
	case VK_MULTIPLY: return "Numpad *";
	case VK_ADD: return "Numpad +";
	case VK_SEPARATOR: return "Numpad Separator";
	case VK_SUBTRACT: return "Numpad -";
	case VK_DECIMAL: return "Numpad .";
	case VK_DIVIDE: return "Numpad /";

	case VK_F1: return "F1";
	case VK_F2: return "F2";
	case VK_F3: return "F3";
	case VK_F4: return "F4";
	case VK_F5: return "F5";
	case VK_F6: return "F6";
	case VK_F7: return "F7";
	case VK_F8: return "F8";
	case VK_F9: return "F9";
	case VK_F10: return "F10";
	case VK_F11: return "F11";
	case VK_F12: return "F12";

	case VK_NUMLOCK: return "Num Lock";
	case VK_SCROLL: return "Scroll Lock";

	case VK_LSHIFT: return "Left Shift";
	case VK_RSHIFT: return "Right Shift";
	case VK_LCONTROL: return "Left Control";
	case VK_RCONTROL: return "Right Control";
	case VK_LMENU: return "Left Alt";
	case VK_RMENU: return "Right Alt";

	case VK_VOLUME_MUTE: return "Volume Mute";
	case VK_VOLUME_DOWN: return "Volume Down";
	case VK_VOLUME_UP: return "Volume Up";
	case VK_MEDIA_NEXT_TRACK: return "Next Track";
	case VK_MEDIA_PREV_TRACK: return "Previous Track";
	case VK_MEDIA_STOP: return "Stop Media";
	case VK_MEDIA_PLAY_PAUSE: return "Play/Pause Media";

	case VK_BROWSER_BACK: return "Browser Back";
	case VK_BROWSER_FORWARD: return "Browser Forward";
	case VK_BROWSER_REFRESH: return "Browser Refresh";
	case VK_BROWSER_STOP: return "Browser Stop";
	case VK_BROWSER_SEARCH: return "Browser Search";
	case VK_BROWSER_FAVORITES: return "Browser Favorites";
	case VK_BROWSER_HOME: return "Browser Home";

	default: return "Unknown Key";
	}
}


inline void cache()
{
	Cached::World = read<UWorld*>(virtualaddy + Offsets::UWorld);
	Uworld_Cam = (FortPTR)Cached::World;

	if (!Cached::World)
		return;

	UGameInstance* GameInstance = Cached::World->OwningGameInstance();
	if (!GameInstance)
		return;

	Cached::LocalPlayer = read<ULocalPlayer*>(GameInstance->LocalPlayers());
	if (!Cached::LocalPlayer)
		return;

	Cached::PlayerController = Cached::LocalPlayer->PlayerController();
	Copy_PlayerController_Camera = (FortPTR)Cached::PlayerController;

	if (!Cached::PlayerController)
		return;

	Cached::CameraManager = read<uintptr_t>((FortPTR)Cached::PlayerController + Offsets::CameraManager);
	Cached::LocalPawn = (AFortPlayerPawn*)Cached::PlayerController->AcknowledgedPawn();

	if (Cached::LocalPawn)
	{
		Cached::LocalPlayerState = Cached::LocalPawn->PlayerState();
		Cached::LocalRootComponent = Cached::LocalPawn->RootComponent();
		Cached::CurrentWeapon = Cached::LocalPawn->CurrentWeapon();
		Cached::Mesh = Cached::LocalPawn->Mesh();
	}

	Cached::closest_mesh = NULL;

	Cached::GameState = Cached::World->GameState();
}