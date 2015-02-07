include config.mk

default: all done

all: mkdirs
	@make -s -C src
	@make -s -C tests

debug: mkdirs
	@make -C src
	@make -C tests

mkdirs: rmdirs
	@mkdir bin
	@mkdir obj
	@mkdir lib

rmdirs:
	@rm -rf bin
	@rm -rf obj
	@rm -rf lib

run_tests: scripts/unittest_runner.py
	@./$<

clean: rmdirs
	@echo "cleaning ..."
	@echo "done! :)"

install:
	@echo "installing cog"
	@cp .$(LIB_DIR)/libcog.a /usr/local/lib/
	@mkdir -p /usr/local/include/cog
	@cp include/* /usr/local/include/cog/
	@mv /usr/local/include/cog/cog.h /usr/local/include/cog.h

uninstall:
	@echo "uninstalling cog"
	@rm /usr/local/lib/libcog.a

done:
	@echo "done! :)"
