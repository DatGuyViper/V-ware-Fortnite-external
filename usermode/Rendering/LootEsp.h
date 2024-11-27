#include "../Game/Classes.h"
#include "../Rendering/FName.h"

namespace loot {
    inline std::wstring MBytesToWString(const char* lpcszString)
    {
        int len = strlen(lpcszString);
        int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
        wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
        memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
        ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
        std::wstring wString = (wchar_t*)pUnicode;
        delete[] pUnicode;
        return wString;
    }

    inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
    {
        char* pElementText;
        int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
        pElementText = new char[iTextLen + 1];
        memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
        ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
        std::string strReturn(pElementText);
        delete[] pElementText;
        return strReturn;
    }

    inline void DrawString3(float fontSize, int x, int y, ImVec4 color, bool bCenter, bool stroke, const char* pText, ...)
    {
        ImU32 converted_color = ImGui::ColorConvertFloat4ToU32(color);
        va_list va_alist;
        char buf[1024] = { 0 };
        va_start(va_alist, pText);
        _vsnprintf_s(buf, sizeof(buf), pText, va_alist);
        va_end(va_alist);
        std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
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

    inline void DrawString2(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
    {

        va_list va_alist;
        char buf[1024] = { 0 };
        va_start(va_alist, pText);
        _vsnprintf_s(buf, sizeof(buf), pText, va_alist);
        va_end(va_alist);
        std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
        if (bCenter)
        {
            ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
            x = x - textSize.x / 4;
            y = y - textSize.y;
        }
        if (stroke)
        {
            /*ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());*/
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        }
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
    }

    class item {
    public:
        uintptr_t
            Actor;

        std::string
            Name;
        bool
            isVehicle,
            isChest,
            isPickup,
            isAmmoBox;
        float
            distance;
    };

    class world_t
    {
    public:
        bool enable = false;
        bool chests = false;
        bool pickups = false;
        bool uncommon = false;
        bool common = false;
        bool epic = false;
        bool rare = false;
        bool legendary = false;
        bool mythic = false;

        int loot_distance = 35;
        int cache_update_speed = 0;
    }; world_t world;

    std::vector<item> item_pawns;

    static auto root_c(uintptr_t actor) {
        return read<uintptr_t>(actor + Offsets::RootComponent);
    }

    static auto get_location(uintptr_t actor) {
        return read<Vector3>(root_c(actor) + Offsets::RelativeLocation);
    }

    void cache_levels()
    {
        for (;;)
        {
            if (!world.pickups or !world.chests) continue;
            if (!Cached::World) continue;

            std::vector<item> mrxd;
            uintptr_t item_levels = read<uintptr_t>(Cached::World->GetAddress() + Offsets::levels); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=UWorld&member=Levels

            for (int i = 0; i < read<DWORD>(Cached::World->GetAddress() + (Offsets::levels + sizeof(PVOID))); ++i)
            {
                uintptr_t item_level = read<uintptr_t>(item_levels + (i * sizeof(uintptr_t)));;

                for (int i = 0; i < read<DWORD>(item_level + (Offsets::AActors + sizeof(PVOID))); ++i) {

                    uintptr_t item_pawns = read<uintptr_t>(item_level + Offsets::AActors);

                    uintptr_t current_item_pawn = read<uintptr_t>(item_pawns + (i * sizeof(uintptr_t)));

                    Vector3 item_position = get_location(current_item_pawn);

                    float item_dist = GetCameraInfo().location.Distance(item_position) / 100;

                    int item_index = read<int>(current_item_pawn + 0x18);

                    auto current_item_pawn_name = decryption.get_fname(item_index);

                    if (is_valid(current_item_pawn))
                    {
                        if (world.pickups or world.chests)
                        {
                            item Item{ };
                            Item.Actor = current_item_pawn;
                            Item.Name = current_item_pawn_name;
                            Item.isPickup = true;
                            Item.distance = item_dist;

                            mrxd.push_back(Item);
                        }
                    }
                }
            }

            item_pawns.clear();
            item_pawns = mrxd;
            std::this_thread::sleep_for(std::chrono::milliseconds(0));
        }
    }

    enum class EFortRarity : uint8_t
    {
        EFortRarity__Common = 0,
        EFortRarity__Uncommon = 1,
        EFortRarity__Rare = 2,
        EFortRarity__Epic = 3,
        EFortRarity__Legendary = 4,
        EFortRarity__Mythic = 5,
        EFortRarity__Transcendent = 6,
        EFortRarity__Unattainable = 7,
        EFortRarity__NumRarityValues = 8,
    };

    inline ImVec4 get_loot_color(EFortRarity tier) {
        if (tier == EFortRarity::EFortRarity__Common)
            return ImVec4(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 1.f);
        else if (tier == EFortRarity::EFortRarity__Uncommon)
            return ImVec4(58 / 255.0f, 121 / 255.0f, 19 / 255.0f, 1.f);
        else if (tier == EFortRarity::EFortRarity__Rare)
            return ImVec4(18 / 255.0f, 88 / 255.0f, 162 / 255.0f, 1.f);
        else if (tier == EFortRarity::EFortRarity__Epic)
            return ImVec4(189 / 255.0f, 63 / 255.0f, 250 / 255.0f, 1.f);
        else if (tier == EFortRarity::EFortRarity__Legendary)
            return ImVec4(255 / 255.0f, 118 / 255.0f, 5 / 255.0f, 1.f);
        else if (tier == EFortRarity::EFortRarity__Mythic)
            return ImVec4(220 / 255.0f, 160 / 255.0f, 30 / 255.0f, 1.f);
        else if (tier == EFortRarity::EFortRarity__Transcendent)
            return ImVec4(0 / 255.0f, 225 / 255.0f, 252 / 255.0f, 1.f);

        return ImVec4(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 1.f);
    }

    void level_drawing()
    {
        if (world.enable)
        {
            for (auto entity : item_pawns)
            {
                auto definition = read<uint64_t>(entity.Actor + 0x348 + 0x18);

                if (is_valid(definition))
                {
                    EFortRarity tier = read<EFortRarity>(definition + Offsets::tier);

                    ImColor Color, RGBAColor;
                    Vector3 Location = get_location(entity.Actor);

                    Vector2 ChestPosition = APlayerController::ProjectWorldLocationToScreen(Location);

                    if (entity.distance <= world.loot_distance)
                    {
                        if (IsInScreen(ChestPosition))
                        {
                            uint64_t ftext_ptr = read<uint64_t>(definition + Offsets::item_name);

                            if (is_valid(ftext_ptr))
                            {
                                uint64_t ftext_data = read<uint64_t>(ftext_ptr + 0x28);
                                int ftext_length = read<int>(ftext_ptr + 0x30);
                                if (ftext_length > 0 && ftext_length < 50) {
                                    wchar_t* ftext_buf = new wchar_t[ftext_length];
                                    read1(ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));
                                    std::wstring wstr_buf(ftext_buf);
                                    std::string WeaponName = std::string(wstr_buf.begin(), wstr_buf.end());
                                    delete[] ftext_buf;

                                    std::string wtf2 = WeaponName + " [" + std::to_string((int)entity.distance) + ("m]");

                                    ImVec2 text_size = ImGui::CalcTextSize(wtf2.c_str());

                                    if (tier == EFortRarity::EFortRarity__Uncommon and world.uncommon)
                                    {
                                        loot::DrawString3(25, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
                                    }
                                    else if (tier == EFortRarity::EFortRarity__Common and world.common)
                                    {
                                        loot::DrawString3(25, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
                                    }
                                    else if (tier == EFortRarity::EFortRarity__Rare and world.rare)
                                    {
                                        loot::DrawString3(25, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
                                    }
                                    else if (tier == EFortRarity::EFortRarity__Epic and world.epic)
                                    {
                                        loot::DrawString3(25, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
                                    }
                                    else if (tier == EFortRarity::EFortRarity__Legendary and world.legendary)
                                    {
                                        loot::DrawString3(25, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
                                    }
                                    else if (tier == EFortRarity::EFortRarity__Mythic and world.mythic)
                                    {
                                        loot::DrawString3(25, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
                                    }
                                }
                            }
                        }
                    }
                }

                if (world.chests && strstr(entity.Name.c_str(), ("Tiered_Chest")))
                {
                    if (entity.distance <= world.loot_distance)
                    {
                        Vector3 Location = get_location(entity.Actor);
                        Vector2 Screen = APlayerController::ProjectWorldLocationToScreen(Location);

                        if (IsInScreen(Screen))
                        {
                            std::string BuiltString = "Chest [" + std::to_string((int)entity.distance) + "]";
                            ImVec2 text_size = ImGui::CalcTextSize(BuiltString.c_str());

                            DrawString2(13, Screen.x - (text_size.x / 2), Screen.y - 18, ImColor(255, 255, 0), false, false, BuiltString.c_str());
                        }
                    }
                }
            }
        }
    }
}