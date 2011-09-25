all:
	@echo -e "[compiling obj2asset]"
	@gcc sqrtf.c pgeObj.c obj2h.c /usr/lib/libm.a -o obj2h
	@gcc sqrtf.c pgeObj.c obj2asset.c /usr/lib/libm.a -o obj2asset
	@echo -e "[finished compiling obj2asset]"

clean:
	@echo -e "[cleaning obj2asset]"
	@rm -rf *.o obj2h obj2asset
	@echo -e "[finished cleaning obj2asset]"

install:
	@echo -e "[installing obj2asset]"
	@cp -Rp obj2h $(PSPDEV)/bin/
	@cp -Rp obj2asset $(PSPDEV)/bin/
	@echo -e "[finished installing obj2asset]"

uninstall:
	@echo -e "[uninstalling obj2asset]"
	@rm -rf $(PSPDEV)/bin/obj2asset
	@rm -rf $(PSPDEV)/bin/obj2h
	@echo -e "[finished uninstalling obj2asset]"
