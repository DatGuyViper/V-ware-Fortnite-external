#include <sstream>
#include <iomanip>
#include <mutex>
#include <filesystem>
#include <random>
#include <string>
#include <fstream>
#include <windows.h>
#include <d3d9.h>
#include <Uxtheme.h>
#include <dwmapi.h>
#include <ctime>
#include <array>
#include <limits>
#include <io.h>
#include <tchar.h>
#include <math.h>
#include "../Game/Classes.h"



void save_config(const std::string& filename = "config.txt") {
	const std::string folder_path = "C:\\V-WarePrivate";
	CreateDirectory(folder_path.c_str(), nullptr);

	std::ofstream file(folder_path + "\\" + filename);

	if (file.is_open()) {
		file << ("aimbot.enabled=") << Features::rAimbot << "\n";
		file << ("aimbot.vischeck=") << Features::rVisibleCheck << "\n";
		file << ("aimbot.drawfov=") << Features::rAimCircle << "\n";
		file << ("aimbot.prediction=") << Features::rPrediction << "\n";
		file << ("aimbot.fov=") << Features::rFovSize << "\n";
		file << ("aimbot.fovcircle=") << Features::rFovCircle << "\n";
		file << ("aimbot.fovcirclefill=") << Features::rFovFill << "\n";
		file << ("aimbot.fovoutline=") << Features::rFovCircleOut << "\n";
		file << ("aimbot.aimline=") << Features::rAimline << "\n";
		file << ("aimbot.aimcricle=") << Features::rAimCircle << "\n";
		file << ("aimbot.ignorebots=") << Features::rBotCheck << "\n";
		file << ("aimbot.ingnoredowned=") << Features::rDownedCheck << "\n";
		file << ("aimbot.smooth=") << Features::rSmooth << "\n";
		file << ("aimbot.distance=") << Features::rMaxDistance << "\n";

		file << ("triggerbot.keystatus=") << Features::rTriggerbot << "\n";
		file << ("triggerbot.clickdelay=") << Features::rTriggerbotDelay << "\n";

		file << ("visuals.2d-box=") << Esp::rFullbox << "\n";
		file << ("visuals.Corner-Box=") << Esp::rCornerBox << "\n";
		file << ("visuals.RGB-Box=") << Esp::rRgbBox << "\n";
		file << ("visuals.Box-Outlines=") << Esp::rboxOutlines << "\n";
		file << ("visuals.Box-Fill=") << Esp::rFillBoxs << "\n";
		file << ("visuals.julian-3d=") << Esp::julian3d << "\n";
		file << ("visuals.julian-2d=") << Esp::julian2d << "\n";
		file << ("visuals.julian2d-type=") << Esp::julian2d_type << "\n";
		file << ("visuals.Radar=") << Esp::rRadar << "\n";
		file << ("visuals.Skeleton=") << Esp::rSkeleton << "\n";
		file << ("visuals.Feet=") << Esp::rfeet << "\n";
		file << ("visuals.Joint=") << Esp::rjointEsp << "\n";
		file << ("visuals.Head=") << Esp::rHead << "\n";
		file << ("visuals.3D-Head=") << Esp::rHeadBox << "\n";
		file << ("visuals.Outline=") << Esp::rskelOutlines << "\n";
		file << ("visuals.Rainbow=") << Esp::rainbowMode << "\n";
		file << ("visuals.MiscOutline=") << Esp::MiscOutline << "\n";
		file << ("visuals.ArrayList=") << Features::ArrayList << "\n";
		file << ("visuals.WeaponEsp=") << Esp::rWeaponEsp << "\n";
		file << ("visuals.Snapline=") << Esp::rSnaplines << "\n";
		file << ("visuals.Rank=") << Esp::rRanked << "\n";
		file << ("visuals.ViewAngle=") << Esp::rViewAngle << "\n";
		file << ("visuals.Distance=") << Esp::rDistance << "\n";
		file << ("visuals.Username=") << Esp::rUsername << "\n";
		file << ("visuals.Platform=") << Esp::rPlatformname << "\n";
		file << ("visuals.RenderCount=") << Esp::rRenderCount << "\n";
		file << ("visuals.FOV-Arrows=") << Esp::rFovRadar << "\n";
		file << ("visuals.Kills=") << Esp::rKills << "\n";
		file << ("visuals.Level=") << Esp::rLevel << "\n";

		file << ("exploits.NoRecoil=") << Exploits::rNoRecoil << "\n";
		file << ("exploits.MajicBullet=") << Exploits::MajicBullet << "\n";
		file << ("exploits.NoSpectator=") << Exploits::NoSpec << "\n";
		file << ("exploits.NoSpread=") << Exploits::Spread << "\n";
		file << ("exploits.AdsInAir=") << Exploits::AdsInAir << "\n";
		file << ("exploits.AirStuck=") << Exploits::AirStuck << "\n";
		file << ("exploits.FirstPerson=") << Exploits::FirstPerson << "\n";
		file << ("exploits.StreamProof=") << Exploits::rStreamProof << "\n";
		file << ("exploits.FreezePlayer=") << Exploits::FreezePlr << "\n";
		file << ("exploits.AutoRun=") << Exploits::autorun << "\n";
		file << ("exploits.FovChanger=") << Exploits::rFOVChanger << "\n";
		file << ("exploits.NoEquipAnimation=") << Exploits::NoEquipAnimation << "\n";
		file << ("exploits.InstaReboot=") << Exploits::instaReboot << "\n";
		file << ("exploits.RapidFire=") << Exploits::bRapidFire << "\n";
		file << ("exploits.NoReload=") << Exploits::rNoReload << "\n";
		file << ("exploits.PlayerSize=") << Exploits::playersize << "\n";
		file << ("exploits.CarFly=") << Exploits::rCarFly << "\n";
		file << ("exploits.RainbowCrosshair=") << Exploits::Rainbowcrosshair << "\n";
		file << ("exploits.MaxCharge=") << Exploits::rMaxCharge << "\n";
		file << ("StreamProof=") << Exploits::rStreamProof << "\n";
	}
}

