LIB=libcommon
SRC=src/log.c         \
    src/secure_rw.c   \
    src/crc.c         \
    src/gpio.c

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
LDCONFIG=$(CROSS_COMPILE)ldconfig
STRIP=$(CROSS_COMPILE)strip
PKG_CONFIGS_CFLAGS:=$(shell $(SYSROOT)/usr/bin/pkg-config --cflags zlib)
PKG_CONFIGS_LDLAGS:=$(shell $(SYSROOT)/usr/bin/pkg-config --libs zlib)
STAGING=$(SYSROOT)/../staging/
ARFLAGS=rcs
INCLUDE=-I.                           \
        -Isrc                         \
        -Iinclude                     \
        -I$(STAGING)/usr/include

CFLAGS=$(PKG_CONFIGS_CFLAGS) -Wall -g -O0 -Wextra -fPIC -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
LDFLAGS=$(PKG_CONFIGS_CFLAGS) -shared
OBJECTS=$(SRC:.c=.o)

all:$(LIB)

$(LIB):$(OBJECTS)
	@echo "[ Build $(LIB) ]"
	@echo create $(LIB).a
	@$(AR) -qc $(LIB).a $(OBJECTS)
	@echo create $(LIB).so
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $(LIB).so

%.o:%.c
	@echo cc $< ...
	@$(CC) $(INCLUDE) $(CFLAGS) $< -c -o $@

.PHONY:clean

clean:
	@rm -f $(OBJECTS)
	@rm -f $(LIB).a
	@rm -f $(LIB).so

clean_examples:
	@cd examples && $(MAKE) clean

dist_clean:clean clean_examples
	@rm -f cross_toolchain.config

#
# Examples Build
#
ifdef CROSS_COMPILE
examples:$(LIB)
	@echo [ Cross Build examples ]
	@cd examples && $(MAKE) cross_build
else
examples:$(LIB)
	@echo [ Build examples ]
	@cd examples && $(MAKE) all
endif
