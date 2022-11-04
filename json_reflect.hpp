#pragma once
#include "reflect_meta.hpp"
#include "json.hpp"

namespace jreflect {

template<typename T>
static T from_json_detail(const nlohmann::json& json);

template<typename Container>
static Container to_std_container(const nlohmann::json& j);

template<typename ValueType, typename Pred>
static void deal_to_detail(const nlohmann::json& j, Pred&& pred) {
    using type = std::remove_reference_t<ValueType>;
    if constexpr (reflection::is_reflection_v<type>) {
        j.is_null() ? pred(type{}) : pred(from_json_detail<type>(j));
    }
    else if constexpr (reflection::is_std_tuple_v<type> ||
        (reflection::is_std_container_v<type> && reflection::is_has_reflect_type_v<type>)) {
        j.is_null() ? pred(type{}) : pred(to_std_container<type>(j));
    }
    else if constexpr (reflection::is_std_optional_v<type>) {
        using real_type = typename type::value_type;
        j.is_null() ? pred(std::nullopt) : pred(from_json_detail<real_type>(j));
    }
    else {
        j.is_null() ? pred(type{}) : pred(j.get<type>());
    }
}

template<typename Container>
static Container to_std_container(const nlohmann::json& j) {
    Container c{};
    if constexpr (reflection::is_sequence_std_container_v<Container>) {
        using value_type = typename Container::value_type;
        auto size = j.size();
        if constexpr (reflection::is_std_vector_v<Container>
            || reflection::is_std_unordered_set_v<Container> || reflection::is_std_unordered_multiset_v<Container>) {
            c.reserve(size);
        }

        for (size_t i = 0; i < size; ++i) {
            if constexpr (reflection::is_std_vector_v<Container>
                || reflection::is_std_deque_v<Container> || reflection::is_std_list_v<Container>) {
                deal_to_detail<value_type>(j[i], [&c](auto&& value) {
                    c.emplace_back(std::move(value));
                });
            }
            else if constexpr (reflection::is_std_forward_list_v<Container>) {
                deal_to_detail<value_type>(j[i], [&c](auto&& value) {
                    c.emplace_front(std::move(value));
                });
            }
            else if constexpr (reflection::is_std_set_v<Container> || reflection::is_std_unordered_set_v<Container>
                || reflection::is_std_multiset_v<Container> || reflection::is_std_unordered_multiset_v<Container>) {
                deal_to_detail<value_type>(j[i], [&c](auto&& value) {
                    c.emplace(std::move(value));
                });
            }
            else if constexpr (reflection::is_std_array_v<Container>) {
                deal_to_detail<value_type>(j[i], [&c, &i](auto&& value) {
                    c.at(i) = std::move(value);
                });
            }
        }
    }
    else if constexpr (reflection::is_associative_std_container_v<Container>) {
        using key_type = typename Container::key_type;
        using mapped_type = typename Container::mapped_type;

        if constexpr (!std::is_same_v<key_type, std::string>) {
            static_assert(reflection::always_false_v<key_type>, "associative containers key type only can be std::string");
        }
        if constexpr (reflection::is_std_unordered_map_v<Container> || reflection::is_std_unordered_multimap_v<Container>) {
            c.reserve(j.size());
        }

        for (auto it = j.begin(); it != j.end(); it++) {
            deal_to_detail<mapped_type>(it.value(), [&c, key = it.key()](auto&& value) mutable {
                c.emplace(std::move(key), std::move(value));
            });
        }
    }
    else if constexpr (reflection::is_std_tuple_v<Container>) { //Mixed Array
        constexpr auto size = std::tuple_size_v<Container>;
        for_each_tuple([&j, &c](auto i) {
            auto& v = std::get<i>(c);
            using type = std::decay_t<decltype(v)>;
            deal_to_detail<type>(j[i], [&v](auto&& value) {
                v = std::move(value);
            });
        }, std::make_index_sequence<size>());
    }
    else {
        static_assert(reflection::always_false_v<Container>, "Container type is error");
    }
    return c;
}

template<typename ReflectType, typename T>
static void traversing_from_type(const nlohmann::json& j, T&& obj) {
    constexpr auto names = ReflectType::elements_name();
    constexpr auto address = ReflectType::elements_address();
    for_each_tuple([&j, &obj, &names, &address](auto index) {
        auto& element = obj.*std::get<index>(address);
        using element_type = std::remove_reference_t<decltype(element)>;
        auto element_name = std::string(names[index]);

        if (!j.contains(element_name)) {
            if constexpr (reflection::is_std_optional_v<element_type>) {
                return;
            }
            else {
                throw std::logic_error("key is not exist: " + element_name);
            }
        }

        auto& jj = j[element_name];
        if constexpr (reflection::is_std_optional_v<element_type>) {
            using real_type = typename element_type::value_type;
            if (jj.is_null()) {
                element = std::nullopt;
                return;
            }

            deal_to_detail<real_type>(jj, [&element](auto&& value) {
                element = std::move(value);
            });
        }
        else {
            deal_to_detail<element_type>(jj, [&element](auto&& value) {
                element = std::move(value);
            });
        }
    }, std::make_index_sequence<ReflectType::args_size_t::value>());
}

template<typename T>
static T from_json_detail(const nlohmann::json& j) {
    T t{};
    if constexpr (reflection::is_intrusive_reflection_v<T>) {
        traversing_from_type<T>(j, t);
    }
    else if constexpr (reflection::is_non_intrusive_reflection_v<T>) {
        using TT = decltype(reflection_reflect_member(std::declval<T>()));
        traversing_from_type<TT>(j, t);
    }
    else if constexpr (reflection::is_std_tuple_v<T>
        || (reflection::is_std_container_v<T> && reflection::is_has_reflect_type_v<T>)) {
        t = to_std_container<T>(j);
    }
    else if constexpr (reflection::is_std_optional_v<T>) {
        using type = typename T::value_type;
        t = j.is_null() ? std::nullopt : from_json_detail<type>(j);
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
static nlohmann::json to_json_detail(T&& t);

template<typename Container>
static nlohmann::json from_std_container(Container&& c);

template<typename Element, typename Pred>
static void deal_from_detail(Element&& element, Pred&& pred) {
    using element_type = std::remove_reference_t<Element>;

    if constexpr (reflection::is_reflection_v<element_type>) {
        pred(to_json_detail(std::forward<Element>(element)));
    }
    else if constexpr (reflection::is_std_tuple_v<element_type>
        || (reflection::is_std_container_v<element_type> && reflection::is_has_reflect_type_v<element_type>)) {
        pred(from_std_container(std::forward<Element>(element)));
    }
    else if constexpr (reflection::is_std_optional_v<element_type>) {
        element.has_value() ?
            pred(to_json_detail(element.value())) :
            pred(nlohmann::json{});
    }
    else {
        pred(std::forward<Element>(element));
    }
}

template<typename Container>
static nlohmann::json from_std_container(Container&& c) {
    using container_type = std::decay_t<Container>;
    nlohmann::json j;
    if constexpr (reflection::is_sequence_std_container_v<container_type>) {
        for (auto iter = c.begin(); iter != c.end(); ++iter) {
            deal_from_detail(*iter, [&j](auto&& obj) {
                j.emplace_back(std::forward<decltype(obj)>(obj));
            });
        }
    }
    else if constexpr (reflection::is_associative_std_container_v<container_type>) {
        using key_type = typename container_type::key_type;
        if constexpr (!std::is_same_v<key_type, std::string>) {
            static_assert(reflection::always_false_v<key_type>,
                "associative containers key type only can be std::string");
        }
        for (auto iter = c.begin(); iter != c.end(); ++iter) {
            deal_from_detail(iter->second, [&j, &iter](auto&& obj) {
                j.emplace(iter->first, std::forward<decltype(obj)>(obj));
            });
        }
    }
    else if constexpr (reflection::is_std_tuple_v<container_type>) { //Mixed Array
        constexpr auto size = std::tuple_size_v<container_type>;
        for_each_tuple([&j, &c](auto i) {
            auto& value = std::get<i>(c);
            deal_from_detail(value, [&j](auto&& obj) {
                j.emplace_back(std::forward<decltype(obj)>(obj));
            });
        }, std::make_index_sequence<size>());
    }
    else {
        static_assert(reflection::always_false_v<container_type>, "Container type is error");
    }
    return j;
}

template<typename ReflectType, typename T>
static void traversing_to_type(nlohmann::json& j, T&& obj) {
    constexpr auto names = ReflectType::elements_name();
    constexpr auto address = ReflectType::elements_address();
    for_each_tuple([&j, &obj, &names, &address](auto index) {
        auto& element = obj.*std::get<index>(address);
        using element_type = std::remove_reference_t<decltype(element)>;
        auto element_name = std::string(names[index]);

        if constexpr (reflection::is_std_optional_v<element_type>) {
            element.has_value() ?
                deal_from_detail(element.value(), [&j, &element_name](auto&& obj) {
                j.emplace(std::move(element_name), std::forward<decltype(obj)>(obj)); })
                :
                (void)j.emplace(std::move(element_name), nlohmann::json{});
        }
        else {
            deal_from_detail(element, [&j, &element_name](auto&& obj) {
                j.emplace(std::move(element_name), std::forward<decltype(obj)>(obj));
            });
        }
    }, std::make_index_sequence<ReflectType::args_size_t::value>());
}

template<typename T>
static nlohmann::json to_json_detail(T&& obj) {
    using type = std::remove_reference_t<T>;
    nlohmann::json j;
    if constexpr (reflection::is_intrusive_reflection_v<type>) {
        traversing_to_type<type>(j, std::forward<T>(obj));
    }
    else if constexpr (reflection::is_non_intrusive_reflection_v<type>) {
        using TT = decltype(reflection_reflect_member(std::declval<type>()));
        traversing_to_type<TT>(j, std::forward<T>(obj));
    }
    else if constexpr (reflection::is_std_tuple_v<type> ||
        (reflection::is_std_container_v<type> && reflection::is_has_reflect_type_v<type>)) {
        j = from_std_container(std::forward<T>(obj));
    }
    else if (reflection::is_std_optional_v<type>) {
        //for the total (part) json may be null
        j = obj.has_value() ?
            to_json_detail(obj.value()) : nlohmann::json{};
    }
    else {
        j = nlohmann::json{ std::forward<T>(obj) };
    }
    return j;
}

template<typename T>
static std::string to_json(T&& obj) {
    auto j = to_json_detail(std::forward<T>(obj));
    return j.dump();
}
}
