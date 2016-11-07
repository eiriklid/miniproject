# program executable name
TARGET = miniproject
# compiler flags
CFLAGS = -g -Wall -D_GNU_SOURCE
# linker flags
LDFLAGS = -g
# list of sources
SOURCES = $(shell find -name "*.c")
# default rule, to compile everything
all: $(TARGET)
# define object files
OBJECTS = $(SOURCES:.c=.o)
# link programs
$(TARGET): $(OBJECTS)
	~/Downloads/buildroot-avr32-v3.0.0_TTK4147/output/staging/usr/bin/avr32-linux-gcc  $(LDFLAGS) -o $@ $^
# compile
%.o : %.c
	~/Downloads/buildroot-avr32-v3.0.0_TTK4147/output/staging/usr/bin/avr32-linux-gcc  $(CFLAGS) -c -o $@ $<
# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS)