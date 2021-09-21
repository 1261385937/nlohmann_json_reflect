#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <optional>
#include "reflection.hpp"

namespace jreflect {

template<template<typename...> class Container, typename T>
struct is_specialization_of :std::false_type {};

template<template<typename...> class Container, typename ...Args>
struct is_specialization_of<Container, Container<Args...>> :std::true_type {};

template<template<typename...> typename Container, typename T>
struct is_sequence_specialization_of :std::false_type {};

template<template<typename...> typename Container, typename ...Args>
struct is_sequence_specialization_of <Container, Container<Args...>> :std::true_type {
    using element_type = typename Container<Args...>::value_type;
};

template<template<typename...> typename Container, typename T>
struct is_associative_specialization_of :std::false_type {};

template<template<typename...> typename Container, typename ...Args>
struct is_associative_specialization_of <Container, Container<Args...>> :std::true_type {
    using element_type = typename Container<Args...>::mapped_type;
};

//sequence container for json
template<typename T>
struct is_std_vector :is_sequence_specialization_of<std::vector, std::decay_t<T>> {};

template<typename T>
struct is_std_deque :is_sequence_specialization_of<std::deque, std::decay_t<T>> {};

template<typename T>
struct is_std_list : is_sequence_specialization_of<std::list, std::decay_t<T>> {};

template<typename T>
struct is_std_forward_list : is_sequence_specialization_of<std::forward_list, std::decay_t<T>> {};

template<typename T>
struct is_std_set : is_sequence_specialization_of<std::set, std::decay_t<T>> {};

template<typename T>
struct is_std_unordered_set : is_sequence_specialization_of<std::unordered_set, std::decay_t<T>> {};

template<typename T>
struct is_std_multiset : is_sequence_specialization_of<std::multiset, std::decay_t<T>> {};

template<typename T>
struct is_std_unordered_multiset : is_sequence_specialization_of<std::unordered_multiset, std::decay_t<T>> {};

template<typename Type>
struct is_std_array :std::false_type {};

template<typename Item, std::size_t N>
struct is_std_array<std::array<Item, N>> :std::true_type {
    using element_type = Item;
};

//associative container for json
template<typename T>
struct is_std_map :is_associative_specialization_of<std::map, std::decay_t<T>> {};

template<typename T>
struct is_std_unordered_map :is_associative_specialization_of<std::unordered_map, std::decay_t<T>> {};

template<typename T>
struct is_std_multimap :is_associative_specialization_of<std::multimap, std::decay_t<T>> {};

template<typename T>
struct is_std_unordered_multimap :is_associative_specialization_of<std::unordered_multimap, std::decay_t<T>> {};

//other container
template<typename T>
struct is_std_tuple :is_specialization_of<std::tuple, std::decay_t<T>> {};

template<typename T>
struct is_std_optional : is_specialization_of<std::optional, std::decay_t<T>> {};

//compile time true/false
template <typename T>
inline constexpr bool is_std_vector_v = is_std_vector<T>::value;

template <typename T>
inline constexpr bool is_std_deque_v = is_std_deque<T>::value;

template <typename T>
inline constexpr bool is_std_list_v = is_std_list<T>::value;

template <typename T>
inline constexpr bool is_std_forward_list_v = is_std_forward_list<T>::value;

template <typename T>
inline constexpr bool is_std_set_v = is_std_set<T>::value;

template <typename T>
inline constexpr bool is_std_unordered_set_v = is_std_unordered_set<T>::value;

template <typename T>
inline constexpr bool is_std_multiset_v = is_std_multiset<T>::value;

template <typename T>
inline constexpr bool is_std_unordered_multiset_v = is_std_unordered_multiset<T>::value;

template <typename T>
inline constexpr bool is_std_map_v = is_std_map<T>::value;

template <typename T>
inline constexpr bool is_std_unordered_map_v = is_std_unordered_map<T>::value;

template <typename T>
inline constexpr bool is_std_multimap_v = is_std_multimap<T>::value;

template <typename T>
inline constexpr bool is_std_unordered_multimap_v = is_std_unordered_multimap<T>::value;

template <typename T>
inline constexpr bool is_std_array_v = is_std_array<T>::value;

template <typename T>
inline constexpr bool is_std_tuple_v = is_std_tuple<T>::value;

template <typename T>
inline constexpr bool is_std_optional_v = is_std_optional<T>::value;

template<typename T>
inline constexpr bool is_sequence_std_container_v =
is_std_vector_v<T> || is_std_deque_v<T> || is_std_list_v<T> ||
is_std_forward_list_v<T> || is_std_set_v<T> || is_std_unordered_set_v<T> ||
is_std_multiset_v<T> || is_std_unordered_multiset_v<T> || is_std_array_v<T>;

template<typename T>
inline constexpr bool is_associative_std_container_v =
is_std_map_v<T> || is_std_unordered_map_v<T> || is_std_multimap_v<T> || is_std_unordered_multimap_v<T>;

template<typename T>
inline constexpr bool is_std_container_v = is_sequence_std_container_v<T> || is_associative_std_container_v<T>;

template <typename>
inline constexpr bool always_false_v = false;

//detect std container has reflect type
template<typename T, typename U = void>
struct is_has_reflect_type :std::false_type {};

template<typename T>
struct is_has_reflect_type<T, std::enable_if_t<std::is_same_v<typename T::reflect_type, reflection::reflect>>> :std::true_type {};

template<typename T>
struct is_has_reflect_type<T, std::enable_if_t<std::is_same_v<typename decltype(reflection_reflect_member(std::declval<T>()))::reflect_type, reflection::reflect>>> :std::true_type {};

template<typename T>
struct is_has_reflect_type<T, std::enable_if_t<is_sequence_std_container_v<T>/*, std::void_t<typename T::value_type>*/>>
    : is_has_reflect_type<typename T::value_type> {};

template<typename T>
struct is_has_reflect_type<T, std::enable_if_t<is_associative_std_container_v<T>/*, std::void_t<typename T::mapped_type>*/>>
    : is_has_reflect_type<typename T::mapped_type> {};

template<typename T>
inline constexpr bool is_has_reflect_type_v = is_has_reflect_type<T>::value;
}
