BIN=example_secure_rw.bin

SRC=main.c

LIBCOMMON=../../libcommon.a

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
LDCONFIG=$(CROSS_COMPILE)ldconfig
STRIP=$(CROSS_COMPILE)strip
STAGING=$(SYSROOT)/../staging/
ARFLAGS=rcs
INCLUDE=-I.                            \
        -I../../include/               \
        -I$(STAGING)/usr/include

CFLAGS= -Wall -g -O0 -Wextra -fPIC -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
LDFLAGS= $(INCLUDE) $(LIBCOMMON)
OBJECTS=$(SRC:.c=.o)

all:$(BIN)

$(BIN):$(LIBCOMMON) $(OBJECTS)
	@echo "[ Build $(BIN) ]"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(BIN)

%.o:%.c
	@ echo cc $< ...
	@$(CC) $(INCLUDE) $(CFLAGS) $< -c -o $@

.PHONY:clean

clean:
	@rm -f $(OBJECTS)
	@rm -f $(BIN)
