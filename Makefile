CC=g++
BN=CppAssetPacker#build name
CFLAGS=-O3 -Wall
INCLUDEPATH=-I ./src/include
#UNAME_S := $(shell uname -s)

ifndef $(OS)
	OS=Other
endif

SRC = $(wildcard ./src/*.cpp)
all:
	_build

_build:
	ifeq ($(OS), "Windows_NT")
		$(CC) $(CFLAGS) src/main.cpp -o build/$(BN).exe
	endif
	ifeq ($(UNAME_S), "Linux")
		$(CC) $(CFLAGS) src/main.cpp -o build/$(BN)
	endif
	ifeq ($(UNAME_S), "Darwin")
		$(CC) $(CFLAGS) src/main.cpp -o build/$(BN)
	endif

run:
	ifeq ($(OS), "Windows_NT")
		build/$(BN).exe
	endif
	ifeq ($(UNAME_S), "Linux")
		build/$(BN)
	endif
	ifeq ($(UNAME_S), "Darwin")
		build/$(BN)
	endif
