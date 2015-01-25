include $(PWD)/config.mk

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

default: $(OBJS) libcog

libdstruct:
	@make -s -C dstruct

%.o: %.c
	$(COMPILE_OBJ)

libcog: libdstruct
	$(MAKE_STATIC_LIB)
