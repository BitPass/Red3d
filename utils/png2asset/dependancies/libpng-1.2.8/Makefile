
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	include scripts/Makefile.Linux
endif
ifeq ($(UNAME), CYGWIN_NT-5.1)
	include scripts/Makefile.cygwin
endif
