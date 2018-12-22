CXXFLAGS=-Wall -g
CC=g++

SRCDIR=src
BUILDDIR=build
TARGET=bin/speck
SOURCES=$(shell find $(SRCDIR) -type f -name "*.cpp")
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf bin
	rm -rf build

.PHONY: clean
