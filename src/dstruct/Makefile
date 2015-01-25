include $(PWD)/config.mk

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

default: $(OBJS)

%.o: %.c
	$(COMPILE_OBJ)
