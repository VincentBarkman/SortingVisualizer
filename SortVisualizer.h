#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

#include <SDL.h>

enum Algorithm { BUBBLE_SORT, SELECTION_SORT, INSERTION_SORT, GNOME_SORT };

class SortVisualizer {
public:
    SortVisualizer(int arraySize);
    ~SortVisualizer();
    void Reset(int newSize);
    void StartSorting(Algorithm algo);
    void TogglePause();
    void Step();
    void Update(float sortSpeed);
    void Render(SDL_Renderer* renderer, float barColor[3]);
    
    long long GetComparisons() const;
    long long GetSwaps() const;
    long long GetStepsExecuted() const;
    Algorithm GetCurrentAlgorithm() const;
    bool IsSorting() const;
    
private:
    int* array;
    int arraySize;
    long long comparisons;
    long long swaps;
    long long stepsExecuted;
    bool isSorting;
    
    Algorithm currentAlgorithm;
    int bubble_i, bubble_j;
    int selection_i, selection_j, selection_minIndex;
    int insertion_i, insertion_j;
    bool insertion_innerLoop;
    int insertion_key;
    int gnome_index;
    
    void resetArray();
};

#endif // SORTVISUALIZER_H

