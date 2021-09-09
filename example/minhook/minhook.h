#pragma once

#if !(defined _M_IX86) && !(defined _M_X64) && !(defined __i386__) && !(defined __x86_64__)
    #error MinHook supports only x86 and x64 systems.
#endif

typedef enum MH_STATUS
{
    MH_UNKNOWN = -1,

    MH_OK = 0,

    MH_ERROR_ALREADY_INITIALIZED,

    MH_ERROR_NOT_INITIALIZED,

    MH_ERROR_ALREADY_CREATED,

    MH_ERROR_NOT_CREATED,

    MH_ERROR_ENABLED,

    MH_ERROR_DISABLED,

    MH_ERROR_NOT_EXECUTABLE,

    MH_ERROR_UNSUPPORTED_FUNCTION,

    MH_ERROR_MEMORY_ALLOC,

    MH_ERROR_MEMORY_PROTECT,

    MH_ERROR_MODULE_NOT_FOUND,

    MH_ERROR_FUNCTION_NOT_FOUND
}
MH_STATUS;

#define MH_ALL_HOOKS NULL

#ifdef __cplusplus
extern "C"
{
#endif
    MH_STATUS __stdcall MH_Initialize(void);

    MH_STATUS __stdcall MH_Uninitialize(void);

    MH_STATUS __stdcall MH_CreateHook(void* pTarget, void* pDetour, void* *ppOriginal);

    MH_STATUS __stdcall MH_CreateHookApi(const wchar_t* pszModule, const char* pszProcName, void* pDetour, void**ppOriginal);

    MH_STATUS __stdcall MH_CreateHookApiEx(const wchar_t* pszModule, const char* pszProcName, void* pDetour, void* *ppOriginal, void* *ppTarget);

    MH_STATUS __stdcall MH_RemoveHook(void* pTarget);

    MH_STATUS __stdcall MH_EnableHook(void* pTarget);

    MH_STATUS __stdcall MH_DisableHook(void* pTarget);

    MH_STATUS __stdcall MH_QueueEnableHook(void* pTarget);

    MH_STATUS __stdcall MH_QueueDisableHook(void* pTarget);

    MH_STATUS __stdcall MH_ApplyQueued(void);

    const char * __stdcall MH_StatusToString(MH_STATUS status);

#ifdef __cplusplus
}
#endif

