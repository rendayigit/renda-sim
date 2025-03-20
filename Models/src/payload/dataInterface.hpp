#pragma once

#include <nlohmann/json.hpp>
#include <string>

struct DataStruct {
  int integer = 1;
  bool boolean = true;
  std::string string = "Default structure string";
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataStruct, integer, boolean, string);
};
