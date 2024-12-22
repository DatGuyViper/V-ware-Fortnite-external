#pragma once
#include "../Game/sdk.h"
#include <thread>
#include <unordered_map>
#include <cmath>
#include "../D3DX/d3dx9math.h"
#include "../Extra/Crypt.h"
#include <string>

#define PI 3.14159265358979323846f
#define M_PI 3.14159265358979323846



int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);




namespace Exploits
{
	inline float rFOVValue = 80;
	inline bool rFOVChanger;
	inline bool AirStuck;
	inline bool debuggui;
	inline bool CrashServer;
	inline bool NoSpec;
	inline bool Spread;
	inline bool MajicBullet;
	inline bool rStreamProof;
	inline bool magic_bullet = true;
	inline bool FirstPerson;
	inline bool AdsInAir;
	inline bool rCarFly;

	inline bool rNoRecoil;
	inline bool bRapidFire;
	inline bool SpinBot;
	inline bool Rainbowcrosshair;
	inline bool rNoReload;
	inline bool rMaxCharge;
	inline bool test;
	inline bool FreezePlr;
	inline bool autorun;
	inline bool NoEquipAnimation;
	inline bool instaReboot;
	inline bool playersize;

}

namespace Esp
{





	static float espcolor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	static float espcolor2[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	static float espcolor3[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	inline bool rFullbox;
	inline bool Sigma;
	inline bool rRoundedBox;
	static float boxWidthMultiplier = 1.0f;
	static float boxThicknessMultiplier = 1.0f;
	static float HeadBoxThick = 0.5f;
	static float HeadBoxSize = 20.0f;
	static float skeletonThicknessMultiplier = 1.0f;

	inline bool rRadar;
	inline bool rSnaplines;
	inline bool rDistance;
	inline bool rKills;
	inline bool rLevel;
	inline std::string rWeaponname;
	inline bool rPlatformname;
	inline bool rRanked;
	inline bool rUsername;
	inline bool rCornerbox;
	inline bool rHeadBox;
	inline bool rSkeleton;
	inline bool rfeet;
	inline bool rjointEsp;
	inline bool rViewAngle;
	inline bool rChams;
	inline bool rWeaponEsp;
	inline bool MiscOutline;
	inline bool rRenderCount;
	inline bool rFullbox3D;
	inline bool rCornerBox;
	inline bool rainbowMode;
	inline bool rFillBoxs;
	inline bool rFovRadar;
	inline bool rboxOutlines;
	inline bool rskelOutlines;
	inline bool rHead;
	inline bool julian3d;
	inline bool julian2d;
	inline int julian2d_type;

	inline ImVec4 AimlineColor = ImVec4(1.f, 1.f, 1.f, 1.f);


	inline bool rRadarSize;

	inline bool rWireframe;
	inline bool rRgbBox;
	inline ImVec4 FovColor = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 AccentColor = ImVec4(1.f, 1.f, 1.f, 0.6f);

	inline ImVec4 FovFillColor = ImVec4(1.f, 1.f, 1.f, 0.f);

	inline ImVec4 BoxColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 FillColorVis = ImVec4(1.f, 1.f, 1.f, 0.2f);
	inline ImVec4 DistanceColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 UsernameColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 PlatformColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 KillsColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 LevelsColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 WeaponColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SkeletonColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SnaplineColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 RadarColorVis = ImVec4(1.f, 0.f, 0.f, 1.f);
	inline ImVec4 FovArrowsColorVis = ImVec4(1.f, 0.f, 0.f, 1.f);
	inline ImVec4 outlinecolor = ImVec4(0.f, 0.f, 0.f, 1.f);

	inline ImVec4 BoxColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 FillColorHidden = ImVec4(1.f, 1.f, 1.f, 0.2f);
	inline ImVec4 DistanceColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 UsernameColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 PlatformColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 KillsColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 LevelsColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 WeaponColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SkeletonColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SnaplineColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 RadarColorHidden = ImVec4(0.f, 1.f, 0.f, 1.f);
	inline ImVec4 FovArrowsColorHidden = ImVec4(0.f, 1.f, 0.f, 1.f);

}


namespace Features
{
	inline int rFov = 70;
	float distanceDivisor = 500.0f;
	inline bool rFPS;
	inline bool ArrayList;
	inline bool mouse2;
	inline bool Memory;
	inline float rHumanization;
	inline bool rGunConfigs;
	static bool waitingForAimKey = false;
	static bool waitingForTrigKey = false;
	inline int rAimkey;
	inline int rTrigkey;
	inline bool rVisibleCheck;
	inline bool rDownedCheck;
	inline bool rTargetingOnly;
	inline bool rBotCheck;
	inline bool rAimline;
	inline bool rLockTarget;
	inline float rSmooth = 27.0;
	inline float rTriggerbotDelay = 0;
	inline bool rAimbot;
	inline bool rPrediction;
	inline bool rFovCircle;
	inline bool rFovCircleOut;
	inline bool rAimCircle;
	inline bool rFovFill;
	inline bool rTriggerbot;
	inline bool rFOVArrows;
	inline float rMaxDistance = 100970.f;
	inline bool LevelActorCaching = 1;

	inline int rFovSize = 200;
	inline int rADSFovSize = 200;
}

#include <cstdint>

namespace Offsets {
	uint64_t

		UWorld = 0x169D6108,
		GNames = 0x17B01480,
		GameState = 0x178,
		PlayerArray = 0x2C0,
		OwningGameInstance = 0x1F0,
		LocalPlayers = 0x38,
		PlayerController = 0x30,
		LocalPawn = 0x350,
		PlayerState = 0x2c8,
		RootComponent = 0x1B0,
		PersistentLevel = 0x38,
		AActors = 0xA0,
		ActorCount = 0xA8,
		ReviveFromDBNOTime = 0x4C38,
		Mesh = 0x328,
		TeamIndex = 0x1261,
		Platform = 0x408,
		PawnPrivate = 0x320,
		RelativeLocation = 0x138,
		PrimaryPickupItemEntry = 0x360,
		ItemDefinition = 0x18,
		Rarity = 0xA2,
		ItemName = 0x40,
		Levels = 0x178,
		WeaponData = 0x568,
		AmmoCount = 0xF9c,
		bIsTargeting = 0x12d8,
		ComponentVelocity = 0x180,
		TargetedFortPawn = 0x1920,
		CurrentWeapon = 0xa80,
		CurrentWeaponList = 0xa08,
		BoneArray = 0x5A8,
		BoneCache = 0x5B8,
		LastSubmitTime = 0x2E8,
		LastRenderTime = 0x2F0,
		ComponentToWorld = 0x1E0,
		CameraManager = 0x348,
		LastFiredLoc = 0x57e8,
		LastFiredDir = 0x5800,
		KillScore = 0x124c,
		SeasonLevelUIDisplay = 0x1250,
		ProjectileSpeed = 0x1A24,
		ProjectileGravity = 0x1DF0,
		RankTier = 0xB8,
		HabaneroComponent = 0xa10,
		PlayerName = 0xAF8,
		ViewState = 0xD0,
		RankedProgress = 0xB8;
}

#define FortPTR uintptr_t

#define DECLARE_MEMBER(type, name, offset) \
    type name() { return read<type>(reinterpret_cast<uintptr_t>(this) + offset); }


DWORD_PTR Uworld_Cam;

class UObject {
public:
	FortPTR GetAddress() const {
		return reinterpret_cast<FortPTR>(this);
	}

	DECLARE_MEMBER(int, GetObjectID, 0x18)
};

class USceneComponent : public UObject {
public:
	DECLARE_MEMBER(Vector3, RelativeLocation, Offsets::RelativeLocation)
	DECLARE_MEMBER(Vector3, GetComponentVelocity, Offsets::ComponentVelocity)
};

class AActor : public UObject {
public:
	DECLARE_MEMBER(USceneComponent*, RootComponent, Offsets::RootComponent)

	Vector3 GetActorLocation(bool cached = true) {
		static std::unordered_map<int, Vector3> CachedLocations;
		if (cached) {
			auto it = CachedLocations.find(GetObjectID());
			if (it != CachedLocations.end()) {
				return it->second;
			}
		}
		Vector3 location = RootComponent()->RelativeLocation();
		CachedLocations[GetObjectID()] = location;
		return location;
	}
};
class USkeletalMeshComponent : public AActor {
public:

	 Vector3 GetSocketLocation(int bone_id)
	{
		uintptr_t bone_array = read<uintptr_t>((uintptr_t)this + Offsets::BoneArray);
		if (bone_array == NULL) {
			bone_array = read<uintptr_t>((uintptr_t)this + Offsets::BoneArray + 0x10);
		}

		auto BoneTransform = read<FTransform>(bone_array + (bone_id * 0x60));
		FTransform ComponentToWorld = read<FTransform>((uintptr_t)this + Offsets::ComponentToWorld);

		D3DMATRIX Matrix = MatrixMultiplication(BoneTransform.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}

	__forceinline bool WasRecentlyRendered(uintptr_t mesh)
	   {
		double Seconds = read<double>(Uworld_Cam + 0x150);
		float LastRenderTime = read<float>((uintptr_t)this + 0x2F0);
		return Seconds - LastRenderTime <= 0.06f;
	}
};

struct CameraInfo {
	Vector3 location;
	Vector3 rotation;
	float fov;
};

CameraInfo camera;
CameraInfo Copy_CameraInfo;
FortPTR Copy_PlayerController_Camera;


CameraInfo GetCameraInfo() {
	auto location_pointer = read<uintptr_t>(Uworld_Cam + 0x128);
	auto rotation_pointer = read<uintptr_t>(Uworld_Cam + 0x138);

	struct RotationInfo
	{
		double pitch;
		char pad_0008[24];
		double yaw;
		char pad_0028[424];
		double roll;
	} rotationInfo;

	rotationInfo.pitch = read<double>(rotation_pointer);
	rotationInfo.yaw = read<double>(rotation_pointer + 0x20);
	rotationInfo.roll = read<double>(rotation_pointer + 0x1d0);

	camera.location = read<Vector3>(location_pointer);
	camera.rotation.x = asin(rotationInfo.roll) * (180.0 / M_PI);
	camera.rotation.y = ((atan2(rotationInfo.pitch * -1, rotationInfo.yaw) * (180.0 / M_PI)) * -1) * -1;
	camera.fov = read<float>((uintptr_t)Copy_PlayerController_Camera + 0x3AC) * 90.f; //  * 90.f
	return camera;
}


struct PArray {
	FortPTR Array = 0;
	uint32_t Count = 0;
	uint32_t MaxCount = 0;

	FortPTR Get(uint32_t Index) const {
		if (Index >= Count) {
			return 0;
		}
		return read<FortPTR>(Array + (Index * sizeof(FortPTR)));
	}

	uint32_t size() const {
		return Count;
	}

	FortPTR operator[](uint32_t Index) const {
		return Get(Index);
	}

	bool isValid() const {
		return Array && Count <= MaxCount && MaxCount <= 1000000;
	}

	FortPTR getAddress() const {
		return Array;
	}
};

class ULevel : public UObject {
public:
	DECLARE_MEMBER(uint32_t, ActorCount, Offsets::ActorCount)
	DECLARE_MEMBER(FortPTR, AActors, Offsets::AActors)
};

class AFortPlayerState : public AActor {
public:
	DECLARE_MEMBER(int, TeamIndex, Offsets::TeamIndex)
	DECLARE_MEMBER(AActor*, PawnPrivate, Offsets::PawnPrivate)
	DECLARE_MEMBER(DWORD_PTR, Platform, Offsets::Platform)
};

class UFortItemDefinition : public AActor {
public:
	DECLARE_MEMBER(int, RarityInt, Offsets::Rarity)

	std::string GetItemName() const {
		uint64_t itemNameAddr = read<uint64_t>(GetAddress() + Offsets::ItemName);
		if (!itemNameAddr) return "";

		uint64_t dataAddr = read<uint64_t>(itemNameAddr + 0x28);
		int length = read<int>(itemNameAddr + 0x30);
		if (length <= 0 || length >= 50) return "";

		std::wstring wideBuffer(length, 0);
		handler::read_physical(reinterpret_cast<void*>(dataAddr), &wideBuffer[0], length * sizeof(wchar_t));
		return std::string(wideBuffer.begin(), wideBuffer.end());
	}
};

class AFortWeapon : public AActor {
public:
	float GetProjectileSpeed() const {
		return read<float>(GetAddress() + 0x1d08);
	}

	float GetGravityScale() const {
		return read<float>(GetAddress() + 0x1d0c);
	}

	DECLARE_MEMBER(UFortItemDefinition*, WeaponData, Offsets::WeaponData)
	DECLARE_MEMBER(int, AmmoCount, Offsets::AmmoCount)
	DECLARE_MEMBER(bool, IsTargeting, Offsets::bIsTargeting)
};

class AFortPlayerPawn : public AActor {
public:
	DECLARE_MEMBER(float, ReviveFromDBNOTime, Offsets::ReviveFromDBNOTime)
	DECLARE_MEMBER(AFortPlayerState*, PlayerState, Offsets::PlayerState)
	DECLARE_MEMBER(USkeletalMeshComponent*, Mesh, Offsets::Mesh)
	DECLARE_MEMBER(AFortWeapon*, CurrentWeapon, Offsets::CurrentWeapon)
};

class APlayerController : public AActor {
public:
	static D3DMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0.f, 0.f, 0.f)) {
		float radPitch = rot.x * PI / 180.f;
		float radYaw = rot.y * PI / 180.f;
		float radRoll = rot.z * PI / 180.f;

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix = {};
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	static Vector2 ProjectWorldLocationToScreen(Vector3 worldLocation) {
		CameraInfo viewInfo = GetCameraInfo();
		D3DMATRIX tempMatrix = Matrix(viewInfo.rotation);
		Vector3 axisX(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		Vector3 axisY(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		Vector3 axisZ(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 delta = worldLocation - viewInfo.location;
		Vector3 transformed(delta.Dot(axisY), delta.Dot(axisZ), delta.Dot(axisX));

		if (transformed.z < 1.f) transformed.z = 1.f;

		return Vector2(
			(screen_width / 2.0f) + transformed.x * ((screen_width / 2.0f) / tanf(viewInfo.fov * PI / 360.f)) / transformed.z,
			(screen_height / 2.0f) - transformed.y * ((screen_width / 2.0f) / tanf(viewInfo.fov * PI / 360.f)) / transformed.z
		);
	}

	Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
	{
		CameraInfo viewInfo = GetCameraInfo();
		D3DMATRIX tempMatrix = Matrix(viewInfo.rotation);
		Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 vDelta = WorldLocation - viewInfo.location;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		return Vector3((screen_width / 2.0f) + vTransformed.x * (((screen_width / 2.0f) / tanf(viewInfo.fov * (float)PI / 360.f))) / vTransformed.z, (screen_height / 2.0f) - vTransformed.y * (((screen_width / 2.0f) / tanf(viewInfo.fov * (float)PI / 360.f))) / vTransformed.z, 0);
	}


	DECLARE_MEMBER(FortPTR, AcknowledgedPawn, Offsets::LocalPawn)
	DECLARE_MEMBER(AFortPlayerPawn*, TargetedFortPawn, Offsets::TargetedFortPawn)
};

auto IsInScreen(Vector2 screen_location) -> bool
{
	if (screen_location.x > 0 && screen_location.x < ScreenWidth && screen_location.y > 0 && screen_location.y < ScreenHeight) return true;
	else return false;
}


class fvector
{
public:
	fvector() : x(0.f), y(0.f), z(0.f)
	{

	}

	fvector(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~fvector()
	{

	}

	double x;
	double y;
	double z;

	inline double dot(fvector v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline double distance(fvector v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double length() {
		return sqrt(x * x + y * y + z * z);
	}

	fvector operator+(fvector v)
	{
		return fvector(x + v.x, y + v.y, z + v.z);
	}

	fvector operator-(fvector v)
	{
		return fvector(x - v.x, y - v.y, z - v.z);
	}

	fvector operator/(double flNum)
	{
		return fvector(x / flNum, y / flNum, z / flNum);
	}


	fvector operator*(double flNum) { return fvector(x * flNum, y * flNum, z * flNum); }
};

class ULocalPlayer : public AFortPlayerPawn {
public:
	DECLARE_MEMBER(APlayerController*, PlayerController, Offsets::PlayerController)
};

class UGameInstance : public AActor {
public:
	DECLARE_MEMBER(DWORD_PTR, LocalPlayers, Offsets::LocalPlayers)
};

class AGameStateBase : public UObject {
public:
	DECLARE_MEMBER(TArray, PlayerArray, Offsets::PlayerArray)
};

class UWorld : public AActor {
public:
	DECLARE_MEMBER(UGameInstance*, OwningGameInstance, Offsets::OwningGameInstance)
	DECLARE_MEMBER(ULevel*, PersistentLevel, Offsets::PersistentLevel)
	DECLARE_MEMBER(AGameStateBase*, GameState, Offsets::GameState)
};

namespace Cached
{
	float ProjectileSpeed;
	float ProjectileGravity;
	APlayerController* PlayerController;
	AFortPlayerState* PlayerState;
	AFortPlayerState* LocalPlayerState;
	AFortPlayerPawn* LocalPawn;
	USceneComponent* LocalRootComponent;
	ULocalPlayer* LocalPlayer;
	USkeletalMeshComponent* Mesh;
	ULevel* PersistentLevel;
	UWorld* World;
	AGameStateBase* GameState;
	AFortWeapon* CurrentWeapon;
	uintptr_t CameraManager;
	Vector3 relativeLocation;
	uintptr_t TEST;
	inline uintptr_t closest_mesh;

	inline float ClosestDistance = FLT_MAX;
	inline AFortPlayerPawn* TargetEntity = 0;

	float closestDistance = FLT_MAX;

	AFortPlayerPawn* closestPawn = NULL;


	Vector3 localactorpos;
}

class Player {
public:
	uintptr_t Pointer = NULL;
	uintptr_t PlayerController = NULL;
	uintptr_t Pawn = NULL;
	uintptr_t PlayerState = NULL;
	uintptr_t RootComponent = NULL;

	uintptr_t Mesh = NULL;
	uintptr_t CurrentWeapon = NULL;
	uintptr_t PreviousWeapon = NULL;
	Vector3 RelativeLocation = Vector3();
	char TeamIndex = 0;
	bool IsVisible = true;
	bool IsBot = false;
	std::string Name = std::string(skCrypt("Unknown"));

	float MouseSensitivityX = 20.0f;
	float MouseSensitivityY = 20.0f;

	Vector3 Head = Vector3();
	Vector2 Head2D = Vector2();
};

struct FNCamera
{
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
};

namespace Saved
{
	static uintptr_t UWorld = 0;
	static uintptr_t GameInstance = 0;
	static uintptr_t PersistentLevel = 0;
	static uintptr_t ActorsArray = 0;
	static uintptr_t GameState = 0;
	static Player LocalPlayer;
	static uintptr_t ClientSettingsRecord;
	static uintptr_t PlayerArray = 0;
	static int PlayersCount = 0;
	static FNCamera Camera;

	float TargetDistance = FLT_MAX;
	Player TargetPlayer = Player();
};


static D3DMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

static ImVec2 WorldToScreen(Vector3 worldlocation) {
	auto DMatrix = Matrix(Saved::Camera.Rotation);

	auto AxisX = Vector3(DMatrix.m[0][0], DMatrix.m[0][1], DMatrix.m[0][2]);
	auto AxisY = Vector3(DMatrix.m[1][0], DMatrix.m[1][1], DMatrix.m[1][2]);
	auto AxisZ = Vector3(DMatrix.m[2][0], DMatrix.m[2][1], DMatrix.m[2][2]);

	auto Delta = worldlocation - Saved::Camera.Location;
	auto Transformed = Vector3(Delta.Dot(AxisY), Delta.Dot(AxisZ), Delta.Dot(AxisX));

	if (Transformed.z < 1.f)
		Transformed.z = 1.f;

	float screenX = (ScreenWidth / 2.0f) + Transformed.x * (((ScreenWidth / 2.0f) / tanf(Saved::Camera.FOV * (float)M_PI / 360.f)) / Transformed.z);
	float screenY = (ScreenHeight / 2.0f) - Transformed.y * (((ScreenWidth / 2.0f) / tanf(Saved::Camera.FOV * (float)M_PI / 360.f)) / Transformed.z);

	return ImVec2(screenX, screenY);
}


double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

namespace lazy {
	std::string ReadWideString(uint64_t address, int length) {
		if (length <= 0 || length > 50) return "";

		std::wstring buffer(length, L'\0');
		handler::read_physical((void*)address, (PVOID)buffer.data(), length * sizeof(wchar_t));
		return std::string(buffer.begin(), buffer.end());
	}

	std::string GetWeaponNameFromData(uint64_t weaponData) {
		uint64_t itemNameAddr = read<uint64_t>(weaponData + Offsets::ItemName);
		if (!itemNameAddr) return "";

		uint64_t fData = read<uint64_t>(itemNameAddr + 0x28);
		int length = read<int>(itemNameAddr + 0x30);
		return ReadWideString(fData, length);
	}

	std::string GetWeaponName(uintptr_t Player) {
		std::string weaponName = std::string(skCrypt(""));

		uint64_t currentWeapon = read<uint64_t>((FortPTR)Player + Offsets::CurrentWeapon);
		uint64_t weaponData = read<uint64_t>(currentWeapon + Offsets::WeaponData);
		uint64_t itemName = read<uint64_t>(weaponData + Offsets::ItemName);

		if (!itemName)
			return "";

		uint64_t FData = read<uint64_t>(itemName + 0x28);
		int FLength = read<int>(itemName + 0x30);

		if (FLength > 0 && FLength < 50) {
			wchar_t* weaponBuffer = new wchar_t[FLength];

			handler::read_physical((void*)FData, (PVOID)weaponBuffer, FLength * sizeof(wchar_t));
			std::wstring wstr_buf(weaponBuffer);
			weaponName.append(std::string(wstr_buf.begin(), wstr_buf.end()));

			delete[] weaponBuffer;
		}

		return weaponName;
	}

	void radar_range(float* x, float* y, float range)
	{
		if (fabs((*x)) > range || fabs((*y)) > range)
		{
			if ((*y) > (*x))
			{
				if ((*y) > -(*x))
				{
					(*x) = range * (*x) / (*y);
					(*y) = range;
				}
				else
				{
					(*y) = -range * (*y) / (*x);
					(*x) = -range;
				}
			}
			else
			{
				if ((*y) > -(*x))
				{
					(*y) = range * (*y) / (*x);
					(*x) = range;
				}
				else
				{
					(*x) = -range * (*x) / (*y);
					(*y) = -range;
				}
			}
		}
	}

	void project_world_to_radar(Vector3 vOrigin, int& screenx, int& screeny)
	{
		Vector3 vAngle = camera.rotation;
		auto fYaw = vAngle.y * M_PI / 180.0f;
		float dx = vOrigin.x - camera.location.x;
		float dy = vOrigin.y - camera.location.y;
		float fsin_yaw = sinf(fYaw);
		float fminus_cos_yaw = -cosf(fYaw);
		float x = dy * fminus_cos_yaw + dx * fsin_yaw;
		x = -x;
		float y = dx * fminus_cos_yaw - dy * fsin_yaw;
		float range = (float)(250.0f / 5) * 1000.f;

		radar_range(&x, &y, range);

		ImVec2 DrawPos = ImVec2(10.0f, 60.0f);
		ImVec2 DrawSize = ImVec2(250.0f, 250.0f);
		float radarRadius = 250.0f / 2;
		float distance = sqrt(pow(screenx - DrawPos.x, 2) + pow(screeny - DrawPos.y, 2));

		if (distance > radarRadius)
		{
			float angle = atan2(screeny - DrawPos.y, screenx - DrawPos.x);
			screenx = static_cast<int>(DrawPos.x + radarRadius * cos(angle));
			screeny = static_cast<int>(DrawPos.y + radarRadius * sin(angle));
		}

		int rad_x = (int)DrawPos.x;
		int rad_y = (int)DrawPos.y;
		float r_siz_x = DrawSize.x;
		float r_siz_y = DrawSize.y;
		int x_max = (int)r_siz_x + rad_x - 5;
		int y_max = (int)r_siz_y + rad_y - 5;

		screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
		screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

		if (screenx > x_max)
			screenx = x_max;

		if (screenx < rad_x)
			screenx = rad_x;

		if (screeny > y_max)
			screeny = y_max;

		if (screeny < rad_y)
			screeny = rad_y;
	}

	std::string GetPlatformName(uintptr_t playerState) {
		uintptr_t platformAddr = read<uintptr_t>(playerState + Offsets::Platform);
		wchar_t platformBuffer[64];
		handler::read_physical((void*)platformAddr, platformBuffer, sizeof(platformBuffer));

		std::string platformStr(platformBuffer, platformBuffer + wcslen(platformBuffer));

		if (platformStr == std::string(skCrypt("XBL"))) return std::string(skCrypt(" Xbox "));
		if (platformStr == std::string(skCrypt("PSN")) || platformStr == std::string(skCrypt("PS5"))) return std::string(skCrypt(" PlayStation "));
		if (platformStr == std::string(skCrypt("XSX"))) return std::string(skCrypt(" Xbox "));
		if (platformStr == std::string(skCrypt("SWT"))) return std::string(skCrypt(" Nintendo "));
		if (platformStr == std::string(skCrypt("WIN"))) return std::string(skCrypt(" Windows "));

		return std::string(skCrypt(" B O T "));
	}

	std::string GetPlayerName(uintptr_t playerState) {
		__int64 FString = read<__int64>(playerState + Offsets::PlayerName);

		int length = read<int>(FString + 16);
		__int64 v6 = length;

		if (v6 == 0) return std::string(skCrypt(" AI "));

		uintptr_t FText = read<__int64>(FString + 8);

		wchar_t* nameBuffer = new wchar_t[length];

		handler::read_physical((void*)FText, nameBuffer, length * sizeof(wchar_t));

		char v21 = v6 - 1;
		if (!(DWORD)v6) {
			v21 = 0;
		}

		int v22 = 0;
		WORD* v23 = (WORD*)nameBuffer;
		for (int i = (v21 & 3); ; *v23++ += i & 7) {
			int v25 = v6 - 1;
			if (!(DWORD)v6) {
				v25 = 0;
			}
			if (v22 >= v25) {
				break;
			}
			i += 3;
			++v22;
		}

		std::wstring wbuffer{ nameBuffer };

		delete[] nameBuffer;

		return std::string(wbuffer.begin(), wbuffer.end());
	}

	auto getranked(uintptr_t PlayerState) -> int {
		if (is_valid(PlayerState)) {
			uintptr_t HabaneroComponent = read<uintptr_t>(PlayerState + 0x9e8);
			if (is_valid(HabaneroComponent)) {
				int rankTier = read<int>(HabaneroComponent + 0xb8);
				return rankTier;
			}
		}
		return 0;
	}


	std::string get_rank(int32_t Tier)
	{



		if (Tier == 0)
			return std::string("Bronze 1");
		else if (Tier == 1)
			return std::string("Bronze 2");
		else if (Tier == 2)
			return std::string("Bronze 3");
		else if (Tier == 3)
			return std::string("Silver 1");
		else if (Tier == 4)
			return std::string("Silver 2");
		else if (Tier == 5)
			return std::string("Silver 3");
		else if (Tier == 6)
			return std::string("Gold 1");
		else if (Tier == 7)
			return std::string("Gold 2");
		else if (Tier == 8)
			return std::string("Gold 3");
		else if (Tier == 9)
			return std::string("Platinum 1");
		else if (Tier == 10)
			return std::string("Platinum 2");
		else if (Tier == 11)
			return std::string("Platinum 3");
		else if (Tier == 12)
			return std::string("Diamond 1");
		else if (Tier == 13)
			return std::string("Diamond 2");
		else if (Tier == 14)
			return std::string("Diamond 3");
		else if (Tier == 15)
			return std::string("Elite");
		else if (Tier == 16)
			return std::string("Champion");
		else if (Tier == 17)
			return std::string("Unreal");
		else
			return std::string("Unranked");
	}


	ImVec4 get_rank_color(int32_t Tier)
	{
		if (Tier == 0 || Tier == 1 || Tier == 2)
			return ImVec4(0.902f, 0.580f, 0.227f, 1.0f); // Bronze
		else if (Tier == 3 || Tier == 4 || Tier == 5)
			return ImVec4(0.843f, 0.843f, 0.843f, 1.0f); // Silver
		else if (Tier == 6 || Tier == 7 || Tier == 8)
			return ImVec4(1.0f, 0.871f, 0.0f, 1.0f); // Gold
		else if (Tier == 9 || Tier == 10 || Tier == 11)
			return ImVec4(0.0f, 0.7f, 0.7f, 1.0f); // Platinum
		else if (Tier == 12 || Tier == 13 || Tier == 14)
			return ImVec4(0.1686f, 0.3294f, 0.8235f, 1.0f); // Diamond
		else if (Tier == 15)
			return ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Elite
		else if (Tier == 16)
			return ImVec4(1.0f, 0.6f, 0.0f, 1.0f); // Champion
		else if (Tier == 17)
			return ImVec4(0.6f, 0.0f, 0.6f, 1.0f); // Unreal
		else
			return ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Unranked
	}
}

struct WeaponInformation
{
	int32_t ammo_count;
	int32_t max_ammo;

	BYTE tier;
	std::string weapon_name;
	std::string buildplan;

};

struct WeaponInformation1
{
	int32_t ammo_count1;
	int32_t max_ammo1;

	BYTE tier;
	std::string weapon_name1;
	std::string buildplan1;

};
namespace draw {

	void DrawFilledRect(int x, int y, int w, int h, ImU32 color, float alpha) {
		ImU32 fillColor = ImGui::ColorConvertFloat4ToU32(ImVec4(ImColor(color).Value.x, ImColor(color).Value.y, ImColor(color).Value.z, alpha));
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), fillColor);
	}

	void addtofovradar(Vector3 WorldLocation, float fDistance, bool visible, ImVec2 drawPos, ImColor color) {
		Vector3 vAngle = camera.rotation;
		float fYaw = vAngle.y * PI / 180.0f;
		float dx = WorldLocation.x - camera.location.x;
		float dy = WorldLocation.y - camera.location.y;
		float fsin_yaw = sinf(fYaw);
		float fminus_cos_yaw = -cosf(fYaw);

		float x = -(dy * fminus_cos_yaw + dx * fsin_yaw);
		float y = dx * fminus_cos_yaw - dy * fsin_yaw;

		float fovRadius = Features::rFovSize;
		float angle = atan2f(y, x);
		float triangleSize = 12.0f;
		float widthFactor = 8.0f;
		float outlineThickness = 2.0f;

		ImVec2 triangleCenter = ImVec2(drawPos.x + cosf(angle) * (fovRadius + triangleSize),
			drawPos.y + sinf(angle) * (fovRadius + triangleSize));
		
		ImVec2 point1 = ImVec2(triangleCenter.x + cosf(angle) * triangleSize,
			triangleCenter.y + sinf(angle) * triangleSize);
		ImVec2 point2 = ImVec2(triangleCenter.x + cosf(angle + widthFactor) * triangleSize,
			triangleCenter.y + sinf(angle + widthFactor) * triangleSize);
		ImVec2 point3 = ImVec2(triangleCenter.x + cosf(angle - widthFactor) * triangleSize,
			triangleCenter.y + sinf(angle - widthFactor) * triangleSize);

		ImU32 fillColor = ImGui::ColorConvertFloat4ToU32(visible ? color : ImColor(color.Value.x, color.Value.y, color.Value.z, 0.5f));
		ImU32 outlineColor = ImGui::ColorConvertFloat4ToU32(ImColor(0.0f, 0.0f, 0.0f, 1.0f));

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		drawList->AddTriangleFilled(point1, point2, point3, fillColor);

		drawList->AddTriangle(point1, point2, point3, outlineColor, outlineThickness);
	}

	void AddLine(Vector2 start, Vector2 end, ImU32 color, float thickness, ImU32 shadowColor, float shadowOffset) {
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		drawList->AddLine(ImVec2(start.x + shadowOffset, start.y + shadowOffset), ImVec2(end.x + shadowOffset, end.y + shadowOffset), shadowColor, thickness);
		drawList->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), color, thickness);
	}

	void DrawCornerBox(int X, int Y, int W, int H, const ImColor color, int thickness) {
		float lineW = W / 3.0f;
		float lineH = H / 3.0f;
		ImU32 shadowColor = ImColor(0, 0, 0, 255);
		float shadowOffset = 1.0f;

		AddLine(Vector2{ (float)X, (float)Y }, Vector2{ (float)X, (float)(Y + lineH) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)X, (float)Y }, Vector2{ (float)(X + lineW), (float)Y }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)(X + W - lineW), (float)Y }, Vector2{ (float)(X + W), (float)Y }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)(X + W), (float)Y }, Vector2{ (float)(X + W), (float)(Y + lineH) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)X, (float)(Y + H - lineH) }, Vector2{ (float)X, (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)X, (float)(Y + H) }, Vector2{ (float)(X + lineW), (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)(X + W - lineW), (float)(Y + H) }, Vector2{ (float)(X + W), (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)(X + W), (float)(Y + H - lineH) }, Vector2{ (float)(X + W), (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
	}


	void connected_corner(const Vector3& position, const Vector3& size, ImColor color) {

		auto line_width = (size.x / 5);
		auto line_height = (size.y / 4);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		if (Esp::rboxOutlines) {
			ImU32 blackColor = IM_COL32(0, 0, 0, 255);
			int outlineThickness = 4;

			drawList->AddLine(ImVec2(position.x, position.y), ImVec2(position.x + size.x, position.y), blackColor, outlineThickness);
			drawList->AddLine(ImVec2(position.x, position.y), ImVec2(position.x, position.y + line_height), blackColor, outlineThickness);
			drawList->AddLine(ImVec2(position.x + size.x, position.y), ImVec2(position.x + size.x, position.y + line_height), blackColor, outlineThickness);

			drawList->AddLine(ImVec2(position.x, position.y + size.y), ImVec2(position.x + size.x, position.y + size.y), blackColor, outlineThickness);
			drawList->AddLine(ImVec2(position.x, position.y + size.y), ImVec2(position.x, position.y + size.y - line_height), blackColor, outlineThickness);
			drawList->AddLine(ImVec2(position.x + size.x, position.y + size.y), ImVec2(position.x + size.x, position.y + size.y - line_height), blackColor, outlineThickness);
		}

		drawList->AddLine(ImVec2(position.x, position.y), ImVec2(position.x + size.x, position.y), color, 2.f);
		drawList->AddLine(ImVec2(position.x, position.y), ImVec2(position.x, position.y + line_height), color, 2.f); 
		drawList->AddLine(ImVec2(position.x + size.x, position.y), ImVec2(position.x + size.x, position.y + line_height), color, 2.f);

		drawList->AddLine(ImVec2(position.x, position.y + size.y), ImVec2(position.x + size.x, position.y + size.y), color, 2.f);
		drawList->AddLine(ImVec2(position.x, position.y + size.y), ImVec2(position.x, position.y + size.y - line_height), color, 2.f);
		drawList->AddLine(ImVec2(position.x + size.x, position.y + size.y), ImVec2(position.x + size.x, position.y + size.y - line_height), color, 2.f);
	}

	void DrawSkeleton(USkeletalMeshComponent* Mesh, int cache_idx, D3DMATRIX matrix, float distance, ImColor color) {
		bool isRainbowMode = Esp::rainbowMode;

		ImColor lineColor;
		ImColor outlineColor = ImColor(0, 0, 0);

		if (distance > 100.0f) return;

		float lineThickness = 1.1f * Esp::skeletonThicknessMultiplier;
		float outlineThickness = lineThickness + 2.0f;

		float jointRadius = 0.5f * (100.0f / distance);

		std::vector<Vector3> bones = {
			Mesh->GetSocketLocation(66),
			Mesh->GetSocketLocation(66),
			Mesh->GetSocketLocation(9),
			Mesh->GetSocketLocation(10),
			Mesh->GetSocketLocation(11),
			Mesh->GetSocketLocation(38),
			Mesh->GetSocketLocation(39),
			Mesh->GetSocketLocation(40),
			Mesh->GetSocketLocation(2),
			Mesh->GetSocketLocation(71),
			Mesh->GetSocketLocation(72),
			Mesh->GetSocketLocation(75),
			Mesh->GetSocketLocation(76),
			Mesh->GetSocketLocation(78),
			Mesh->GetSocketLocation(79),
			Mesh->GetSocketLocation(82),
			Mesh->GetSocketLocation(83),
			Mesh->GetSocketLocation(110),
			Mesh->GetSocketLocation(66)
		};

		std::vector<Vector2> screenPositions(bones.size());
		for (size_t i = 0; i < bones.size(); ++i) {
			screenPositions[i] = Cached::PlayerController->ProjectWorldLocationToScreen(bones[i]);
		}

		Vector2 leftHip = screenPositions[9];
		Vector2 rightHip = screenPositions[13];
		Vector2 pelvisPosition = screenPositions[8];

		Vector2 hipMidPoint;
		hipMidPoint.x = (leftHip.x + rightHip.x) / 2;
		hipMidPoint.y = (leftHip.y + rightHip.y) / 2;

		pelvisPosition.x = (pelvisPosition.x + hipMidPoint.x) / 2;
		pelvisPosition.y = (pelvisPosition.y + hipMidPoint.y) / 2;
		screenPositions[8] = pelvisPosition;

		pelvisPosition.y -= 10;
		screenPositions[8] = pelvisPosition;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		auto DrawLine = [&](Vector2 start, Vector2 end, ImColor color, float thickness) {
			drawList->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), color, thickness);
			};

