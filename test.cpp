// #include <algorithm>
// #include <array>
// #include <cctype>
// #include <cfloat>
// #include <climits>
// #include <cmath>
// #include <cstdarg>
// #include <cstdio>
// #include <cstdlib>
// #include <cstring>
// #include <ctime>
// #include <fstream>
// #include <functional>
// #include <iomanip>
// #include <iosfwd>
#include <iostream>
// #include <limits>
#include <map>
// #include <memory>
// #include <mutex>
#include <ostream>
// #include <queue>
// #include <random>
// #include <regex>
// #include <set>
#include <sstream>
// #include <stdarg.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <string>
// #include <time.h>
// #include <type_traits>
// #include <unordered_map>
// #include <unordered_set>
#include <vector>

#include "lodash.hpp"
// #include "test/json.hpp"

using namespace std::string_literals; 

#define TEST(NAME, ...) \
    std::cout << "\n\n********\n" << #NAME << ":\n" << (__VA_ARGS__)();

template<typename T>
std::string join(const T& elements, const char* const separator) {
    std::ostringstream os;

    const char* _separator = "";
    for (auto& item : elements) {
        os << _separator << item;
        _separator = separator;
    }
    return os.str();
}

int main(int argc, const char** argv) {

    // instead, you could also write (which looks very similar to the JSON above)
    // json object = {
        // {"pi", 3.141},
        // {"happy", true},
        // {"name", "Niels"},
        // {"nothing", nullptr},
        // {"answer", {
                       // {"everything", 42}
                   // }},
        // {"list", {1, 0, 2}},
        // {"object", {
                       // {"currency", "USD"},
                       // {"value", 42.99}
                   // }}
    // };

    TEST(reduceArray, []{
            std::vector<int> v{ 1, 2, 3 };
            return 
                _::reduceArray(v, [](auto accumulator, auto currentValue, auto currentIndex, auto container) {
                    return accumulator + "Index: "s + std::to_string(currentIndex) + " = "s + std::to_string(currentValue) + '\n';
                }, "Output: "s);
    });

    TEST(keys, [&]{
            std::map<std::string, int> m = {
                {"a", 1},
                {"b", 2},
                {"c", 3}
            };
            return join(_::keys<std::vector<std::string>>(m), ", ");
    });
    TEST(keys2, [&]{
            std::map<std::string, int> m = {
                {"a", 1},
                {"b", 2},
                {"c", 3}
            };
            return join(_::keys2(m), ", ");
    });
    TEST(reduceObject, [&]{
            std::map<std::string, int> m = {
                {"a", 1},
                {"b", 2},
                {"c", 3}
            };
            return 
                _::reduceObject(m, [](
                            auto accumulator, 
                            const auto& currentValue, 
                            const auto& currentKey, 
                            const auto& container) 
                {
                    return accumulator
                        + "Key: "s
                        + currentKey
                        + " = "s
                        + std::to_string(currentValue)
                        + '\n'
                        ;
                }, "Output: "s);
    });
}
