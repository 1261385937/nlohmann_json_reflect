#include "json_reflect.hpp"

auto json1 = R"({
    "MixedArray": [
       "one", 
        50, 
        false, 
        12.005
    ], 
    "People": [
        null,
        {
            "name": "qwer", 
            "age": 1000, 
            "sex": true,
			"flow": 3.000
        }, 
        {
            "name": "qq849635649", 
            "age": 10, 
            "sex": null
        }, 
        {
            "name": null, 
            "age": 20, 
            "sex": true,
			"zzzz": "11"
        }
    ]
})";

struct e1 {
    std::optional<std::string> name;
    int age;
    bool sex;
    float flow;
    REFLECT_INTRUSIVE(e1, name, age, sex, flow);
};

struct e2 {
    std::string name;
    int age;
    std::optional<bool> sex;
    REFLECT_INTRUSIVE(e2, name, age, sex);
};

struct e3 {
    std::optional<std::string> name;
    int age;
    bool sex;
    std::string zzzz;
    REFLECT_INTRUSIVE(e3, name, age, sex, zzzz);
};

struct sjson1 {
    std::tuple<std::string, int, bool, float> MixedArray;
    std::tuple<std::optional<e2>, std::optional<e1>, e2, e3> People;
    REFLECT_INTRUSIVE(sjson1, MixedArray, People);
};



auto json_str = R"(
{
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
 
  "answer": {
    "everything": 42
  },
  "list": [7, 8, 9, 9 ],
  "object": {
    "currency": "USD",
    "value": 42.99
  },
  "map":{
    "key1": [{"currency": "USD","value" : 40.99},{"currency": "USD","value" : 41.99,"yes" : true},{"currency": "USD","value" : 42.99}],
    "key2": [{"currency": "USD","value" : 43.99},{"currency": "USD","value" : 44.99,"yes" : true},{"currency": "USD","value" : 45.99}]
  },
  "taowa":{
	"keyzz": {
		"wa":{
			"zz":"zz"
		}
	}
  }
})";

struct obj {
    std::optional<std::string> currency;
    float value;
};
REFLECT_NON_INTRUSIVE(obj, currency, value);

struct zzz {
    std::string zz;
};
REFLECT_NON_INTRUSIVE(zzz, zz);

struct obj1 {
    std::string currency;
    float value;
    bool yes;
};
REFLECT_NON_INTRUSIVE(obj1, currency, value, yes);

struct keymap {
    std::tuple<obj, obj1, obj> key1;
    std::tuple<obj, obj1, obj> key2;
};
REFLECT_NON_INTRUSIVE(keymap, key1, key2);

struct json_struct {
    std::optional<std::string> nothing;
    std::string name;
    bool happy;
    float pi;
    std::unordered_map <std::string, int> answer;
    std::vector<int> list;
    obj object;
    keymap map;
    std::unordered_map<std::string, std::map<std::string, zzz>> taowa;
};
REFLECT_NON_INTRUSIVE(json_struct, nothing, name, happy, pi, answer, list, object, map, taowa);

struct test_struct {
    std::optional<std::string> f;
    REFLECT_INTRUSIVE(test_struct, f);
};


int main() {
    auto json1_data = jreflect::from_json<sjson1>(json1);
    auto json1_str = jreflect::to_json(json1_data);

    auto j_data = jreflect::from_json<json_struct>(json_str);
    auto j_str = jreflect::to_json(j_data);

    test_struct ts{ "3445988958568569586565446e5yeyrtyru" };
    auto test_struct_str = jreflect::to_json(std::move(ts));
 
    return 0;
}
