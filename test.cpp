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
#include <set>
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
using vector_string = std::vector<std::string>;

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
            return join(_::keys<vector_string>(m), ", ");
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
    TEST(values<std::map>, [&]{
            std::map<int, std::string> m = {
                {1, "a" },
                {2, "b" },
                {3, "c" }
            };
            auto result = _::values2<vector_string>(m);
            return join(result, ", ");
    });
    TEST(values<std::set>, [&]{
            std::set<std::string> m = 
                {"a", "b", "c"}
            ;
            auto result = _::values<vector_string>(m);
            return join(result, ", ");
    });
    TEST(values<std::vector>, [&]{
            vector_string m = 
                {"a", "b", "c"}
            ;
            auto result = _::values<vector_string>(m);
            return join(result, ", ");
    });
    TEST(concat<std::vector>, [&]{
            vector_string a = {"a", "b", "c"};
            vector_string b = {"a", "b", "c"};
            auto result = _::concat<vector_string>(a, b);
            return join(result, ", ");
    });
    TEST(reduce<std::vector>, [&]{
            vector_string a = {"a", "b", "c"};
            a = _::reduce(a, [](auto& accum, const auto& curr) { return _::concat<vector_string>(accum, vector_string{ curr + "2" });  }, a);
            return join(a, ", ");
    });
    TEST(uniqBy<std::vector>(_::identity), [&]{
            vector_string a = {"a", "b", "b", "c"};
            vector_string result = _::uniqBy<vector_string, std::string>(a, [](const auto& _) { return _; });
            return join(result, ", ");
    });
    TEST(combinate, [&]{
            vector_string a = {"cat ", "dog ", "lion ", "hill ", "mountain "};
            vector_string b = {"mountain", "lion"};
            auto result = _::permutate<vector_string>(a, b, [](const auto& a, const auto& b) {
                    return a + b;
            });
            return join(result, ", ");
            // return join(result, ", ");
    });
    TEST(flatten, [&]{
            vector_string a = {"cat", "dog", "lion", "hill", "mountain"};
            vector_string b = {"mountain", "lion", "a", "b", "c"};
            std::vector<vector_string> c = { a, b };
            auto result = _::helper::flatten_one_layer<vector_string>(c);

            return join(result, ", ");
            // return join(result, ", ");
    });
    TEST(chain, [&]{
            vector_string a = {"cat", "dog", "lion", "hill", "mountain"};
            vector_string result;
            _::chain(a)
                    .filter([=](const auto& _) { return _[1] == 'i'; })
                    .each(  [&](const auto& _) { result.emplace_back(_); });

            return join(result, ", ");
    });
    TEST(common, [&]{
            vector_string a = {"cat", "dog", "lion", "hill", "mountain"};
            vector_string b = {"cat", "dog", "hill", "lion", "mountain"};
            auto result = _::match_consecutive<vector_string>(a, b);

            return join(result, ", ");
            // return join(result, ", ");
    });
    TEST(compare, [&]{
            vector_string a = {"cat", "dog", "a_lion", "hill", "mountain"};
            vector_string b = {"cat", "dog", "hill", "lion", "mountain"};
            auto result = _::compare(a, b);

            return std::to_string(result);
            // return join(result, ", ");
    });
}
