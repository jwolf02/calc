#ifndef __PRINT_STL_HPP
#define __PRINT_STL_HPP

// Header library to faciliate the output of STL containers

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

template <typename T>
void print(const std::vector<T> &vector) {
  std::cout << '[';
  for (auto it = vector.begin(); it != vector.end(); ++it) {
    std::cout << *it;
    auto i = it;
    if (++i != vector.end())
      std::cout << ", ";
  }
  std::cout << ']' << std::endl;
}

template <typename T, typename pfunc_t>
void print(const std::vector<T> &vector, pfunc_t pfunc) {
  std::cout << '[';
  for (auto it = vector.begin(); it != vector.end(); ++it) {
    pfunc(*it);
    auto i = it;
    if (++i != vector.end())
      std::cout << ", ";
  }
  std::cout << ']' << std::endl;
}

template <typename T>
void print(const std::list<T> &list) {
  std::cout << '[';
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it;
    auto i = it;
    if (++i != list.end())
      std::cout << ", ";
  }
  std::cout << ']' << std::endl;
}

template <typename T, typename pfunc_t>
void print(const std::list<T> &list, pfunc_t pfunc) {
  std::cout << '[';
  for (auto it = list.begin(); it != list.end(); ++it) {
    pfunc(*it);
    auto i = it;
    if (++i != list.end())
      std::cout << ", ";
  }
  std::cout << ']' << std::endl;
}

template <typename T>
void print(const std::set<T> &set) {
  std::cout << '{';
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::cout << *it;
    auto i = it;
    if (++i != set.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename T, typename pfunc_t>
void print(const std::set<T> &set, pfunc_t pfunc) {
  std::cout << '{';
  for (auto it = set.begin(); it != set.end(); ++it) {
    pfunc(*it);
    auto i = it;
    if (++i != set.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename T>
void print(const std::unordered_set<T> &set) {
  std::cout << '{';
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::cout << *it;
    auto i = it;
    if (++i != set.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename T, typename pfunc_t>
void print(const std::unordered_set<T> &set, pfunc_t pfunc) {
  std::cout << '{';
  for (auto it = set.begin(); it != set.end(); ++it) {
    pfunc(*it);
    auto i = it;
    if (++i != set.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename K, typename V>
void print(const std::map<K, V> &map) {
  std::cout << '{';
  for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << it->first << " : " << it->second;
    auto i = it;
    if (++i != map.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename K, typename V, typename pfunc_t>
void print(const std::map<K, V> &map, pfunc_t pfunc) {
  std::cout << '{';
  for (auto it = map.begin(); it != map.end(); ++it) {
    pfunc(*it);
    auto i = it;
    if (++i != map.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename K, typename V>
void print(const std::unordered_map<K, V> &map) {
  std::cout << '{';
  for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << it->first << " : " << it->second;
    auto i = it;
    if (++i != map.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

template <typename K, typename V, typename pfunc_t>
void print(const std::unordered_map<K, V> &map, pfunc_t pfunc) {
  std::cout << '{';
  for (auto it = map.begin(); it != map.end(); ++it) {
    pfunc(*it);
    auto i = it;
    if (++i != map.end())
      std::cout << ", ";
  }
  std::cout << '}' << std::endl;
}

#endif // __PRINT_STL_HPP
