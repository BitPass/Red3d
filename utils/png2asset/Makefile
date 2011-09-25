all:
	@echo -e "[compiling png2asset dependancies]"
	@cd dependancies/zlib-1.2.3/ && make && make install && cd ..
	@cd dependancies/libpng-1.2.8/ && make && make install && cd ../../
	@echo -e "[finished compiling png2asset dependancies]"
	@echo -e "[compiling png2asset]"
	@gcc main.c $(PSPDEV)/lib/libpng12.a $(PSPDEV)/lib/libz.a /usr/lib/libm.a -o png2asset
	@echo -e "[finished compiling png2asset]"
	
clean:
	@echo -e "[cleaning png2asset dependancies]"
	@cd dependancies/zlib-1.2.3/ && make clean && cd ..
	@cd dependancies/libpng-1.2.8/ && make clean && cd ../../
	@echo -e "[cleaning png2asset]"
	@rm -rf png2asset.exe png2asset main.o
	@echo -e "[finished cleaning png2asset]"

install:
	@echo -e "[installing png2asset]"
	@cp -Rp png2asset $(PSPDEV)/bin/
	@echo -e "[finished installing png2asset]"
	
uninstall:
	@echo -e "[uninstalling png2asset]"
	@rm -rf $(PSPDEV)/bin/obj2asset
	@echo -e "[finished uninstalling png2asset]"
	
