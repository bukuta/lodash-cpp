#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <ostream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

template <typename ResultContainer, typename Container, typename Function>
ResultContainer map(const Container& container, Function&& function) {
    ResultContainer result;

    std::transform(std::begin(container), std::end(container),
                   std::back_inserter(result), std::forward<Function>(function));
    return result;
}

template <typename ResultContainer, std::size_t I, typename Container>
ResultContainer get_item(const Container& container) {
    return map<ResultContainer>(container, [ ](auto & value) {
        return std::get<I>(value);
    });
}

template <typename ResultContainer, typename Container>
ResultContainer tuple_keys(const Container& container) {
    return get_item<ResultContainer, 0>(container);
}

int main(int argc, const char **argv) {
    std::map<std::string, std::string> m = {
        {"a", "x"},
        {"b", "y"},
        {"c", "z"}
    };

    tuple_keys<std::vector<std::string>>(m);

    json j(m);
    // will not compile with this line uncommented
    tuple_keys<std::vector<std::string>>(j);
}
