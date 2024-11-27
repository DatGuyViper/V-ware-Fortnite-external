#include "../Game/sdk.h"
#include <string>
#include "../Game/Classes.h"



void AddLine(Vector2 start, Vector2 end, ImU32 color, float thickness)
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), color, thickness);
}

BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf_s(lpString, sizeof(lpString), TEXT("%d"), nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf_s(lpString, sizeof(lpString), TEXT("%f"), nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
	char szData[32];

	GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

	return (float)atof(szData);
}

void DrawFilledRect(int x, int y, int w, int h, ImU32 color, Vector3& top, const Vector3& bottom)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}


void FullBox(int X, int Y, int W, int H, const ImColor color, int thickness, bool fillBox, bool recentlyRendered, float lineFraction = 0.8f)
{
	float adjustedWidth = W * Esp::boxWidthMultiplier;

	float reducedWidth = adjustedWidth * lineFraction;
	float offsetX = (W - reducedWidth) / 2.0f;

	Vector2 topLeft{ (float)X + offsetX, (float)Y };
	Vector2 topRight{ (float)(X + offsetX + reducedWidth), (float)Y };
	Vector2 bottomRight{ (float)(X + offsetX + reducedWidth), (float)(Y + H) };
	Vector2 bottomLeft{ (float)X + offsetX, (float)(Y + H) };

	if (Esp::rboxOutlines) {
		ImColor blackColor = ImColor(0, 0, 0, 255);
		int outlineThickness = (thickness + 2) * Esp::boxThicknessMultiplier;

		AddLine(topLeft, topRight, blackColor, outlineThickness);
		AddLine(topRight, bottomRight, blackColor, outlineThickness);
		AddLine(bottomRight, bottomLeft, blackColor, outlineThickness);
		AddLine(bottomLeft, topLeft, blackColor, outlineThickness);
	}

	int adjustedThickness = thickness * Esp::boxThicknessMultiplier;

	AddLine(topLeft, topRight, color, adjustedThickness);
	AddLine(topRight, bottomRight, color, adjustedThickness);
	AddLine(bottomRight, bottomLeft, color, adjustedThickness);
	AddLine(bottomLeft, topLeft, color, adjustedThickness);

	ImU32 fillColor = recentlyRendered
		? ImGui::ColorConvertFloat4ToU32(ImVec4(0, 1, 0, 0.25f))
		: ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0, 0.25f));

	if (Esp::rFillBoxs) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2((float)X + offsetX, (float)Y),
			ImVec2((float)(X + offsetX + reducedWidth), (float)(Y + H)),
			fillColor, 0, 0);
	}
}


void CorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness, bool fillBox, bool recentlyRendered)
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	float adjustedWidth = W * Esp::boxWidthMultiplier;
	float lineW = adjustedWidth / 4.0f;
	float lineH = H / 4.0f;

	float offsetX = (W - adjustedWidth) / 2.0f;

	ImVec2 topLeft(X + offsetX, Y);
	ImVec2 topRight(X + offsetX + adjustedWidth, Y);
	ImVec2 bottomRight(X + offsetX + adjustedWidth, Y + H);
	ImVec2 bottomLeft(X + offsetX, Y + H);

	int adjustedThickness = thickness * Esp::boxThicknessMultiplier;

	if (Esp::rboxOutlines) {
		ImU32 blackColor = IM_COL32(0, 0, 0, 255);

		int outlineThickness = adjustedThickness + 2;

		drawList->AddLine(topLeft, ImVec2(topLeft.x + lineW, topLeft.y), blackColor, outlineThickness);
		drawList->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + lineH), blackColor, outlineThickness);

		drawList->AddLine(topRight, ImVec2(topRight.x - lineW, topRight.y), blackColor, outlineThickness);
		drawList->AddLine(topRight, ImVec2(topRight.x, topRight.y + lineH), blackColor, outlineThickness);

		drawList->AddLine(bottomLeft, ImVec2(bottomLeft.x + lineW, bottomLeft.y), blackColor, outlineThickness);
		drawList->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - lineH), blackColor, outlineThickness);

		drawList->AddLine(bottomRight, ImVec2(bottomRight.x - lineW, bottomRight.y), blackColor, outlineThickness);
		drawList->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - lineH), blackColor, outlineThickness);
	}

	drawList->AddLine(topLeft, ImVec2(topLeft.x + lineW, topLeft.y), color, adjustedThickness);
	drawList->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + lineH), color, adjustedThickness);

	drawList->AddLine(topRight, ImVec2(topRight.x - lineW, topRight.y), color, adjustedThickness);
	drawList->AddLine(topRight, ImVec2(topRight.x, topRight.y + lineH), color, adjustedThickness);

	drawList->AddLine(bottomLeft, ImVec2(bottomLeft.x + lineW, bottomLeft.y), color, adjustedThickness);
	drawList->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - lineH), color, adjustedThickness);

	drawList->AddLine(bottomRight, ImVec2(bottomRight.x - lineW, bottomRight.y), color, adjustedThickness);
	drawList->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - lineH), color, adjustedThickness);

	ImU32 fillColor = recentlyRendered
		? ImGui::ColorConvertFloat4ToU32(ImVec4(0, 1, 0, 0.25f))
		: ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0, 0.25f));

	if (Esp::rFillBoxs) {
		drawList->AddRectFilled(ImVec2((float)X + offsetX, (float)Y),
			ImVec2((float)(X + offsetX + adjustedWidth), (float)(Y + H)),
			fillColor, 0, 0);
	}
}



