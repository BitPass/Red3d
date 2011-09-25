
all:
	@echo -e "[building utilities]"
	@cd obj2asset && make && cd ..
	@cd png2asset && make && cd ..
	@echo -e "[finished building utilities]"
	
clean:
	@echo -e "[cleaing utilities]"
	@cd obj2asset && make clean && cd ..
	@cd png2asset && make clean && cd ..
	@echo -e "[finished cleaning utilities]"

install:
	@echo -e "[installing utilities]"
	@cd obj2asset && make install && cd ..
	@cd png2asset && make install && cd ..
	@echo -e "[finished installing utilities]"

uninstall:
	@echo -e "[uninstalling utilities]"
	@cd obj2asset && make uninstall && cd ..
	@cd png2asset && make uninstall && cd ..
	@echo -e "[finished uninstalling utilities]"

