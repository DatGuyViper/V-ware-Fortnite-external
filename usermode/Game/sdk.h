#pragma once
#pragma comment (lib, "d3d9.lib")

#include "../Imgui/imgui.h"
#include <emmintrin.h>
#include <immintrin.h>
#include <d3d9.h>
#include <corecrt_math.h>
#include <cstdint>
#include "../Driver/driver.h"

int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

enum class EFortRarity : uint8_t {
	EFortRarity__Common = 0,
	EFortRarity__Uncommon = 1,
	EFortRarity__Rare = 2,
	EFortRarity__Epic = 3,
	EFortRarity__Legendary = 4,
	EFortRarity__Mythic = 5,
	EFortRarity__Transcendent = 6,
	EFortRarity__Unattainable = 7,
	EFortRarity__NumRarityValues = 8,
	EFortRarity__EFortRarity_MAX = 9
};

struct TArray
{
	std::uintptr_t Array;
	std::uint32_t Count;
	std::uint32_t MaxCount;

	std::uintptr_t Get(std::uint32_t Index)
	{
		return read<std::uintptr_t>(Array + (Index * 0x8));
	}
};

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(double _x, double _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	double x;
	double y;
	double z;
};

template<class T>
class FArray
{
public:
	int Size() const
	{
		return Count;
	}

	bool Valid() const
	{
		if (Count > Max)
			return false;
		if (!Data)
			return false;
		return true;
	}

	uintptr_t Get() const
	{
		return Data;
	}

	T operator[](int i)
	{
		return read<T>(Data + i * sizeof(T));
	};
protected:
	uintptr_t Data;
	uint32_t Count;
	uint32_t Max;
};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	double x;
	double y;
	double z;

	inline double Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline bool isValid() const {
		return isfinite(x) && isfinite(y) && isfinite(z);
	}

	inline double Distance(Vector3 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double Length() {
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 operator+(const Vector3& other) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
	Vector3 operator-(const Vector3& other) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
	Vector3 operator*(float offset) const { return { this->x * offset, this->y * offset, this->z * offset }; }
	Vector3 operator/(float offset) const { return { this->x / offset, this->y / offset, this->z / offset }; }

	Vector3& operator*=(const double other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
	Vector3& operator/=(const double other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

	Vector3& operator=(const Vector3& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
	Vector3& operator+=(const Vector3& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	Vector3& operator-=(const Vector3& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	Vector3& operator*=(const Vector3& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }

	operator bool() { return bool(this->x || this->y || this->z); }
	friend bool operator==(const Vector3& a, const Vector3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
};

class FBoxSphereBounds
{
public:
	Vector3 Origin;
	Vector3 BoxExtent;
	double SphereRadius;
};

struct FQuat
{
	double x;
	double y;
	double z;
	double w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

class frotator {
public:
	frotator() : pitch(0), yaw(0), roll(0) { }
	frotator(double Pitch, double Yaw, double Roll) : pitch(Pitch), yaw(Yaw), roll(Roll) { }

	frotator operator + (const frotator& other) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
	frotator operator - (const frotator& other) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
	frotator operator * (double offset) const { return { this->pitch * offset, this->yaw * offset, this->roll * offset }; }
	frotator operator / (double offset) const { return { this->pitch / offset, this->yaw / offset, this->roll / offset }; }

	frotator& operator = (const double other) { this->pitch = other; this->yaw = other; this->roll = other; return *this; }
	frotator& operator *= (const double other) { this->pitch *= other; this->yaw *= other; this->roll *= other; return *this; }
	frotator& operator /= (const double other) { this->pitch /= other; this->yaw /= other; this->roll /= other; return *this; }

	frotator& operator = (const frotator& other) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
	frotator& operator += (const frotator& other) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
	frotator& operator -= (const frotator& other) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
	frotator& operator /= (const frotator& other) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

	operator bool() const { return this->pitch != 0 && this->yaw != 0 && this->roll != 0; }
	friend bool operator == (const frotator& a, const frotator& b) { return a.pitch == b.pitch && a.yaw == b.yaw && a.roll == b.roll; }
	friend bool operator != (const frotator& a, const frotator& b) { return !(a == b); }

	frotator get() const {
		return frotator(pitch, yaw, roll);
	}

	void set(double _Pitch, double _Yaw, double _Roll) {
		pitch = _Pitch;
		yaw = _Yaw;
		roll = _Roll;
	}

	frotator normalize() const {
		frotator result = get();

		if (std::isfinite(result.pitch) && std::isfinite(result.yaw) && std::isfinite(result.roll)) {
			result.pitch = std::clamp(result.pitch, -89.0, 89.0);
			result.yaw = std::clamp(result.yaw, -180.0, 180.0);
			result.roll = 0.0;
		}

		return result;
	}

	double length() const {
		return std::sqrt(pitch * pitch + yaw * yaw + roll * roll);
	}

	double dot(const frotator& V) const { return pitch * V.pitch + yaw * V.yaw + roll * V.roll; }

	double distance(const frotator& V) const {
		return std::sqrt(std::pow(V.pitch - this->pitch, 2.0) + std::pow(V.yaw - this->yaw, 2.0) + std::pow(V.roll - this->roll, 2.0));
	}

	double pitch;
	double yaw;
	double roll;
};