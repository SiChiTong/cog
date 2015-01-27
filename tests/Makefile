include $(PWD)/config.mk

SRCS = $(wildcard *.c)
TESTS = $(SRCS:.c=)

default: $(TESTS)

%: %.c
	$(MAKE_TEST)
