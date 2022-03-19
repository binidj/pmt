# CMakeList.txt : CMake project for pmt, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pmt "pmt.cpp" "pmt.h" "Text.h" "Text.cpp" "SlidingWindow.h" "SlidingWindow.cpp" "KMP.h" "KMP.cpp" "BoyerMoore.h" "BoyerMoore.cpp" "Sellers.h" "Sellers.cpp" "WuManber.h" "WuManber.cpp" "AhoCorasick.h" "AhoCorasick.cpp" "Constants.h" "BenchmarkTimer.h" "BenchmarkTimer.cpp")

# TODO: Add tests and install targets if needed.
