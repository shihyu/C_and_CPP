# =============================================================================
#  Copyright (c) 2008 ActiveSys.Wangbo
#
#  copyright description ...
#
#  Project:    cstl
#  Module:     make
#  Filename:   Makefile
#      
#  The project compilation file.
#
#  2008-11-01 20:59:29
# =============================================================================

# set compiler and options
CC = gcc
CEXPFLAGS = -DCSTL_TYPES_UNIFICATION=2 -DNDEBUG
CFLAGS = -c -g -ansi -pedantic -Wall -Wextra $(CEXPFLAGS)
CPPFLAGS = -I include
LINKSOFLAGS = -fPIC -shared -Wl,-soname,libcstl.so.1

ARFLAGS = ruv

# set file manipulation tools
RM = rm -rf
SED = sed
INSTALL = install
MKDIR = mkdir
LN = ln -s
MAKE = make

# set compilation directory
vpath %.c src test
vpath %.h include test

SRCS = $(notdir $(wildcard src/*.c))
OBJS = $(subst .c,.o,$(SRCS))
TESTSRC = $(notdir $(wildcard test/*.c))
TESTOBJ = $(subst .c,.o,$(TESTSRC))

BINDIR = bin
SRCDIR = src
INCDIR = include
TESTDIR = test
LIBDIR = /usr/lib/
LIBINCDIR = /usr/include/cstl/

# set compilation targets
TARGETVER = 1.0.0
LINKTARGET = libcstl.so
SONAME = libcstl.so.1
ARTARGET = $(BINDIR)/libcstl.a
SOTARGET = $(BINDIR)/libcstl.so.$(TARGETVER)
TESTTARGET = $(BINDIR)/test
HEADERTARGET = $(INCDIR)/*.h

# compile rule
.PHONY: all
all : $(ARTARGET) $(SOTARGET) $(TESTTARGET)

$(ARTARGET): $(addprefix $(BINDIR)/,$(OBJS))
	$(AR) $(ARFLAGS) $@ $^

$(SOTARGET): $(addprefix $(BINDIR)/,$(OBJS))
	$(CC) $^ $(LINKSOFLAGS) -o $@

$(TESTTARGET): $(addprefix $(BINDIR)/,$(TESTOBJ)) $(ARTARGET)
	$(CC) $^ $(ARTARGET) -o $@

# include depend file
ifneq ($(MAKECMDGOALS),clean)
    -include $(addprefix $(BINDIR)/,$(subst .c,.d,$(SRCS)))
    -include $(addprefix $(BINDIR)/,$(subst .c,.d,$(TESTSRC)))
endif

# user defined rule
$(BINDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BINDIR)/%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
	$(SED) 's,\($*\).o[ :]*,$(BINDIR)/\1.o $@: ,g' < $@.$$$$ > $@;\
	$(RM) $@.$$$$

# phony target
.PHONY: install
install:
	$(INSTALL) $(ARTARGET) $(LIBDIR)
	$(INSTALL) $(SOTARGET) $(LIBDIR)
	$(LN) $(LIBDIR)$(LINKTARGET).$(TARGETVER) $(LIBDIR)$(SONAME)
	$(LN) $(LIBDIR)$(LINKTARGET).$(TARGETVER) $(LIBDIR)$(LINKTARGET)
	$(MKDIR) $(LIBINCDIR)
	$(INSTALL) $(HEADERTARGET) $(LIBINCDIR)

.PHONY: uninstall
uninstall:
	$(RM) $(LIBDIR)$(LINKTARGET).$(TARGETVER)
	$(RM) $(LIBDIR)$(SONAME)
	$(RM) $(LIBDIR)$(LINKTARGET)
	$(RM) $(LIBINCDIR)

.PHONY: update
update:
	$(MAKE) uninstall
	$(MAKE) install

.PHONY: clean
clean:
	$(RM) $(ARTARGET) 
	$(RM) $(SOTARGET)
	$(RM) $(TESTTARGET)
	$(RM) $(addprefix $(BINDIR)/,$(OBJS)) 
	$(RM) $(addprefix $(BINDIR)/,$(subst .o,.d,$(OBJS))) 
	$(RM) $(addprefix $(BINDIR)/,$(TESTOBJ))
	$(RM) $(addprefix $(BINDIR)/,$(subst .o,.d,$(TESTOBJ)))
	$(RM) core.* $(BINDIR)/core.*

.PHONY: remake
remake:
	make clean
	make

