#include "json_reflect.hpp"

auto json1 = R"({
    "MixedArray": [
       "one", 
        50, 
        false, 
        12.005
    ], 
    "People": [
        { 
        }, 
        {
            "name": "qq849635649", 
            "age": 10, 
            "sex": false
        }, 
        {
            "name": "qq849635649", 
            "age": 20, 
            "sex": true,
			"zzzz": "11"
        }
    ]
})";
auto json2 = R"([
        "one", 
        50, 
        false, 
        12.005
    ])";

struct e1 {
    std::string name;
    int age;
    bool sex;
    float flow;
    //REFLECT_INTRUSIVE(e1, name, age, sex, flow);
};
REFLECT_NON_INTRUSIVE(e1, name, age, sex, flow);

struct e2 {
    std::string name;
    int age;
    bool sex;
    //REFLECT_INTRUSIVE(e2, name, age, sex);
};
REFLECT_NON_INTRUSIVE(e2, name, age, sex);

struct e3 {
    std::string name;
    int age;
    bool sex;
    std::string zzzz;
    //REFLECT_INTRUSIVE(e3, name, age, sex, zzzz);
};
REFLECT_NON_INTRUSIVE(e3, name, age, sex, zzzz);

struct sjson1 {
    std::tuple<std::string, int, bool, float> MixedArray;
    std::tuple<e1, e2, e3> People;
    //REFLECT_INTRUSIVE(sjson1, MixedArray, People);
};
REFLECT_NON_INTRUSIVE(sjson1, MixedArray, People);



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

int main() {

    try {
        auto j = nlohmann::json::parse(json_str);
        auto b = j["nothing"].is_object();
        std::string pi;
        j.at("xx").get_to(pi);
    }
    catch (std::exception& e) {
        auto err = e.what();
        int x = 4;
    }

  
    auto j_data = jreflect::from_json<json_struct>(json_str);
    auto j_str = jreflect::to_json(j_data);

    auto sjson1_data = jreflect::from_json<sjson1>(json1);
    auto sjson1_str = jreflect::to_json(sjson1_data);

    auto sjson2_data = jreflect::from_json<std::tuple<std::string, int, bool, float>>(json2);
    auto sjson2_str = jreflect::to_json(sjson2_data);
    return 0;
}
