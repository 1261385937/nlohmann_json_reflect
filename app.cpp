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

int main() {	
	auto j_data = jreflect::from_json<json_struct>(json_str);
	auto j_str = jreflect::to_json(j_data);
	return 0;
}