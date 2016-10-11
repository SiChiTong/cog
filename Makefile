include config.mk
PREFIX="/usr/local"

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

run_tests: scripts/test_runner.sh
	@./$<

clean: rmdirs
	@echo "cleaning ..."
	@echo "done! :)"

install:
	@echo "installing cog to [$(PREFIX)/lib]"
	@cp $(LIB_DIR)/libcog.a $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include/cog
	@cp include/* $(PREFIX)/include/cog/
	@echo "cog installed!"

uninstall:
	@echo "removing cog"
	@rm $(PREFIX)/lib/libcog.a
	@rm -rf $(PREFIX)/include/cog

done:
	@echo "done! :)"
