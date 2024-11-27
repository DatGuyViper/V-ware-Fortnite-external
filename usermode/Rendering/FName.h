#include <cstdint>
#include <string>
#include "../Driver/driver.h"
#include "../Game/Classes.h"


#define FNAMEPOOL_OFFSET 0x117284C0

class decryption_t {
public:
    static std::string get_fname(int key)
    {
        uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
        uint16_t NameOffset = (uint16_t)key;

        uint64_t NamePoolChunk = read<uint64_t>(va_text + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
        if (read<uint16_t>(NamePoolChunk) < 64)
        {
            auto a1 = read<DWORD>(NamePoolChunk + 2);
            return GetNameFromIndex(a1);
        }
        else
        {
            return GetNameFromIndex(key);
        }
    }

    static std::string GetNameFromIndex(int key)
    {
        uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
        uint16_t NameOffset = (uint16_t)key;
        uint64_t NamePoolChunk = read<uint64_t>(va_text + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset);
        uint16_t nameEntry = read<uint16_t>(NamePoolChunk);
        int nameLength = nameEntry >> 6;
        char buff[1024] = {};

        char* v3 = buff; // rdi
        int v5; // r8d
        __int64 result = nameLength; // rax
        __int64 v7 = 0; // rdx
        unsigned int v8; // r8d
        v5 = 26;
        if ((int)result)
        {
            handler::read_physical(reinterpret_cast<void*>(NamePoolChunk + 2), static_cast<uint8_t*>(static_cast<void*>(buff)), 2 * nameLength);
            do
            {
                v8 = v5 + 45297;
                *v3 = v8 + ~*v3;
                result = v8 << 8;
                v5 = result | (v8 >> 8);
                ++v3;
                --v7;
            } while (v7);
            buff[nameLength] = '\0';
            return std::string(buff);
        }
        return std::string("");
    }

}; decryption_t decryption;