		auto DrawCircleFilled = [&](Vector2 position, float radius, ImColor color) {
			drawList->AddCircleFilled(ImVec2(position.x, position.y), radius, color, 16);
			};

		auto GetRainbowColor = [&](float offset) -> ImColor {
			float speed = 0.5f;
			float time = ImGui::GetTime() * speed + offset;
			int r = (sin(time) * 127 + 128);
			int g = (sin(time + 2.0f) * 127 + 128);
			int b = (sin(time + 4.0f) * 127 + 128);
			return ImColor(r, g, b);
			};

		if (isRainbowMode) {
			lineColor = GetRainbowColor(0.0f);
		}
		else {
			bool recentlyRendered = Mesh->WasRecentlyRendered(0.06f);
			lineColor = ImGui::ColorConvertFloat4ToU32(
				recentlyRendered ? ImVec4(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
				: ImVec4(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3])
			);
		}

		if (Esp::rskelOutlines) {
			DrawLine(screenPositions[2], screenPositions[0], outlineColor, outlineThickness);
			DrawLine(screenPositions[5], screenPositions[0], outlineColor, outlineThickness);
			DrawLine(screenPositions[0], screenPositions[1], outlineColor, outlineThickness);
			DrawLine(screenPositions[2], screenPositions[3], outlineColor, outlineThickness);
			DrawLine(screenPositions[3], screenPositions[4], outlineColor, outlineThickness);
			DrawLine(screenPositions[5], screenPositions[6], outlineColor, outlineThickness);
			DrawLine(screenPositions[6], screenPositions[7], outlineColor, outlineThickness);
			DrawLine(screenPositions[1], screenPositions[8], outlineColor, outlineThickness);
			DrawLine(screenPositions[8], screenPositions[9], outlineColor, outlineThickness);
			DrawLine(screenPositions[9], screenPositions[10], outlineColor, outlineThickness);
			DrawLine(screenPositions[10], screenPositions[11], outlineColor, outlineThickness);

			if (Esp::rfeet) {
				DrawLine(screenPositions[11], screenPositions[12], outlineColor, outlineThickness);
			}

			DrawLine(screenPositions[8], screenPositions[13], outlineColor, outlineThickness);
			DrawLine(screenPositions[13], screenPositions[14], outlineColor, outlineThickness);
			DrawLine(screenPositions[14], screenPositions[15], outlineColor, outlineThickness);

			if (Esp::rfeet) {
				DrawLine(screenPositions[15], screenPositions[16], outlineColor, outlineThickness);
			}
		}

