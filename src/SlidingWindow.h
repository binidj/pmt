#pragma once
#include <vector>
#include "Text.h"
#include "SinglePatternSearch.h"

class SlidingWindow : public SinglePatternSearch
{
public:
    void Init(const Text& pattern, const int EditDistance);
    const int Search(const Text& text, const Text& pattern, const int EditDistance);
};