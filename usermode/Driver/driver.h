#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <vector>

uintptr_t virtualaddy;
uintptr_t cr3;

#define RDWCode CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4756, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define SHACode CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3626, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FGACode CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1347, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define CR3Code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1348, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define SecurityCode 0x457c1d6

typedef struct _RD {
    INT32 security;
    INT32 process_id;
    ULONGLONG address;
    ULONGLONG buffer;
    ULONGLONG size;
    BOOLEAN write;
} RD, * RDW;

typedef struct _SH {
    INT32 security;
    INT32 process_id;
    ULONGLONG* address;
} SH, * SHA;

typedef struct _FA {
    INT32 security;
    ULONGLONG* address;
} FA, * FGA;

typedef struct _MOUSE_MOVE_REQUEST {
    LONG dx;
    LONG dy;
} MOUSE_MOVE_REQUEST, * PMOUSE_MOVE_REQUEST;

typedef struct _MEMORY_OPERATION_DATA {
    uint32_t pid;
    ULONGLONG* cr3;
} MEMORY_OPERATION_DATA, * PMEMORY_OPERATION_DATA;

using mouse_invoke = struct _mouse_invoke {
    uint32_t pid;
    USHORT IndicatorFlags;
    LONG MovementX;
    LONG MovementY;
    ULONG PacketsConsumed;
};
using pmouse_invoke = mouse_invoke*;

namespace handler {
    HANDLE driver_handle;
    INT32 process_id;

    bool find_driver() {
        driver_handle = CreateFileW((L"\\\\.\\{rdbss}"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

        if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
            return false;

        return true;
    }

    void read_physical(PVOID address, PVOID buffer, DWORD size) {
        _RD arguments = { 0 };

        arguments.security = SecurityCode;
        arguments.address = (ULONGLONG)address;
        arguments.buffer = (ULONGLONG)buffer;
        arguments.size = size;
        arguments.process_id = process_id;
        arguments.write = FALSE;

        DeviceIoControl(driver_handle, RDWCode, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
    }

    void write_physical(PVOID address, PVOID buffer, DWORD size) {
        _RD arguments = { 0 };

        arguments.security = SecurityCode;
        arguments.address = (ULONGLONG)address;
        arguments.buffer = (ULONGLONG)buffer;
        arguments.size = size;
        arguments.process_id = process_id;
        arguments.write = TRUE;

        DeviceIoControl(driver_handle, RDWCode, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
    }


    uintptr_t fetch_cr3() {
        uintptr_t cr3 = NULL;
        _MEMORY_OPERATION_DATA arguments = { 0 };

        arguments.pid = process_id;
        arguments.cr3 = (ULONGLONG*)&cr3;

        DeviceIoControl(driver_handle, CR3Code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

        return cr3;
    }

    uintptr_t find_image() {
        uintptr_t image_address = { NULL };
        _SH arguments = { NULL };

        arguments.security = SecurityCode;
        arguments.process_id = process_id;
        arguments.address = (ULONGLONG*)&image_address;

        DeviceIoControl(driver_handle, SHACode, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

        return image_address;
    }

    uintptr_t get_guarded_region() {
        uintptr_t guarded_region_address = { NULL };
        _FA arguments = { NULL };

        arguments.security = SecurityCode;
        arguments.address = (ULONGLONG*)&guarded_region_address;

        DeviceIoControl(driver_handle, FGACode, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

        return guarded_region_address;
    }

    INT32 find_process(LPCTSTR process_name) {
        PROCESSENTRY32 pt;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        pt.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hsnap, &pt)) {
            do {
                if (!lstrcmpi(pt.szExeFile, process_name)) {
                    CloseHandle(hsnap);
                    process_id = pt.th32ProcessID;
                    return pt.th32ProcessID;
                }
            } while (Process32Next(hsnap, &pt));
        }
        CloseHandle(hsnap);

        return { NULL };
    }
}

bool is_valid(const uint64_t address)
{
    if (address == 0 || address == 0xCCCCCCCCCCCCCCCC || address == 0xFFFFFFFFFFFFFFFF)
        return false;

    if (address <= 0x400000 || address > 0x7FFFFFFFFFFFFFFF)
        return false;

    return true;
}

template <typename T>
T read(uint64_t address) {
    T buffer{ };
    if (is_valid(address))
        handler::read_physical((PVOID)address, &buffer, sizeof(T));
    return buffer;
}

template <typename T>
void write(uint64_t address, T buffer) {
    if (is_valid(address))
        handler::write_physical((PVOID)address, &buffer, sizeof(T));
}

template <typename T>
std::vector<T> batch_read(const std::vector<uint64_t>& addresses) {
    size_t num_addresses = addresses.size();
    std::vector<T> results(num_addresses);
    std::vector<uint8_t> buffer(num_addresses * sizeof(T));

    for (size_t i = 0; i < num_addresses; ++i) {
        if (!is_valid(addresses[i])) {
            continue;
        }
        handler::read_physical(reinterpret_cast<PVOID>(addresses[i]), buffer.data() + i * sizeof(T), sizeof(T));
    }
    for (size_t i = 0; i < num_addresses; ++i) {
        results[i] = *reinterpret_cast<T*>(buffer.data() + i * sizeof(T));
    }
    return results;
}

inline bool read1(const std::uintptr_t address, void* buffer, const std::size_t size)
{
    if (buffer == nullptr || size == 0) {
        return false;
    }
    handler::read_physical(reinterpret_cast<PVOID>(address), buffer, static_cast<DWORD>(size));
}

struct BatchReadEntry {
    uint64_t address;
    PVOID buffer;
    size_t size;
};

std::vector<BatchReadEntry> readBatchQueue;

static void AddToBatchRead(uint64_t Address, PVOID Buffer, size_t Size) {
    BatchReadEntry entry;
    entry.address = Address;
    entry.buffer = Buffer;
    entry.size = Size;

    readBatchQueue.push_back(entry);
}

static void ReadBatch() {
    for (const auto& entry : readBatchQueue) {
        if (entry.buffer && entry.size > 0) {
            handler::read_physical((PVOID)entry.address, entry.buffer, static_cast<DWORD>(entry.size));
        }
    }

    readBatchQueue.clear();
}
