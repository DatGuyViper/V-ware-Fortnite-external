#include "../Game/Classes.h"
#include "../ImGui/imgui.h"
#include "../Driver/driver.h"
#include "../Extra/spoof.h"
#include "../Extra/Crypt.h"
#include "../Rendering/Cache.h"


float distanceDivisor = 50.0f;

bool IsTargetWithinFOV(const Vector2& target2D, float screenWidth, float screenHeight) {
	float distance = GetCrossDistance(target2D.x, target2D.y, screenWidth / 2, screenHeight / 2);
	return distance <= Features::rFovSize && target2D.x != 0 && target2D.y != 0;
}

static Vector3 GetPrediction(Vector3 position, Vector3 velocity, float distance, float speed, float gravity) {
	auto TimeToTarget = distance / speed;
	auto PredictedTargetPosition = position + (velocity * TimeToTarget);
	auto GravityAdjustment = abs(gravity * -980.0) * (TimeToTarget * TimeToTarget) * 0.5;
	auto AdjustedPosition = Vector3(PredictedTargetPosition.x, PredictedTargetPosition.y, PredictedTargetPosition.z + GravityAdjustment);
	return AdjustedPosition;
}

namespace SonyDriverHelper {
	class api {
	public:
		static void Init();
		static void MouseMove(float x, float y);
		static bool GetKey(int id);
	};
}

ImVec2 CalculateAimOffset(const Vector2& target2D, const ImVec2& screenCenter, int aimSpeed, float screenWidth, float screenHeight) {
	float targetX = 0.0f;
	float targetY = 0.0f;

	if (target2D.x != 0) {
		targetX = (target2D.x > screenCenter.x) ? -(screenCenter.x - target2D.x) / aimSpeed : (target2D.x - screenCenter.x) / aimSpeed;
		if ((target2D.x > screenCenter.x && targetX + screenCenter.x > screenWidth) ||
			(target2D.x < screenCenter.x && targetX + screenCenter.x < 0)) {
			targetX = 0.0f;
		}
	}

	if (target2D.y != 0) {
		targetY = (target2D.y > screenCenter.y) ? -(screenCenter.y - target2D.y) / aimSpeed : (target2D.y - screenCenter.y) / aimSpeed;
		if ((target2D.y > screenCenter.y && targetY + screenCenter.y > screenHeight) ||
			(target2D.y < screenCenter.y && targetY + screenCenter.y < 0)) {
			targetY = 0.0f;
		}
	}

	return ImVec2(targetX, targetY);
}

uintptr_t NetConnection = 0x508; // SDK, UNetConnection* NetConnection 

uintptr_t RotationInput = NetConnection + 0x8;

void ResetTarget() {
	Cached::closestDistance = FLT_MAX;
	Cached::closestPawn = nullptr;
}

bool memory_event(Vector3 newpos)
{
	write<Vector3>(Cached::PlayerController->GetAddress() + RotationInput, newpos);
	return true;
}

void aimbot(int bone, const std::string& weapon) {
	if (!Cached::closestPawn) return;

	auto mesh = Cached::closestPawn->Mesh();
	if (!mesh) {
		ResetTarget();
		return;
	}

	Vector3 LocalHead3D = Cached::LocalPawn->Mesh()->GetSocketLocation2(bone);
	Vector3 Head3D = mesh->GetSocketLocation2(bone);
	Vector2 Head2D = Cached::PlayerController->ProjectWorldLocationToScreen(Head3D);

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 screenCenter(io.DisplaySize.x / 2, io.DisplaySize.y / 2);

	if (Features::rAimline) {
		ImGui::GetBackgroundDrawList()->AddLine(screenCenter, ImVec2(Head2D.x, Head2D.y),
			ImGui::ColorConvertFloat4ToU32(Esp::AimlineColor), 1.0f);

		if (Features::rAimCircle) {
			float distance2D = sqrtf(powf(Head2D.x - screenCenter.x, 2) + powf(Head2D.y - screenCenter.y, 2));
			float dynamicRadius = 5.0f;
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Head2D.x, Head2D.y), dynamicRadius,
				ImGui::ColorConvertFloat4ToU32(Esp::AimlineColor), 32, 1.0f);
		}
	}

	if (Features::rVisibleCheck && !mesh->WasRecentlyRendered(0.06f)) return;

	auto root = Cached::closestPawn->RootComponent();
	Vector3 velocity = root->GetComponentVelocity();
	float distance = Head3D.Distance(camera.location) / distanceDivisor;

	if (Features::rPrediction && Cached::LocalPawn->CurrentWeapon()->GetAddress()) {
		auto ProjectileSpeed = read<float>(Cached::LocalPawn->CurrentWeapon()->GetAddress() + Offsets::ProjectileSpeed);
		auto ProjectileGravity = read<float>(Cached::LocalPawn->CurrentWeapon()->GetAddress() + Offsets::ProjectileGravity);

		if (ProjectileSpeed > 0.1f && ProjectileGravity > 0.1f) {
			Vector3 targetVelocity = root->GetComponentVelocity();
			float targetDistance = Head3D.Distance(camera.location);
			Head3D = GetPrediction(Head3D, targetVelocity, targetDistance, ProjectileSpeed, ProjectileGravity);
		}
	}

	Head2D = Cached::PlayerController->ProjectWorldLocationToScreen(Head3D);

	if (!IsTargetWithinFOV(Head2D, io.DisplaySize.x, io.DisplaySize.y)) {
		ResetTarget();
		return;
	}

	ImVec2 targetOffset = CalculateAimOffset(Head2D, screenCenter, Features::rSmooth, io.DisplaySize.x, io.DisplaySize.y);

	if (Features::Memory) {


	}
	else {

		if (Features::mouse2) {
		}

		else {
			SonyDriverHelper::api::MouseMove(static_cast<int>(targetOffset.x), static_cast<int>(targetOffset.y));
		}
	}

	if (!Features::rLockTarget) {
		ResetTarget();
	}
}

