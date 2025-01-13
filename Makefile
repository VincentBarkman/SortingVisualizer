CXX := g++
CXXFLAGS := -std=c++11 -I/usr/include/SDL2 -I./imgui -I./imgui/backends $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs) -ldl -pthread

SOURCES := main.cpp SortVisualizer.cpp \
           imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp \
           imgui/backends/imgui_impl_sdl2.cpp imgui/backends/imgui_impl_sdlrenderer2.cpp
TARGET := sort_visualizer

OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

