#pragma once
#include <vector>
#include <bitset>
#include "Text.h"

class WuManber
{
private:
    static const size_t ALPHA_SIZE = 128;
    static const size_t MAX_BITS = 1024;
    static std::vector<std::bitset<MAX_BITS>> CharMasks;
    static std::vector<std::bitset<MAX_BITS>> Errors;
    static std::vector<std::bitset<MAX_BITS>> NextErrors;

    static void GetCharMasks(const Text& pattern);
public:
    static const std::vector<size_t>& Search(const Text& text, const Text& pattern, const int Err = 0);
};