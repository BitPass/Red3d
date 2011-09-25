TARGET = Red3d

OBJS = \
valloc/valloc.o \
intrafont/libccc.o \
intrafont/intrafont.o \
Red3dIO.o \
Red3dGuInit.o \
Red3dVertex.o \
Red3dModel.o \
Red3dTexture.o \
Red3dCollision.o \
Red3dKeys.o

TARGET_LIB = LibRed3d.a

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpsprtc -lpspgum -lpspgu -lm

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

install:
	cp -Rp $(TARGET_LIB) $(PSPSDK)/lib/$(TARGET_LIB)
	cp -Rp Red3d.h $(PSPSDK)/include/Red3d.h
	cp -Rp utils/png2asset.exe $(PSPDEV)/bin/png2asset.exe
	cp -Rp utils/libpng13.dll $(PSPDEV)/bin/libpng13.dll
	cp -Rp utils/zlib1.dll $(PSPDEV)/bin/zlib1.dll
	cp -Rp utils/obj2asset.exe $(PSPDEV)/bin/obj2asset.exe

uninstall:
	rm -f $(PSPSDK)/lib/$(TARGET_LIB)
	rm -f $(PSPSDK)/include/Red3d.h
	rm -f $(PSPDEV)/bin/png2asset.exe
	rm -f $(PSPDEV)/bin/libpng13.dll
	rm -f $(PSPDEV)/bin/zlib1.dll
	rm -f $(PSPDEV)/bin/obj2asset.exe
