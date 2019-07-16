# powturbo  (c) Copyright 2013-2018
# nmake /f makefile.vs
# or
# nmake "AVX2=1" /f makefile.vs

.SUFFIXES: .c .obj .dllobj

CC = cl /nologo
LD = link /nologo
AR = lib /nologo
CFLAGS = /MD /O2 -I. /W0 
LDFLAGS = 
ARCH =

LIB_LIB = libic.lib
LIB_DLL = ic.dll
LIB_IMP = ic.lib

OBJS = bitpack.obj bitunpack.obj vp4c.obj vp4d.obj transpose.obj bitutil.obj fp.obj vsimple.obj vint.obj

!if "$(NSIMD)" == "1"
CFLAGS = $(CFLAGS) /DNSIMD
!else
OBJS = $(OBJS) transpose_sse.obj bitpack_sse.obj bitunpack_sse.obj vp4c_sse.obj vp4d_sse.obj
CFLAGS = $(CFLAGS) /D__SSE__ /D__SSE2__ /D__SSE3__ /D__SSSE3__ /D__SSE4_1__ /D__SSE4_2__ /DUSE_SSE
ARCH = /arch:SSE2
!if "$(AVX2)" == "1"
OBJS = $(OBJS) bitpack_avx2.obj bitunpack_avx2.obj transpose_avx2.obj vp4c_avx2.obj vp4d_avx2.obj 
CFLAGS = $(CFLAGS) /D__AVX2__ /DUSE_AVX2
ARCH = /arch:AVX2
!endif
!endif

!if "$(CODEC1)" == "1"
CFLAGS = $(CFLAGS) /DCODEC1
!endif

!IF "$(CODEC2)" == "1"
CFLAGS = $(CFLAGS) /DCODEC2
!endif

!IF "($(BLOSC)" == "1"
CFLAGS = $(CFLAGS) /DBLOSC
!endif

DLL_OBJS = $(OBJS:.obj=.dllobj)

all: $(LIB_LIB) icbench.exe 

#$(LIB_DLL) $(LIB_IMP) 

#------------
.c.obj:
	$(CC) -c /Fo$@ /O2 $(CFLAGS) $(ARCH) $**

.cc.obj:
	$(CC) -c /Fo$@ /O2 $(CFLAGS) $(ARCH) $**

.c.dllobj:
	$(CC) -c /Fo$@ /O2 $(CFLAGS) $(ARCH) /DLIB_DLL $**

$(LIB_LIB): $(OBJS)
	$(AR) $(ARFLAGS) -out:$@ $(OBJS)

$(LIB_DLL): $(DLL_OBJS)
	$(LD) $(LDFLAGS) -out:$@ -dll -implib:$(LIB_IMP) $(DLL_OBJS)

$(LIB_IMP): $(LIB_DLL)

icbench.exe: icbench.obj vs/getopt.obj plugins.obj eliasfano.obj vsimple.obj $(LIB_LIB)
	$(LD) $(LDFLAGS) -out:$@ $**

clean:
	-del *.dll *.exe *.exp *.obj *.dllobj *.lib *.manifest 2>nul
