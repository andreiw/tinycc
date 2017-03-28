andreiw's tinycc changes
========================

This tree adds:
- some bare minimum OSX support **(merged)**.
- support for generating ARM64 PE32+ images **(not yet merged)**.
- support for generating X64, ARM64, IA32 (untested) and ARM (untested) UEFI images **(not yet merged)**.
- a "Hello, World!" UEFI example in examples/uefi **(not yet merged)**.
- a UEFI-targetting compiler (x86_64-uefi-tcc and arm64-uefi-tcc), that can be built (Tiano EDK2) to be hosted on UEFI **(not yet merged)**.

OSX support
-----------

Today this includes some basic build support (CONFIG_OSX)
in ./configure and ./Makefile. It also makes
the '-run' mode function, allowing tcc to
open up libc.dylib.

Usage:

    $ ./configure
    $ make
    $ ./tcc -B. -I./include -I. -I.. -D_ANSI_SOURCE -run examples/ex1.c
    Hello World

ARM64 PE32+ images
------------------

The targets are arm64-win32-tcc and arm64-uefi-tcc. libtcc1 is not built, so this
is only useful for standalone code, such as UEFI images.

UEFI images
-----------

This example requires a Tiano Core source tree:

    #include <Uefi.h>

    CHAR16 *gHello = L"Hello from a TinyCC compiled UEFI binary!\r\n";

    EFI_STATUS EFIAPI
    _start(EFI_HANDLE Handle,
           EFI_SYSTEM_TABLE *SystemTable)
    {
      SystemTable->ConOut->OutputString(SystemTable->ConOut, gHello);
      return EFI_SUCCESS;
    }

Building:

    $ x86_64-win32-tcc -I ../edk2/MdePkg/Include/ -I ../edk2/MdePkg/Include/X64/  efitest.c  -Wl,-subsystem=efiapp -nostdlib -o efitest.x64.efi
    $ arm64-win32-tcc -I ../edk2/MdePkg/Include/ -I ../edk2/MdePkg/Include/AArch64/  efitest.c  -Wl,-subsystem=efiapp -nostdlib -o efitest.aa64.efi

Or, with the UEFI-targetting compiler, which is is a subset of the win32 compiler.

    $ x86_64-uefi-tcc -I ../edk2/MdePkg/Include/ -I ../edk2/MdePkg/Include/X64/ efitest.c -o efitest.x64.efi
    $ arm64-uefi-tcc -I ../edk2/MdePkg/Include/ -I ../edk2/MdePkg/Include/AArch64/ efitest.c -o efitest.aa64.efi

Running (on the appropriate architecture, of course!):

    fs0:\> efitest.aa64.efi
    Hello from a TinyCC compiled UEFI binary!
    fs0:\>

A similar example is already present in examples/uefi. To build:

    $ make -C examples/uefi

TCC in UEFI
-----------

This has only been validated with X64 and AArch64. To build, you need
an EDK2 tree. Use the TCCInUEFI.inf build file. This will get you
a compiler equivalent to x86_64-uefi-tcc/arm64-uefi-tcc.

Also see https://github.com/andreiw/UefiToolsPkg, which might
be an easier way of building my private TinyCC tree for UEFI.

    fs16:> tcc hello.c
    fs16:> hello.efi
    Hello, World!

Note: too lazy to copy headers, so far only tested building pre-processed
files (-E is your friend).
