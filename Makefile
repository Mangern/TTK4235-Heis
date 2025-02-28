
EXECUTABLE  = elevator

COMPILER    = clang
CFLAGS      = -Wall -g -std=gnu11 -fsanitize=address
LDFLAGS     = -fsanitize=address
EXCLUDE     = '*test*'


SOURCEDIR = source
OBJECTDIR = build

SOURCES := $(patsubst $(SOURCEDIR)/%, %, $(shell find $(SOURCEDIR) -name '*.c'  ! -name $(EXCLUDE)  ! -path $(EXCLUDE)))
OBJECTS = $(addprefix $(OBJECTDIR)/, $(SOURCES:.c=.o))
HEADERS := $(SOURCES:.c=.h)

all: $(EXECUTABLE) 

rebuild: clean all
	
clean:
	rm -f $(EXECUTABLE)
	rm -rf $(OBJECTDIR)

## executable depends on object files: link them
$(EXECUTABLE): $(OBJECTS) 
	$(COMPILER) $^ -o $@ $(LDFLAGS)

## object files depend on source files: compile them. ALSO ON HEADER FILES OMG
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) -o $@ -c $(CFLAGS) $<

	
.PHONY: all rebuild clean

