#pragma once
#include "json_reflect_meta.hpp"
#include "json.hpp"

namespace jreflect {

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
            else if constexpr (is_std_set_v<Container> || is_std_unordered_set_v<Container> || is_std_multiset_v<Container> || is_std_unordered_multiset_v<Container>) {
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
    else if constexpr (is_std_tuple_v<Container>) { //Mixed Array
        constexpr auto size = std::tuple_size_v<Container>;
        for_each_tuple([&j, &c](auto i) {
            auto& value = std::get<i>(c);
            using type = std::decay_t<decltype(value)>;
            if constexpr (reflection::is_reflection_v<type>) {
                value = from_json_detail<type>(j[i]);
            }
            else if constexpr ((is_std_container_v<type> && is_has_reflect_type_v<type>) || is_std_tuple_v<type>) {
                value = to_std_container<type>(j[i]);
            }
            else {
                if (j.size() > 0) {
                    value = j[i].get<type>();
                }
            }
        }, std::make_index_sequence<size>());
    }
    else {
        static_assert(always_false_v<Container>, "Container type is error");
    }
    return c;
}

template<typename T>
static T from_json_detail(const nlohmann::json& j) {
    auto deal_reflect = [](auto index, auto&&...args) {
        auto&& [json, names, address, t] = std::forward_as_tuple(std::forward<decltype(args)>(args)...);
        auto& element = t.*std::get<index>(address);
        using type = std::remove_reference_t<decltype(element)>;
        auto element_name = std::string(names[index]);
        if (!json.contains(element_name)) {
            return;
        }

        auto& j = json[element_name];
        if constexpr (is_std_optional_v<type>) {
            using real_type = typename type::value_type;  
            if constexpr (reflection::is_reflection_v<real_type>) {
                element = from_json_detail<real_type>(j);
            }
            else if constexpr ((is_std_container_v<real_type> && is_has_reflect_type_v<real_type>) || is_std_tuple_v<real_type>) {
                element = to_std_container<real_type>(j);
            }
            else {
                element = j.get<real_type>();
            }
        }
        else {
            if constexpr (reflection::is_reflection_v<type>) {
                element = from_json_detail<type>(j);
            }
            else if constexpr ((is_std_container_v<type> && is_has_reflect_type_v<type>) || is_std_tuple_v<type>) {
                element = to_std_container<type>(j);
            }
            else {
                element = j.get<type>();
            }
        }
    };

    T t{};
    if constexpr (reflection::is_intrusive_reflection_v<T>) {
        constexpr auto names = T::elements_name();
        constexpr auto address = T::elements_address();
        for_each_tuple([&j, &names, &address, &t, &deal_reflect](auto index) {
            deal_reflect(index, j, names, address, t);
        }, std::make_index_sequence<T::args_size_t::value>());
    }
    else if constexpr (reflection::is_non_intrusive_reflection_v<T>) {
        using TT = decltype(reflection_reflect_member(std::declval<T>()));
        constexpr auto names = TT::elements_name();
        constexpr auto address = TT::elements_address();
        for_each_tuple([&j, &names, &address, &t, &deal_reflect](auto index) {
            deal_reflect(index, j, names, address, t);
        }, std::make_index_sequence<TT::args_size_t::value>());
    }
    else if constexpr ((is_std_container_v<T> && is_has_reflect_type_v<T>) || is_std_tuple_v<T>) {
        t = to_std_container<T>(j);
    }
    else {
        t = j.get<T>();
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
    else if constexpr (is_std_tuple_v<Container>) { //Mixed Array
        constexpr auto size = std::tuple_size_v<Container>;
        for_each_tuple([&j, &c](auto i) {
            auto& value = std::get<i>(c);
            using type = std::decay_t<decltype(value)>;
            if constexpr (reflection::is_reflection_v<type>) {
                j.emplace_back(to_json_deatil<type>(value));
            }
            else if constexpr ((is_std_container_v<type> && is_has_reflect_type_v<type>) || is_std_tuple_v<type>) {
                j.emplace_back(from_std_container(value));
            }
            else {
                j.emplace_back(nlohmann::json(value));
            }
        }, std::make_index_sequence<size>());
    }
    else {
        static_assert(always_false_v<Container>, "Container type is error");
    }
    return j;
}

template<typename T>
static nlohmann::json to_json_deatil(const T& t) {
    constexpr auto deal_reflect = [](auto index, auto&&...args) {
        auto&& [j, names, address, t] = std::forward_as_tuple(std::forward<decltype(args)>(args)...);
        auto& element = t.*std::get<index>(address);
        using type = std::remove_reference_t<decltype(element)>;
        auto element_name = std::string(names[index]);

        if constexpr (is_std_optional_v<type>) {
            using real_type = typename type::value_type;
            if constexpr (reflection::is_reflection_v<real_type>) {
                if (element.has_value()) {
                    j.emplace(element_name, to_json_deatil<real_type>(element.value()));
                }
            }
            else if constexpr (is_std_container_v<real_type> && is_has_reflect_type_v<real_type> || is_std_tuple_v<real_type>) {
                if (element.has_value()) {
                    j.emplace(element_name, from_std_container<real_type>(element.value()));
                }
            }
            else {
                if (element.has_value()) {
                    j.emplace(element_name, element.value());
                }
            }
        }
        else {
            if constexpr (reflection::is_reflection_v<type>) {
                j.emplace(element_name, to_json_deatil<type>(element));
            }
            else if constexpr (is_std_container_v<type> && is_has_reflect_type_v<type> || is_std_tuple_v<type>) {
                j.emplace(element_name, from_std_container<type>(element));
            }
            else {
                j.emplace(element_name, element);
            }
        }
    };

    nlohmann::json j;
    if constexpr (reflection::is_intrusive_reflection_v<T>) {
        constexpr auto names = T::elements_name();
        constexpr auto address = T::elements_address();
        for_each_tuple([&j, &names, &address, &t, &deal_reflect](auto index) {
            deal_reflect(index, j, names, address, t);
        }, std::make_index_sequence<T::args_size_t::value>());
    }
    else if constexpr (reflection::is_non_intrusive_reflection_v<T>) {
        using TT = decltype(reflection_reflect_member(std::declval<T>()));
        constexpr auto names = TT::elements_name();
        constexpr auto address = TT::elements_address();
        for_each_tuple([&j, &names, &address, &t, &deal_reflect](auto index) {
            deal_reflect(index, j, names, address, t);
        }, std::make_index_sequence<TT::args_size_t::value>());
    }
    else if constexpr (is_std_container_v<T> && is_has_reflect_type_v<T> || is_std_tuple_v<T>) {
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
