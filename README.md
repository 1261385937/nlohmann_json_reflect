# nlohmann_json_reflect
A reflect extension for https://github.com/nlohmann/json, written by c++17
</br>Support any complex data structure which is defined by user.

## Introduce
It is an extension for nlohmann/json. 
<br/>
<br/>Why write this? Because nlohmann/json reflect is not very powerful. It can not support complex nested data structure. 
<br/>For example: you can not use nlohmann/json reflect macro on the reflect structure nested by std container. Or you must implement the interface defined by nlohmann/json.
<br/>
<br/>Anyway, it is not convenient for reflecting json to data structure directly, also data structure to json.
<br/>Use this extension, you can nest very complex data structure. Std container nest Std container, then nest reflect struct , then nest std container, and so on, layer after layer.

## Note
Structure fields do not need to be forced a one-to-one correspondence with JSON field.
<br/>If you are not sure the field existed or not, std::optional is provided when reflecting

## Usage
intrusive reflect 
```c++
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

int main() {
    auto json1_data = jreflect::from_json<sjson1>(json1);
    auto json1_str = jreflect::to_json(json1_data);
    return 0;
}
```
<br>no intrusive reflect
```c++
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
    "key1": [{"currency": "USD","value" : 40.99},
             {"currency": "USD","value" : 41.99,"yes" : true},
             {"currency": "USD","value" : 42.99}],
    "key2": [{"currency": "USD","value" : 43.99},
             {"currency": "USD","value" : 44.99,"yes" : true},
             {"currency": "USD","value" : 45.99}]
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
    auto j_data = jreflect::from_json<json_struct>(json_str);
    auto j_str = jreflect::to_json(j_data);
    return 0;
}
```
## Any issue is welcome, have a joy
