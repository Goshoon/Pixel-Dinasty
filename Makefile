# ===MAKEFILE CONFS===
# DEBUG MAKEFILE?
# Q := # ON
Q := @# OFF
# DEFAULT TASK
.DEFAULT_GOAL := help
# MAKES SURE THESE ALWAYS GETS RUN
.PHONY: help build run clean linux windows x64

# ===MULTIPLATFORM SETUP===
PLATFORM ?= linux# Default platform
ARCH ?= x64# Default architecture

# ===PROGRAM SETUP===
NAME := LaberintoSDL

OUT_PATH := Bin
OBJ_PATH := Obj
RES_PATH := Resources

MODULES = Source
SOURCES:= $(shell find $(MODULES) -name "*.cpp")
OBJS = $(SOURCES:%.cpp=$(OBJ_PATH)/$(PLATFORM)/$(ARCH)/%.o)
DEPS = $(OBJS:.o=.d)
-include $(DEPS)

INCLUDE := $(shell find Headers -type d)
INCLUDE := $(INCLUDE:%=-I%)
LIBS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
FLAGS := -std=c++17 \
	   -Wall \
	   -Wextra \
	   -Wconversion \
	   -Wpedantic \
	   -Wmaybe-uninitialized \
	   -D_NAME=\"$(NAME)\" \
	   -D_DEBUG
	   # -D_RELEASE


setup:
	$Qecho "Making for $(PLATFORM)-$(ARCH)"
	$Qmkdir -p "${OBJ_PATH}/${PLATFORM}/${ARCH}"

	$Qmkdir -p "${OBJ_PATH}/${PLATFORM}/${ARCH}"

	$Qfor module in $(MODULES); do \
		find $$module -type d | while read subfolder; do \
			mkdir -p ${OBJ_PATH}/${PLATFORM}/${ARCH}/$$subfolder; \
		done; \
	done

	$Qmkdir -p "${OUT_PATH}/${PLATFORM}/${ARCH}"

# Platform/Architecture specific setups
linux: $(ARCH)
	$Qecho "Setting up $@ environment..."
	$(eval CC:= g++)
	$Qecho Set compiler as $(CC)...

DLLS_PATH := /usr/x86_64-w64-mingw32/bin
DLLS := libgcc_s_seh-1 libstdc++-6 libwinpthread-1
DLLS := $(DLLS:%=%.dll)
windows: $(ARCH) $(DLLS)
	$Qecho "Setting up $@ environment..."
	$(eval CC:= x86_64-w64-mingw32-g++)
	$Qecho Set compiler as $(CC)...
%.dll:
	$Qecho "Copying DLL $@.."
	$Qcp "$(DLLS_PATH)/$@" "${OUT_PATH}/${PLATFORM}/${ARCH}"


build: setup $(PLATFORM) $(OBJS)
	$Qecho Assembling $(NAME)...
	$Q${CC} ${FLAGS} $(OBJS) ${LIBS} -o ${OUT_PATH}/${PLATFORM}/${ARCH}/${NAME}
	$Qecho Copying resources...
	$Qcp -r ${RES_PATH} ${OUT_PATH}/${PLATFORM}/${ARCH}
	$Qecho Done!

$(OBJ_PATH)/$(PLATFORM)/$(ARCH)/%.o: %.cpp
	$Qecho Making $<...
	$Q${CC} -c $< ${FLAGS} ${INCLUDE} -o $@ 
	$Q${CC} -MM -MF $(@:.o=.d) -MT $@ $< ${FLAGS} ${INCLUDE}

clean:
	$Qrm -r ${OBJ_PATH}/*

run: 
	$Q${OUT_PATH}/${PLATFORM}/${ARCH}/${NAME} 2

help:
	$Qecho "Usage: make [TARGET] [PLATFORM=<platform>] [ARCH=<architecture>]"
	$Qecho "Targets:"
	$Qecho "	help	- Shows this message."
	$Qecho "	build	- Builts the project. Default PLATFORM=linux, ARCH=x64."
	$Qecho "		Example: make build PLATFORM=windows ARCH=x64"
	$Qecho "	run	- Run the built binary. Default PLATFORM=linux, ARCH=x64."
	$Qecho "		Example: make run PLATFORM=windows"
	$Qecho "	clean	- Cleans all the object files."
	$Qecho "	all     - Builts the project for all supported platforms and architectures."

SUPPORTED_PLATFORMS = linux windows
SUPPORTED_ARCHS = x64
all:
	for platform in $(SUPPORTED_PLATFORMS); do \
        for arch in $(SUPPORTED_ARCHS); do \
            $(MAKE) build PLATFORM=$$platform ARCH=$$arch; \
        done; \
    done
