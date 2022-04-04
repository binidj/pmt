#pragma once
#include <vector>
#include "Text.h"
#include "SinglePatternSearch.h"

class Sellers : public SinglePatternSearch
{
private:
    std::vector<int> Column;
    std::vector<int> NextColumn;
    void GetNext(const Text& pattern, char Ch);
public:
    void Init(const Text& pattern, const int EditDistance);
    const int Search(const Text& text, const Text& pattern, const int EditDistance);
};