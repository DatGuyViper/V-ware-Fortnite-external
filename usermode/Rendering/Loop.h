#include <vector>
#include "Render.h"
#include "../Driver/driver.h"
#include <iostream>
#include <cstdint>
#include <string>
#include "../Game/Classes.h"
#include "../Extra/spoof.h"
#include "../stuff/hooks.h"


HWND MyHwnd = NULL;


static float rotationSpeed = 0.9f;
static float currentAngle = 8.0f;
static bool isSpinning = false;
static Vector3 originalRotation;
static int currentTarget = 0;
static int currentTarget2 = 0;
const char* snaplineOptions[] = { "None", "Bottom", "Top", "Center" };
static int currentSnapline = 0;
const char* boxOptions[] = { "None", "Full", "Cornered" };
static int currentBox = 0;
const char* gunOptions[] = { "Pistol", "Rifle", "Shotgun", "SMG", "Sniper", "Other" };
static int currentGun = 0;
static bool exploitDisable;
float maxDistance = 500.0f;
float playersizee = 0.0f;


std::wstring string_to_wstring(const std::string& str) {
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
	return wstr;
}

std::string wstring_to_utf8(const std::wstring& wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
	return str;
}

inline void DrawString3(float fontSize, int x, int y, ImVec4 color, bool bCenter, bool stroke, const char* pText, ...)
{
	ImU32 converted_color = ImGui::ColorConvertFloat4ToU32(color);
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = wstring_to_utf8(string_to_wstring(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), converted_color, text.c_str());
}


