lodash-cpp
==============

originally forked from [underscore.cpp](https://github.com/cromo/underscore.cpp), this has been updated for **c++14**, and includes more underscore functionality and a smattering of the more useful container functions from lodash.

c++14 has allowed for compatability with some of the quirkier stl containers (e.g. std::set) that weren't previously compatible.

Installation
------------

lodash-cpp is a single-file, header only library. 

Usage
-----

```cpp
std::vector<int> numbers;
for (int i = 0; i < 10; i++) {
  numbers.push_back(i);
}

// Display is a function that takes one argument of type int.
_::each(numbers, display);
```

```cpp
using json = nlohmann::json;
Vector3 fromJSON(json& values) {
    auto v = _::values<std::vector<float>>(values);
    return Vector3(v.data());
}
```

```cpp
#include <nowide/convert.hpp>
using namespace nowide;
using fspath = std::experimental::filesystem::path;

template<typename Container>
std::string pathCombine(Container container) {
	// see: https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_Objects/Array/reduce
	fspath path = _::reduce(Container, [](fspath _path, std::string segment) {
		return _path /= filepath(segment);
	}, fspath);
	return narrow(path.wstring());
}
```
```cpp
// filter, then sort by predicate
std::vector<Player> players;

players = _::sort_by<decltype(players)>(
    _::filter<decltype(players)>(getPlayers(), [=](const Player& player) {
        return player.inVehicle();
    }), [](auto a, auto b) { return distanceTo(a.ped()) < distanceTo(b.ped()) });
```

The functions that have been implemented:

 *  all
 *  any
 *  chain
 *  collect
 *  compact
 *  contains
 *  detect
 *  difference
 *  each
 *  each_iter — version of `each` that passes an iterator
 *  each_with_distance — version of `each` that passes an index
 *  every
 *  filter
 *  find
 *  first
 *  flatten
 *  foldl
 *  foldr
 *  for_each
 *  group_by
 *  head
 *  includes
 *  indexOf
 *  initial
 *  inject
 *  intersection
 *  keys
 *  last
 *  last_index_of
 *  map
 *  map_iter — version of `map` that passes an iterator
 *  max
 *  min
 *  pluck
 *  pull
 *  pullAll
 *  reduce
 *  reduce_right
 *  reject
 *  remove — light-weight version of lodash `remove` that doesn't return an array
 *  removeAndReturn — full-weight vesion of lodash `remove`
 *  rest
 *  select
 *  shuffle
 *  size
 *  some
 *  sort_by
 *  tail
 *  to_array
 *  union_of
 *  uniq
 *  unique
 *  values
 *  without
 *  zip

