CXX      = g++ 
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = stack.out
DEBFLAGS = -g
RELFLAGS = -O2

ifneq ($(BUILD),release)
	BUILD = debug
	FLAGS = $(DEBFLAGS)
else
	FLAGS = $(RELFLAGS)
endif

$(BUILD)_$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $(FLAGS) -o $@ $<

.PHONY: release debug clean

release debug:
	$(MAKE) BUILD=$@

clean:
	rm -r release_$(TARGET) debug_$(TARGET)
