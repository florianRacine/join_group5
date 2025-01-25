
CXX = g++
CXXFLAGS = -std=c++17 -O3
TARGET = yourjoin

all: $(TARGET)

$(TARGET): yourjoin.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) yourjoin.cpp

clean:
	rm -f $(TARGET)

.PHONY: all clean
