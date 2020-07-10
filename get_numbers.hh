#ifndef AKELEY_GET_NUMBERS_HH_
#define AKELEY_GET_NUMBERS_HH_

#include <ctype.h>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

// MIT License

// Copyright (c) 2020 David Zhao Akeley

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// ---
//
// Convert a string of whitespace-separated numbers into a container
// of doubles (default: vector<double>) using strtod.
template <typename Container=std::vector<double> >
inline Container get_numbers(const std::string& str)
{
    Container numbers;

    const char* remaining_chars = str.c_str();
    char* endptr = const_cast<char*>(remaining_chars);

    while (*remaining_chars != '\0') {
        double num = strtod(remaining_chars, &endptr);
        if (endptr == remaining_chars) {
            throw std::runtime_error(
                std::string("Not parsed as number: ") + remaining_chars);
        }
        numbers.push_back(num);
        remaining_chars = endptr;

        // Skip whitespace (needed to deal with whitespace at the end).
        while (1) {
            char c = *remaining_chars;
            if (isspace(c)) {
                remaining_chars++;
                continue;
            }
            break;
        }
    }
    return numbers;
}
#endif // !AKELEY_GET_NUMBERS_HH_
