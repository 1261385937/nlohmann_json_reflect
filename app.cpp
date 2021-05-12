#include "json_reflect.hpp"

auto json_str = R"(
{
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": "null",
  "answer": {
    "everything": 42
  },
  "list": [7, 8, 9, 9 ],
  "object": {
    "currency": "USD",
    "value": 42.99
  },
  "map":{
    "key1": [{"currency": "USD","value" : 40.99},{"currency": "USD","value" : 41.99},{"currency": "USD","value" : 42.99}],
    "key2": [{"currency": "USD","value" : 43.99},{"currency": "USD","value" : 44.99},{"currency": "USD","value" : 45.99}]
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
	std::string currency;
	float value;
	REFLECT(obj, currency, value);
};

struct zzz {
	std::string zz;
	REFLECT(zzz, zz);
};

struct json_struct {
	std::string nothing;
	std::string name;
	bool happy;
	float pi;
	std::unordered_map <std::string, int> answer;
	std::vector<int> list;
	obj object;
	std::map<std::string, std::forward_list<obj>> map;
	std::unordered_map<std::string, std::map<std::string, zzz>> taowa;
	REFLECT(json_struct, nothing, name, happy, pi, answer, list, object, map, taowa);
};

auto json1 = R"({
    "MixedArray": [
        "one", 
        50, 
        false, 
        12.005
    ], 
    "People": [
        {
            "name": "qq849635649", 
            "age": 0, 
            "sex": true,
			"flow":3.156
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
	REFLECT(e1, name, age, sex, flow);
};
struct e2 {
	std::string name;
	int age;
	bool sex;
	REFLECT(e2, name, age, sex);
};
struct e3 {
	std::string name;
	int age;
	bool sex;
	std::string zzzz;
	REFLECT(e3, name, age, sex, zzzz);
};
struct sjson1 {
	std::tuple<std::string, int, bool, float> MixedArray;
	std::tuple<e1, e2, e3> People;
	REFLECT(sjson1, MixedArray, People);
};

int main() {
	auto sjson1_data = jreflect::from_json<sjson1>(json1);
	auto sjson1_str = jreflect::to_json(sjson1_data);

	auto sjson2_data = jreflect::from_json<std::tuple<std::string, int, bool, float>>(json2);
	auto sjson2_str = jreflect::to_json(sjson2_data);

	auto j_data = jreflect::from_json<json_struct>(json_str);
	auto j_str = jreflect::to_json(j_data);
	return 0;
}