		DrawLine(screenPositions[2], screenPositions[0], lineColor, lineThickness);
		DrawLine(screenPositions[5], screenPositions[0], lineColor, lineThickness);
		DrawLine(screenPositions[0], screenPositions[1], lineColor, lineThickness);
		DrawLine(screenPositions[2], screenPositions[3], lineColor, lineThickness);
		DrawLine(screenPositions[3], screenPositions[4], lineColor, lineThickness);
		DrawLine(screenPositions[5], screenPositions[6], lineColor, lineThickness);
		DrawLine(screenPositions[6], screenPositions[7], lineColor, lineThickness);
		DrawLine(screenPositions[1], screenPositions[8], lineColor, lineThickness);
		DrawLine(screenPositions[8], screenPositions[9], lineColor, lineThickness);
		DrawLine(screenPositions[9], screenPositions[10], lineColor, lineThickness);
		DrawLine(screenPositions[10], screenPositions[11], lineColor, lineThickness); 

		if (Esp::rfeet) {
			DrawLine(screenPositions[11], screenPositions[12], lineColor, lineThickness); 
		}

		DrawLine(screenPositions[8], screenPositions[13], lineColor, lineThickness);
		DrawLine(screenPositions[13], screenPositions[14], lineColor, lineThickness);
		DrawLine(screenPositions[14], screenPositions[15], lineColor, lineThickness);

