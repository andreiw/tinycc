#include <Uefi.h>

#if defined(__aarch64__)
#define ARCH 1
#elif defined(__x86_64__)
#define ARCH 2
#else
#define ARCH 0
#endif

CHAR16 *gArch[3] = {
  L"UNKNOWN",
  L"AA64",
  L"X64"
};

CHAR16 *gHello = L"Hello from a TinyCC compiled ";

EFI_STATUS EFIAPI
_start(EFI_HANDLE Handle,
       EFI_SYSTEM_TABLE *SystemTable)
{
  CHAR16 *Bye = L" UEFI binary!\n";
  SystemTable->ConOut->OutputString(SystemTable->ConOut, gHello);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, gArch[ARCH]);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, Bye);
  return EFI_SUCCESS;
}
