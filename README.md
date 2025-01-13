# Sorting Visualizer

This repository contains a lightweight application for visualizing various sorting algorithms using SDL2 and Dear ImGui. The code is structured in a modular way, with a clear separation between the sorting logic and the UI/rendering code, making it maintainable and extensible.

---

## Features

- **Multiple Sorting Algorithms:** 
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Gnome Sort
- **Real-time Statistics:** Tracks and displays:
  - Steps executed
  - Number of comparisons
  - Number of swaps
- **User Controls:**
  - Start, pause/resume, and reset sorting
  - Step-by-step execution when paused
  - Adjustable array size and sort speed
  - Color customization for the visualization bars

---

## Repository Structure

```
.
├── imgui/                  
│   ├── backends/
│   │   ├── imgui_impl_sdl2.*     
│   │   └── imgui_impl_sdlrenderer2.*
│   ├── imconfig.h
│   ├── imgui.h
│   ├── imgui.cpp
│   ├── imgui_draw.cpp
│   ├── imgui_tables.cpp
│   └── imgui_widgets.cpp
├── SortVisualizer.h              
├── SortVisualizer.cpp            
├── main.cpp                      
```

---

## Dependencies

- **SDL2:** Simple DirectMedia Layer for window and rendering management.
- **Dear ImGui:** Immediate mode GUI library for the user interface.

Ensure you have the SDL2 development package installed:

```bash
sudo apt-get install libsdl2-dev
```

---

## Build Instructions

1. **Clone the repository:**

   ```bash
   git clone git@github.com:VincentBarkman/SortingVisualizer.git
   cd SortingVisualizer
   ```

2. **Compile the application:**

   Use the following command to compile:

   ```bash
   g++ -std=c++11 \
       -I/usr/include/SDL2 \
       -I./imgui \
       -I./imgui/backends \
       $(sdl2-config --cflags) \
       main.cpp \
       SortVisualizer.cpp \
       imgui/imgui.cpp \
       imgui/imgui_draw.cpp \
       imgui/imgui_tables.cpp \
       imgui/imgui_widgets.cpp \
       imgui/backends/imgui_impl_sdl2.cpp \
       imgui/backends/imgui_impl_sdlrenderer2.cpp \
       $(sdl2-config --libs) \
       -ldl -pthread \
       -o sort_visualizer
   ```

   Adjust the compilation command if diffrent on your machine this was made on (ubuntu 24).

3. **Run the application:**

   ```bash
   ./sort_visualizer
   ```

---

## Usage

- **Reset:** Reinitializes the array with a new size and random values.
- **Start Sorting:** Begins sorting using the selected algorithm.
- **Pause/Resume:** Toggles the sorting process.
- **Step:** Executes a single sorting iteration.
- **Bar Color:** Use the color picker to customize the visualization bars.
- **Adjust Speed and Size:** Sliders allow you to change the sort speed and array size (effective on reset).

---

## Notes

- This minimal setup includes only the essential ImGui files required for SDL2 with the SDL_Renderer backend, reducing repository bloat.
- For further development, algorithms can be added or existing ones extended by modifying `SortVisualizer.cpp`.

---

## License

This project is provided under no license, this was just to visualize algorithms. The ImGui components are also under the MIT License, and their licenses are included within their respective files.

---

## Contact

For questions, issues, or contributions, please open an issue or contact the repository maintainer.
