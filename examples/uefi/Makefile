#
# This builds a simple "Hello, World!" UEFI
# application for X86_64 and Aarch64
# environments. It relies on Tiano Core
# (edk2) headers, which you must provide
# yourself, by checking-out Tiano
# (e.g. https://github.com/tianocore/edk2)
# and tweaking EDK2 below.
#
# EDK2 should point to a Tiano Core (edk2) tree.
# $(CC_blah) should be valid if you built these
# in the top TCC directory.
#
EDK2 ?= ../../../edk2
CC_x86_64 ?= ../../x86_64-uefi-tcc
CC_arm64 ?= ../../arm64-uefi-tcc

HELLO_X = x86_64 arm64

TARGETS = $(foreach X,$(HELLO_X),$X-hello.efi)

INCLUDES = -I $(EDK2)/MdePkg/Include/
INCLUDES_x86_64 = -I $(EDK2)/MdePkg/Include/X64
INCLUDES_arm64 = -I $(EDK2)/MdePkg/Include/AArch64

all: $(TARGETS)

%-hello.efi: hello.c
	$(CC_$*) $(INCLUDES) $(INCLUDES_$*) $^ -o $@

clean:
	rm -rf *~ *.o $(TARGETS)

.PHONY: clean all