void triggerbot(std::string weapon, uintptr_t playercontroller) {
	SPOOF_FUNC;
	if (Features::rTriggerbot) {
		if (weapon.find(skCrypt("Shotgun")) != std::string::npos) {
			if (read<uintptr_t>(playercontroller + Offsets::TargetedFortPawn)) {
				mouse_event_Spoofed(MOUSEEVENTF_LEFTDOWN, DWORD(NULL), DWORD(NULL), DWORD(0x0002), ULONG_PTR(NULL));
				mouse_event_Spoofed(MOUSEEVENTF_LEFTUP, DWORD(NULL), DWORD(NULL), DWORD(0x0004), ULONG_PTR(NULL));
			}
		}
	}
}




void Render1() {
	SPOOF_FUNC;
	if (GetAsyncKeyState(Features::rAimkey) && Features::rAimbot) {
		int boneID = 0;

		switch (currentTarget) {
		case 0:  boneID = 110; break; // Head
		case 1:  boneID = 106; break; // Lower Head
		case 2:  boneID = 67;  break; // Neck
		case 3:  boneID = 66;  break; // Chest
		case 5:  boneID = 2;   break; // Human Pelvis
		case 6:  boneID = 7;   break; // Spine 1
		case 7:  boneID = 5;   break; // Spine 2
		case 8:  boneID = 2;   break; // Spine 3
		case 9:  boneID = 9;   break; // L Collarbone
		case 10: boneID = 35;  break; // L Upperarm
		case 11: boneID = 36;  break; // L Forearm 1
		case 12: boneID = 10;  break; // L Forearm 23
		case 13: boneID = 34;  break; // L Forearm 2
		case 14: boneID = 33;  break; // L Forearm 3
		case 15: boneID = 32;  break; // L Palm
		case 16: boneID = 11;  break; // L Hand
		case 17: boneID = 98;  break; // R Collarbone
		case 18: boneID = 64;  break; // R Upperarm
		case 19: boneID = 65;  break; // R Forearm 1
		case 20: boneID = 39;  break; // R Forearm 23
		case 21: boneID = 63;  break; // R Forearm 2
		case 22: boneID = 62;  break; // R Forearm 3
		case 23: boneID = 40;  break; // R Hand
		case 24: boneID = 58;  break; // R Palm
		case 25: boneID = 71;  break; // L Thigh 1
		case 26: boneID = 77;  break; // L Thigh 2
		case 27: boneID = 72;  break; // L Thigh 3
		case 28: boneID = 74;  break; // L Calf
		case 29: boneID = 73;  break; // L Foot 2
		case 30: boneID = 86;  break; // L Foot
		case 31: boneID = 76;  break; // L Toe
		case 32: boneID = 78;  break; // R Thigh 1
		case 33: boneID = 84;  break; // R Thigh 2
		case 34: boneID = 79;  break; // R Thigh 3
		case 35: boneID = 81;  break; // R Calf
		case 36: boneID = 82;  break; // R Foot 2
		case 37: boneID = 87;  break; // R Foot
		case 38: boneID = 83;  break; // R Toe
		default: break;
		}

		if (boneID != 0) {

			aimbot(boneID, lazy::GetWeaponName((FortPTR)(Cached::LocalPawn)));

		}
	}
	if (GetAsyncKeyState_Spoofed(Features::rTrigkey) && Features::rTriggerbot) {

		triggerbot(lazy::GetWeaponName((FortPTR)(Cached::LocalPawn)), (FortPTR)(Cached::PlayerController));

	}

	cache();
	loop();
}