		if (Esp::rfeet) {
			DrawLine(screenPositions[15], screenPositions[16], lineColor, lineThickness);
		}

		if (Esp::rjointEsp) {
			for (size_t i = 0; i < screenPositions.size(); ++i) {
				ImColor jointColor = Mesh->WasRecentlyRendered(0.06f)
					? ImColor(Esp::espcolor[0], Esp::espcolor[1], Esp::espcolor[2], Esp::espcolor[3])
					: ImColor(Esp::espcolor2[0], Esp::espcolor2[1], Esp::espcolor2[2], Esp::espcolor2[3]);

				DrawCircleFilled(screenPositions[i], jointRadius, jointColor);
			}
		}

		if (Esp::rHead) {
			float baseHeadSize = 1.0f;
			float distanceFactor = (distance / 100.0f);

			float dynamicHeadRadius = baseHeadSize / distanceFactor;
			if (dynamicHeadRadius < 1.0f) {
				dynamicHeadRadius = 1.0f;
			}

			Vector2 headPosition = screenPositions[17];

			Vector2 bottomOfCircle = Vector2(headPosition.x, headPosition.y + dynamicHeadRadius);

			if (Esp::rskelOutlines) {
				drawList->AddCircle(ImVec2(headPosition.x, headPosition.y), dynamicHeadRadius, outlineColor, 16, outlineThickness);
				DrawLine(screenPositions[18], bottomOfCircle, outlineColor, outlineThickness);
			}

			drawList->AddCircle(ImVec2(headPosition.x, headPosition.y), dynamicHeadRadius, lineColor, 16, lineThickness);
			DrawLine(screenPositions[18], bottomOfCircle, lineColor, lineThickness);
		}
	}



	void Draw3DBoxHead(Vector3 headPosition, float boxSize, ImColor boxColor, ImColor outlineColor, float lineThickness, bool drawOutline) {
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		float halfBoxSize = boxSize / 2.0f;

		Vector3 boxCorners[8] = {
			headPosition + Vector3(-halfBoxSize, halfBoxSize, -halfBoxSize),
			headPosition + Vector3(halfBoxSize, halfBoxSize, -halfBoxSize),
			headPosition + Vector3(-halfBoxSize, -halfBoxSize, -halfBoxSize),
			headPosition + Vector3(halfBoxSize, -halfBoxSize, -halfBoxSize),

			headPosition + Vector3(-halfBoxSize, halfBoxSize, halfBoxSize),
			headPosition + Vector3(halfBoxSize, halfBoxSize, halfBoxSize),
			headPosition + Vector3(-halfBoxSize, -halfBoxSize, halfBoxSize),
			headPosition + Vector3(halfBoxSize, -halfBoxSize, halfBoxSize)
		};

		Vector2 screenCorners[8];
		for (int i = 0; i < 8; ++i) {
			screenCorners[i] = Cached::PlayerController->ProjectWorldLocationToScreen(boxCorners[i]);
		}

		auto DrawBoxEdge = [&](int i, int j, ImColor color) {
			drawList->AddLine(ImVec2(screenCorners[i].x, screenCorners[i].y), ImVec2(screenCorners[j].x, screenCorners[j].y), color, lineThickness);
			};

		auto DrawOutlineEdge = [&](int i, int j) {
			if (drawOutline) {
				drawList->AddLine(ImVec2(screenCorners[i].x, screenCorners[i].y), ImVec2(screenCorners[j].x, screenCorners[j].y), outlineColor, lineThickness + 2.0f);
			}
			};

		DrawOutlineEdge(0, 1); DrawBoxEdge(0, 1, boxColor);
		DrawOutlineEdge(1, 3); DrawBoxEdge(1, 3, boxColor);
		DrawOutlineEdge(3, 2); DrawBoxEdge(3, 2, boxColor);
		DrawOutlineEdge(2, 0); DrawBoxEdge(2, 0, boxColor);

		DrawOutlineEdge(4, 5); DrawBoxEdge(4, 5, boxColor);
		DrawOutlineEdge(5, 7); DrawBoxEdge(5, 7, boxColor);
		DrawOutlineEdge(7, 6); DrawBoxEdge(7, 6, boxColor);
		DrawOutlineEdge(6, 4); DrawBoxEdge(6, 4, boxColor);

		DrawOutlineEdge(0, 4); DrawBoxEdge(0, 4, boxColor);
		DrawOutlineEdge(1, 5); DrawBoxEdge(1, 5, boxColor);
		DrawOutlineEdge(2, 6); DrawBoxEdge(2, 6, boxColor);
		DrawOutlineEdge(3, 7); DrawBoxEdge(3, 7, boxColor);
	}


	void FullBox(int X, int Y, int W, int H, const ImColor color, int thickness) {
		ImU32 shadowColor = ImColor(0, 0, 0, 255);
		float shadowOffset = 1.0f;

		AddLine(Vector2{ (float)X, (float)Y }, Vector2{ (float)(X + W), (float)Y }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)(X + W), (float)Y }, Vector2{ (float)(X + W), (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)X, (float)(Y + H) }, Vector2{ (float)(X + W), (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
		AddLine(Vector2{ (float)X, (float)Y }, Vector2{ (float)X, (float)(Y + H) }, color, thickness, shadowColor, shadowOffset);
	}

	void DrawFill(int X, int Y, int W, int H, const ImColor color, int thickness) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(color));
	}
}

