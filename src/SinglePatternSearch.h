#pragma once
#include "Text.h"
#include <vector>
#include <list>

class SinglePatternSearch
{
protected:
    int CurrentOcc = 0;
public:
    std::vector<size_t> Occurences;
    virtual void Init(const Text& pattern, const int EditDistance) = 0;
    virtual const int Search(const Text& text, const Text& pattern, const int EditDistance) = 0;
    SinglePatternSearch() = default;
    virtual ~SinglePatternSearch() = default;
};