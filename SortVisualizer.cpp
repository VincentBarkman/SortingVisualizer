#include "SortVisualizer.h"
#include <ctime>

SortVisualizer::SortVisualizer(int size)
    : arraySize(size), comparisons(0), swaps(0), stepsExecuted(0), isSorting(false) {
    array = new int[arraySize];
    resetArray();
    currentAlgorithm = BUBBLE_SORT;
    bubble_i = bubble_j = 0;
    selection_i = 0; selection_j = 1; selection_minIndex = 0;
    insertion_i = 1; insertion_j = 1; insertion_innerLoop = false; insertion_key = 0;
    gnome_index = 1;
}

SortVisualizer::~SortVisualizer() {
    delete[] array;
}

void SortVisualizer::resetArray() const {
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % arraySize + 1;
    }
}

void SortVisualizer::Reset(const int newSize) {
    delete[] array;
    arraySize = newSize;
    array = new int[arraySize];
    resetArray();
    isSorting = false;
    bubble_i = bubble_j = 0;
    selection_i = 0; selection_j = 1; selection_minIndex = 0;
    insertion_i = 1; insertion_j = 1; insertion_innerLoop = false; insertion_key = 0;
    gnome_index = 1;
    comparisons = swaps = stepsExecuted = 0;
}

void SortVisualizer::StartSorting(Algorithm algo) {
    currentAlgorithm = algo;
    isSorting = true;
    bubble_i = bubble_j = 0;
    selection_i = 0; selection_j = 1; selection_minIndex = 0;
    insertion_i = 1; insertion_j = 1; insertion_innerLoop = false; insertion_key = 0;
    gnome_index = 1;
    comparisons = swaps = stepsExecuted = 0;
}

void SortVisualizer::TogglePause() {
    isSorting = !isSorting;
}

void SortVisualizer::Step() {
    Update(1.0f);
}

void SortVisualizer::Update(float sortSpeed) {
    int steps = static_cast<int>(sortSpeed);
    if (steps < 1) steps = 1;
    for (int step = 0; step < steps; ++step) {
        stepsExecuted++;
        if (currentAlgorithm == BUBBLE_SORT) {
            if (bubble_i < arraySize) {
                if (bubble_j < arraySize - bubble_i - 1) {
                    comparisons++;
                    if (array[bubble_j] > array[bubble_j + 1]) {
                        int temp = array[bubble_j];
                        array[bubble_j] = array[bubble_j + 1];
                        array[bubble_j + 1] = temp;
                        swaps++;
                    }
                    bubble_j++;
                } else {
                    bubble_j = 0;
                    bubble_i++;
                }
            } else { isSorting = false; }
        } else if (currentAlgorithm == SELECTION_SORT) {
            if (selection_i < arraySize - 1) {
                if (selection_j < arraySize) {
                    comparisons++;
                    if (array[selection_j] < array[selection_minIndex]) {
                        selection_minIndex = selection_j;
                    }
                    selection_j++;
                } else {
                    int temp = array[selection_i];
                    array[selection_i] = array[selection_minIndex];
                    array[selection_minIndex] = temp;
                    swaps++;
                    selection_i++;
                    selection_j = selection_i + 1;
                    selection_minIndex = selection_i;
                }
            } else { isSorting = false; }
        } else if (currentAlgorithm == INSERTION_SORT) {
            if (insertion_i < arraySize) {
                if (!insertion_innerLoop) {
                    insertion_key = array[insertion_i];
                    insertion_j = insertion_i - 1;
                    insertion_innerLoop = true;
                }
                if (insertion_innerLoop) {
                    comparisons++;
                    if (insertion_j >= 0 && array[insertion_j] > insertion_key) {
                        array[insertion_j + 1] = array[insertion_j];
                        insertion_j--;
                        swaps++;
                    } else {
                        array[insertion_j + 1] = insertion_key;
                        insertion_innerLoop = false;
                        insertion_i++;
                    }
                }
            } else { isSorting = false; }
        } else if (currentAlgorithm == GNOME_SORT) {
            if (gnome_index < arraySize) {
                comparisons++;
                if (gnome_index == 0 || array[gnome_index] >= array[gnome_index - 1]) {
                    gnome_index++;
                } else {
                    int temp = array[gnome_index];
                    array[gnome_index] = array[gnome_index - 1];
                    array[gnome_index - 1] = temp;
                    swaps++;
                    gnome_index--;
                }
            } else { isSorting = false; }
        }
    }
}

void SortVisualizer::Render(SDL_Renderer* renderer, const float barColor[3]) const {
    const int barWidth = 800 / (arraySize > 0 ? arraySize : 1);
    SDL_SetRenderDrawColor(renderer,
                           static_cast<Uint8>(barColor[0] * 255),
                           static_cast<Uint8>(barColor[1] * 255),
                           static_cast<Uint8>(barColor[2] * 255),
                           255);
    for (int k = 0; k < arraySize; ++k) {
        float heightFactor = static_cast<float>(array[k]) / arraySize;
        int barHeight = static_cast<int>(heightFactor * 600);
        SDL_Rect rect = { k * barWidth, 600 - barHeight, barWidth, barHeight };
        SDL_RenderFillRect(renderer, &rect);
    }
}

long long SortVisualizer::GetComparisons() const { return comparisons; }
long long SortVisualizer::GetSwaps() const { return swaps; }
long long SortVisualizer::GetStepsExecuted() const { return stepsExecuted; }
Algorithm SortVisualizer::GetCurrentAlgorithm() const { return currentAlgorithm; }
bool SortVisualizer::IsSorting() const { return isSorting; }