void load_config(const std::string& filename = "config.txt") {
	const std::string folder_path = "C:\\V-WarePrivate";
	std::ifstream file(folder_path + "\\" + filename);

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string key;
			if (std::getline(iss, key, '=')) {
				std::string value;
				if (std::getline(iss, value)) {
					if (key == "aimbot.enabled") Features::rAimbot = std::stof(value);
					else if (key == "aimbot.vischeck") Features::rVisibleCheck = std::stof(value);
					else if (key == "aimbot.drawfov") Features::rAimCircle = std::stof(value);
					else if (key == "aimbot.prediction") Features::rPrediction = std::stof(value);
					else if (key == "aimbot.fov") Features::rFovSize = std::stof(value);
					else if (key == "aimbot.fovcircle") Features::rFovCircle = std::stof(value);
					else if (key == "aimbot.fovcirclefill") Features::rFovFill = std::stof(value);
					else if (key == "aimbot.fovoutline") Features::rFovCircleOut = std::stof(value);
					else if (key == "aimbot.aimline") Features::rAimline = std::stof(value);
					else if (key == "aimbot.aimcricle") Features::rAimCircle = std::stof(value);
					else if (key == "aimbot.ignorebots") Features::rBotCheck = std::stof(value);
					else if (key == "aimbot.ingnoredowned") Features::rDownedCheck = std::stof(value);
					else if (key == "aimbot.smooth") Features::rSmooth = std::stof(value);
					else if (key == "aimbot.distance") Features::rMaxDistance = std::stof(value);

					else if (key == "triggerbot.keystatus") Features::rTriggerbot = std::stoi(value);
					else if (key == "triggerbot.clickdelay") Features::rTriggerbotDelay = std::stoi(value);

					else if (key == "visuals.2d-box") Esp::rFullbox = std::stof(value);
					else if (key == "visuals.Corner-Box") Esp::rCornerBox = std::stof(value);
					else if (key == "visuals.RGB-Box") Esp::rRgbBox = std::stof(value);
					else if (key == "visuals.Box-Outlines") Esp::rboxOutlines = std::stof(value);
					else if (key == "visuals.Box-Fill") Esp::rFillBoxs = std::stof(value);
					else if (key == "visuals.julian-3d") Esp::julian3d = std::stof(value);
					else if (key == "visuals.julian-2d") Esp::julian2d = std::stof(value);
					else if (key == "visuals.julian2d-type") Esp::julian2d_type = std::stof(value);
					else if (key == "visuals.Radar") Esp::rRadar = std::stof(value);
					else if (key == "visuals.Skeleton") Esp::rSkeleton = std::stof(value);
					else if (key == "visuals.Feet") Esp::rfeet = std::stof(value);
					else if (key == "visuals.Joint") Esp::rjointEsp = std::stof(value);
					else if (key == "visuals.Head") Esp::rHead = std::stof(value);
					else if (key == "visuals.3D-Head") Esp::rHeadBox = std::stof(value);
					else if (key == "visuals.Outline") Esp::rskelOutlines = std::stof(value);
					else if (key == "visuals.Rainbow") Esp::rainbowMode = std::stof(value);
					else if (key == "visuals.MiscOutline") Esp::MiscOutline = std::stof(value);
					else if (key == "visuals.ArrayList") Features::ArrayList = std::stof(value);
					else if (key == "visuals.WeaponEsp") Esp::rWeaponEsp = std::stof(value);
					else if (key == "visuals.Snapline") Esp::rSnaplines = std::stof(value);
					else if (key == "visuals.Rank") Esp::rRanked = std::stof(value);
					else if (key == "visuals.ViewAngle") Esp::rViewAngle = std::stof(value);
					else if (key == "visuals.Distance") Esp::rDistance = std::stof(value);
					else if (key == "visuals.Username") Esp::rUsername = std::stof(value);
					else if (key == "visuals.Platform") Esp::rPlatformname = std::stof(value);
					else if (key == "visuals.RenderCount") Esp::rRenderCount = std::stof(value);
					else if (key == "visuals.FOV-Arrows") Esp::rFovRadar = std::stof(value);
					else if (key == "visuals.Kills") Esp::rKills = std::stof(value);
					else if (key == "visuals.Level") Esp::rLevel = std::stof(value);

					else if (key == "exploits.NoRecoil") Exploits::rNoRecoil = std::stof(value);
					else if (key == "exploits.MajicBullet") Exploits::MajicBullet = std::stof(value);
					else if (key == "exploits.NoSpectator") Exploits::NoSpec = std::stof(value);
					else if (key == "exploits.NoSpread") Exploits::Spread = std::stof(value);
					else if (key == "exploits.AdsInAir") Exploits::AdsInAir = std::stof(value);
					else if (key == "exploits.AirStuck") Exploits::AirStuck = std::stof(value);
					else if (key == "exploits.FirstPerson") Exploits::FirstPerson = std::stof(value);
					else if (key == "exploits.StreamProof") Exploits::rStreamProof = std::stof(value);
					else if (key == "exploits.FreezePlayer") Exploits::FreezePlr = std::stof(value);
					else if (key == "exploits.AutoRun") Exploits::autorun = std::stof(value);
					else if (key == "exploits.FovChanger") Exploits::rFOVChanger = std::stof(value);
					else if (key == "exploits.NoEquipAnimation") Exploits::NoEquipAnimation = std::stof(value);
					else if (key == "exploits.InstaReboot") Exploits::instaReboot = std::stof(value);
					else if (key == "exploits.RapidFire") Exploits::bRapidFire = std::stof(value);
					else if (key == "exploits.NoReload") Exploits::rNoReload = std::stof(value);
					else if (key == "exploits.PlayerSize") Exploits::playersize = std::stof(value);
					else if (key == "exploits.CarFly") Exploits::rCarFly = std::stof(value);
					else if (key == "exploits.RainbowCrosshair") Exploits::Rainbowcrosshair = std::stof(value);
					else if (key == "exploits.MaxCharge") Exploits::rMaxCharge = std::stof(value);
					else if (key == "StreamProof") Exploits::rStreamProof = std::stof(value);
				}
			}
		}
	}
}