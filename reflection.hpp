#pragma once
#ifndef MARCO_REFLECTION
#define MARCO_REFLECTION

#include <string_view>
#include <tuple>
#include <array>
#include <type_traits>

#define MARCO_EXPAND(...) __VA_ARGS__
/* vs2019 most support 125 args */
#define MAKE_ARG_LIST_1(operate, arg, ...)   operate(arg)
#define MAKE_ARG_LIST_2(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_1(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_3(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_2(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_4(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_3(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_5(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_4(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_6(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_5(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_7(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_6(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_8(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_7(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_9(operate, arg, ...)   operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_8(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_10(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_9(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_11(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_10(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_12(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_11(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_13(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_12(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_14(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_13(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_15(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_14(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_16(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_15(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_17(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_16(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_18(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_17(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_19(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_18(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_20(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_19(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_21(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_20(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_22(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_21(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_23(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_22(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_24(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_23(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_25(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_24(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_26(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_25(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_27(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_26(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_28(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_27(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_29(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_28(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_30(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_29(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_31(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_30(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_32(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_31(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_33(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_32(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_34(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_33(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_35(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_34(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_36(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_35(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_37(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_36(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_38(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_37(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_39(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_38(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_40(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_39(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_41(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_40(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_42(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_41(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_43(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_42(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_44(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_43(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_45(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_44(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_46(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_45(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_47(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_46(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_48(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_47(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_49(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_48(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_50(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_49(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_51(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_50(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_52(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_51(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_53(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_52(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_54(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_53(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_55(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_54(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_56(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_55(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_57(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_56(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_58(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_57(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_59(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_58(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_60(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_59(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_61(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_60(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_62(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_61(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_63(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_62(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_64(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_63(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_65(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_64(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_66(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_65(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_67(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_66(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_68(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_67(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_69(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_68(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_70(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_69(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_71(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_70(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_72(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_71(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_73(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_72(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_74(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_73(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_75(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_74(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_76(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_75(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_77(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_76(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_78(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_77(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_79(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_78(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_80(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_79(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_81(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_80(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_82(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_81(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_83(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_82(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_84(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_83(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_85(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_84(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_86(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_85(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_87(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_86(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_88(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_87(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_89(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_88(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_90(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_89(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_91(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_90(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_92(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_91(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_93(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_92(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_94(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_93(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_95(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_94(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_96(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_95(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_97(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_96(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_98(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_97(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_99(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_98(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_100(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_99(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_101(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_100(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_102(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_101(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_103(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_102(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_104(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_103(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_105(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_104(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_106(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_105(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_107(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_106(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_108(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_107(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_109(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_108(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_110(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_109(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_111(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_110(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_112(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_111(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_113(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_112(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_114(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_113(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_115(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_114(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_116(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_115(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_117(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_116(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_118(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_117(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_119(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_118(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_120(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_119(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_121(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_120(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_122(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_121(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_123(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_122(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_124(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_123(operate, __VA_ARGS__))
#define MAKE_ARG_LIST_125(operate, arg, ...)  operate(arg), MARCO_EXPAND(MAKE_ARG_LIST_124(operate, __VA_ARGS__))

//see https://groups.google.com/forum/#!topic/comp.std.c/d-6Mj5Lko_s
#define RSEQ_N() \
		 125,124,123,122,121,120,\
         119,118,117,116,115,114,113,112,111,110,\
         109,108,107,106,105,104,103,102,101,100,\
         99,98,97,96,95,94,93,92,91,90, \
         89,88,87,86,85,84,83,82,81,80, \
         79,78,77,76,75,74,73,72,71,70, \
         69,68,67,66,65,64,63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define ARG_N(\
         _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
         _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
         _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
         _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
         _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, \
         _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, \
		 _121, _122, _123, _124, _125, N, ...) N

#define MACRO_CONCAT_INTERNAL(A, B) A##_##B
#define MACRO_CONCAT(A, B) MACRO_CONCAT_INTERNAL(A, B)

