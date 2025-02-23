#include "SortVisualizer.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

int main(int, char **) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    return -1;
  SDL_Window *window = SDL_CreateWindow(
      "Sorting Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window)
    return -1;
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  const ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  constexpr int initialArraySize = 100;
  SortVisualizer visualizer(initialArraySize);
  int desiredArraySize = initialArraySize;
  float sortSpeed = 1.0f;
  bool stepOnce = false;
  float barColor[3] = {1.0f, 1.0f, 1.0f};
  const char *algorithms[] = {"Bubble Sort", "Selection Sort", "Insertion Sort",
                              "Gnome Sort"};
  static int algoIndex = 0;

  int targetFPS = 144;
  bool unlimitedFPS = false;

  static Uint32 lastTime = SDL_GetTicks();
  static int frameCount = 0;
  static int currentFPS = 0;

  bool done = false;
  while (!done) {
    const Uint32 frameStart = SDL_GetTicks();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
    }

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Sorting Visualizer Settings");
    ImGui::SliderInt("Array Size", &desiredArraySize, 10, 500);
    ImGui::SliderFloat("Sort Speed", &sortSpeed, 0.1f, 10.0f);
    ImGui::Combo("Algorithm", &algoIndex, algorithms, IM_ARRAYSIZE(algorithms));
    if (ImGui::Button("Reset")) {
      visualizer.Reset(desiredArraySize);
    }
    if (ImGui::Button("Start Sorting")) {
      visualizer.StartSorting(static_cast<Algorithm>(algoIndex));
    }
    if (ImGui::Button("Pause/Resume")) {
      visualizer.TogglePause();
    }
    if (ImGui::Button("Step")) {
      stepOnce = true;
    }
    ImGui::ColorEdit3("Bar Color", barColor);

    ImGui::Separator();
    ImGui::SliderInt("Target FPS", &targetFPS, 1, 240);
    ImGui::Checkbox("Unlimited FPS", &unlimitedFPS);
    ImGui::End();

    ImGui::Begin("Stats");
    ImGui::Text("Algorithm: %s", algorithms[algoIndex]);
    ImGui::Text("Steps executed: %lld", visualizer.GetStepsExecuted());
    ImGui::Text("Comparisons: %lld", visualizer.GetComparisons());
    ImGui::Text("Swaps: %lld", visualizer.GetSwaps());
    ImGui::Text("FPS: %d", currentFPS);
    ImGui::End();

    if (visualizer.IsSorting() || stepOnce) {
      if (stepOnce) {
        visualizer.Step();
        stepOnce = false;
      } else {
        visualizer.Update(sortSpeed);
      }
    }

    ImGui::Render();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    visualizer.Render(renderer, barColor);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);

    frameCount++;
    const Uint32 currentTime = SDL_GetTicks();
    if(currentTime - lastTime >= 1000) {
        currentFPS = frameCount;
        frameCount = 0;
        lastTime = currentTime;
    }

    if (!unlimitedFPS) {
      int frameDelay = 1000 / targetFPS;
      int frameTime = SDL_GetTicks() - frameStart;
      if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
      }
    }
  }

  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