inline auto loop() -> void
{
	auto PlayerArray = Cached::GameState->PlayerArray();


	if (Features::rFovCircle) {
		ImVec2 screenCenter(screen_width / 2, screen_height / 2);

		ImColor borderColor(255, 255, 255, 255);
		ImColor fillColor(255, 255, 255, 20);
		ImColor outlineColor(0, 0, 0, 255);

		int numSegments = 64;
		float outlineThickness = 1.5f;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		std::vector<ImVec2> vertices;
		float angleStep = 2.0f * IM_PI / numSegments;
		for (int i = 0; i < numSegments; ++i) {
			float angle = i * angleStep;
			vertices.push_back(ImVec2(
				screenCenter.x + Features::rFovSize * cos(angle),
				screenCenter.y + Features::rFovSize * sin(angle)
			));
		}

		if (Features::rFovCircleOut) {
			drawList->AddCircle(screenCenter, Features::rFovSize - 1.0f, outlineColor, numSegments, outlineThickness);
			drawList->AddCircle(screenCenter, Features::rFovSize + 1.0f, outlineColor, numSegments, outlineThickness);
		}

		if (Features::rFovFill) {
			drawList->AddConvexPolyFilled(vertices.data(), vertices.size(), fillColor);
		}

		drawList->AddCircle(screenCenter, Features::rFovSize, borderColor, numSegments);
	}

	int MyTeamId = Cached::LocalPlayerState->TeamIndex();

	ImVec2 ScreenCenter(ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f);

	vector<FortPTR> addressesToRead;
	addressesToRead.reserve(PlayerArray.Count * 2);


	Esp::rWeaponname = lazy::GetWeaponName((FortPTR)Cached::LocalPawn->GetAddress());

	for (int i = 0; i < PlayerArray.Count; i++) {
		AFortPlayerState* PlayerState = reinterpret_cast<AFortPlayerState*>(PlayerArray.Get(i));
		if (!PlayerState) continue;

		AFortPlayerPawn* Player = reinterpret_cast<AFortPlayerPawn*>(PlayerState->PawnPrivate());
		if (!Player || Player == Cached::LocalPawn) continue;

		USkeletalMeshComponent* Mesh = Player->Mesh();
		if (!Mesh) continue;

		int ActorTeamId = PlayerState->TeamIndex();
		if (MyTeamId && ActorTeamId == MyTeamId) continue;

		addressesToRead.push_back((FortPTR)PlayerState + 0x29A); // bot check
		vector<char> batchData = batch_read<char>(addressesToRead);

		size_t batchIndex = 0;

		char botCheck = batchData[batchIndex++];

		auto bone_cache = read<int>(reinterpret_cast<uintptr_t>(Mesh) + Offsets::BoneCache);
		auto cmp2_wrld = read<FTransform>(reinterpret_cast<uintptr_t>(Mesh) + 0x1c0);
		auto cmp2_wrld_matrix = cmp2_wrld.ToMatrixWithScale();

		Vector3 Head3D = Mesh->GetSocketLocation(110);
		Vector2 Head2D = Cached::PlayerController->ProjectWorldLocationToScreen(Head3D);

		Vector3 Bottom3D = Mesh->GetSocketLocation(0);//
		Vector2 Bottom2D = Cached::PlayerController->ProjectWorldLocationToScreen(Bottom3D);

		float BoxHeight = abs(Head2D.y - Bottom2D.y) * 1.2f;
		float CornerHeight = BoxHeight;
		float CornerWidth = BoxHeight * 0.5f;

		float distance = Head3D.Distance(camera.location) / 100;

		if (distance > Features::rMaxDistance) continue;

		auto crossdist = GetCrossDistance(Head2D.x, Head2D.y, screen_width / 2, screen_height / 2);
		Vector2 Center = Head2D;
		Center.y = (Head2D.y + Bottom2D.y) / 2.0f;

		bool isRecentlyRendered = Mesh->WasRecentlyRendered(0.06f);

		ImColor visible_color = isRecentlyRendered
			? ImColor(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
			: ImColor(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3]);

		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		float textSpacing = 12.0f;
		float textYPos = Bottom2D.y + 2;
		float multiplier = max(1.0f, 1.0f + distance * 0.025f);
		float topTextYPos = Center.y - (CornerHeight / 2) * multiplier;

		ImFont* font = nullptr;
		auto draw_centered_text = [&](const std::string& text, ImColor color, float yPos) {
			if (font) {
				draw_list->AddText(font, 12.f, ImVec2(Center.x - (font->CalcTextSizeA(12.f, FLT_MAX, 0.0f, text.c_str()).x / 2), yPos), color, text.c_str());
			}
			};


		if (Esp::rRgbBox) {
			float halfWidth = CornerWidth / 2.0f;
			float halfHeight = CornerHeight / 2.0f;


			float startX = Center.x - halfWidth;
			float startY = Center.y - halfHeight;

			float extendedHeight = CornerHeight;

			float time = static_cast<float>(ImGui::GetTime());
			float frequency = 0.8f;
			int r = static_cast<int>(std::sin(frequency * time + 0) * 127 + 128);
			int g = static_cast<int>(std::sin(frequency * time + 2) * 127 + 128);
			int b = static_cast<int>(std::sin(frequency * time + 4) * 127 + 128);

			ImColor boxColor(r, g, b);
			float borderThickness = 1.7f;

			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06);

			FullBox(startX, startY, CornerWidth, extendedHeight, boxColor, borderThickness, false, recentlyRendered);
		}

		if (currentBox == 1) {
			draw::FullBox(Center.x - (CornerWidth / 2), Center.y - (CornerHeight / 2), CornerWidth, CornerHeight, visible_color, 1.6f);
			draw::DrawFill(Center.x - (CornerWidth / 2), Center.y - (CornerHeight / 2), CornerWidth, CornerHeight, visible_color, 1.6f);
		}
		else if (currentBox == 2) {
			draw::DrawCornerBox(Center.x - (CornerWidth / 2), Center.y - (CornerHeight / 2), CornerWidth, CornerHeight, visible_color, 1.6f);
			draw::DrawFill(Center.x - (CornerWidth / 2), Center.y - (CornerHeight / 2), CornerWidth, CornerHeight, visible_color, 1.6f);
		}



		if (Esp::rSkeleton) {

			draw::DrawSkeleton(Mesh, bone_cache, cmp2_wrld_matrix, distance, visible_color);
		}

		if (Esp::rHeadBox) {

			bool drawOutline = Esp::rskelOutlines;

			draw::Draw3DBoxHead(Head3D, Esp::HeadBoxSize, visible_color, Esp::outlinecolor, Esp::HeadBoxThick, drawOutline);
		}

		if (Esp::rSnaplines) {
			ImVec2 topMiddleScreen(screen_width / 2, 5);

			if (Head2D.x > 0 && Head2D.y > 0) {
				float baseHeadSize = 1.0f;
				float distanceFactor = (distance / 100.0f);

				float dynamicHeadRadius = baseHeadSize / distanceFactor;
				if (dynamicHeadRadius < 1.0f) {
					dynamicHeadRadius = 1.0f;
				}

				ImVec2 topOfHead(Head2D.x, Head2D.y - dynamicHeadRadius);

				if (Esp::MiscOutline) {
					ImGui::GetBackgroundDrawList()->AddLine(
						topMiddleScreen,
						topOfHead,
						ImColor(0.0f, 0.0f, 0.0f, 1.0f),
						3.0f
					);
				}

				ImGui::GetBackgroundDrawList()->AddLine(
					topMiddleScreen,
					topOfHead,
					visible_color,
					1.0f
				);
			}
		}

		auto dist = GetCrossDistance(Head2D.x, Head2D.y, screen_width / 2, screen_height / 2);

		if (Head2D.x > 0 && Head2D.y > 0 && dist < Features::rFovSize && dist < Cached::ClosestDistance) {
			Cached::ClosestDistance = dist;
			Cached::TargetEntity = Player;
		}


		if (Esp::rViewAngle) {
			float playerAngle = camera.rotation.y * (PI / 180.0f);
			float fovAngle = camera.fov * (PI / 180.0f);

			ImVec2 direction(cos(playerAngle - fovAngle), sin(playerAngle - fovAngle));
			direction = ImVec2(direction.x / sqrt(direction.x * direction.x + direction.y * direction.y),
				direction.y / sqrt(direction.x * direction.x + direction.y * direction.y));

			float lineLength = 175.0f / distance;
			ImVec2 lineEnd(Head2D.x + lineLength * direction.x, Head2D.y + lineLength * direction.y);

			draw_list->AddLine(ImVec2(Head2D.x, Head2D.y), lineEnd, ImGui::ColorConvertFloat4ToU32(visible_color), 1.5f);
		}

		if (read<BYTE>((FortPTR)Player + 0x982) >> 4 & 1) {
			continue;
		}

		bool bot = botCheck >> 3 & 1;

		if (Esp::rFovRadar) {
			draw::addtofovradar(Head3D, 187, isRecentlyRendered, ScreenCenter, visible_color);
		}



		ImVec2 center(screen_width / 2, screen_height / 2);

		if (currentSnapline == 1)
			draw_list->AddLine(ImVec2(screen_width / 2, screen_height - 5), ImVec2(Bottom2D.x, Bottom2D.y), ImColor(visible_color), 1);
		else if (currentSnapline == 2)
			draw_list->AddLine(ImVec2(screen_width / 2, 0), ImVec2(Head2D.x, Head2D.y), ImColor(visible_color), 1);
		else if (currentSnapline == 3)
			draw_list->AddLine(ImVec2(center.x, center.y), ImVec2(Head2D.x, Head2D.y), ImColor(visible_color), 1);


		if (Esp::rRenderCount) {
			char rendercount[256];
			sprintf(rendercount, skCrypt("Render Count: %d"), PlayerArray.Count);
			ImVec2 text_size = ImGui::CalcTextSize(rendercount);
			float x = (screen_width - text_size.x) / 2.0f;
			float y = 80.0f;
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 15.0f, ImVec2(x, y), ImColor(255, 0, 0, 255), rendercount);
		}


		if (Exploits::rStreamProof)
		{
			SetWindowDisplayAffinity_Spoofed(MyHwnd, WDA_EXCLUDEFROMCAPTURE);
		}
		else
		{
			SetWindowDisplayAffinity_Spoofed(MyHwnd, WDA_NONE);
		}



		bool knocked = read<BYTE>((FortPTR)Player + 0x982) >> 4 & 1;
		if ((!Features::rDownedCheck || !knocked) && crossdist < Features::rFovSize && crossdist < Cached::closestDistance) {
			if (!Features::rBotCheck || !bot) {
				Cached::closestDistance = crossdist;
				Cached::closestPawn = Player;
			}
		}


		if (Features::rTargetingOnly && Player != Cached::closestPawn) continue;



		if (Esp::rRanked) {
			ImVec2 text_size;
			uintptr_t habenero = read<uintptr_t>(Cached::PlayerState->GetAddress() + 0x9E8 - 0x10);
			int32_t RankProgress = read<int32_t>(habenero + 0xb8 + 0x10);
			std::string ranktype = lazy::get_rank(RankProgress);
			std::wstring w_ranktype = string_to_wstring(ranktype);
			std::string final = wstring_to_utf8(w_ranktype);
			char ranked[64];
			sprintf_s(ranked, "%s", (final));

			ImVec4 rankedColor = lazy::get_rank_color(RankProgress);
			float textWidth = ImGui::CalcTextSize(ranktype.c_str()).x;
			float xCentered = Bottom2D.x - textWidth / 2;


			topTextYPos += textSpacing;
			textWidth = ImGui::CalcTextSize(ranked).x;
			xCentered = Bottom2D.x - textWidth / 2;
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos), ImColor(rankedColor), ranked);
		}



		if (Esp::rUsername || Esp::rPlatformname) {
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06f);

			ImColor usernameTextColor = ImGui::ColorConvertFloat4ToU32(
				recentlyRendered ? ImVec4(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
				: ImVec4(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3])
			);

			std::string nameText;
			if (Esp::rUsername) {
				nameText = lazy::GetPlayerName((FortPTR)PlayerState);
			}
			if (Esp::rPlatformname) {
				if (!nameText.empty()) nameText += skCrypt("");
				nameText += lazy::GetPlatformName((FortPTR)PlayerState);
				if (!nameText.empty()) nameText += skCrypt("");
			}

			float textWidth = ImGui::CalcTextSize(nameText.c_str()).x;
			float xCentered = Bottom2D.x - textWidth / 2;

			float outlineThickness = 2.0f;

			if (Esp::MiscOutline) {
				ImColor outlineColor = ImColor(0, 0, 0, 255);

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered - outlineThickness, topTextYPos), outlineColor, nameText.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered + outlineThickness, topTextYPos), outlineColor, nameText.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos - outlineThickness), outlineColor, nameText.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos + outlineThickness), outlineColor, nameText.c_str());
			}

			ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos), usernameTextColor, nameText.c_str());
			topTextYPos += textSpacing;
		}



		float yOffset = Head2D.y;


		static bool magic = false;
		if (Exploits::MajicBullet) {
			{
				if (Cached::LocalPawn->GetAddress() && !magic)
				{
					std::printf("\Working...\n");
					uintptr_t Class = read<uintptr_t>(Cached::LocalPawn->GetAddress() + 0x10);
					uintptr_t DefaultObject = read<uintptr_t>(Class + 0x110);
					uintptr_t DefaultMesh = read<uintptr_t>(DefaultObject + 0x310);
					uintptr_t DefaultStaticMesh = read<uintptr_t>(DefaultMesh + 0x508);
					FArray<FTransform> RefFinalBonePose = read<FArray<FTransform>>(DefaultStaticMesh + 0x338);
					FTransform RefFinalBonePose_Head = read<FTransform>(RefFinalBonePose.Get() + 0x1E0);
					RefFinalBonePose_Head.scale = { 15, 15, 20 };
					write<FTransform>(RefFinalBonePose.Get() + 0x1E0, RefFinalBonePose_Head);
					magic = true;
					std::printf("\Working...\n");
				}

			}

		}
		
		if (Exploits::SpinBot) {
			if (Cached::LocalPawn) {

				SPOOF_FUNC;
				auto Mesh = read<uint64_t>((uint64_t)Cached::LocalPawn + Offsets::Mesh);

				if (!isSpinning) {
					isSpinning = true;
					originalRotation = read<Vector3>(Mesh + 0x338);
					currentAngle = static_cast<float>(originalRotation.y);
				}
				currentAngle += rotationSpeed;

				Vector3 CachedRotation = read<Vector3>(Mesh + 0x338);
				Vector3 newRotation = Vector3(CachedRotation.x, currentAngle, CachedRotation.z);
				write<Vector3>(Mesh + 0x338, newRotation);
			}
		}
		else {
			if (Cached::LocalPawn) {
				auto Mesh = read<uint64_t>((uint64_t)Cached::LocalPawn + Offsets::Mesh);

				if (isSpinning) {
					isSpinning = false;
					write<Vector3>(Mesh + 0x338, originalRotation);
				}
			}
		}

		if (Esp::rRadar)
		{
			ImGui::SetNextWindowPos({ 10.0f, 60.0f });
			ImGui::SetNextWindowSize({ 250.0f, 250.0f });
			ImGui::Begin(skCrypt("##radar"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize);
			{
				int ScreenX, ScreenY = 0;
				lazy::project_world_to_radar(Bottom3D, ScreenX, ScreenY);
				ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(ScreenX, ScreenY), 2.0f, ImColor(255, 50, 50, 255), 64);

				ImVec2 winpos = ImGui::GetWindowPos();
				ImVec2 winsize = ImGui::GetWindowSize();
				ImGui::GetWindowDrawList()->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y), ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y), ImColor(24, 24, 24, 255), 1.0f);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(winpos.x, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x + winsize.x, winpos.y + winsize.y * 0.5f), ImColor(24, 24, 24, 255), 1.0f);
				ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), 2.0f, ImColor(255, 255, 255, 255), 64);
			}
			ImGui::End();
		}

		if (Esp::rCornerBox) {
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06);

			ImColor boxColor = ImGui::ColorConvertFloat4ToU32(
				ImVec4(
					recentlyRendered ? Esp::espcolor[0] : Esp::espcolor2[0],
					recentlyRendered ? Esp::espcolor[1] : Esp::espcolor2[1],
					recentlyRendered ? Esp::espcolor[2] : Esp::espcolor2[2],
					recentlyRendered ? Esp::espcolor[3] : Esp::espcolor2[3]
				)
			);

			CorneredBox(Center.x - (CornerWidth / 2), Center.y - (CornerHeight / 2), CornerWidth, CornerHeight, boxColor, 1.0, false, recentlyRendered);
		}

		if (Esp::rFullbox3D)
		{
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06);

			ImColor boxColor = ImGui::ColorConvertFloat4ToU32(
				ImVec4(
					recentlyRendered ? Esp::espcolor[0] : Esp::espcolor2[0],
					recentlyRendered ? Esp::espcolor[1] : Esp::espcolor2[1],
					recentlyRendered ? Esp::espcolor[2] : Esp::espcolor2[2],
					recentlyRendered ? Esp::espcolor[3] : Esp::espcolor2[3]
				)
			);

			draw3DBox(Head3D, Bottom3D, boxColor, Esp::rFillBoxs, recentlyRendered);
		}


		if (Esp::rFullbox)
		{
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06);

			ImColor boxColor = ImGui::ColorConvertFloat4ToU32(
				ImVec4(
					recentlyRendered ? Esp::espcolor[0] : Esp::espcolor2[0],
					recentlyRendered ? Esp::espcolor[1] : Esp::espcolor2[1],
					recentlyRendered ? Esp::espcolor[2] : Esp::espcolor2[2],
					recentlyRendered ? Esp::espcolor[3] : Esp::espcolor2[3]
				)
			);

			FullBox(Center.x - (CornerWidth / 2), Center.y - (CornerHeight / 2), CornerWidth, CornerHeight, boxColor, 1.0, false, recentlyRendered);
		}



		if (Esp::rDistance) {
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06f);

			ImColor DisColor = ImGui::ColorConvertFloat4ToU32(
				recentlyRendered ? ImVec4(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
				: ImVec4(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3])
			);

			std::string distanceText = "[" + to_string((int)distance) + " m]";

			float textWidth = ImGui::CalcTextSize(distanceText.c_str()).x;
			float xCentered = Bottom2D.x - textWidth / 2;

			float outlineThickness = 1.0f;

			if (Esp::MiscOutline) {
				ImColor outlineColor = ImColor(0, 0, 0, 255);

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered - outlineThickness, textYPos), outlineColor, distanceText.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered + outlineThickness, textYPos), outlineColor, distanceText.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, textYPos - outlineThickness), outlineColor, distanceText.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, textYPos + outlineThickness), outlineColor, distanceText.c_str());
			}

			ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, textYPos), DisColor, distanceText.c_str());

			textYPos += textSpacing;
		}



		if (Esp::rWeaponEsp) {
			std::string weaponname = lazy::GetWeaponName((FortPTR)Player);
			if (weaponname.empty()) weaponname = skCrypt("Hands");

			float textWidth = ImGui::CalcTextSize(weaponname.c_str()).x;
			float xCentered = Bottom2D.x - textWidth / 2;

			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06f);

			ImColor weaponTextColor = ImGui::ColorConvertFloat4ToU32(
				recentlyRendered ? ImVec4(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
				: ImVec4(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3])
			);

			float adjustedYOffset = yOffset - 20.0f;

			float outlineThickness = 1.0f;

			if (Esp::MiscOutline) {
				ImColor outlineColor = ImColor(0, 0, 0, 255);

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered - outlineThickness, topTextYPos), outlineColor, weaponname.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered + outlineThickness, topTextYPos), outlineColor, weaponname.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos - outlineThickness), outlineColor, weaponname.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos + outlineThickness), outlineColor, weaponname.c_str());
			}

			ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, topTextYPos), weaponTextColor, weaponname.c_str());
			yOffset += ImGui::GetFontSize() + 2;
		}

		uintptr_t CurrentVehicle = read<DWORD_PTR>(Cached::LocalPawn->GetAddress() + 0x2a10);

		if (Esp::rKills || Esp::rLevel) {
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06f);

			ImColor textColor = ImGui::ColorConvertFloat4ToU32(
				recentlyRendered ? ImVec4(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
				: ImVec4(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3])
			);

			std::string combinedInfo;
			if (Esp::rKills) {
				combinedInfo = std::string(skCrypt("Kills: ")) + to_string(read<int>((FortPTR)PlayerState + Offsets::KillScore));
			}
			if (Esp::rLevel) {
				if (!combinedInfo.empty()) combinedInfo += " | ";
				combinedInfo += std::string(skCrypt("Level: ")) + to_string(read<int>((FortPTR)PlayerState + Offsets::SeasonLevelUIDisplay));
			}

			float textWidth = ImGui::CalcTextSize(combinedInfo.c_str()).x;
			float xCentered = Bottom2D.x - textWidth / 2;

			float outlineThickness = 1.0f;

			if (Esp::MiscOutline) {
				ImColor outlineColor = ImColor(0, 0, 0, 255);

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered - outlineThickness, textYPos), outlineColor, combinedInfo.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered + outlineThickness, textYPos), outlineColor, combinedInfo.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, textYPos - outlineThickness), outlineColor, combinedInfo.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, textYPos + outlineThickness), outlineColor, combinedInfo.c_str());
			}

			ImGui::GetBackgroundDrawList()->AddText(ImVec2(xCentered, textYPos), textColor, combinedInfo.c_str());

			textYPos += textSpacing;
		}
	}
}

