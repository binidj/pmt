#pragma once
#include <vector>
#include "Text.h"

class Sellers
{
private:
    static std::vector<int> Column;
    static std::vector<int> NextColumn;

    static std::vector<int> GetNext(const std::vector<int>& Column, const Text& pattern, char Ch);
public:
    static const std::vector<size_t>& Search(const Text& text, const Text& pattern, const int Err = 0);
};