#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include "reflection.hpp"
#include "json.hpp"

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

	// std sequence container
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

	// std associative container
	template<typename T>
	struct is_std_map :is_associative_specialization_of<std::map, std::decay_t<T>> {};

	template<typename T>
	struct is_std_unordered_map :is_associative_specialization_of<std::unordered_map, std::decay_t<T>> {};

	template<typename T>
	struct is_std_multimap :is_associative_specialization_of<std::multimap, std::decay_t<T>> {};

	template<typename T>
	struct is_std_unordered_multimap :is_associative_specialization_of<std::unordered_multimap, std::decay_t<T>> {};

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
	/*template<typename T, typename = void>
	struct is_has_reflect_type :std::false_type {};

	template<typename T>
	struct is_has_reflect_type<T, std::void_t<std::enable_if_t<std::is_same_v<typename T::reflect_type, reflection::reflect>>>> :std::true_type {};

	template<typename T>
	struct is_has_reflect_type<T, std::void_t<std::enable_if_t<is_sequence_std_container_v<T>, typename T::value_type>>>
		: is_has_reflect_type<typename T::value_type> {};

	template<typename T>
	struct is_has_reflect_type<T, std::void_t<std::enable_if_t<is_associative_std_container_v<T>, typename T::mapped_type>>>
		: is_has_reflect_type<typename T::mapped_type> {};*/

	template<typename T, typename U = void>
	struct is_has_reflect_type :std::false_type {};

	template<typename T>
	struct is_has_reflect_type<T, std::enable_if_t<std::is_same_v<typename T::reflect_type, reflection::reflect>>> :std::true_type {};

	template<typename T>
	struct is_has_reflect_type<T, std::enable_if_t<is_sequence_std_container_v<T>, std::void_t<typename T::value_type>>>
		: is_has_reflect_type<typename T::value_type> {};

	template<typename T>
	struct is_has_reflect_type<T, std::enable_if_t<is_associative_std_container_v<T>, std::void_t<typename T::mapped_type>>>
		: is_has_reflect_type<typename T::mapped_type> {};

	template<typename T>
	inline constexpr bool is_has_reflect_type_v = is_has_reflect_type<T>::value;


	template<typename T>
	static T from_json_detail(const nlohmann::json& json);

	template<typename Container>
	static Container to_std_container(const nlohmann::json& j) {
		Container c{};
		if constexpr (is_sequence_std_container_v<Container>) {
			using value_type = typename Container::value_type;
			auto size = j.size();
			if constexpr (is_std_vector_v<Container> || is_std_unordered_set_v<Container> || is_std_unordered_multiset_v<Container>) {
				c.reserve(size);
			}

			for (size_t i = 0; i < size; ++i) {
				if constexpr (is_std_vector_v<Container> || is_std_deque_v<Container> || is_std_list_v<Container>) {
					if constexpr (reflection::is_reflection_v<value_type>) {
						c.emplace_back(from_json_detail<value_type>(j[i]));
					}
					else if constexpr (is_std_container_v<value_type> && is_has_reflect_type_v<value_type>) {
						c.emplace_back(to_std_container<value_type>(j[i]));
					}
					else {
						c.emplace_back(j[i].get<value_type>());
					}
				}
				else if constexpr (is_std_forward_list_v<Container>) {
					if constexpr (reflection::is_reflection_v<value_type>) {
						c.emplace_front(from_json_detail<value_type>(j[i]));
					}
					else if constexpr (is_std_container_v<value_type> && is_has_reflect_type_v<value_type>) {
						c.emplace_front(to_std_container<value_type>(j[i]));
					}
					else {
						c.emplace_front(j[i].get<value_type>());
					}
				}
				else if constexpr (is_std_set_v<Container> || is_std_unordered_set_v<Container> ||
					is_std_multiset_v<Container> || is_std_unordered_multiset_v<Container>) {
					if constexpr (reflection::is_reflection_v<value_type>) {
						c.emplace(from_json_detail<value_type>(j[i]));
					}
					else if constexpr (is_std_container_v<value_type> && is_has_reflect_type_v<value_type>) {
						c.emplace(to_std_container<value_type>(j[i]));
					}
					else {
						c.emplace(j[i].get<value_type>());
					}
				}
				else if constexpr (is_std_array_v<Container>) {
					if constexpr (reflection::is_reflection_v<value_type>) {
						c.at(i) = from_json_detail<value_type>(j[i]);
					}
					else if constexpr (is_std_container_v<value_type> && is_has_reflect_type_v<value_type>) {
						c.at(i) = to_std_container<value_type>(j[i]);
					}
					else {
						c.at(i) = j[i].get<value_type>();
					}
				}
			}
		}
		else if constexpr (is_associative_std_container_v<Container>) {
			using key_type = typename Container::key_type;
			using mapped_type = typename Container::mapped_type;

			if constexpr (!std::is_same_v<key_type, std::string>) {
				static_assert(always_false_v<key_type>, "associative containers key type only can be std::string");
			}
			if constexpr (is_std_unordered_map_v<Container> || is_std_unordered_multimap_v<Container>) {
				c.reserve(j.size());
			}

			for (auto it = j.begin(); it != j.end(); it++) {
				if constexpr (reflection::is_reflection_v<mapped_type>) {
					c.emplace(it.key(), from_json_detail<mapped_type>(it.value()));
				}
				else if constexpr (is_std_container_v<mapped_type> && is_has_reflect_type_v<mapped_type>) {
					c.emplace(it.key(), to_std_container<mapped_type>(it.value()));
				}
				else {
					c.emplace(it.key(), it.value().get<mapped_type>());
				}
			}
		}
		return c;
	}

	template<typename T>
	static T from_json_detail(const nlohmann::json& json)
	{
		T t{};
		if constexpr (reflection::is_reflection_v<T>) {
			constexpr auto names = T::elements_name();
			constexpr auto address = T::elements_address();
			for_each_tuple([&json, &names, &address, &t](auto index) {
				auto element_name = std::string(names[index]);
				if (!json.contains(element_name)) {
					return;
				}

				auto& element = t.*std::get<index>(address);
				using type = std::remove_reference_t<decltype(element)>;
				auto& j = json[element_name];
				if constexpr (reflection::is_reflection_v<type>) {
					element = from_json_detail<type>(j);
				}
				else if constexpr (is_std_container_v<type> && is_has_reflect_type_v<type>) {
					element = to_std_container<type>(j);
				}
				else {
					element = j.get<type>();
				}
			}, std::make_index_sequence<T::args_size_t::value>());
		}
		else if constexpr (is_std_container_v<T> && is_has_reflect_type_v<T>) {
			t = to_std_container<T>(json);
		}
		else {
			t = json.get<T>();
		}
		return t;
	}

	template<typename T>
	static T from_json(const std::string& json_str) {
		auto j = nlohmann::json::parse(json_str);
		return from_json_detail<T>(j);
	}


	template<typename T>
	static nlohmann::json to_json_deatil(const T& t);

	template<typename Container>
	static nlohmann::json from_std_container(const Container& c) {
		nlohmann::json j;
		if constexpr (is_sequence_std_container_v<Container>) {
			using value_type = typename Container::value_type;
			for (auto iter = c.begin(); iter != c.end(); ++iter) {
				if constexpr (reflection::is_reflection_v<value_type>) {
					j.emplace_back(to_json_deatil<value_type>(*iter));
				}
				else if constexpr (is_std_container_v<value_type> && is_has_reflect_type_v<value_type>) {
					j.emplace_back(from_std_container(*iter));
				}
				else {
					j.emplace_back(nlohmann::json(*iter));
				}
			}
		}
		else if constexpr (is_associative_std_container_v<Container>) {
			using key_type = typename Container::key_type;
			using mapped_type = typename Container::mapped_type;

			if constexpr (!std::is_same_v<key_type, std::string>) {
				static_assert(always_false_v<key_type>, "associative containers key type only can be std::string");
			}

			for (auto iter = c.begin(); iter != c.end(); ++iter) {
				if constexpr (reflection::is_reflection_v<mapped_type>) {
					j.emplace(iter->first, to_json_deatil<mapped_type>(iter->second));
				}
				else if constexpr (is_std_container_v<mapped_type> && is_has_reflect_type_v<mapped_type>) {
					j.emplace(iter->first, from_std_container(iter->second));
				}
				else {
					j.emplace(iter->first, nlohmann::json(iter->second));
				}
			}
		}
		return j;
	}

	template<typename T>
	static nlohmann::json to_json_deatil(const T& t)
	{
		nlohmann::json j;
		if constexpr (reflection::is_reflection_v<T>) {
			constexpr auto names = T::elements_name();
			constexpr auto address = T::elements_address();
			for_each_tuple([&j, &names, &address, &t](auto index) {
				auto& element = t.*std::get<index>(address);
				using type = std::remove_reference_t<decltype(element)>;
				auto element_name = std::string(names[index]);

				if constexpr (reflection::is_reflection_v<type>) {
					j.emplace(element_name, to_json_deatil<type>(element));
				}
				else if constexpr (is_std_container_v<type> && is_has_reflect_type_v<type>) {
					j.emplace(element_name, from_std_container<type>(element));
				}
				else {
					j.emplace(element_name, element);
				}
			}, std::make_index_sequence<T::args_size_t::value>());
		}
		else if constexpr (is_std_container_v<T> && is_has_reflect_type_v<T>) {
			j = from_std_container<T>(t);
		}
		else {
			nlohmann::json j0(t);
			j = std::move(j0);
		}
		return j;
	}

	template<typename T>
	static std::string to_json(const T& t) {
		auto j = to_json_deatil<T>(t);
		return j.dump();
	}
}