#define MAKE_ARG_LIST(N, address, arg, ...) \
        MACRO_CONCAT(MAKE_ARG_LIST, N)(address, arg, __VA_ARGS__)

#define GET_ARG_COUNT_INNER(...)    MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...)          GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())

#define ELEMENT(e) e

namespace reflection {
    struct reflect {};

    template<typename T, typename = void>
    struct intrusive_reflection :std::false_type {};

    template<typename T>
    struct intrusive_reflection<T, std::enable_if_t<std::is_same_v<typename std::decay_t<T>::reflect_type, reflect>>> :std::true_type {};

    template<typename T>
    inline constexpr bool is_intrusive_reflection_v = intrusive_reflection<T>::value;

    template<typename T, typename = void>
    struct non_intrusive_reflection :std::false_type {};

    template<typename T>
    struct non_intrusive_reflection<T, std::enable_if_t<std::is_same_v<typename decltype(reflection_reflect_member(std::declval<T>()))::reflect_type, reflect>>> :std::true_type {};

    template<typename T>
    inline constexpr bool is_non_intrusive_reflection_v = non_intrusive_reflection<T>::value;

    template<typename T>
    inline constexpr bool is_reflection_v = is_intrusive_reflection_v<T> || is_non_intrusive_reflection_v<T>;


    static constexpr decltype(auto) trim_front_space(std::string_view src) {
        if (src.empty()) {
            return src;
        }
        while (src[0] == ' ') {
            src = src.substr(1);
        }
        return src;
    }

    template<size_t N>
    static constexpr decltype(auto) split(std::string_view s) {
        auto end = s.find_first_of(',');
        std::array<std::string_view, N> output;
        size_t i = 0;
        while (end != std::string_view::npos) {
            output[i++] = trim_front_space(s.substr(0, end));
            s = s.substr(end + 1);
            end = s.find_first_of(',');
        }
        output[i] = trim_front_space(s);
        return output;
    }
}

template<typename F, std::size_t ... Index>
static constexpr void for_each_tuple(F&& f, std::index_sequence<Index...>) {
    (std::forward<F>(f)(std::integral_constant<std::size_t, Index>()), ...);
}

template<typename F, size_t...I>
static constexpr void switch_tuple (size_t t, F&& f, std::index_sequence<I...>) {
    using func_type_array = void(*[sizeof...(I)])(F&&);
    constexpr func_type_array pfn = { [](auto&& f) { f(std::integral_constant<std::size_t, I>()); } ... };
    return pfn[t](std::forward<F>(f));
}

#define ADDRESS(...) \
    using args_size_t = std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>;\
	constexpr static decltype(auto) elements_address(){\
        return std::make_tuple(__VA_ARGS__);\
    }

#define ELEMENTS_ADDRESS(STRUCT_NAME, ARG_COUNT, ...) \
   ADDRESS(MAKE_ARG_LIST(ARG_COUNT, &STRUCT_NAME::ELEMENT, __VA_ARGS__))

#define REFLECT_INTRUSIVE(STRUCT_NAME, ...) \
	using reflect_type = reflection::reflect;\
    ELEMENTS_ADDRESS(STRUCT_NAME, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)\
	constexpr static decltype(auto) elements_name() { \
		return reflection::split<args_size_t::value>(#__VA_ARGS__); \
	}\


#define REFLECT_NON_INTRUSIVE(STRUCT_NAME, ...) \
    constexpr static decltype(auto) reflection_reflect_member(const STRUCT_NAME& ) {\
        struct reflection_member {\
            using reflect_type = reflection::reflect; \
            ELEMENTS_ADDRESS(STRUCT_NAME, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)\
            constexpr static decltype(auto) elements_name() { \
                return reflection::split<args_size_t::value>(#__VA_ARGS__); \
            }\
        };\
        return reflection_member{};\
    };

#endif // !MARCO_REFLECTION
