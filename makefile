# Compiler to use
CC := g++

# Folders
SRCDIR    := src
BUILDDIR  := build
TARGETDIR := .

# Targets
EXECUTABLE := gemboy
TARGET     := $(TARGETDIR)/$(EXECUTABLE)

# Final Path for the target executable.
INSTALLBINDIR := "$$HOME/bin"

# Code Lists
SRCEXT  := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Folder Lists
# Note: Intentionally excludes the root of the include folder so the lists are clean
INCDIRS   := $(shell find include/* -name '*.h' -exec dirname {} \; | sort | uniq)
INCLIST   := $(patsubst include/%,-I include/%,$(INCDIRS))
BUILDLIST := $(patsubst include/%,$(BUILDDIR)/%,$(INCDIRS))

# Shared Compiler Flags
CFLAGS := -ggdb -O0
OFLAGS  = $(LIBDIRS) -lm -lpthread -lncurses

###################################################################
# SDL Build compiler flags
###################################################################
OFLAGS  += -lSDL2 `pkg-config --cflags --libs sdl2` -lSDL2_mixer
CFLAGS	+= -DLIB_SDL
###################################################################

INC := -I include #$(INCLIST) -I /usr/local/include
LIB := -L /usr/local/lib

CFLAGS += -std=c++11

# rule for the main program
$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "  Linking $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIB) $(OFLAGS) $(CFLAGS)

# rule for the object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

install: $(TARGET)
	install $(TARGET) $(INSTALLBINDIR)

clean:
	@echo "Cleaning $(TARGET)..."; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