void draw3DBox(const Vector3& top, const Vector3& bottom, ImVec4 boxColor, bool fillBox, bool recentlyRendered) {
	Vector3 bottom1 = Cached::PlayerController->ProjectWorldToScreen(Vector3(bottom.x + 40, bottom.y - 40, bottom.z));
	Vector3 bottom2 = Cached::PlayerController->ProjectWorldToScreen(Vector3(bottom.x - 40, bottom.y - 40, bottom.z));
	Vector3 bottom3 = Cached::PlayerController->ProjectWorldToScreen(Vector3(bottom.x - 40, bottom.y + 40, bottom.z));
	Vector3 bottom4 = Cached::PlayerController->ProjectWorldToScreen(Vector3(bottom.x + 40, bottom.y + 40, bottom.z));

	Vector3 top1 = Cached::PlayerController->ProjectWorldToScreen(Vector3(top.x + 40, top.y - 40, top.z + 15));
	Vector3 top2 = Cached::PlayerController->ProjectWorldToScreen(Vector3(top.x - 40, top.y - 40, top.z + 15));
	Vector3 top3 = Cached::PlayerController->ProjectWorldToScreen(Vector3(top.x - 40, top.y + 40, top.z + 15));
	Vector3 top4 = Cached::PlayerController->ProjectWorldToScreen(Vector3(top.x + 40, top.y + 40, top.z + 15));

	ImU32 boxCol = ImGui::ColorConvertFloat4ToU32(boxColor);

	ImU32 fillColor = recentlyRendered
		? ImGui::ColorConvertFloat4ToU32(ImVec4(0, 1, 0, 0.25f))
		: ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0, 0.25f));

	if (Esp::rFillBoxs) {
		ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y),
			ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), fillColor);
		ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y),
			ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), fillColor);

		ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y),
			ImVec2(top2.x, top2.y), ImVec2(bottom2.x, bottom2.y), fillColor);
		ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y),
			ImVec2(top3.x, top3.y), ImVec2(bottom3.x, bottom3.y), fillColor);
		ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y),
			ImVec2(top4.x, top4.y), ImVec2(bottom4.x, bottom4.y), fillColor);
		ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y),
			ImVec2(top1.x, top1.y), ImVec2(bottom1.x, bottom1.y), fillColor);
	}

	if (Esp::rboxOutlines) {
		ImU32 blackColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1.0f));
		float outlineThickness = 4.0f;

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), blackColor, outlineThickness);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), blackColor, outlineThickness);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), blackColor, outlineThickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), blackColor, outlineThickness);
	}

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), boxCol, 2.0f);

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), boxCol, 2.0f);

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), boxCol, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), boxCol, 2.0f);
}
