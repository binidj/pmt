#pragma once
#include <vector>
#include <bitset>
#include "Constants.h"
#include "Text.h"

class WuManber
{
private:
    static std::vector<std::bitset<MAX_BITS>> CharMasks;
    static std::vector<std::bitset<MAX_BITS>> Errors;
    static std::vector<std::bitset<MAX_BITS>> NextErrors;

    static void GetCharMasks(const Text& pattern);
public:
    static const std::vector<size_t>& Search(const Text& text, const Text& pattern, const int Err = 0);
};